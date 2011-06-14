/* A Bison parser, made from ./cfparse.y
   by GNU bison 1.35.  */

#define YYBISON 1  /* Identify Bison output.  */

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

#line 3 "./cfparse.y"

/*
 * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002 and 2003 WIDE Project.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE PROJECT AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE PROJECT OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include "config.h"

#include <sys/types.h>
#include <sys/param.h>
#include <sys/queue.h>
#include <sys/socket.h>

#include <netinet/in.h>
#ifdef HAVE_NETINET6_IPSEC
#  include <netinet6/ipsec.h>
#else
#  include <netinet/ipsec.h>
#endif

#ifdef ENABLE_HYBRID
#include <arpa/inet.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <pwd.h>
#include <grp.h>

#include "var.h"
#include "misc.h"
#include "vmbuf.h"
#include "plog.h"
#include "sockmisc.h"
#include "str2val.h"
#include "genlist.h"
#include "debug.h"
#ifdef ENABLE_ADMINPORT
#include "admin.h"
#endif

#include "cfparse_proto.h"
#include "cftoken_proto.h"
#include "algorithm.h"
#include "localconf.h"
#include "policy.h"
#include "sainfo.h"
#include "oakley.h"
#include "pfkey.h"
#include "remoteconf.h"
#include "grabmyaddr.h"
#include "isakmp_var.h"
#include "handler.h"
#include "isakmp.h"
#ifdef ENABLE_HYBRID
#include "isakmp_xauth.h"
#include "isakmp_cfg.h"
#endif
#include "ipsec_doi.h"
#include "strnames.h"
#include "gcmalloc.h"
#ifdef HAVE_GSSAPI
#include "gssapi.h"
#endif
#include "vendorid.h"
#include "rsalist.h"

struct proposalspec {
	time_t lifetime;		/* for isakmp/ipsec */
	int lifebyte;			/* for isakmp/ipsec */
	struct secprotospec *spspec;	/* the head is always current spec. */
	struct proposalspec *next;	/* the tail is the most prefered. */
	struct proposalspec *prev;
};

struct secprotospec {
	int prop_no;
	int trns_no;
	int strength;		/* for isakmp/ipsec */
	int encklen;		/* for isakmp/ipsec */
	time_t lifetime;	/* for isakmp */
	int lifebyte;		/* for isakmp */
	int proto_id;		/* for ipsec (isakmp?) */
	int ipsec_level;	/* for ipsec */
	int encmode;		/* for ipsec */
	int vendorid;		/* for isakmp */
	char *gssid;
	struct sockaddr *remote;
	int algclass[MAXALGCLASS];

	struct secprotospec *next;	/* the tail is the most prefiered. */
	struct secprotospec *prev;
	struct proposalspec *back;
};

static int num2dhgroup[] = {
	0,
	OAKLEY_ATTR_GRP_DESC_MODP768,
	OAKLEY_ATTR_GRP_DESC_MODP1024,
	OAKLEY_ATTR_GRP_DESC_EC2N155,
	OAKLEY_ATTR_GRP_DESC_EC2N185,
	OAKLEY_ATTR_GRP_DESC_MODP1536,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	OAKLEY_ATTR_GRP_DESC_MODP2048,
	OAKLEY_ATTR_GRP_DESC_MODP3072,
	OAKLEY_ATTR_GRP_DESC_MODP4096,
	OAKLEY_ATTR_GRP_DESC_MODP6144,
	OAKLEY_ATTR_GRP_DESC_MODP8192
};

static struct remoteconf *cur_rmconf;
static int tmpalgtype[MAXALGCLASS];
static struct sainfo *cur_sainfo;
static int cur_algclass;

static struct proposalspec *newprspec __P((void));
static void insprspec __P((struct proposalspec *, struct proposalspec **));
static struct secprotospec *newspspec __P((void));
static void insspspec __P((struct secprotospec *, struct proposalspec **));
static void adminsock_conf __P((vchar_t *, vchar_t *, vchar_t *, int));

static int set_isakmp_proposal
	__P((struct remoteconf *, struct proposalspec *));
static void clean_tmpalgtype __P((void));
static int expand_isakmpspec __P((int, int, int *,
	int, int, time_t, int, int, int, char *, struct remoteconf *));
static int listen_addr __P((struct sockaddr *addr, int udp_encap));

void freeetypes (struct etypes **etypes);

#if 0
static int fix_lifebyte __P((u_long));
#endif

#line 172 "./cfparse.y"
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
#ifndef YYDEBUG
# define YYDEBUG 0
#endif



#define	YYFINAL		463
#define	YYFLAG		-32768
#define	YYNTBASE	128

/* YYTRANSLATE(YYLEX) -- Bison token number corresponding to YYLEX. */
#define YYTRANSLATE(x) ((unsigned)(x) <= 381 ? yytranslate[x] : 265)

/* YYTRANSLATE[YYLEX] -- Bison token number corresponding to YYLEX. */
static const short yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    95,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   109,   110,   111,   112,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,   127
};

#if YYDEBUG
static const short yyprhs[] =
{
       0,     0,     1,     4,     6,     8,    10,    12,    14,    16,
      18,    20,    22,    24,    26,    27,    33,    34,    39,    43,
      46,    47,    52,    53,    58,    62,    64,    66,    71,    72,
      75,    76,    81,    82,    87,    88,    93,    94,    99,   100,
     105,   110,   111,   114,   115,   120,   121,   126,   127,   132,
     133,   141,   142,   147,   148,   153,   154,   158,   161,   162,
     164,   169,   170,   173,   174,   179,   180,   185,   186,   191,
     192,   197,   198,   203,   204,   209,   210,   215,   216,   221,
     222,   227,   228,   233,   234,   239,   240,   245,   246,   251,
     256,   257,   260,   261,   266,   267,   273,   274,   279,   280,
     286,   287,   293,   294,   300,   301,   302,   311,   313,   316,
     322,   325,   326,   330,   331,   334,   335,   340,   341,   348,
     349,   356,   357,   362,   363,   368,   369,   375,   377,   378,
     383,   386,   387,   389,   390,   392,   394,   396,   398,   400,
     401,   403,   404,   411,   412,   417,   421,   424,   426,   427,
     430,   431,   436,   437,   442,   443,   448,   451,   452,   457,
     458,   464,   465,   471,   472,   478,   479,   484,   485,   490,
     491,   496,   497,   502,   503,   509,   510,   515,   516,   522,
     523,   528,   529,   534,   535,   540,   541,   546,   547,   552,
     553,   559,   560,   566,   567,   572,   573,   578,   579,   584,
     585,   590,   591,   596,   597,   602,   603,   608,   609,   614,
     615,   620,   621,   626,   627,   634,   635,   640,   641,   648,
     649,   655,   656,   659,   660,   666,   667,   672,   674,   676,
     677,   679,   681,   682,   685,   686,   691,   692,   699,   700,
     707,   708,   713,   714,   719,   720,   726,   728,   730,   732,
     734,   736,   738
};
static const short yyrhs[] =
{
      -1,   128,   129,     0,   130,     0,   134,     0,   135,     0,
     139,     0,   141,     0,   149,     0,   161,     0,   177,     0,
     186,     0,   207,     0,   132,     0,     0,     3,     4,   115,
     131,   124,     0,     0,    90,   112,   133,   124,     0,     5,
     115,   124,     0,     6,   136,     0,     0,     7,   137,   115,
     124,     0,     0,    66,   115,   138,   124,     0,     8,   140,
     124,     0,   114,     0,     9,     0,    10,   125,   142,   126,
       0,     0,   142,   143,     0,     0,    11,   112,   144,   124,
       0,     0,    12,   112,   145,   124,     0,     0,    13,   111,
     146,   124,     0,     0,    14,   112,   147,   124,     0,     0,
      15,   112,   148,   124,     0,    16,   125,   150,   126,     0,
       0,   150,   151,     0,     0,    17,   159,   152,   124,     0,
       0,    18,   159,   153,   124,     0,     0,    19,   154,    97,
     124,     0,     0,    21,   115,   115,   115,   111,   155,   124,
       0,     0,    21,   115,   156,   124,     0,     0,    21,    22,
     157,   124,     0,     0,    20,   158,   124,     0,   116,   160,
       0,     0,    97,     0,    23,   125,   162,   126,     0,     0,
     162,   163,     0,     0,    24,   116,   164,   124,     0,     0,
      25,   116,   165,   124,     0,     0,    26,   116,   166,   124,
       0,     0,    27,   116,   167,   124,     0,     0,    28,    29,
     168,   124,     0,     0,    28,    30,   169,   124,     0,     0,
      33,    32,   170,   124,     0,     0,    33,    30,   171,   124,
       0,     0,    36,   111,   172,   124,     0,     0,    37,   111,
     173,   124,     0,     0,    34,    31,   174,   124,     0,     0,
      34,    30,   175,   124,     0,     0,    35,   115,   176,   124,
       0,    38,   125,   178,   126,     0,     0,   178,   179,     0,
       0,    39,   111,   180,   124,     0,     0,    40,   111,   263,
     181,   124,     0,     0,    41,   111,   182,   124,     0,     0,
      42,   111,   263,   183,   124,     0,     0,    43,   111,   263,
     184,   124,     0,     0,    44,   111,   263,   185,   124,     0,
       0,     0,    48,   187,   189,   191,   125,   192,   188,   126,
       0,    51,     0,   190,   190,     0,    66,   116,   203,   204,
     205,     0,    66,   115,     0,     0,    49,    66,   254,     0,
       0,   192,   193,     0,     0,   103,   253,   194,   124,     0,
       0,   104,   105,   111,   263,   195,   124,     0,     0,   104,
     106,   111,   264,   196,   124,     0,     0,    45,   197,   200,
     124,     0,     0,     6,    66,   198,   124,     0,     0,    67,
      66,   115,   199,   124,     0,   202,     0,     0,   202,   201,
     127,   200,     0,    46,   206,     0,     0,    96,     0,     0,
      97,     0,    98,     0,   111,     0,    99,     0,   100,     0,
       0,   111,     0,     0,    50,   211,    52,   211,   208,   210,
       0,     0,    50,   211,   209,   210,     0,   125,   212,   126,
       0,    51,   160,     0,   159,     0,     0,   212,   213,     0,
       0,    53,   214,   249,   124,     0,     0,    55,    56,   215,
     124,     0,     0,    57,    58,   216,   124,     0,    59,   250,
       0,     0,    61,   115,   217,   124,     0,     0,    62,    71,
     115,   218,   124,     0,     0,    61,    71,   115,   219,   124,
       0,     0,    61,    72,   115,   220,   124,     0,     0,    61,
      70,   221,   124,     0,     0,    63,   112,   222,   124,     0,
       0,    64,   112,   223,   124,     0,     0,    65,   112,   224,
     124,     0,     0,    67,    66,   254,   225,   124,     0,     0,
      95,   254,   226,   124,     0,     0,    68,    66,   254,   227,
     124,     0,     0,    69,   112,   228,   124,     0,     0,    73,
     111,   229,   124,     0,     0,    74,   230,   253,   124,     0,
       0,    76,   112,   231,   124,     0,     0,   101,   112,   232,
     124,     0,     0,   108,   115,   109,   233,   124,     0,     0,
     108,   115,   110,   234,   124,     0,     0,   102,   112,   235,
     124,     0,     0,    82,   112,   236,   124,     0,     0,    83,
     112,   237,   124,     0,     0,    77,   112,   238,   124,     0,
       0,    78,   112,   239,   124,     0,     0,    78,    79,   240,
     124,     0,     0,    91,   112,   241,   124,     0,     0,    92,
     111,   242,   124,     0,     0,    93,   111,   243,   124,     0,
       0,    94,   111,   244,   124,     0,     0,   104,   105,   111,
     263,   245,   124,     0,     0,    80,    81,   246,   124,     0,
       0,   104,   106,   111,   264,   247,   124,     0,     0,    84,
     248,   125,   255,   126,     0,     0,   249,    54,     0,     0,
      71,   115,   115,   251,   124,     0,     0,    72,   115,   252,
     124,     0,    46,     0,   111,     0,     0,   116,     0,   115,
       0,     0,   255,   256,     0,     0,   107,   257,    47,   124,
       0,     0,   104,   105,   111,   263,   258,   124,     0,     0,
     104,   106,   111,   264,   259,   124,     0,     0,    74,   253,
     260,   124,     0,     0,    89,   115,   261,   124,     0,     0,
      45,    46,   206,   262,   124,     0,   121,     0,   122,     0,
     123,     0,   117,     0,   118,     0,   119,     0,   120,     0
};

