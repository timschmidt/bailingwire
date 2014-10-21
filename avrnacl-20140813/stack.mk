STACKHELPERC=../test/print.c ../test/avr.c
STACKHELPERH=../test/print.h ../test/avr.h

stack: test/stack_crypto_scalarmult_curve25519.hex \
 			 test/stack_crypto_auth_hmacsha512256.hex \
 			 test/stack_crypto_onetimeauth_poly1305.hex \
 			 test/stack_crypto_box_curve25519xsalsa20poly1305.hex \
 			 test/stack_crypto_secretbox_xsalsa20poly1305.hex \
 			 test/stack_crypto_core_salsa20.hex \
 			 test/stack_crypto_core_hsalsa20.hex \
 			 test/stack_crypto_dh_curve25519.hex \
 			 test/stack_crypto_hashblocks_sha512.hex \
 			 test/stack_crypto_hash_sha512.hex \
 			 test/stack_crypto_stream_salsa20.hex \
 			 test/stack_crypto_stream_xsalsa20.hex \
 			 test/stack_crypto_sign_ed25519.hex \
 			 test/stack_crypto_verify_16.hex \
 			 test/stack_crypto_verify_32.hex

test/stack_crypto_stream_salsa20: ../test/stack_crypto_stream.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_stream.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=salsa20

test/stack_crypto_stream_xsalsa20: ../test/stack_crypto_stream.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_stream.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=xsalsa20

test/stack_crypto_core_salsa20: ../test/stack_crypto_core.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_core.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=salsa20

test/stack_crypto_core_hsalsa20: ../test/stack_crypto_core.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_core.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=hsalsa20

test/stack_crypto_verify_16: ../test/stack_crypto_verify.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_verify.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=16

test/stack_crypto_verify_32: ../test/stack_crypto_verify.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_verify.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=32

test/stack_crypto_scalarmult_curve25519: ../test/stack_crypto_scalarmult.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_scalarmult.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=curve25519

test/stack_crypto_dh_curve25519: ../test/stack_crypto_dh.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_dh.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=curve25519

test/stack_crypto_hashblocks_sha512: ../test/stack_crypto_hashblocks.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_hashblocks.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=sha512

test/stack_crypto_hash_sha512: ../test/stack_crypto_hash.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_hash.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=sha512

test/stack_crypto_auth_hmacsha512256: ../test/stack_crypto_auth.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_auth.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=hmacsha512256

test/stack_crypto_onetimeauth_poly1305: ../test/stack_crypto_onetimeauth.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_onetimeauth.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=poly1305

test/stack_crypto_secretbox_xsalsa20poly1305: ../test/stack_crypto_secretbox.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_secretbox.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=xsalsa20poly1305

test/stack_crypto_box_curve25519xsalsa20poly1305: ../test/stack_crypto_box.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_box.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=curve25519xsalsa20poly1305

test/stack_crypto_sign_ed25519: ../test/stack_crypto_sign.c $(STACKHELPERC) $(STACKHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/stack_crypto_sign.c $(STACKHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DPRIMITIVE=ed25519

test/%.hex: test/%
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

