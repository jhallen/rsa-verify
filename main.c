#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rsa.h"
#include "vb21_struct.h"
#include "rwsig.h"

/* Signature */

unsigned char signature[] = {
  0x56, 0x62, 0x32, 0x53, 0x03, 0x00, 0x00, 0x00, 0x38, 0x01, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
  0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x03, 0x00, 0x02, 0x00,
  0xe7, 0x58, 0xc1, 0x9c, 0x5b, 0x07, 0xee, 0x59, 0x28, 0xfa, 0x63, 0xb7,
  0xaf, 0x9d, 0x17, 0x3f, 0x1c, 0xdd, 0x93, 0x52, 0x38, 0x16, 0xbf, 0xc0,
  0xed, 0xd9, 0xaa, 0x66, 0x9b, 0x1e, 0xc0, 0x89, 0x2d, 0xe0, 0xa9, 0x95,
  0x3e, 0x46, 0x4a, 0x94, 0x20, 0x3e, 0x66, 0x6f, 0xa6, 0x06, 0xb2, 0x3d,
  0x75, 0xdd, 0x69, 0x62, 0xe3, 0xfd, 0x6e, 0x6b, 0xbe, 0x69, 0x08, 0x49,
  0x29, 0x1a, 0x67, 0x05, 0x10, 0x59, 0x67, 0xcc, 0xd6, 0xde, 0x6b, 0x70,
  0xcc, 0x12, 0x6f, 0x9e, 0x3e, 0xa7, 0x1d, 0xa3, 0x2f, 0xa9, 0xb0, 0xd5,
  0x77, 0xc3, 0xbd, 0xe9, 0x88, 0x02, 0xa8, 0xec, 0x08, 0xb6, 0x3b, 0x8a,
  0xe1, 0x1a, 0xeb, 0x08, 0x64, 0x6b, 0xad, 0xeb, 0x93, 0x33, 0xe9, 0x68,
  0x89, 0x24, 0xaa, 0xc5, 0xed, 0xc4, 0xca, 0x48, 0xb8, 0x2d, 0xc7, 0x04,
  0x3d, 0x4f, 0x81, 0x6d, 0xda, 0x4d, 0x90, 0xa4, 0xea, 0x96, 0x60, 0x84,
  0x68, 0xe4, 0xc5, 0x5a, 0xe5, 0x67, 0x40, 0xd0, 0xb3, 0x4a, 0xfe, 0x25,
  0xf4, 0x96, 0xe4, 0x9b, 0xf8, 0x09, 0x07, 0x6c, 0x67, 0xe5, 0xcd, 0xd0,
  0xb9, 0x7c, 0x01, 0xf5, 0x9b, 0xbf, 0x28, 0x40, 0x34, 0xe6, 0xe7, 0x44,
  0x0c, 0x7f, 0xf8, 0x7a, 0xa5, 0xd1, 0x3f, 0x72, 0x07, 0x96, 0xec, 0x5b,
  0xe4, 0x42, 0x5b, 0x92, 0x6f, 0x6a, 0x5d, 0xa5, 0x04, 0x27, 0xb1, 0x51,
  0xc7, 0x6c, 0xd7, 0x46, 0xe5, 0x20, 0x3b, 0xa5, 0xcb, 0x25, 0xee, 0x80,
  0xfc, 0xfd, 0x1c, 0x44, 0x94, 0xff, 0x28, 0x3f, 0x10, 0xee, 0x9d, 0x8f,
  0x0d, 0xde, 0x19, 0x05, 0xf8, 0x4e, 0x4b, 0x04, 0x3b, 0x63, 0xec, 0xca,
  0x44, 0x74, 0x34, 0x48, 0x56, 0x15, 0xa3, 0xb0, 0xb2, 0x12, 0x78, 0x0d,
  0x64, 0xf3, 0x03, 0x74, 0x87, 0x75, 0x61, 0xf7, 0x62, 0x65, 0xf1, 0xab,
  0xb5, 0xf0, 0x76, 0x0a, 0x90, 0xc5, 0x47, 0x08, 0xd1, 0x86, 0xf8, 0x83,
  0xd1, 0x98, 0xce, 0x82, 0x88, 0xbb, 0x3c, 0x6e, 0x5d, 0xbc, 0xdc, 0x0b
};

/* Public key */