#endif

#if YYDEBUG
/* YYRLINE[YYN] -- source line where rule number YYN was defined. */
static const short yyrline[] =
{
       0,   249,   250,   253,   254,   255,   256,   257,   258,   259,
     260,   261,   262,   263,   268,   268,   288,   288,   293,   307,
     310,   310,   315,   315,   331,   334,   343,   356,   359,   360,
     363,   363,   364,   364,   365,   365,   366,   366,   367,   367,
     372,   375,   376,   379,   379,   384,   384,   393,   393,   398,
     398,   407,   407,   416,   416,   425,   425,   428,   440,   441,
     445,   448,   449,   452,   452,   463,   463,   474,   474,   485,
     485,   496,   496,   505,   505,   518,   518,   527,   527,   540,
     540,   549,   549,   558,   558,   567,   567,   580,   580,   595,
     598,   599,   602,   602,   607,   607,   612,   612,   617,   617,
     622,   622,   627,   627,   640,   640,   640,   683,   688,   695,
     744,   772,   777,   804,   805,   808,   808,   813,   813,   818,
     818,   830,   830,   834,   834,   839,   839,   847,   851,   851,
     858,   914,   915,   918,   919,   920,   923,   924,   925,   928,
     929,   934,   934,   960,   960,   984,  1055,  1061,  1071,  1072,
    1075,  1075,  1080,  1080,  1081,  1081,  1082,  1083,  1083,  1092,
    1092,  1100,  1100,  1107,  1107,  1130,  1130,  1140,  1140,  1141,
    1141,  1142,  1142,  1143,  1143,  1152,  1152,  1166,  1166,  1183,
    1183,  1184,  1184,  1185,  1185,  1191,  1191,  1192,  1192,  1193,
    1193,  1196,  1196,  1199,  1199,  1200,  1200,  1201,  1201,  1202,
    1202,  1203,  1203,  1211,  1211,  1219,  1219,  1227,  1227,  1236,
    1236,  1245,  1245,  1254,  1254,  1259,  1259,  1260,  1260,  1274,
    1274,  1286,  1287,  1310,  1310,  1319,  1319,  1341,  1349,  1361,
    1362,  1363,  1366,  1367,  1370,  1370,  1374,  1374,  1379,  1379,
    1391,  1391,  1396,  1396,  1405,  1405,  1503,  1504,  1505,  1508,
    1509,  1510,  1511
};
#endif


#if (YYDEBUG) || defined YYERROR_VERBOSE

