SPEEDHELPERC=../test/print.c ../test/avr.c ../test/fail.c ../test/cpucycles.c
SPEEDHELPERH=../test/print.h ../test/avr.h ../test/fail.h ../test/cpucycles.c

speed: test/speed_crypto_scalarmult_curve25519.hex \
       test/speed_crypto_dh_curve25519.hex \
 			 test/speed_crypto_auth_hmacsha512256.hex \
 			 test/speed_crypto_onetimeauth_poly1305.hex \
 			 test/speed_crypto_stream_salsa20.hex \
 			 test/speed_crypto_stream_xsalsa20.hex \
 			 test/speed_crypto_core_salsa20.hex \
 			 test/speed_crypto_core_hsalsa20.hex \
 			 test/speed_crypto_hashblocks_sha512.hex \
 			 test/speed_crypto_hash_sha512.hex \
 			 test/speed_crypto_verify_16.hex \
 			 test/speed_crypto_verify_32.hex \
 			 test/speed_crypto_secretbox_xsalsa20poly1305.hex \
 			 test/speed_crypto_box_curve25519xsalsa20poly1305.hex \
 			 test/speed_crypto_sign_ed25519.hex

test/speed_crypto_stream_salsa20: ../test/speed_crypto_stream.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_stream.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=salsa20

test/speed_crypto_stream_xsalsa20: ../test/speed_crypto_stream.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_stream.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=xsalsa20

test/speed_crypto_core_salsa20: ../test/speed_crypto_core.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_core.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=salsa20

test/speed_crypto_core_hsalsa20: ../test/speed_crypto_core.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_core.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=hsalsa20

test/speed_crypto_verify_16: ../test/speed_crypto_verify.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_verify.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=16

test/speed_crypto_verify_32: ../test/speed_crypto_verify.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_verify.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=32

test/speed_crypto_scalarmult_curve25519: ../test/speed_crypto_scalarmult.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_scalarmult.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=curve25519

test/speed_crypto_dh_curve25519: ../test/speed_crypto_dh.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_dh.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=curve25519

test/speed_crypto_hashblocks_sha512: ../test/speed_crypto_hashblocks.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_hashblocks.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=sha512

test/speed_crypto_hash_sha512: ../test/speed_crypto_hash.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_hash.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=sha512

test/speed_crypto_auth_hmacsha512256: ../test/speed_crypto_auth.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_auth.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=hmacsha512256

test/speed_crypto_onetimeauth_poly1305: ../test/speed_crypto_onetimeauth.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_onetimeauth.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=poly1305

test/speed_crypto_secretbox_xsalsa20poly1305: ../test/speed_crypto_secretbox.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_secretbox.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=xsalsa20poly1305

test/speed_crypto_box_curve25519xsalsa20poly1305: ../test/speed_crypto_box.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_box.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=curve25519xsalsa20poly1305

test/speed_crypto_sign_ed25519: ../test/speed_crypto_sign.c $(SPEEDHELPERC) $(SPEEDHELPERH) obj/randombytes.o obj/libnacl.a
	mkdir -p test/
	$(CC) $(CFLAGS) ../test/speed_crypto_sign.c $(SPEEDHELPERC) obj/randombytes.o obj/libnacl.a -o $@ -DNRUNS=10 -DPRIMITIVE=ed25519

test/%.hex: test/%
	$(OBJCOPY) -O ihex -R .eeprom $^ $@

