
all: fast \
		 small \
		 8bitc

.PHONY: small fast clean 

small: 
	cd avrnacl_small && $(MAKE)

fast: 
	cd avrnacl_fast && $(MAKE)

8bitc: 
	cd avrnacl_8bitc && $(MAKE)



clean:
	-cd avrnacl_small && $(MAKE) clean
	-cd avrnacl_fast && $(MAKE) clean
	-cd avrnacl_8bitc && $(MAKE) clean