/* YYTNAME[TOKEN_NUM] -- String name of the token TOKEN_NUM. */
static const char *const yytname[] =
{
  "$", "error", "$undefined.", "PATH", "PATHTYPE", "INCLUDE", "IDENTIFIER", 
  "VENDORID", "LOGGING", "LOGLEV", "PADDING", "PAD_RANDOMIZE", 
  "PAD_RANDOMIZELEN", "PAD_MAXLEN", "PAD_STRICT", "PAD_EXCLTAIL", 
  "LISTEN", "X_ISAKMP", "X_ISAKMP_NATT", "X_ADMIN", "STRICT_ADDRESS", 
  "ADMINSOCK", "DISABLED", "MODECFG", "CFG_NET4", "CFG_MASK4", "CFG_DNS4", 
  "CFG_NBNS4", "CFG_AUTH_SOURCE", "CFG_SYSTEM", "CFG_RADIUS", "CFG_LOCAL", 
  "CFG_NONE", "CFG_ACCOUNTING", "CFG_CONF_SOURCE", "CFG_MOTD", 
  "CFG_POOL_SIZE", "CFG_AUTH_THROTTLE", "RETRY", "RETRY_COUNTER", 
  "RETRY_INTERVAL", "RETRY_PERSEND", "RETRY_PHASE1", "RETRY_PHASE2", 
  "NATT_KA", "ALGORITHM_CLASS", "ALGORITHMTYPE", "STRENGTHTYPE", "SAINFO", 
  "FROM", "REMOTE", "ANONYMOUS", "INHERIT", "EXCHANGE_MODE", 
  "EXCHANGETYPE", "DOI", "DOITYPE", "SITUATION", "SITUATIONTYPE", 
  "CERTIFICATE_TYPE", "CERTTYPE", "PEERS_CERTFILE", "CA_TYPE", 
  "VERIFY_CERT", "SEND_CERT", "SEND_CR", "IDENTIFIERTYPE", 
  "MY_IDENTIFIER", "PEERS_IDENTIFIER", "VERIFY_IDENTIFIER", "DNSSEC", 
  "CERT_X509", "CERT_PLAINRSA", "NONCE_SIZE", "DH_GROUP", "KEEPALIVE", 
  "PASSIVE", "INITIAL_CONTACT", "NAT_TRAVERSAL", "NAT_TRAVERSAL_LEVEL", 
  "PROPOSAL_CHECK", "PROPOSAL_CHECK_LEVEL", "GENERATE_POLICY", 
  "SUPPORT_PROXY", "PROPOSAL", "EXEC_PATH", "EXEC_COMMAND", 
  "EXEC_SUCCESS", "EXEC_FAILURE", "GSSAPI_ID", "COMPLEX_BUNDLE", "DPD", 
  "DPD_DELAY", "DPD_RETRY", "DPD_MAXFAIL", "XAUTH_LOGIN", "PREFIX", 
  "PORT", "PORTANY", "UL_PROTO", "ANY", "IKE_FRAG", "MODE_CFG", 
  "PFS_GROUP", "LIFETIME", "LIFETYPE_TIME", "LIFETYPE_BYTE", "STRENGTH", 
  "SCRIPT", "PHASE1_UP", "PHASE1_DOWN", "NUMBER", "SWITCH", "BOOLEAN", 
  "HEXSTRING", "QUOTEDSTRING", "ADDRSTRING", "UNITTYPE_BYTE", 
  "UNITTYPE_KBYTES", "UNITTYPE_MBYTES", "UNITTYPE_TBYTES", "UNITTYPE_SEC", 
  "UNITTYPE_MIN", "UNITTYPE_HOUR", "EOS", "BOC", "EOC", "COMMA", 
  "statements", "statement", "path_statement", "@1", "special_statement", 
  "@2", "include_statement", "identifier_statement", "identifier_stmt", 
  "@3", "@4", "logging_statement", "log_level", "padding_statement", 
  "padding_stmts", "padding_stmt", "@5", "@6", "@7", "@8", "@9", 
  "listen_statement", "listen_stmts", "listen_stmt", "@10", "@11", "@12", 
  "@13", "@14", "@15", "@16", "ike_addrinfo_port", "ike_port", 
  "modecfg_statement", "modecfg_stmts", "modecfg_stmt", "@17", "@18", 
  "@19", "@20", "@21", "@22", "@23", "@24", "@25", "@26", "@27", "@28", 
  "@29", "timer_statement", "timer_stmts", "timer_stmt", "@30", "@31", 
  "@32", "@33", "@34", "@35", "sainfo_statement", "@36", "@37", 
  "sainfo_name", "sainfo_id", "sainfo_peer", "sainfo_specs", 
  "sainfo_spec", "@38", "@39", "@40", "@41", "@42", "@43", "algorithms", 
  "@44", "algorithm", "prefix", "port", "ul_proto", "keylength", 
  "remote_statement", "@45", "@46", "remote_specs_block", "remote_index", 
  "remote_specs", "remote_spec", "@47", "@48", "@49", "@50", "@51", "@52", 
  "@53", "@54", "@55", "@56", "@57", "@58", "@59", "@60", "@61", "@62", 
  "@63", "@64", "@65", "@66", "@67", "@68", "@69", "@70", "@71", "@72", 
  "@73", "@74", "@75", "@76", "@77", "@78", "@79", "@80", "@81", 
  "exchange_types", "cert_spec", "@82", "@83", "dh_group_num", 
  "identifierstring", "isakmpproposal_specs", "isakmpproposal_spec", 
  "@84", "@85", "@86", "@87", "@88", "@89", "unittype_time", 
  "unittype_byte", 0
};
#endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives. */
static const short yyr1[] =
{
       0,   128,   128,   129,   129,   129,   129,   129,   129,   129,
     129,   129,   129,   129,   131,   130,   133,   132,   134,   135,
     137,   136,   138,   136,   139,   140,   140,   141,   142,   142,
     144,   143,   145,   143,   146,   143,   147,   143,   148,   143,
     149,   150,   150,   152,   151,   153,   151,   154,   151,   155,
     151,   156,   151,   157,   151,   158,   151,   159,   160,   160,
     161,   162,   162,   164,   163,   165,   163,   166,   163,   167,
     163,   168,   163,   169,   163,   170,   163,   171,   163,   172,
     163,   173,   163,   174,   163,   175,   163,   176,   163,   177,
     178,   178,   180,   179,   181,   179,   182,   179,   183,   179,
     184,   179,   185,   179,   187,   188,   186,   189,   189,   190,
     190,   191,   191,   192,   192,   194,   193,   195,   193,   196,
     193,   197,   193,   198,   193,   199,   193,   200,   201,   200,
     202,   203,   203,   204,   204,   204,   205,   205,   205,   206,
     206,   208,   207,   209,   207,   210,   211,   211,   212,   212,
     214,   213,   215,   213,   216,   213,   213,   217,   213,   218,
     213,   219,   213,   220,   213,   221,   213,   222,   213,   223,
     213,   224,   213,   225,   213,   226,   213,   227,   213,   228,
     213,   229,   213,   230,   213,   231,   213,   232,   213,   233,
     213,   234,   213,   235,   213,   236,   213,   237,   213,   238,
     213,   239,   213,   240,   213,   241,   213,   242,   213,   243,
     213,   244,   213,   245,   213,   246,   213,   247,   213,   248,
     213,   249,   249,   251,   250,   252,   250,   253,   253,   254,
     254,   254,   255,   255,   257,   256,   258,   256,   259,   256,
     260,   256,   261,   256,   262,   256,   263,   263,   263,   264,
     264,   264,   264
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN. */
static const short yyr2[] =
{
       0,     0,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     5,     0,     4,     3,     2,
       0,     4,     0,     4,     3,     1,     1,     4,     0,     2,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       4,     0,     2,     0,     4,     0,     4,     0,     4,     0,
       7,     0,     4,     0,     4,     0,     3,     2,     0,     1,
       4,     0,     2,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     4,
       0,     2,     0,     4,     0,     5,     0,     4,     0,     5,
       0,     5,     0,     5,     0,     0,     8,     1,     2,     5,
       2,     0,     3,     0,     2,     0,     4,     0,     6,     0,
       6,     0,     4,     0,     4,     0,     5,     1,     0,     4,
       2,     0,     1,     0,     1,     1,     1,     1,     1,     0,
       1,     0,     6,     0,     4,     3,     2,     1,     0,     2,
       0,     4,     0,     4,     0,     4,     2,     0,     4,     0,
       5,     0,     5,     0,     5,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     5,     0,     4,     0,     5,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       5,     0,     5,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     0,     6,     0,
       5,     0,     2,     0,     5,     0,     4,     1,     1,     0,
       1,     1,     0,     2,     0,     4,     0,     6,     0,     6,
       0,     4,     0,     4,     0,     5,     1,     1,     1,     1,
       1,     1,     1
};

/* YYDEFACT[S] -- default rule to reduce with in state S when YYTABLE
   doesn't specify something else to do.  Zero means the default is an
   error. */
static const short yydefact[] =
{
       1,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     104,     0,     0,     2,     3,    13,     4,     5,     6,     7,
       8,     9,    10,    11,    12,     0,     0,    20,     0,    19,
      26,    25,     0,    28,    41,    61,    90,     0,    58,    58,
     147,   143,    16,    14,    18,     0,    22,    24,     0,     0,
       0,     0,   107,     0,   111,     0,    59,   146,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      27,    29,     0,     0,    47,    55,     0,    40,    42,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      62,     0,     0,     0,     0,     0,     0,    89,    91,   110,
     131,     0,     0,   108,   141,   148,   144,    17,    15,    21,
      23,    30,    32,    34,    36,    38,    43,    45,     0,     0,
      53,    51,    63,    65,    67,    69,    71,    73,    77,    75,
      85,    83,    87,    79,    81,    92,     0,    96,     0,     0,
       0,   132,   133,   229,   113,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    56,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   246,   247,   248,    94,     0,    98,   100,
     102,   134,   135,     0,   231,   230,   112,   105,   142,   150,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   183,     0,     0,     0,     0,     0,     0,   219,
       0,     0,     0,     0,   229,     0,     0,     0,     0,   145,
     149,    31,    33,    35,    37,    39,    44,    46,    48,    54,
       0,    52,    64,    66,    68,    70,    72,    74,    78,    76,
      86,    84,    88,    80,    82,    93,     0,    97,     0,     0,
       0,   137,   138,   136,   109,     0,   121,     0,     0,     0,
       0,   114,   221,   152,   154,     0,     0,   156,   165,     0,
       0,   157,     0,   167,   169,   171,   229,   229,   179,   181,
       0,   185,   199,   203,   201,   215,   195,   197,     0,   205,
     207,   209,   211,   175,   187,   193,     0,     0,     0,    49,
      95,    99,   101,   103,   123,     0,     0,   227,   228,   115,
       0,     0,   106,     0,     0,     0,     0,   225,     0,   161,
     163,     0,   159,     0,     0,     0,   173,   177,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   232,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   189,   191,
       0,     0,   139,     0,   127,   125,     0,     0,     0,   222,
     151,   153,   155,   223,     0,   166,     0,     0,   158,     0,
     168,   170,   172,     0,     0,   180,   182,   184,   186,   200,
     204,   202,   216,   196,   198,     0,   206,   208,   210,   212,
     176,   188,   194,   213,   249,   250,   251,   252,   217,     0,
       0,    50,   124,   140,   130,   122,     0,     0,   116,   117,
     119,     0,   226,   162,   164,   160,   174,   178,     0,     0,
       0,     0,   234,   220,   233,     0,     0,   190,   192,     0,
     126,     0,     0,   224,   139,   240,   242,     0,     0,     0,
     214,   218,   129,   118,   120,   244,     0,     0,     0,     0,
       0,     0,   241,   243,   236,   238,   235,   245,     0,     0,
     237,   239,     0,     0
};

static const short yydefgoto[] =
{
       1,    13,    14,    62,    15,    61,    16,    17,    29,    45,
      64,    18,    32,    19,    48,    71,   147,   148,   149,   150,
     151,    20,    49,    78,   152,   153,   118,   350,   158,   156,
     119,    40,    57,    21,    50,    90,   159,   160,   161,   162,
     163,   164,   166,   165,   170,   171,   168,   167,   169,    22,
      51,    98,   172,   246,   177,   248,   249,   250,    23,    37,
     260,    54,    55,   102,   187,   261,   356,   431,   432,   305,
     351,   407,   353,   406,   354,   142,   183,   254,   404,    24,
     145,    60,   106,    41,   146,   220,   262,   314,   315,   321,
     369,   366,   367,   318,   323,   324,   325,   373,   343,   374,
     328,   329,   280,   331,   344,   399,   400,   345,   336,   337,
     332,   334,   333,   339,   340,   341,   342,   425,   335,   426,
     288,   313,   267,   411,   364,   309,   186,   385,   424,   439,
     458,   459,   446,   447,   451,   176,   398
};

static const short yypact[] =
{
  -32768,    33,    40,   -67,    19,     6,   -70,   -62,   -55,   -43,
  -32768,   -27,   -26,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   -24,   -29,-32768,    -2,-32768,
  -32768,-32768,   -17,-32768,-32768,-32768,-32768,   -14,    13,    13,
  -32768,    70,-32768,-32768,-32768,    11,-32768,-32768,    -7,    -8,
      -5,    18,-32768,   -65,    75,    62,-32768,-32768,-32768,   -27,
       5,    14,    23,    27,    29,    20,    49,    32,    50,    56,
  -32768,-32768,    53,    53,-32768,-32768,    -6,-32768,-32768,    54,
      55,    59,    61,    37,    10,    63,    57,    67,    68,-32768,
  -32768,    71,    73,    74,    76,    77,    78,-32768,-32768,-32768,
      85,   117,    65,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,    89,    69,
  -32768,    79,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   -49,-32768,   -49,   -49,
     -49,-32768,     1,   -15,-32768,     5,    72,    80,    81,    82,
      83,    86,    88,    90,    91,-32768,    92,    84,    93,    94,
      96,    97,    98,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,-32768,-32768,-32768,-32768,   109,-32768,-32768,
  -32768,-32768,-32768,   -35,-32768,-32768,-32768,     8,-32768,-32768,
     135,   134,    31,   -25,   124,   122,   123,   125,   130,   131,
     126,   128,-32768,   129,   132,   -44,   119,   133,   136,-32768,
     137,   139,   140,   141,   -15,   142,   143,    -1,   121,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
     145,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   116,-32768,   118,   138,
     144,-32768,-32768,-32768,-32768,   147,-32768,   177,   -19,     9,
     120,-32768,-32768,-32768,-32768,   146,   148,-32768,-32768,   149,
     150,-32768,   151,-32768,-32768,-32768,   -15,   -15,-32768,-32768,
     -19,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   152,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,   156,   158,     7,-32768,
  -32768,-32768,-32768,-32768,-32768,   155,   157,-32768,-32768,-32768,
     159,   160,-32768,   -36,   154,   161,   164,-32768,   162,-32768,
  -32768,   163,-32768,   165,   166,   167,-32768,-32768,   168,   169,
     170,   171,   172,   173,   174,   175,   176,   178,-32768,   179,
     180,   181,   182,   183,   184,   185,   -49,   -40,-32768,-32768,
     187,   188,   190,   189,   153,-32768,   191,   -49,   -40,-32768,
  -32768,-32768,-32768,-32768,   192,-32768,   193,   194,-32768,   195,
  -32768,-32768,-32768,   196,   197,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,   -20,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   198,
     199,-32768,-32768,-32768,-32768,-32768,   200,   201,-32768,-32768,
  -32768,   202,-32768,-32768,-32768,-32768,-32768,-32768,   207,   -19,
     209,    52,-32768,-32768,-32768,   204,   205,-32768,-32768,   155,
  -32768,   206,   208,-32768,   190,-32768,-32768,   203,   220,   210,
  -32768,-32768,-32768,-32768,-32768,-32768,   211,   212,   -49,   -40,
     213,   214,-32768,-32768,-32768,-32768,-32768,-32768,   215,   216,
  -32768,-32768,   247,-32768
};

static const short yypgoto[] =
{
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,    87,   219,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,   218,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,  -227,-32768,-32768,-32768,-32768,-32768,  -231,-32768,
  -32768,-32768,    64,   217,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,  -277,  -180,-32768,-32768,-32768,
  -32768,-32768,-32768,-32768,-32768,  -138,  -341
};


#define	YYLAST		340


static const short yytable[] =
{
     178,   179,   180,   330,    65,    66,    67,    68,    69,    72,
      73,    74,    75,    76,   255,    30,   120,   410,   359,    79,
      80,    81,    82,    83,    38,   418,    27,   307,    84,    85,
      86,    87,    88,   462,   293,   283,     2,    52,     3,     4,
     128,     5,   129,     6,    25,   268,   269,   270,    26,     7,
      99,   100,    53,   256,   419,    33,     8,    91,    92,    93,
      94,    95,    96,    34,   251,   252,   126,   127,   284,   420,
      35,     9,   173,   174,   175,   257,   253,   394,   395,   396,
     397,    10,    36,    11,   421,    28,    42,   422,   360,    39,
     271,    43,   308,   130,   131,    44,   326,   327,   181,   182,
     184,   185,   265,   266,   296,   297,   423,    47,   455,   121,
      56,   258,   259,    46,   310,   311,   348,   349,    77,    70,
      31,    89,    59,    12,   101,   189,    63,   190,    53,   191,
     105,   192,   111,   193,   194,   195,   196,   197,   107,   198,
     199,   200,   435,   113,    97,   201,   202,   108,   203,   204,
     205,   109,   206,   110,   207,   208,   209,   437,   438,   116,
     117,   112,   114,   210,   211,   212,   213,   214,   115,    39,
     122,   123,   132,   215,   216,   124,   217,   125,   133,   134,
     218,   141,   135,   143,   136,   137,   154,   138,   139,   140,
     144,   263,   264,   155,   157,   272,   276,   277,   219,   230,
     285,   352,   442,   445,   221,   222,   223,   224,   393,   188,
     225,     0,   226,   304,   227,   228,   229,   231,   232,   409,
     233,   234,   235,   236,   237,   238,   239,   240,   241,   242,
     243,   244,   245,   247,   273,   274,   298,   275,   278,   279,
     300,   281,   301,   306,   282,   286,   312,   463,   287,   289,
     290,   291,   292,   434,   294,   295,   299,   450,    58,     0,
       0,   316,   302,   317,   319,   320,   322,   346,   303,   347,
     357,   358,   355,   103,     0,     0,   104,   338,   361,   363,
    -128,     0,     0,     0,     0,   362,   365,   368,     0,   370,
     371,   372,   375,   376,   377,   378,   379,   380,   381,   382,
     383,   403,   384,   386,   387,   388,   389,   390,   391,   392,
     454,   401,   402,   405,   448,   408,   412,   413,   414,   415,
     416,   417,   427,   428,   436,   430,   433,   429,   440,   441,
     443,   449,   444,     0,     0,   452,   453,   456,   457,   460,
     461
};

static const short yycheck[] =
{
     138,   139,   140,   280,    11,    12,    13,    14,    15,    17,
      18,    19,    20,    21,     6,     9,    22,   358,    54,    24,
      25,    26,    27,    28,    51,    45,     7,    46,    33,    34,
      35,    36,    37,     0,   214,    79,     3,    51,     5,     6,
      30,     8,    32,    10,     4,    70,    71,    72,   115,    16,
     115,   116,    66,    45,    74,   125,    23,    39,    40,    41,
      42,    43,    44,   125,    99,   100,    29,    30,   112,    89,
     125,    38,   121,   122,   123,    67,   111,   117,   118,   119,
     120,    48,   125,    50,   104,    66,   112,   107,   124,   116,
     115,   115,   111,    30,    31,   124,   276,   277,    97,    98,
     115,   116,    71,    72,   105,   106,   126,   124,   449,   115,
      97,   103,   104,   115,   105,   106,   109,   110,   126,   126,
     114,   126,    52,    90,    49,    53,   115,    55,    66,    57,
     125,    59,   112,    61,    62,    63,    64,    65,   124,    67,
      68,    69,   419,   111,   126,    73,    74,   124,    76,    77,
      78,   124,    80,   124,    82,    83,    84,   105,   106,    72,
      73,   112,   112,    91,    92,    93,    94,    95,   112,   116,
     116,   116,   115,   101,   102,   116,   104,   116,   111,   111,
     108,    96,   111,    66,   111,   111,    97,   111,   111,   111,
     125,    56,    58,   124,   115,    71,    66,    66,   126,   115,
      81,    46,   429,   434,   124,   124,   124,   124,   346,   145,
     124,    -1,   124,    66,   124,   124,   124,   124,   124,   357,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   112,   112,   115,   112,   112,   111,
     124,   112,   124,    66,   112,   112,   126,     0,   112,   112,
     111,   111,   111,    46,   112,   112,   111,    47,    39,    -1,
      -1,   115,   124,   115,   115,   115,   115,   111,   124,   111,
     111,   111,   115,    55,    -1,    -1,    59,   125,   124,   115,
     127,    -1,    -1,    -1,    -1,   124,   124,   124,    -1,   124,
     124,   124,   124,   124,   124,   124,   124,   124,   124,   124,
     124,   111,   124,   124,   124,   124,   124,   124,   124,   124,
     448,   124,   124,   124,   111,   124,   124,   124,   124,   124,
     124,   124,   124,   124,   115,   124,   124,   127,   124,   124,
     124,   111,   124,    -1,    -1,   124,   124,   124,   124,   124,
     124
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "/usr/share/bison/bison.simple"

/* Skeleton output parser for bison,

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002 Free Software
   Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser when
   the %semantic_parser declaration is not specified in the grammar.
   It was written by Richard Stallman by simplifying the hairy parser
   used when %semantic_parser is specified.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

#if ! defined (yyoverflow) || defined (YYERROR_VERBOSE)

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# if YYSTACK_USE_ALLOCA
#  define YYSTACK_ALLOC alloca
# else
#  ifndef YYSTACK_USE_ALLOCA
#   if defined (alloca) || defined (_ALLOCA_H)
#    define YYSTACK_ALLOC alloca
#   else
#    ifdef __GNUC__
#     define YYSTACK_ALLOC __builtin_alloca
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC malloc
#  define YYSTACK_FREE free
# endif
#endif /* ! defined (yyoverflow) || defined (YYERROR_VERBOSE) */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (YYLTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short yyss;
  YYSTYPE yyvs;
# if YYLSP_NEEDED
  YYLTYPE yyls;
# endif
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAX (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# if YYLSP_NEEDED
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE) + sizeof (YYLTYPE))	\
      + 2 * YYSTACK_GAP_MAX)
# else
#  define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short) + sizeof (YYSTYPE))				\
      + YYSTACK_GAP_MAX)
