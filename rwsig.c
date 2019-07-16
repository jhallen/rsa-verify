/* Copyright (c) 2014 The Chromium OS Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

/*
 * Implementation of the RW firmware signature verification
 */

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "sha256.h"
#include "rsa.h"
#include "vb21_struct.h"
#include "rwsig.h"

static uint32_t rsa_workbuf[3 * RSANUMWORDS];

int rsa_check_signature(
	const uint8_t *rwdata, // Address of image
	unsigned int rwlen, // Length of image
	const struct rsa_public_key *key, // Key
	const uint8_t *sig // Signature of image
) {
	struct sha256_ctx ctx;
	uint8_t *hash;
	int good = 0;

//	printf("Verifying RW image...\n");

	/* SHA-256 Hash of the RW firmware */
//	printf("Compute SHA256 hash...\n");
	SHA256_init(&ctx);
	SHA256_update(&ctx, rwdata, rwlen);
	hash = SHA256_final(&ctx);

	//printf("RSA Verify...\n");
	good = rsa_verify(key, sig, hash, rsa_workbuf);
	if (!good)
		goto out;

out:
	//printf("RW verify %s\n", good ? "OK" : "FAILED");

	return good;
}

int vblock_check_signature(
	const uint8_t *rwdata,
	const struct vb21_packed_key *vb21_key,
	const struct vb21_signature *vb21_sig
) {
	const struct rsa_public_key *key; // Key
	const uint8_t *sig; // Signature of image
	unsigned int rwlen; // Length of image
	int good = 0;

	if (vb21_key->c.magic != VB21_MAGIC_PACKED_KEY ||
	    vb21_key->key_size != sizeof(struct rsa_public_key)) {
		printf("Invalid vblock key. %d vs. %lu\n", vb21_key->key_size, sizeof(struct rsa_public_key));
		goto out;
	}
	key = (const struct rsa_public_key *)
		((const uint8_t *)vb21_key + vb21_key->key_offset);

	if (vb21_sig->c.magic != VB21_MAGIC_SIGNATURE ||
	    vb21_sig->sig_size != RSANUMBYTES ||
	    vb21_key->sig_alg != vb21_sig->sig_alg ||
	    vb21_key->hash_alg != vb21_sig->hash_alg ||
	    /* Sanity check signature offset and data size. */
	    vb21_sig->sig_offset < sizeof(vb21_sig) /* ||
	    (vb21_sig->sig_offset + RSANUMBYTES) > CONFIG_RW_SIG_SIZE ||
	    vb21_sig->data_size > (CONFIG_RW_SIZE - CONFIG_RW_SIG_SIZE) */) {
		printf("Invalid vblock signature.");
		goto out;
	}

	sig = (const uint8_t *)vb21_sig + vb21_sig->sig_offset;
	rwlen = vb21_sig->data_size;

	good = rsa_check_signature(rwdata, rwlen, key, sig);

	out:
	return good;
}
