TESTHELPERC=../test/print.c ../test/avr.c ../test/fail.c
TESTHELPERH=../test/print.h ../test/avr.h ../test/fail.h

test: test/test_crypto_stream_salsa20.hex \
 			test/test_crypto_stream_xsalsa20.hex \
 			test/test_crypto_core_salsa20.hex \
 			test/test_crypto_core_hsalsa20.hex \
 			test/test_crypto_verify_16.hex \
 			test/test_crypto_verify_32.hex \
 			test/test_crypto_scalarmult_curve25519.hex \
 			test/test_crypto_dh_curve25519.hex \
 			test/test_crypto_hashblocks_sha512.hex \
 			test/test_crypto_hash_sha512.hex \
 			test/test_crypto_auth_hmacsha512256.hex \
 			test/test_crypto_onetimeauth_poly1305.hex \
 			test/test_crypto_secretbox_xsalsa20poly1305.hex \
 			test/test_crypto_box_curve25519xsalsa20poly1305.hex \
			test/test_crypto_sign_ed25519.hex


test/test_crypto_stream_salsa20: ../test/test_crypto_stream.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_stream.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=salsa20

test/test_crypto_stream_xsalsa20: ../test/test_crypto_stream.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_stream.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=xsalsa20

test/test_crypto_core_salsa20: ../test/test_crypto_core.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_core.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=salsa20

test/test_crypto_core_hsalsa20: ../test/test_crypto_core.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_core.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=hsalsa20

test/test_crypto_verify_16: ../test/test_crypto_verify.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_verify.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=16

test/test_crypto_verify_32: ../test/test_crypto_verify.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_verify.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=32

test/test_crypto_scalarmult_curve25519: ../test/test_crypto_scalarmult.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_scalarmult.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=curve25519

test/test_crypto_dh_curve25519: ../test/test_crypto_dh.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_dh.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=curve25519

test/test_crypto_hashblocks_sha512: ../test/test_crypto_hashblocks.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_hashblocks.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=sha512

test/test_crypto_hash_sha512: ../test/test_crypto_hash.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_hash.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=sha512

test/test_crypto_auth_hmacsha512256: ../test/test_crypto_auth.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_auth.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=hmacsha512256

test/test_crypto_onetimeauth_poly1305: ../test/test_crypto_onetimeauth.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_onetimeauth.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=poly1305

test/test_crypto_secretbox_xsalsa20poly1305: ../test/test_crypto_secretbox.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_secretbox.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=xsalsa20poly1305

test/test_crypto_box_curve25519xsalsa20poly1305: ../test/test_crypto_box.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_box.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=curve25519xsalsa20poly1305

test/test_crypto_sign_ed25519: ../test/test_crypto_sign.c $(TESTHELPERC) $(TESTHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/test_crypto_sign.c $(TESTHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=ed25519

test/%.hex: test/%
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