# endif

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAX;	\
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif


#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");			\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256


/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).

   When YYLLOC_DEFAULT is run, CURRENT is set the location of the
   first token.  By default, to implement support for ranges, extend
   its range to the last symbol.  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)       	\
   Current.last_line   = Rhs[N].last_line;	\
   Current.last_column = Rhs[N].last_column;
#endif


/* YYLEX -- calling `yylex' with the right arguments.  */

#if YYPURE
# if YYLSP_NEEDED
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, &yylloc, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval, &yylloc)
#  endif
# else /* !YYLSP_NEEDED */
#  ifdef YYLEX_PARAM
#   define YYLEX		yylex (&yylval, YYLEX_PARAM)
#  else
#   define YYLEX		yylex (&yylval)
#  endif
# endif /* !YYLSP_NEEDED */
#else /* !YYPURE */
# define YYLEX			yylex ()
#endif /* !YYPURE */


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)
/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
#endif /* !YYDEBUG */

/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif

#ifdef YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif
#endif

#line 315 "/usr/share/bison/bison.simple"


/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
#  define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL
# else
#  define YYPARSE_PARAM_ARG YYPARSE_PARAM
#  define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
# endif
#else /* !YYPARSE_PARAM */
# define YYPARSE_PARAM_ARG
# define YYPARSE_PARAM_DECL
#endif /* !YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
# ifdef YYPARSE_PARAM
int yyparse (void *);
# else
int yyparse (void);
# endif
#endif

/* YY_DECL_VARIABLES -- depending whether we use a pure parser,
   variables are global, or local to YYPARSE.  */

#define YY_DECL_NON_LSP_VARIABLES			\
/* The lookahead symbol.  */				\
int yychar;						\
							\
/* The semantic value of the lookahead symbol. */	\
YYSTYPE yylval;						\
							\
/* Number of parse errors so far.  */			\
int yynerrs;

#if YYLSP_NEEDED
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES			\
						\
/* Location data for the lookahead symbol.  */	\
YYLTYPE yylloc;
#else
# define YY_DECL_VARIABLES			\
YY_DECL_NON_LSP_VARIABLES
#endif


/* If nonreentrant, generate the variables here. */

#if !YYPURE
YY_DECL_VARIABLES
#endif  /* !YYPURE */

int
yyparse (YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  /* If reentrant, generate the variables here. */
#if YYPURE
  YY_DECL_VARIABLES
#endif  /* !YYPURE */

  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yychar1 = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack. */
  short	yyssa[YYINITDEPTH];
  short *yyss = yyssa;
  register short *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;

#if YYLSP_NEEDED
  /* The location stack.  */
  YYLTYPE yylsa[YYINITDEPTH];
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;
#endif

#if YYLSP_NEEDED
# define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
# define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  YYSIZE_T yystacksize = YYINITDEPTH;


  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
#if YYLSP_NEEDED
  YYLTYPE yyloc;
#endif

  /* When reducing, the number of symbols on the RHS of the reduced
     rule. */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;
#if YYLSP_NEEDED
  yylsp = yyls;
#endif
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short *yyss1 = yyss;

	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  */
# if YYLSP_NEEDED
	YYLTYPE *yyls1 = yyls;
	/* This used to be a conditional around just the two extra args,
	   but that might be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yyls1, yysize * sizeof (*yylsp),
		    &yystacksize);
	yyls = yyls1;
# else
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),
		    &yystacksize);
# endif
	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;

      {
	short *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);
# if YYLSP_NEEDED
	YYSTACK_RELOCATE (yyls);
# endif
# undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
#if YYLSP_NEEDED
      yylsp = yyls + yysize - 1;
#endif

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yychar1 = YYTRANSLATE (yychar);

#if YYDEBUG
     /* We have to keep this `#if YYDEBUG', since we use variables
	which are defined only if `YYDEBUG' is set.  */
      if (yydebug)
	{
	  YYFPRINTF (stderr, "Next token is %d (%s",
		     yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise
	     meaning of a token, for further debugging info.  */
# ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
# endif
	  YYFPRINTF (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %d (%s), ",
	      yychar, yytname[yychar1]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to the semantic value of
     the lookahead token.  This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

#if YYLSP_NEEDED
  /* Similarly for the default location.  Let the user run additional
     commands if for instance locations are ranges.  */
  yyloc = yylsp[1-yylen];
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
#endif

#if YYDEBUG
  /* We have to keep this `#if YYDEBUG', since we use variables which
     are defined only if `YYDEBUG' is set.  */
  if (yydebug)
    {
      int yyi;

      YYFPRINTF (stderr, "Reducing via rule %d (line %d), ",
		 yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (yyi = yyprhs[yyn]; yyrhs[yyi] > 0; yyi++)
	YYFPRINTF (stderr, "%s ", yytname[yyrhs[yyi]]);
      YYFPRINTF (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif

  switch (yyn) {

case 14:
#line 269 "./cfparse.y"
{
			if (yyvsp[-1].num >= LC_PATHTYPE_MAX) {
				yyerror("invalid path type %d", yyvsp[-1].num);
				return -1;
			}

			/* free old pathinfo */
			if (lcconf->pathinfo[yyvsp[-1].num])
				racoon_free(lcconf->pathinfo[yyvsp[-1].num]);

			/* set new pathinfo */
			lcconf->pathinfo[yyvsp[-1].num] = strdup(yyvsp[0].val->v);
			vfree(yyvsp[0].val);
		}
    break;
case 16:
#line 288 "./cfparse.y"
{ lcconf->complex_bundle = yyvsp[0].num; }
    break;
case 18:
#line 294 "./cfparse.y"
{
			char path[MAXPATHLEN];

			getpathname(path, sizeof(path),
				LC_PATHTYPE_INCLUDE, yyvsp[-1].val->v);
			vfree(yyvsp[-1].val);
			if (yycf_switch_buffer(path) != 0)
				return -1;
		}
    break;
case 20:
#line 311 "./cfparse.y"
{
			/*XXX to be deleted */
		}
    break;
case 22:
#line 316 "./cfparse.y"
{
			/*XXX to be deleted */
			yyvsp[0].val->l--;	/* nuke '\0' */
			lcconf->ident[yyvsp[-1].num] = yyvsp[0].val;
			if (lcconf->ident[yyvsp[-1].num] == NULL) {
				yyerror("failed to set my ident: %s",
					strerror(errno));
				return -1;
			}
		}
    break;
case 25:
#line 335 "./cfparse.y"
{
			/*
			 * XXX ignore it because this specification
			 * will be obsoleted.
			 */
			yywarn("see racoon.conf(5), such a log specification will be obsoleted.");
			vfree(yyvsp[0].val);
		}
    break;
case 26:
#line 344 "./cfparse.y"
{
			/*
			 * set the loglevel by configuration file only when
			 * the command line did not specify any loglevel.
			 */
			if (loglevel <= LLV_BASE)
				loglevel += yyvsp[0].num;
		}
    break;
case 30:
#line 363 "./cfparse.y"
{ lcconf->pad_random = yyvsp[0].num; }
    break;
case 32:
#line 364 "./cfparse.y"
{ lcconf->pad_randomlen = yyvsp[0].num; }
    break;
case 34:
#line 365 "./cfparse.y"
{ lcconf->pad_maxsize = yyvsp[0].num; }
    break;
case 36:
#line 366 "./cfparse.y"
{ lcconf->pad_strict = yyvsp[0].num; }
    break;
case 38:
#line 367 "./cfparse.y"
{ lcconf->pad_excltail = yyvsp[0].num; }
    break;
case 43:
#line 380 "./cfparse.y"
{
			listen_addr (yyvsp[0].saddr, 0);
		}
    break;
case 45:
#line 385 "./cfparse.y"
{
#ifdef ENABLE_NATT
			listen_addr (yyvsp[0].saddr, 1);
#else
			yyerror("NAT-T support not compiled in.");
#endif
		}
    break;
case 47:
#line 394 "./cfparse.y"
{
			yyerror("admin directive is obsoleted.");
		}
    break;
case 49:
#line 399 "./cfparse.y"
{
#ifdef ENABLE_ADMINPORT
			adminsock_conf(yyvsp[-3].val, yyvsp[-2].val, yyvsp[-1].val, yyvsp[0].num);
#else
			yywarn("admin port support not compiled in");
#endif
		}
    break;
case 51:
#line 408 "./cfparse.y"
{
#ifdef ENABLE_ADMINPORT
			adminsock_conf(yyvsp[0].val, NULL, NULL, -1);
#else
			yywarn("admin port support not compiled in");
#endif
		}
    break;
case 53:
#line 417 "./cfparse.y"
{
#ifdef ENABLE_ADMINPORT
			adminsock_path = NULL;
#else
			yywarn("admin port support not compiled in");
#endif
		}
    break;
case 55:
#line 425 "./cfparse.y"
{ lcconf->strict_address = TRUE; }
    break;
case 57:
#line 429 "./cfparse.y"
{
			char portbuf[10];

			snprintf(portbuf, sizeof(portbuf), "%ld", yyvsp[0].num);
			yyval.saddr = str2saddr(yyvsp[-1].val->v, portbuf);
			vfree(yyvsp[-1].val);
			if (!yyval.saddr)
				return -1;
		}
    break;
case 58:
#line 440 "./cfparse.y"
{ yyval.num = PORT_ISAKMP; }
    break;
case 59:
#line 441 "./cfparse.y"
{ yyval.num = yyvsp[0].num; }
    break;
case 63:
#line 453 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
		 if (inet_pton(AF_INET, yyvsp[0].val->v,
		     &isakmp_cfg_config.network4) != 1)
			yyerror("bad IPv4 network address.");
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 65:
#line 464 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			if (inet_pton(AF_INET, yyvsp[0].val->v,
			    &isakmp_cfg_config.netmask4) != 1)
				yyerror("bad IPv4 netmask address.");
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 67:
#line 475 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			if (inet_pton(AF_INET, yyvsp[0].val->v,
			    &isakmp_cfg_config.dns4) != 1)
				yyerror("bad IPv4 DNS address.");
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 69:
#line 486 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			if (inet_pton(AF_INET, yyvsp[0].val->v,
			    &isakmp_cfg_config.nbns4) != 1)
				yyerror("bad IPv4 WINS address.");
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 71:
#line 497 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			isakmp_cfg_config.authsource = ISAKMP_CFG_AUTH_SYSTEM;
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 73:
#line 506 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
#ifdef HAVE_LIBRADIUS
			isakmp_cfg_config.authsource = ISAKMP_CFG_AUTH_RADIUS;
#else /* HAVE_LIBRADIUS */
			yyerror("racoon not configured with --with-libradius");
#endif /* HAVE_LIBRADIUS */
#else /* ENABLE_HYBRID */
			yyerror("racoon not configured with --enable-hybrid");
#endif /* ENABLE_HYBRID */
		}
    break;
case 75:
#line 519 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			isakmp_cfg_config.accounting = ISAKMP_CFG_ACCT_NONE;
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 77:
#line 528 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
#ifdef HAVE_LIBRADIUS
			isakmp_cfg_config.accounting = ISAKMP_CFG_ACCT_RADIUS;
#else /* HAVE_LIBRADIUS */
			yyerror("racoon not configured with --with-libradius");
#endif /* HAVE_LIBRADIUS */
#else /* ENABLE_HYBRID */
			yyerror("racoon not configured with --enable-hybrid");
#endif /* ENABLE_HYBRID */
		}
    break;