unsigned char key_vbpubk2[] = {
  0x56, 0x62, 0x32, 0x50, 0x03, 0x00, 0x00, 0x00, 0x40, 0x02, 0x00, 0x00,
  0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x00, 0x00, 0x00,
  0x08, 0x02, 0x00, 0x00, 0x03, 0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
  0xe7, 0x58, 0xc1, 0x9c, 0x5b, 0x07, 0xee, 0x59, 0x28, 0xfa, 0x63, 0xb7,
  0xaf, 0x9d, 0x17, 0x3f, 0x1c, 0xdd, 0x93, 0x52, 0x40, 0x00, 0x00, 0x00,
  0x05, 0x70, 0xe3, 0x8a, 0x33, 0x23, 0xe0, 0xd8, 0xf2, 0x6e, 0x7f, 0x02,
  0x81, 0x5a, 0xaf, 0x5b, 0xac, 0xa8, 0x65, 0xda, 0x98, 0x92, 0x69, 0x3e,
  0xa2, 0xe5, 0x50, 0x38, 0xd7, 0xd6, 0xff, 0xc5, 0xc4, 0xc3, 0x94, 0xec,
  0x23, 0x87, 0x71, 0xa1, 0x69, 0x72, 0xf7, 0xd1, 0x6d, 0xbc, 0x62, 0xbd,
  0x04, 0x2a, 0xa8, 0x37, 0xde, 0xe1, 0x7e, 0x87, 0xf1, 0x5b, 0xc7, 0x34,
  0x65, 0xcb, 0xad, 0xf5, 0x5a, 0x3c, 0x9a, 0xce, 0xe1, 0xab, 0xbc, 0x15,
  0x48, 0xbc, 0xa3, 0x2e, 0x5f, 0x14, 0xa2, 0xb8, 0xb8, 0xfb, 0x89, 0x8a,
  0xf3, 0x54, 0xe4, 0x5b, 0xeb, 0x6a, 0xfc, 0x92, 0x10, 0xe8, 0x20, 0x72,
  0xeb, 0xf1, 0x99, 0x32, 0x74, 0x1d, 0x22, 0x63, 0x11, 0x18, 0x83, 0x25,
  0xab, 0x0b, 0xd5, 0x47, 0x94, 0x80, 0xb9, 0x71, 0x78, 0x84, 0x0c, 0x15,
  0xae, 0x4b, 0x73, 0x6d, 0x89, 0x34, 0xbd, 0x8f, 0x44, 0x09, 0xbb, 0x11,
  0x56, 0x08, 0x1d, 0xa7, 0x95, 0x48, 0xf2, 0xb4, 0x3d, 0x01, 0x45, 0x06,
  0x3d, 0xf4, 0xa2, 0xad, 0x33, 0x8a, 0x1d, 0xfa, 0xd5, 0xa0, 0xb2, 0xe3,
  0x93, 0x2c, 0xec, 0xc0, 0x79, 0x3d, 0x0c, 0xe7, 0x16, 0x31, 0xaf, 0xa2,
  0xed, 0x51, 0x74, 0xe1, 0xc6, 0x29, 0xae, 0x98, 0x28, 0xcf, 0x59, 0xb6,
  0xa4, 0xc8, 0x63, 0xe4, 0x14, 0x70, 0x6d, 0x11, 0x4d, 0xd4, 0x5f, 0xc6,
  0x5e, 0x04, 0xfa, 0xf3, 0xef, 0xb3, 0xd2, 0x4c, 0x2d, 0x9d, 0x83, 0xe8,
  0xbe, 0x4f, 0x3a, 0x9f, 0x3f, 0x0d, 0x5e, 0xd6, 0x01, 0xa4, 0x26, 0xf9,
  0x18, 0xeb, 0xe1, 0x83, 0xca, 0x19, 0xb2, 0xc9, 0x17, 0x41, 0xde, 0x4c,
  0x86, 0x5a, 0xc5, 0x03, 0xf3, 0xf5, 0x61, 0xe6, 0xc2, 0x6e, 0x5e, 0xe3,
  0x34, 0xc5, 0x1f, 0xfa, 0x2f, 0x45, 0xe1, 0x92, 0x06, 0x52, 0x46, 0xd5,
  0xf7, 0x0d, 0x91, 0xe1, 0xa0, 0xcc, 0xa6, 0xfa, 0x2a, 0x52, 0x40, 0x6b,
  0xbd, 0xe3, 0xe3, 0x07, 0x06, 0xa8, 0xce, 0x8b, 0x07, 0xc6, 0x66, 0xf8,
  0x73, 0x83, 0x2f, 0x23, 0x7b, 0x65, 0x17, 0x83, 0x97, 0xa2, 0xd2, 0xc6,
  0x3e, 0x9f, 0x33, 0xd4, 0x59, 0x98, 0x88, 0x7a, 0x9b, 0xf1, 0x09, 0x37,
  0xec, 0x31, 0x35, 0x7e, 0x26, 0x3f, 0x38, 0x8f, 0x5e, 0x81, 0x29, 0x5d,
  0xc2, 0x00, 0xfc, 0x37, 0xeb, 0xbf, 0x05, 0x19, 0xc4, 0x9e, 0x19, 0x44,
  0x37, 0xc5, 0xa5, 0x7b, 0x81, 0x1b, 0xde, 0x93, 0xff, 0x90, 0x08, 0x68,
  0xe5, 0xca, 0xb6, 0xbd, 0xa2, 0xe5, 0x9e, 0xd9, 0x2c, 0x9c, 0xe9, 0x22,
  0xa7, 0xc0, 0x48, 0x3f, 0x9e, 0x12, 0xce, 0x8f, 0x6c, 0x55, 0xd2, 0xc5,
  0x71, 0x6c, 0x63, 0xb1, 0x91, 0xcb, 0xee, 0x50, 0x20, 0x59, 0x61, 0xda,
  0xc3, 0xab, 0x29, 0xa4, 0x66, 0xdc, 0x0f, 0x03, 0x3d, 0x2c, 0x15, 0x7b,
  0x6c, 0x8f, 0x15, 0x16, 0x50, 0x70, 0x74, 0x26, 0xf6, 0x1a, 0x0d, 0xb0,
  0xf9, 0x42, 0xa3, 0x30, 0xd9, 0x84, 0xe3, 0x9c, 0xa7, 0x89, 0x48, 0xe8,
  0x10, 0xd5, 0xd6, 0x32, 0xca, 0xac, 0x78, 0x29, 0x10, 0x14, 0x31, 0x13,
  0x42, 0x82, 0xe0, 0xcc, 0x36, 0x0b, 0x9d, 0x58, 0x43, 0xbb, 0x36, 0xa2,
  0xbd, 0x76, 0x88, 0x6b, 0x17, 0xe5, 0xbf, 0xf3, 0x02, 0xe1, 0x44, 0x0a,
  0xd1, 0x2b, 0xb5, 0xb0, 0xc5, 0xef, 0xd3, 0x4a, 0xc1, 0xb3, 0xb3, 0x1a,
  0x06, 0xee, 0x48, 0x8c, 0x20, 0x34, 0xfe, 0xfa, 0x6b, 0x18, 0x56, 0x89,
  0x90, 0xdd, 0x08, 0x5d, 0xe1, 0xb2, 0x23, 0x9a, 0x06, 0x06, 0x9f, 0x22,
  0xdd, 0xae, 0x14, 0x4f, 0x17, 0x64, 0x8e, 0x9a, 0x0d, 0x1b, 0xe5, 0x1a,
  0x1e, 0x30, 0xfd, 0xb7, 0x7c, 0x1a, 0x2f, 0x45, 0xb0, 0x33, 0xe5, 0x43,
  0x9f, 0x8a, 0x62, 0xf5, 0xe0, 0x20, 0xa9, 0x75, 0x4c, 0x21, 0x8a, 0x66
};

int main(int argc, char *argv[])
{
    uint8_t *rwdata;
    long rwlen;
    int status;

    // Image
    FILE *f = fopen(argv[1], "r");
    fseek(f, 0, SEEK_END);
    rwlen = ftell(f);
    rewind(f);

    rwdata = (uint8_t *)malloc(rwlen);
    if (1 != fread(rwdata, rwlen, 1, f)) {
        printf("Couldn't load %s\n", argv[1]);
        return -1;
    }
    fclose(f);

    status = vblock_check_signature(rwdata, (const struct vb21_packed_key *)key_vbpubk2, (const struct vb21_signature *)signature);
    if (status)
      printf("Signature matches!\n");
    else
      printf("Signature does not match :-(\n");
    return status;
}
