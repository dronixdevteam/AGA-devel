#ifndef BISON_Y_TAB_H
# define BISON_Y_TAB_H

#ifndef YYSTYPE
typedef union {
	unsigned long num;
	vchar_t *val;
	struct remoteconf *rmconf;
	struct sockaddr *saddr;
	struct sainfoalg *alg;
} yystype;
# define YYSTYPE yystype
# define YYSTYPE_IS_TRIVIAL 1
#endif
# define	PATH	257
# define	PATHTYPE	258
# define	INCLUDE	259
# define	IDENTIFIER	260
# define	VENDORID	261
# define	LOGGING	262
# define	LOGLEV	263
# define	PADDING	264
# define	PAD_RANDOMIZE	265
# define	PAD_RANDOMIZELEN	266
# define	PAD_MAXLEN	267
# define	PAD_STRICT	268
# define	PAD_EXCLTAIL	269
# define	LISTEN	270
# define	X_ISAKMP	271
# define	X_ISAKMP_NATT	272
# define	X_ADMIN	273
# define	STRICT_ADDRESS	274
# define	ADMINSOCK	275
# define	DISABLED	276
# define	MODECFG	277
# define	CFG_NET4	278
# define	CFG_MASK4	279
# define	CFG_DNS4	280
# define	CFG_NBNS4	281
# define	CFG_AUTH_SOURCE	282
# define	CFG_SYSTEM	283
# define	CFG_RADIUS	284
# define	CFG_LOCAL	285
# define	CFG_NONE	286
# define	CFG_ACCOUNTING	287
# define	CFG_CONF_SOURCE	288
# define	CFG_MOTD	289
# define	CFG_POOL_SIZE	290
# define	CFG_AUTH_THROTTLE	291
# define	RETRY	292
# define	RETRY_COUNTER	293
# define	RETRY_INTERVAL	294
# define	RETRY_PERSEND	295
# define	RETRY_PHASE1	296
# define	RETRY_PHASE2	297
# define	NATT_KA	298
# define	ALGORITHM_CLASS	299
# define	ALGORITHMTYPE	300
# define	STRENGTHTYPE	301
# define	SAINFO	302
# define	FROM	303
# define	REMOTE	304
# define	ANONYMOUS	305
# define	INHERIT	306
# define	EXCHANGE_MODE	307
# define	EXCHANGETYPE	308
# define	DOI	309
# define	DOITYPE	310
# define	SITUATION	311
# define	SITUATIONTYPE	312
# define	CERTIFICATE_TYPE	313
# define	CERTTYPE	314
# define	PEERS_CERTFILE	315
# define	CA_TYPE	316
# define	VERIFY_CERT	317
# define	SEND_CERT	318
# define	SEND_CR	319
# define	IDENTIFIERTYPE	320
# define	MY_IDENTIFIER	321
# define	PEERS_IDENTIFIER	322
# define	VERIFY_IDENTIFIER	323
# define	DNSSEC	324
# define	CERT_X509	325
# define	CERT_PLAINRSA	326
# define	NONCE_SIZE	327
# define	DH_GROUP	328
# define	KEEPALIVE	329
# define	PASSIVE	330
# define	INITIAL_CONTACT	331
# define	NAT_TRAVERSAL	332
# define	NAT_TRAVERSAL_LEVEL	333
# define	PROPOSAL_CHECK	334
# define	PROPOSAL_CHECK_LEVEL	335
# define	GENERATE_POLICY	336
# define	SUPPORT_PROXY	337
# define	PROPOSAL	338
# define	EXEC_PATH	339
# define	EXEC_COMMAND	340
# define	EXEC_SUCCESS	341
# define	EXEC_FAILURE	342
# define	GSSAPI_ID	343
# define	COMPLEX_BUNDLE	344
# define	DPD	345
# define	DPD_DELAY	346
# define	DPD_RETRY	347
# define	DPD_MAXFAIL	348
# define	XAUTH_LOGIN	349
# define	PREFIX	350
# define	PORT	351
# define	PORTANY	352
# define	UL_PROTO	353
# define	ANY	354
# define	IKE_FRAG	355
# define	MODE_CFG	356
# define	PFS_GROUP	357
# define	LIFETIME	358
# define	LIFETYPE_TIME	359
# define	LIFETYPE_BYTE	360
# define	STRENGTH	361
# define	SCRIPT	362
# define	PHASE1_UP	363
# define	PHASE1_DOWN	364
# define	NUMBER	365
# define	SWITCH	366
# define	BOOLEAN	367
# define	HEXSTRING	368
# define	QUOTEDSTRING	369
# define	ADDRSTRING	370
# define	UNITTYPE_BYTE	371
# define	UNITTYPE_KBYTES	372
# define	UNITTYPE_MBYTES	373
# define	UNITTYPE_TBYTES	374
# define	UNITTYPE_SEC	375
# define	UNITTYPE_MIN	376
# define	UNITTYPE_HOUR	377
# define	EOS	378
# define	BOC	379
# define	EOC	380
# define	COMMA	381


extern YYSTYPE yylval;

#endif /* not BISON_Y_TAB_H */