case 79:
#line 541 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			isakmp_cfg_config.pool_size = yyvsp[0].num;
#else /* ENABLE_HYBRID */
			yyerror("racoon not configured with --enable-hybrid");
#endif /* ENABLE_HYBRID */
		}
    break;
case 81:
#line 550 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			isakmp_cfg_config.auth_throttle = yyvsp[0].num;
#else /* ENABLE_HYBRID */
			yyerror("racoon not configured with --enable-hybrid");
#endif /* ENABLE_HYBRID */
		}
    break;
case 83:
#line 559 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			isakmp_cfg_config.confsource = ISAKMP_CFG_CONF_LOCAL;
#else /* ENABLE_HYBRID */
			yyerror("racoon not configured with --enable-hybrid");
#endif /* ENABLE_HYBRID */
		}
    break;
case 85:
#line 568 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
#ifdef HAVE_LIBRADIUS
			isakmp_cfg_config.confsource = ISAKMP_CFG_CONF_RADIUS;
#else /* HAVE_LIBRADIUS */
			yyerror("racoon not configured with --with-libradius");
#endif /* HAVE_LIBRADIUS */
#else /* ENABLE_HYBRID */
			yyerror("racoon not configured with --enable-hybrid");
#endif /* ENABLE_HYBRID */
		}
    break;
case 87:
#line 581 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			strncpy(&isakmp_cfg_config.motd[0], yyvsp[0].val->v, MAXPATHLEN);
			isakmp_cfg_config.motd[MAXPATHLEN] = '\0';
			vfree(yyvsp[0].val);
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 92:
#line 603 "./cfparse.y"
{
			lcconf->retry_counter = yyvsp[0].num;
		}
    break;
case 94:
#line 608 "./cfparse.y"
{
			lcconf->retry_interval = yyvsp[-1].num * yyvsp[0].num;
		}
    break;
case 96:
#line 613 "./cfparse.y"
{
			lcconf->count_persend = yyvsp[0].num;
		}
    break;
case 98:
#line 618 "./cfparse.y"
{
			lcconf->retry_checkph1 = yyvsp[-1].num * yyvsp[0].num;
		}
    break;
case 100:
#line 623 "./cfparse.y"
{
			lcconf->wait_ph2complete = yyvsp[-1].num * yyvsp[0].num;
		}
    break;
case 102:
#line 628 "./cfparse.y"
{
#ifdef ENABLE_NATT
			lcconf->natt_ka_interval = yyvsp[-1].num * yyvsp[0].num;
#else
			yyerror("NAT-T support not compiled in.");
#endif
		}
    break;
case 104:
#line 641 "./cfparse.y"
{
			cur_sainfo = newsainfo();
			if (cur_sainfo == NULL) {
				yyerror("failed to allocate sainfo");
				return -1;
			}
		}
    break;
case 105:
#line 649 "./cfparse.y"
{
			struct sainfo *check;

			/* default */
			if (cur_sainfo->algs[algclass_ipsec_enc] == 0) {
				yyerror("no encryption algorithm at %s",
					sainfo2str(cur_sainfo));
				return -1;
			}
			if (cur_sainfo->algs[algclass_ipsec_auth] == 0) {
				yyerror("no authentication algorithm at %s",
					sainfo2str(cur_sainfo));
				return -1;
			}
			if (cur_sainfo->algs[algclass_ipsec_comp] == 0) {
				yyerror("no compression algorithm at %s",
					sainfo2str(cur_sainfo));
				return -1;
			}

			/* duplicate check */
			check = getsainfo(cur_sainfo->idsrc,
					  cur_sainfo->iddst,
					  cur_sainfo->id_i);
			if (check && (!check->idsrc && !cur_sainfo->idsrc)) {
				yyerror("duplicated sainfo: %s",
					sainfo2str(cur_sainfo));
				return -1;
			}
			inssainfo(cur_sainfo);
		}
    break;
case 107:
#line 684 "./cfparse.y"
{
			cur_sainfo->idsrc = NULL;
			cur_sainfo->iddst = NULL;
		}
    break;
case 108:
#line 689 "./cfparse.y"
{
			cur_sainfo->idsrc = yyvsp[-1].val;
			cur_sainfo->iddst = yyvsp[0].val;
		}
    break;
case 109:
#line 696 "./cfparse.y"
{
			char portbuf[10];
			struct sockaddr *saddr;

			if ((yyvsp[0].num == IPPROTO_ICMP || yyvsp[0].num == IPPROTO_ICMPV6)
			 && (yyvsp[-1].num != IPSEC_PORT_ANY || yyvsp[-1].num != IPSEC_PORT_ANY)) {
				yyerror("port number must be \"any\".");
				return -1;
			}

			snprintf(portbuf, sizeof(portbuf), "%lu", yyvsp[-1].num);
			saddr = str2saddr(yyvsp[-3].val->v, portbuf);
			vfree(yyvsp[-3].val);
			if (saddr == NULL)
				return -1;

			switch (saddr->sa_family) {
			case AF_INET:
				if (yyvsp[0].num == IPPROTO_ICMPV6) {
					yyerror("upper layer protocol mismatched.\n");
					racoon_free(saddr);
					return -1;
				}
				yyval.val = ipsecdoi_sockaddr2id(saddr,
					yyvsp[-2].num == ~0 ? (sizeof(struct in_addr) << 3): yyvsp[-2].num,
					yyvsp[0].num);
				break;
#ifdef INET6
			case AF_INET6:
				if (yyvsp[0].num == IPPROTO_ICMP) {
					yyerror("upper layer protocol mismatched.\n");
					racoon_free(saddr);
					return -1;
				}
				yyval.val = ipsecdoi_sockaddr2id(saddr,
					yyvsp[-2].num == ~0 ? (sizeof(struct in6_addr) << 3) : yyvsp[-2].num,
					yyvsp[0].num);
				break;
#endif
			default:
				yyerror("invalid family: %d", saddr->sa_family);
				yyval.val = NULL;
				break;
			}
			racoon_free(saddr);
			if (yyval.val == NULL)
				return -1;
		}
    break;
case 110:
#line 745 "./cfparse.y"
{
			struct ipsecdoi_id_b *id_b;

			if (yyvsp[-1].num == IDTYPE_ASN1DN) {
				yyerror("id type forbidden: %d", yyvsp[-1].num);
				yyval.val = NULL;
				return -1;
			}

			yyvsp[0].val->l--;

			yyval.val = vmalloc(sizeof(*id_b) + yyvsp[0].val->l);
			if (yyval.val == NULL) {
				yyerror("failed to allocate identifier");
				return -1;
			}

			id_b = (struct ipsecdoi_id_b *)yyval.val->v;
			id_b->type = idtype2doi(yyvsp[-1].num);

			id_b->proto_id = 0;
			id_b->port = 0;

			memcpy(yyval.val->v + sizeof(*id_b), yyvsp[0].val->v, yyvsp[0].val->l);
		}
    break;
case 111:
#line 773 "./cfparse.y"
{
			cur_sainfo->id_i = NULL;
		}
    break;
case 112:
#line 778 "./cfparse.y"
{
			struct ipsecdoi_id_b *id_b;
			vchar_t *idv;

			if (set_identifier(&idv, yyvsp[-1].num, yyvsp[0].val) != 0) {
				yyerror("failed to set identifer.\n");
				return -1;
			}
			cur_sainfo->id_i = vmalloc(sizeof(*id_b) + idv->l);
			if (cur_sainfo->id_i == NULL) {
				yyerror("failed to allocate identifier");
				return -1;
			}

			id_b = (struct ipsecdoi_id_b *)cur_sainfo->id_i->v;
			id_b->type = idtype2doi(yyvsp[-1].num);

			id_b->proto_id = 0;
			id_b->port = 0;

			memcpy(cur_sainfo->id_i->v + sizeof(*id_b),
			       idv->v, idv->l);
			vfree(idv);
		}
    break;
case 115:
#line 809 "./cfparse.y"
{
			cur_sainfo->pfs_group = yyvsp[0].num;
		}
    break;
case 117:
#line 814 "./cfparse.y"
{
			cur_sainfo->lifetime = yyvsp[-1].num * yyvsp[0].num;
		}
    break;
case 119:
#line 819 "./cfparse.y"
{
#if 1
			yyerror("byte lifetime support is deprecated");
			return -1;
#else
			cur_sainfo->lifebyte = fix_lifebyte(yyvsp[-1].num * yyvsp[0].num);
			if (cur_sainfo->lifebyte == 0)
				return -1;
#endif
		}
    break;
case 121:
#line 830 "./cfparse.y"
{
			cur_algclass = yyvsp[0].num;
		}
    break;
case 123:
#line 835 "./cfparse.y"
{
			yyerror("it's deprecated to specify a identifier in phase 2");
		}
    break;
case 125:
#line 840 "./cfparse.y"
{
			yyerror("it's deprecated to specify a identifier in phase 2");
		}
    break;
case 127:
#line 848 "./cfparse.y"
{
			inssainfoalg(&cur_sainfo->algs[cur_algclass], yyvsp[0].alg);
		}
    break;
case 128:
#line 852 "./cfparse.y"
{
			inssainfoalg(&cur_sainfo->algs[cur_algclass], yyvsp[0].alg);
		}
    break;
case 130:
#line 859 "./cfparse.y"
{
			int defklen;

			yyval.alg = newsainfoalg();
			if (yyval.alg == NULL) {
				yyerror("failed to get algorithm allocation");
				return -1;
			}

			yyval.alg->alg = algtype2doi(cur_algclass, yyvsp[-1].num);
			if (yyval.alg->alg == -1) {
				yyerror("algorithm mismatched");
				racoon_free(yyval.alg);
				yyval.alg = NULL;
				return -1;
			}

			defklen = default_keylen(cur_algclass, yyvsp[-1].num);
			if (defklen == 0) {
				if (yyvsp[0].num) {
					yyerror("keylen not allowed");
					racoon_free(yyval.alg);
					yyval.alg = NULL;
					return -1;
				}
			} else {
				if (yyvsp[0].num && check_keylen(cur_algclass, yyvsp[-1].num, yyvsp[0].num) < 0) {
					yyerror("invalid keylen %d", yyvsp[0].num);
					racoon_free(yyval.alg);
					yyval.alg = NULL;
					return -1;
				}
			}

			if (yyvsp[0].num)
				yyval.alg->encklen = yyvsp[0].num;
			else
				yyval.alg->encklen = defklen;

			/* check if it's supported algorithm by kernel */
			if (!(cur_algclass == algclass_ipsec_auth && yyvsp[-1].num == algtype_non_auth)
			 && pk_checkalg(cur_algclass, yyvsp[-1].num, yyval.alg->encklen)) {
				int a = algclass2doi(cur_algclass);
				int b = algtype2doi(cur_algclass, yyvsp[-1].num);
				if (a == IPSECDOI_ATTR_AUTH)
					a = IPSECDOI_PROTO_IPSEC_AH;
				yyerror("algorithm %s not supported by the kernel (missing module?)",
					s_ipsecdoi_trns(a, b));
				racoon_free(yyval.alg);
				yyval.alg = NULL;
				return -1;
			}
		}
    break;
