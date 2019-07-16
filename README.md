# Signature verification for embedded systems

Here is the signature verification code extracted from the Chrome OS
verified boot system "vboot".  This is small convenient source code for
adding RSA-based signature verification to an embedded system.  For example,
this code could be used to verify signed firmware update against an embedded
public key before allowing the update to proceed.

The RSA and SHA256 routines work well on small ARM microcontrollers.  For
example it's used in the embedded controller ("EC") found in Chromebooks:

[https://chromium.googlesource.com/chromiumos/platform/ec/+/refs/heads/master](https://chromium.googlesource.com/chromiumos/platform/ec/+/refs/heads/master)

(The EC is an interesting project all on its own.  It has a small
multi-tasking OS built-in).

# Instructions

First, get and build the Chrome OS vboot code for its "futility" utility and
compile it for Linux.  You can get it here:

[https://chromium.googlesource.com/chromiumos/platform/vboot/+/refs/heads/master](https://chromium.googlesource.com/chromiumos/platform/vboot/+/refs/heads/master)

Build it as follows:

	gunzip <vboot-master.tar.gz | tar -xf -
	cd _vboot_reference
	make
	cd ..

Next, build the signature verification code here, just type:

	make

Main.c is an example of how to use the code.  A signature and public key
are included in main.c.  In your case, you would put this code into your own
bootloader.  Verify the example signature like this:

	./verify test/data
	Signature matches!

Here is the procedure to sign your own data:

Create a private key "key.pem", don't share this:

	cd test
	openssl genrsa -F4 -out key.pem 2048

Create key pair from .pem in "vb21_struct.h" format:

	../_vboot_reference/build/futility/futility create key.pem

	this generates: key.vbprik2 and key.vbpubk2

Don't share key.vbprik2.  The public key "key.vbpubk2" needs to be included
with your code.

Sign some binary data:

	../_vboot_reference/build/futility/futility sign --type rwsig --prikey key.vbprik2 data sig

This generates the signature for "data" in a file "sig".  The signature
should be transported along with the "data".

You can verify the signature using the public key using like this:

	../_vboot_reference/build/futility/futility verify --type rwsig --pubkey key.vbpubk2 -f data sig

You can use xxd to convert "sig" and "key.vbpubk2" into a C literal for
inclusion into main.c:

	xxd --include sig
	xxd --include key.vbpubk2

Note that the vb21_struct.h signature format supports many Chrome-specific
file formats as well as more complex key handling.  Take a look at "futility
sign help".  Anyway, the "rwsig" type seems to be the simplest and would
cover many microcontroller use cases.
