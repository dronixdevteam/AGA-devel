#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
	BIGNUM *bn;
	RSA *rsa;
	char *chr;
	long num;
	struct netaddr *naddr;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	COLON	257
# define	HEX	258
# define	OBRACE	259
# define	EBRACE	260
# define	TAG_RSA	261
# define	TAG_PUB	262
# define	TAG_PSK	263
# define	MODULUS	264
# define	PUBLIC_EXPONENT	265
# define	PRIVATE_EXPONENT	266
# define	PRIME1	267
# define	PRIME2	268
# define	EXPONENT1	269
# define	EXPONENT2	270
# define	COEFFICIENT	271
# define	ADDR4	272
# define	ADDR6	273
# define	ADDRANY	274
# define	SLASH	275
# define	NUMBER	276
# define	BASE64	277


extern YYSTYPE prsalval;

#endif /* not BISON_Y_TAB_H */