case 131:
#line 914 "./cfparse.y"
{ yyval.num = ~0; }
    break;
case 132:
#line 915 "./cfparse.y"
{ yyval.num = yyvsp[0].num; }
    break;
case 133:
#line 918 "./cfparse.y"
{ yyval.num = IPSEC_PORT_ANY; }
    break;
case 134:
#line 919 "./cfparse.y"
{ yyval.num = yyvsp[0].num; }
    break;
case 135:
#line 920 "./cfparse.y"
{ yyval.num = IPSEC_PORT_ANY; }
    break;
case 136:
#line 923 "./cfparse.y"
{ yyval.num = yyvsp[0].num; }
    break;
case 137:
#line 924 "./cfparse.y"
{ yyval.num = yyvsp[0].num; }
    break;
case 138:
#line 925 "./cfparse.y"
{ yyval.num = IPSEC_ULPROTO_ANY; }
    break;
case 139:
#line 928 "./cfparse.y"
{ yyval.num = 0; }
    break;
case 140:
#line 929 "./cfparse.y"
{ yyval.num = yyvsp[0].num; }
    break;
case 141:
#line 935 "./cfparse.y"
{
			struct remoteconf *new;
			struct proposalspec *prspec;

			new = copyrmconf(yyvsp[0].saddr);
			if (new == NULL) {
				yyerror("failed to get remoteconf for %s.", saddr2str (yyvsp[0].saddr));
				return -1;
			}

			new->remote = yyvsp[-2].saddr;
			new->inherited_from = getrmconf_strict(yyvsp[0].saddr, 1);
			new->proposal = NULL;
			new->prhead = NULL;
			cur_rmconf = new;

			prspec = newprspec();
			if (prspec == NULL || !cur_rmconf->inherited_from 
				|| !cur_rmconf->inherited_from->proposal)
				return -1;
			prspec->lifetime = cur_rmconf->inherited_from->proposal->lifetime;
			prspec->lifebyte = cur_rmconf->inherited_from->proposal->lifebyte;
			insprspec(prspec, &cur_rmconf->prhead);
		}
    break;
case 143:
#line 961 "./cfparse.y"
{
			struct remoteconf *new;
			struct proposalspec *prspec;

			new = newrmconf();
			if (new == NULL) {
				yyerror("failed to get new remoteconf.");
				return -1;
			}

			new->remote = yyvsp[0].saddr;
			cur_rmconf = new;

			prspec = newprspec();
			if (prspec == NULL)
				return -1;
			prspec->lifetime = oakley_get_defaultlifetime();
			insprspec(prspec, &cur_rmconf->prhead);
		}
    break;
case 145:
#line 985 "./cfparse.y"
{
			/* check a exchange mode */
			if (cur_rmconf->etypes == NULL) {
				yyerror("no exchange mode specified.\n");
				return -1;
			}

			if (cur_rmconf->idvtype == IDTYPE_UNDEFINED)
				cur_rmconf->idvtype = IDTYPE_ADDRESS;


			if (cur_rmconf->idvtype == IDTYPE_ASN1DN) {
				if (cur_rmconf->mycertfile) {
					if (cur_rmconf->idv)
						yywarn("Both CERT and ASN1 ID "
						       "are set. Hope this is OK.\n");
					/* TODO: Preparse the DN here */
				} else if (cur_rmconf->idv) {
					/* OK, using asn1dn without X.509. */
				} else {
					yyerror("ASN1 ID not specified "
						"and no CERT defined!\n");
					return -1;
				}
			}
			
			if (cur_rmconf->prhead->spspec == NULL
				&& cur_rmconf->inherited_from
				&& cur_rmconf->inherited_from->prhead) {
				cur_rmconf->prhead->spspec = cur_rmconf->inherited_from->prhead->spspec;
			}
			if (set_isakmp_proposal(cur_rmconf, cur_rmconf->prhead) != 0)
				return -1;

			/* DH group settting if aggressive mode is there. */
			if (check_etypeok(cur_rmconf, ISAKMP_ETYPE_AGG) != NULL) {
				struct isakmpsa *p;
				int b = 0;

				/* DH group */
				for (p = cur_rmconf->proposal; p; p = p->next) {
					if (b == 0 || (b && b == p->dh_group)) {
						b = p->dh_group;
						continue;
					}
					yyerror("DH group must be equal "
						"in all proposals "
						"when aggressive mode is "
						"used.\n");
					return -1;
				}
				cur_rmconf->dh_group = b;

				if (cur_rmconf->dh_group == 0) {
					yyerror("DH group must be set in the proposal.\n");
					return -1;
				}

				/* DH group settting if PFS is required. */
				if (oakley_setdhgroup(cur_rmconf->dh_group,
						&cur_rmconf->dhgrp) < 0) {
					yyerror("failed to set DH value.\n");
					return -1;
				}
			}

			insrmconf(cur_rmconf);
		}
    break;
case 146:
#line 1056 "./cfparse.y"
{
			yyval.saddr = newsaddr(sizeof(struct sockaddr));
			yyval.saddr->sa_family = AF_UNSPEC;
			((struct sockaddr_in *)yyval.saddr)->sin_port = htons(yyvsp[0].num);
		}
    break;
case 147:
#line 1062 "./cfparse.y"
{
			yyval.saddr = yyvsp[0].saddr;
			if (yyval.saddr == NULL) {
				yyerror("failed to allocate sockaddr");
				return -1;
			}
		}
    break;
case 150:
#line 1076 "./cfparse.y"
{
			cur_rmconf->etypes = NULL;
		}
    break;
case 152:
#line 1080 "./cfparse.y"
{ cur_rmconf->doitype = yyvsp[0].num; }
    break;
case 154:
#line 1081 "./cfparse.y"
{ cur_rmconf->sittype = yyvsp[0].num; }
    break;
case 157:
#line 1084 "./cfparse.y"
{
			yywarn("This directive without certtype will be removed!\n");
			yywarn("Please use 'peers_certfile x509 \"%s\";' instead\n", yyvsp[0].val->v);
			cur_rmconf->getcert_method = ISAKMP_GETCERT_LOCALFILE;
			cur_rmconf->peerscertfile = strdup(yyvsp[0].val->v);
			vfree(yyvsp[0].val);
		}
    break;
case 159:
#line 1093 "./cfparse.y"
{
			cur_rmconf->cacerttype = yyvsp[-1].num;
			cur_rmconf->getcacert_method = ISAKMP_GETCERT_LOCALFILE;
			cur_rmconf->cacertfile = strdup(yyvsp[0].val->v);
			vfree(yyvsp[0].val);
		}
    break;
case 161:
#line 1101 "./cfparse.y"
{
			cur_rmconf->getcert_method = ISAKMP_GETCERT_LOCALFILE;
			cur_rmconf->peerscertfile = strdup(yyvsp[0].val->v);
			vfree(yyvsp[0].val);
		}
    break;
case 163:
#line 1108 "./cfparse.y"
{
			char path[MAXPATHLEN];
			int ret = 0;

			getpathname(path, sizeof(path),
				LC_PATHTYPE_CERT, yyvsp[0].val->v);
			vfree(yyvsp[0].val);

			if (cur_rmconf->getcert_method == ISAKMP_GETCERT_DNS) {
				yyerror("Different peers_certfile method "
					"already defined: %d!\n",
					cur_rmconf->getcert_method);
				return -1;
			}
			cur_rmconf->getcert_method = ISAKMP_GETCERT_LOCALFILE;
			if (rsa_parse_file(cur_rmconf->rsa_public, path, RSA_TYPE_PUBLIC)) {
				yyerror("Couldn't parse keyfile.\n", path);
				return -1;
			}
			plog(LLV_DEBUG, LOCATION, NULL, "Public PlainRSA keyfile parsed: %s\n", path);
		}
    break;
case 165:
#line 1131 "./cfparse.y"
{
			if (cur_rmconf->getcert_method) {
				yyerror("Different peers_certfile method already defined!\n");
				return -1;
			}
			cur_rmconf->getcert_method = ISAKMP_GETCERT_DNS;
			cur_rmconf->peerscertfile = NULL;
		}
    break;
case 167:
#line 1140 "./cfparse.y"
{ cur_rmconf->verify_cert = yyvsp[0].num; }
    break;
case 169:
#line 1141 "./cfparse.y"
{ cur_rmconf->send_cert = yyvsp[0].num; }
    break;
case 171:
#line 1142 "./cfparse.y"
{ cur_rmconf->send_cr = yyvsp[0].num; }
    break;
case 173:
#line 1144 "./cfparse.y"
{
			if (set_identifier(&cur_rmconf->idv, yyvsp[-1].num, yyvsp[0].val) != 0) {
				yyerror("failed to set identifer.\n");
				return -1;
			}
			cur_rmconf->idvtype = yyvsp[-1].num;
		}
    break;
case 175:
#line 1153 "./cfparse.y"
{
#ifdef ENABLE_HYBRID
			/* formerly identifier type login */
			if (set_identifier(&cur_rmconf->idv, IDTYPE_LOGIN, yyvsp[0].val) != 0) {
				yyerror("failed to set identifer.\n");
				return -1;
			}
			/* cur_rmconf->use_xauth = 1; */
#else
			yyerror("racoon not configured with --enable-hybrid");
#endif
		}
    break;
case 177:
#line 1167 "./cfparse.y"
{
			struct idspec  *id;
			id = newidspec();
			if (id == NULL) {
				yyerror("failed to allocate idspec");
				return -1;
			}
			if (set_identifier(&id->id, yyvsp[-1].num, yyvsp[0].val) != 0) {
				yyerror("failed to set identifer.\n");
				racoon_free(id);
				return -1;
			}
			id->idtype = yyvsp[-1].num;
			genlist_append (cur_rmconf->idvl_p, id);
		}
    break;
case 179:
#line 1183 "./cfparse.y"
{ cur_rmconf->verify_identifier = yyvsp[0].num; }
    break;
case 181:
#line 1184 "./cfparse.y"
{ cur_rmconf->nonce_size = yyvsp[0].num; }
    break;
case 183:
#line 1186 "./cfparse.y"
{
			yyerror("dh_group cannot be defined here.");
			return -1;
		}
    break;
case 185:
#line 1191 "./cfparse.y"
{ cur_rmconf->passive = yyvsp[0].num; }
    break;
case 187:
#line 1192 "./cfparse.y"
{ cur_rmconf->ike_frag = yyvsp[0].num; }
    break;
case 189:
#line 1193 "./cfparse.y"
{ 
			cur_rmconf->script[SCRIPT_PHASE1_UP] = vdup(yyvsp[-1].val);
		}
    break;
case 191:
#line 1196 "./cfparse.y"
{ 
			cur_rmconf->script[SCRIPT_PHASE1_DOWN] = vdup(yyvsp[-1].val);
		}
    break;
case 193:
#line 1199 "./cfparse.y"
{ cur_rmconf->mode_cfg = yyvsp[0].num; }
    break;
case 195:
#line 1200 "./cfparse.y"
{ cur_rmconf->gen_policy = yyvsp[0].num; }
    break;
case 197:
#line 1201 "./cfparse.y"
{ cur_rmconf->support_proxy = yyvsp[0].num; }
    break;
case 199:
#line 1202 "./cfparse.y"
{ cur_rmconf->ini_contact = yyvsp[0].num; }
    break;
case 201:
#line 1204 "./cfparse.y"
{
#ifdef ENABLE_NATT
			cur_rmconf->nat_traversal = yyvsp[0].num;
#else
			yyerror("NAT-T support not compiled in.");
#endif
		}
    break;
case 203:
#line 1212 "./cfparse.y"
{
#ifdef ENABLE_NATT
			cur_rmconf->nat_traversal = yyvsp[0].num;
#else
			yyerror("NAT-T support not compiled in.");
#endif
		}
    break;
case 205:
#line 1220 "./cfparse.y"
{
#ifdef ENABLE_DPD
			cur_rmconf->dpd = yyvsp[0].num;
#else
			yyerror("DPD support not compiled in.");
#endif
		}
    break;
case 207:
#line 1228 "./cfparse.y"
{
#ifdef ENABLE_DPD
			cur_rmconf->dpd_interval = yyvsp[0].num;
#else
			yyerror("DPD support not compiled in.");
#endif
		}
    break;
case 209:
#line 1237 "./cfparse.y"
{
#ifdef ENABLE_DPD
			cur_rmconf->dpd_retry = yyvsp[0].num;
#else
			yyerror("DPD support not compiled in.");
#endif
		}
    break;
case 211:
#line 1246 "./cfparse.y"
{
#ifdef ENABLE_DPD
			cur_rmconf->dpd_maxfails = yyvsp[0].num;
#else
			yyerror("DPD support not compiled in.");
#endif
		}
    break;
case 213:
#line 1255 "./cfparse.y"
{
			cur_rmconf->prhead->lifetime = yyvsp[-1].num * yyvsp[0].num;
		}
    break;
case 215:
#line 1259 "./cfparse.y"
{ cur_rmconf->pcheck_level = yyvsp[0].num; }
    break;
case 217:
#line 1261 "./cfparse.y"
{
#if 1
			yyerror("byte lifetime support is deprecated in Phase1");
			return -1;
#else
			yywarn("the lifetime of bytes in phase 1 "
				"will be ignored at the moment.");
			cur_rmconf->prhead->lifebyte = fix_lifebyte(yyvsp[-1].num * yyvsp[0].num);
			if (cur_rmconf->prhead->lifebyte == 0)
				return -1;
#endif
		}
    break;
case 219:
#line 1275 "./cfparse.y"
{
			struct secprotospec *spspec;

			spspec = newspspec();
			if (spspec == NULL)
				return -1;
			insspspec(spspec, &cur_rmconf->prhead);
		}
    break;
case 222:
#line 1288 "./cfparse.y"
{
			struct etypes *new;
			new = racoon_malloc(sizeof(struct etypes));
			if (new == NULL) {
				yyerror("filed to allocate etypes");
				return -1;
			}
			new->type = yyvsp[0].num;
			new->next = NULL;
			if (cur_rmconf->etypes == NULL)
				cur_rmconf->etypes = new;
			else {
				struct etypes *p;
				for (p = cur_rmconf->etypes;
				     p->next != NULL;
				     p = p->next)
					;
				p->next = new;
			}
		}
    break;
case 223:
#line 1311 "./cfparse.y"
{
			cur_rmconf->certtype = yyvsp[-2].num;
			cur_rmconf->mycertfile = strdup(yyvsp[-1].val->v);
			vfree(yyvsp[-1].val);
			cur_rmconf->myprivfile = strdup(yyvsp[0].val->v);
			vfree(yyvsp[0].val);
		}
    break;
case 225:
#line 1320 "./cfparse.y"
{
			char path[MAXPATHLEN];
			int ret = 0;

			getpathname(path, sizeof(path),
				LC_PATHTYPE_CERT, yyvsp[0].val->v);
			vfree(yyvsp[0].val);

			cur_rmconf->certtype = yyvsp[-1].num;
			cur_rmconf->send_cr = FALSE;
			cur_rmconf->send_cert = FALSE;
			cur_rmconf->verify_cert = FALSE;
			if (rsa_parse_file(cur_rmconf->rsa_private, path, RSA_TYPE_PRIVATE)) {
				yyerror("Couldn't parse keyfile.\n", path);
				return -1;
			}
			plog(LLV_DEBUG, LOCATION, NULL, "Private PlainRSA keyfile parsed: %s\n", path);
		}
    break;
case 227:
#line 1342 "./cfparse.y"
{
			yyval.num = algtype2doi(algclass_isakmp_dh, yyvsp[0].num);
			if (yyval.num == -1) {
				yyerror("must be DH group");
				return -1;
			}
		}
    break;
case 228:
#line 1350 "./cfparse.y"
{
			if (ARRAYLEN(num2dhgroup) > yyvsp[0].num && num2dhgroup[yyvsp[0].num] != 0) {
				yyval.num = num2dhgroup[yyvsp[0].num];
			} else {
				yyerror("must be DH group");
				yyval.num = 0;
				return -1;
			}
		}
    break;
case 229:
#line 1361 "./cfparse.y"
{ yyval.val = NULL; }
    break;
case 230:
#line 1362 "./cfparse.y"
{ yyval.val = yyvsp[0].val; }
    break;
case 231:
#line 1363 "./cfparse.y"
{ yyval.val = yyvsp[0].val; }
    break;
case 234:
#line 1371 "./cfparse.y"
{
			yyerror("strength directive is obsoleted.");
		}
    break;
case 236:
#line 1375 "./cfparse.y"
{
			cur_rmconf->prhead->spspec->lifetime = yyvsp[-1].num * yyvsp[0].num;
		}
    break;
case 238:
#line 1380 "./cfparse.y"
{
#if 1
			yyerror("byte lifetime support is deprecated");
			return -1;
#else
			cur_rmconf->prhead->spspec->lifebyte = fix_lifebyte(yyvsp[-1].num * yyvsp[0].num);
			if (cur_rmconf->prhead->spspec->lifebyte == 0)
				return -1;
#endif
		}
    break;
case 240:
#line 1392 "./cfparse.y"
{
			cur_rmconf->prhead->spspec->algclass[algclass_isakmp_dh] = yyvsp[0].num;
		}
    break;
case 242:
#line 1397 "./cfparse.y"
{
			if (cur_rmconf->prhead->spspec->vendorid != VENDORID_GSSAPI) {
				yyerror("wrong Vendor ID for gssapi_id");
				return -1;
			}
			cur_rmconf->prhead->spspec->gssid = strdup(yyvsp[0].val->v);
		}
    break;
case 244:
#line 1406 "./cfparse.y"
{
			int doi;
			int defklen;

			doi = algtype2doi(yyvsp[-2].num, yyvsp[-1].num);
			if (doi == -1) {
				yyerror("algorithm mismatched 1");
				return -1;
			}

			switch (yyvsp[-2].num) {
			case algclass_isakmp_enc:
			/* reject suppressed algorithms */
#ifndef HAVE_OPENSSL_RC5_H
				if (yyvsp[-1].num == algtype_rc5) {
					yyerror("algorithm %s not supported",
					    s_attr_isakmp_enc(doi));
					return -1;
				}
#endif
#ifndef HAVE_OPENSSL_IDEA_H
				if (yyvsp[-1].num == algtype_idea) {
					yyerror("algorithm %s not supported",
					    s_attr_isakmp_enc(doi));
					return -1;
				}
#endif

				cur_rmconf->prhead->spspec->algclass[algclass_isakmp_enc] = doi;
				defklen = default_keylen(yyvsp[-2].num, yyvsp[-1].num);
				if (defklen == 0) {
					if (yyvsp[0].num) {
						yyerror("keylen not allowed");
						return -1;
					}
				} else {
					if (yyvsp[0].num && check_keylen(yyvsp[-2].num, yyvsp[-1].num, yyvsp[0].num) < 0) {
						yyerror("invalid keylen %d", yyvsp[0].num);
						return -1;
					}
				}
				if (yyvsp[0].num)
					cur_rmconf->prhead->spspec->encklen = yyvsp[0].num;
				else
					cur_rmconf->prhead->spspec->encklen = defklen;
				break;
			case algclass_isakmp_hash:
				cur_rmconf->prhead->spspec->algclass[algclass_isakmp_hash] = doi;
				break;
			case algclass_isakmp_ameth:
				cur_rmconf->prhead->spspec->algclass[algclass_isakmp_ameth] = doi;
				/*
				 * We may have to set the Vendor ID for the
				 * authentication method we're using.
				 */
				switch (yyvsp[-1].num) {
				case algtype_gssapikrb:
					if (cur_rmconf->prhead->spspec->vendorid !=
					    VENDORID_UNKNOWN) {
						yyerror("Vendor ID mismatch "
						    "for auth method");
						return -1;
					}
					/*
					 * For interoperability with Win2k,
					 * we set the Vendor ID to "GSSAPI".
					 */
					cur_rmconf->prhead->spspec->vendorid =
					    VENDORID_GSSAPI;
					break;
				case algtype_rsasig:
					if (cur_rmconf->certtype == ISAKMP_CERT_PLAINRSA) {
						if (rsa_list_count(cur_rmconf->rsa_private) == 0) {
							yyerror ("Private PlainRSA key not set. "
								"Use directive 'certificate_type plainrsa ...'\n");
							return -1;
						}
						if (rsa_list_count(cur_rmconf->rsa_public) == 0) {
							yyerror ("Public PlainRSA keys not set. "
								"Use directive 'peers_certfile plainrsa ...'\n");
							return -1;
						}
					}
					break;
				default:
					break;
				}
				break;
			default:
				yyerror("algorithm mismatched 2");
				return -1;
			}
		}
    break;
case 246:
#line 1503 "./cfparse.y"
{ yyval.num = 1; }
    break;
case 247:
#line 1504 "./cfparse.y"
{ yyval.num = 60; }
    break;
case 248:
#line 1505 "./cfparse.y"
{ yyval.num = (60 * 60); }
    break;
case 249:
#line 1508 "./cfparse.y"
{ yyval.num = 1; }
    break;
case 250:
#line 1509 "./cfparse.y"
{ yyval.num = 1024; }
    break;
case 251:
#line 1510 "./cfparse.y"
{ yyval.num = (1024 * 1024); }
    break;
case 252:
#line 1511 "./cfparse.y"
{ yyval.num = (1024 * 1024 * 1024); }
    break;
}

#line 705 "/usr/share/bison/bison.simple"


  yyvsp -= yylen;
  yyssp -= yylen;
#if YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;
#if YYLSP_NEEDED
  *++yylsp = yyloc;
#endif

  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  char *yymsg;
	  int yyx, yycount;

	  yycount = 0;
	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  for (yyx = yyn < 0 ? -yyn : 0;
	       yyx < (int) (sizeof (yytname) / sizeof (char *)); yyx++)
	    if (yycheck[yyx + yyn] == yyx)
	      yysize += yystrlen (yytname[yyx]) + 15, yycount++;
	  yysize += yystrlen ("parse error, unexpected ") + 1;
	  yysize += yystrlen (yytname[YYTRANSLATE (yychar)]);
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "parse error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[YYTRANSLATE (yychar)]);

	      if (yycount < 5)
		{
		  yycount = 0;
		  for (yyx = yyn < 0 ? -yyn : 0;
		       yyx < (int) (sizeof (yytname) / sizeof (char *));
		       yyx++)
		    if (yycheck[yyx + yyn] == yyx)
		      {
			const char *yyq = ! yycount ? ", expecting " : " or ";
			yyp = yystpcpy (yyp, yyq);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yycount++;
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exhausted");
	}
      else
#endif /* defined (YYERROR_VERBOSE) */
	yyerror ("parse error");
    }
  goto yyerrlab1;


/*--------------------------------------------------.
| yyerrlab1 -- error raised explicitly by an action |
`--------------------------------------------------*/
yyerrlab1:
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;
      YYDPRINTF ((stderr, "Discarding token %d (%s).\n",
		  yychar, yytname[yychar1]));
      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;


/*-------------------------------------------------------------------.
| yyerrdefault -- current state does not do anything special for the |
| error token.                                                       |
`-------------------------------------------------------------------*/
yyerrdefault:
#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */

  /* If its default is to accept any token, ok.  Otherwise pop it.  */
  yyn = yydefact[yystate];
  if (yyn)
    goto yydefault;
#endif


/*---------------------------------------------------------------.
| yyerrpop -- pop the current state because it cannot handle the |
| error token                                                    |
`---------------------------------------------------------------*/
yyerrpop:
  if (yyssp == yyss)
    YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#if YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG
  if (yydebug)
    {
      short *yyssp1 = yyss - 1;
      YYFPRINTF (stderr, "Error: state stack now");
      while (yyssp1 != yyssp)
	YYFPRINTF (stderr, " %d", *++yyssp1);
      YYFPRINTF (stderr, "\n");
    }
#endif

/*--------------.
| yyerrhandle.  |
`--------------*/
yyerrhandle:
  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;
#if YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

/*---------------------------------------------.
| yyoverflowab -- parser overflow comes here.  |
`---------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}
#line 1513 "./cfparse.y"


static struct proposalspec *
newprspec()
{
	struct proposalspec *new;

	new = racoon_calloc(1, sizeof(*new));
	if (new == NULL)
		yyerror("failed to allocate proposal");

	return new;
}

/*
 * insert into head of list.
 */
static void
insprspec(prspec, head)
	struct proposalspec *prspec;
	struct proposalspec **head;
{
	if (*head != NULL)
		(*head)->prev = prspec;
	prspec->next = *head;
	*head = prspec;
}

static struct secprotospec *
newspspec()
{
	struct secprotospec *new;

	new = racoon_calloc(1, sizeof(*new));
	if (new == NULL) {
		yyerror("failed to allocate spproto");
		return NULL;
	}

	new->encklen = 0;	/*XXX*/

	/*
	 * Default to "uknown" vendor -- we will override this
	 * as necessary.  When we send a Vendor ID payload, an
	 * "unknown" will be translated to a KAME/racoon ID.
	 */
	new->vendorid = VENDORID_UNKNOWN;

	return new;
}

/*
 * insert into head of list.
 */
static void
insspspec(spspec, head)
	struct secprotospec *spspec;
	struct proposalspec **head;
{
	spspec->back = *head;

	if ((*head)->spspec != NULL)
		(*head)->spspec->prev = spspec;
	spspec->next = (*head)->spspec;
	(*head)->spspec = spspec;
}

/* set final acceptable proposal */
static int
set_isakmp_proposal(rmconf, prspec)
	struct remoteconf *rmconf;
	struct proposalspec *prspec;
{
	struct proposalspec *p;
	struct secprotospec *s;
	int prop_no = 1; 
	int trns_no = 1;
	u_int32_t types[MAXALGCLASS];

	p = prspec;
	if (p->next != 0) {
		plog(LLV_ERROR, LOCATION, NULL,
			"multiple proposal definition.\n");
		return -1;
	}

	/* mandatory check */
	if (p->spspec == NULL) {
		yyerror("no remote specification found: %s.\n",
			saddr2str(rmconf->remote));
		return -1;
	}
	for (s = p->spspec; s != NULL; s = s->next) {
		/* XXX need more to check */
		if (s->algclass[algclass_isakmp_enc] == 0) {
			yyerror("encryption algorithm required.");
			return -1;
		}
		if (s->algclass[algclass_isakmp_hash] == 0) {
			yyerror("hash algorithm required.");
			return -1;
		}
		if (s->algclass[algclass_isakmp_dh] == 0) {
			yyerror("DH group required.");
			return -1;
		}
		if (s->algclass[algclass_isakmp_ameth] == 0) {
			yyerror("authentication method required.");
			return -1;
		}
	}

	/* skip to last part */
	for (s = p->spspec; s->next != NULL; s = s->next)
		;

	while (s != NULL) {
		plog(LLV_DEBUG2, LOCATION, NULL,
			"lifetime = %ld\n", (long)
			(s->lifetime ? s->lifetime : p->lifetime));
		plog(LLV_DEBUG2, LOCATION, NULL,
			"lifebyte = %d\n",
			s->lifebyte ? s->lifebyte : p->lifebyte);
		plog(LLV_DEBUG2, LOCATION, NULL,
			"encklen=%d\n", s->encklen);

		memset(types, 0, ARRAYLEN(types));
		types[algclass_isakmp_enc] = s->algclass[algclass_isakmp_enc];
		types[algclass_isakmp_hash] = s->algclass[algclass_isakmp_hash];
		types[algclass_isakmp_dh] = s->algclass[algclass_isakmp_dh];
		types[algclass_isakmp_ameth] =
		    s->algclass[algclass_isakmp_ameth];

		/* expanding spspec */
		clean_tmpalgtype();
		trns_no = expand_isakmpspec(prop_no, trns_no, types,
				algclass_isakmp_enc, algclass_isakmp_ameth + 1,
				s->lifetime ? s->lifetime : p->lifetime,
				s->lifebyte ? s->lifebyte : p->lifebyte,
				s->encklen, s->vendorid, s->gssid,
				rmconf);
		if (trns_no == -1) {
			plog(LLV_ERROR, LOCATION, NULL,
				"failed to expand isakmp proposal.\n");
			return -1;
		}

		s = s->prev;
	}

	if (rmconf->proposal == NULL) {
		plog(LLV_ERROR, LOCATION, NULL,
			"no proposal found.\n");
		return -1;
	}

	return 0;
}

static void
clean_tmpalgtype()
{
	int i;
	for (i = 0; i < MAXALGCLASS; i++)
		tmpalgtype[i] = 0;	/* means algorithm undefined. */
}

static int
expand_isakmpspec(prop_no, trns_no, types,
		class, last, lifetime, lifebyte, encklen, vendorid, gssid,
		rmconf)
	int prop_no, trns_no;
	int *types, class, last;
	time_t lifetime;
	int lifebyte;
	int encklen;
	int vendorid;
	char *gssid;
	struct remoteconf *rmconf;
{
	struct isakmpsa *new;

	/* debugging */
    {
	int j;
	char tb[10];
	plog(LLV_DEBUG2, LOCATION, NULL,
		"p:%d t:%d\n", prop_no, trns_no);
	for (j = class; j < MAXALGCLASS; j++) {
		snprintf(tb, sizeof(tb), "%d", types[j]);
		plog(LLV_DEBUG2, LOCATION, NULL,
			"%s%s%s%s\n",
			s_algtype(j, types[j]),
			types[j] ? "(" : "",
			tb[0] == '0' ? "" : tb,
			types[j] ? ")" : "");
	}
	plog(LLV_DEBUG2, LOCATION, NULL, "\n");
    }

#define TMPALGTYPE2STR(n) \
	s_algtype(algclass_isakmp_##n, types[algclass_isakmp_##n])
		/* check mandatory values */
		if (types[algclass_isakmp_enc] == 0
		 || types[algclass_isakmp_ameth] == 0
		 || types[algclass_isakmp_hash] == 0
		 || types[algclass_isakmp_dh] == 0) {
			yyerror("few definition of algorithm "
				"enc=%s ameth=%s hash=%s dhgroup=%s.\n",
				TMPALGTYPE2STR(enc),
				TMPALGTYPE2STR(ameth),
				TMPALGTYPE2STR(hash),
				TMPALGTYPE2STR(dh));
			return -1;
		}
#undef TMPALGTYPE2STR

	/* set new sa */
	new = newisakmpsa();
	if (new == NULL) {
		yyerror("failed to allocate isakmp sa");
		return -1;
	}
	new->prop_no = prop_no;
	new->trns_no = trns_no++;
	new->lifetime = lifetime;
	new->lifebyte = lifebyte;
	new->enctype = types[algclass_isakmp_enc];
	new->encklen = encklen;
	new->authmethod = types[algclass_isakmp_ameth];
	new->hashtype = types[algclass_isakmp_hash];
	new->dh_group = types[algclass_isakmp_dh];
	new->vendorid = vendorid;
#ifdef HAVE_GSSAPI
	if (gssid != NULL) {
		new->gssid = vmalloc(strlen(gssid) + 1);
		memcpy(new->gssid->v, gssid, new->gssid->l);
		racoon_free(gssid);
	} else
		new->gssid = NULL;
#endif
	insisakmpsa(new, rmconf);

	return trns_no;
}

static int
listen_addr (struct sockaddr *addr, int udp_encap)
{
	struct myaddrs *p;

	p = newmyaddr();
	if (p == NULL) {
		yyerror("failed to allocate myaddrs");
		return -1;
	}
	p->addr = addr;
	if (p->addr == NULL) {
		yyerror("failed to copy sockaddr ");
		delmyaddr(p);
		return -1;
	}
	p->udp_encap = udp_encap;

	insmyaddr(p, &lcconf->myaddrs);

	lcconf->autograbaddr = 0;
	return 0;
}

#if 0
/*
 * fix lifebyte.
 * Must be more than 1024B because its unit is kilobytes.
 * That is defined RFC2407.
 */
static int
fix_lifebyte(t)
	unsigned long t;
{
	if (t < 1024) {
		yyerror("byte size should be more than 1024B.");
		return 0;
	}

	return(t / 1024);
}
#endif

int
cfparse()
{
	int error;

	yycf_init_buffer();

	if (yycf_switch_buffer(lcconf->racoon_conf) != 0)
		return -1;

	error = yyparse();
	if (error != 0) {
		if (yyerrorcount) {
			plog(LLV_ERROR, LOCATION, NULL,
				"fatal parse failure (%d errors)\n",
				yyerrorcount);
		} else {
			plog(LLV_ERROR, LOCATION, NULL,
				"fatal parse failure.\n");
		}
		return -1;
	}

	if (error == 0 && yyerrorcount) {
		plog(LLV_ERROR, LOCATION, NULL,
			"parse error is nothing, but yyerrorcount is %d.\n",
				yyerrorcount);
		exit(1);
	}

	yycf_clean_buffer();

	plog(LLV_DEBUG2, LOCATION, NULL, "parse successed.\n");

	return 0;
}

int
cfreparse()
{
	flushph2();
	flushph1();
	flushrmconf();
	flushsainfo();
	clean_tmpalgtype();
	yycf_init_buffer();

	if (yycf_switch_buffer(lcconf->racoon_conf) != 0)
		return -1;

	return(cfparse());
}

#ifdef ENABLE_ADMINPORT
static void
adminsock_conf(path, owner, group, mode_dec)
	vchar_t *path;
	vchar_t *owner;
	vchar_t *group;
	int mode_dec;
{
	struct passwd *pw = NULL;
	struct group *gr = NULL;
	mode_t mode = 0;
	uid_t uid;
	gid_t gid;
	int isnum;

	adminsock_path = path->v;

	if (owner == NULL)
		return;

	errno = 0;
	uid = atoi(owner->v);
	isnum = !errno;
	if (((pw = getpwnam(owner->v)) == NULL) && !isnum)
		yyerror("User \"%s\" does not exist", owner->v);

	if (pw)
		adminsock_owner = pw->pw_uid;
	else
		adminsock_owner = uid;

	if (group == NULL)
		return;

	errno = 0;
	gid = atoi(group->v);
	isnum = !errno;
	if (((gr = getgrnam(group->v)) == NULL) && !isnum)
		yyerror("Group \"%s\" does not exist", group->v);

	if (gr)
		adminsock_group = gr->gr_gid;
	else
		adminsock_group = gid;

	if (mode_dec == -1)
		return;

	if (mode_dec > 777)
		yyerror("Mode 0%03o is invalid", mode_dec);
	if (mode_dec >= 400) { mode += 0400; mode_dec -= 400; }
	if (mode_dec >= 200) { mode += 0200; mode_dec -= 200; }
	if (mode_dec >= 100) { mode += 0200; mode_dec -= 100; }

	if (mode_dec > 77)
		yyerror("Mode 0%03o is invalid", mode_dec);
	if (mode_dec >= 40) { mode += 040; mode_dec -= 40; }
	if (mode_dec >= 20) { mode += 020; mode_dec -= 20; }
	if (mode_dec >= 10) { mode += 020; mode_dec -= 10; }

	if (mode_dec > 7)
		yyerror("Mode 0%03o is invalid", mode_dec);
	if (mode_dec >= 4) { mode += 04; mode_dec -= 4; }
	if (mode_dec >= 2) { mode += 02; mode_dec -= 2; }
	if (mode_dec >= 1) { mode += 02; mode_dec -= 1; }
	
	adminsock_mode = mode;

	return;
}
#endif
