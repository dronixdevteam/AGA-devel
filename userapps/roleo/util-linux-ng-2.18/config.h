/* config.h.  Generated from config.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
/* #undef ENABLE_NLS */

/* search path for fs helpers */
#define FS_SEARCH_PATH "/sbin:/sbin/fs.d:/sbin/fs"

/* Define to 1 if you have the <blkid/blkid.h> header file. */
/* #undef HAVE_BLKID_BLKID_H */

/* Define to 1 if you have the <blkid.h> header file. */
#define HAVE_BLKID_H 1

/* Define to 1 if the system has the type `cpu_set_t'. */
/* #undef HAVE_CPU_SET_T */

/* Define if the GNU dcgettext() function is already present or preinstalled.
   */
/* #undef HAVE_DCGETTEXT */

/* Define to 1 if you have the declaration of `ADDR_COMPAT_LAYOUT', and to 0
   if you don't. */
#define HAVE_DECL_ADDR_COMPAT_LAYOUT 1

/* Define to 1 if you have the declaration of `ADDR_LIMIT_32BIT', and to 0 if
   you don't. */
#define HAVE_DECL_ADDR_LIMIT_32BIT 1

/* Define to 1 if you have the declaration of `ADDR_LIMIT_3GB', and to 0 if
   you don't. */
#define HAVE_DECL_ADDR_LIMIT_3GB 1

/* Define to 1 if you have the declaration of `ADDR_NO_RANDOMIZE', and to 0 if
   you don't. */
#define HAVE_DECL_ADDR_NO_RANDOMIZE 0

/* Define to 1 if you have the declaration of `CPU_ALLOC', and to 0 if you
   don't. */
#define HAVE_DECL_CPU_ALLOC 0

/* Define to 1 if you have the declaration of `FDPIC_FUNCPTRS', and to 0 if
   you don't. */
#define HAVE_DECL_FDPIC_FUNCPTRS 1

/* Define to 1 if you have the declaration of `MMAP_PAGE_ZERO', and to 0 if
   you don't. */
#define HAVE_DECL_MMAP_PAGE_ZERO 1

/* Define to 1 if you have the declaration of `READ_IMPLIES_EXEC', and to 0 if
   you don't. */
#define HAVE_DECL_READ_IMPLIES_EXEC 1

/* Define to 1 if you have the declaration of `STICKY_TIMEOUTS', and to 0 if
   you don't. */
#define HAVE_DECL_STICKY_TIMEOUTS 1

/* Define to 1 if you have the declaration of `WHOLE_SECONDS', and to 0 if you
   don't. */
#define HAVE_DECL_WHOLE_SECONDS 1

/* Define to 1 if you have the declaration of `_NL_TIME_WEEK_1STDAY', and to 0
   if you don't. */
#define HAVE_DECL__NL_TIME_WEEK_1STDAY 0

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <errno.h> header file. */
#define HAVE_ERRNO_H 1

/* Define to 1 if you have the <err.h> header file. */
#define HAVE_ERR_H 1

/* Have valid fallocate() function */
/* #undef HAVE_FALLOCATE */

/* Define to 1 if you have the <fcntl.h> header file. */
#define HAVE_FCNTL_H 1

/* Define to 1 if fseeko (and presumably ftello) exists and is declared. */
#define HAVE_FSEEKO 1

/* Define to 1 if you have the `fstat64' function. */
#define HAVE_FSTAT64 1

/* Define to 1 if you have the `fstatat' function. */
/* #undef HAVE_FSTATAT */

/* Define to 1 if you have the `fsync' function. */
#define HAVE_FSYNC 1

/* Define to 1 if you have the `futimens' function. */
/* #undef HAVE_FUTIMENS */

/* Define to 1 if you have the `getdomainname' function. */
#define HAVE_GETDOMAINNAME 1

/* Define to 1 if you have the `getdtablesize' function. */
#define HAVE_GETDTABLESIZE 1

/* Define to 1 if you have the `getmntinfo' function. */
/* #undef HAVE_GETMNTINFO */

/* Define to 1 if you have the <getopt.h> header file. */
#define HAVE_GETOPT_H 1

/* Define to 1 if you have the `getrlimit' function. */
#define HAVE_GETRLIMIT 1

/* Define if the GNU gettext() function is already present or preinstalled. */
/* #undef HAVE_GETTEXT */

/* Define to 1 if you have the `get_current_dir_name' function. */
#define HAVE_GET_CURRENT_DIR_NAME 1

/* Define if you have the iconv() function. */
/* #undef HAVE_ICONV */

/* Define to 1 if you have the `inet_aton' function. */
#define HAVE_INET_ATON 1

/* Define to 1 if you have the `inotify_init' function. */
/* #undef HAVE_INOTIFY_INIT */

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the `jrand48' function. */
#define HAVE_JRAND48 1

/* Define to 1 if you have the <langinfo.h> header file. */
#define HAVE_LANGINFO_H 1

/* Define to 1 if you have the `lchown' function. */
#define HAVE_LCHOWN 1

/* Define to 1 if you have the `audit' library (-laudit). */
/* #undef HAVE_LIBAUDIT */

/* Define to 1 if you have the -lblkid. */
#define HAVE_LIBBLKID 1

/* Define to 1 if you have the in-tree libblkid. */
#define HAVE_LIBBLKID_INTERNAL 1

/* Define to 1 if you have the `ncurses' library (-lncurses). */
/* #undef HAVE_LIBNCURSES */

/* Define to 1 if you have the `ncursesw' library (-lncursesw). */
/* #undef HAVE_LIBNCURSESW */

/* Define to 1 if you have the `selinux' library (-lselinux). */
/* #undef HAVE_LIBSELINUX */

/* Define to 1 if you have the `termcap' library (-ltermcap). */
/* #undef HAVE_LIBTERMCAP */

/* Define to 1 if you have the `utempter' library (-lutempter). */
/* #undef HAVE_LIBUTEMPTER */

/* Define to 1 if you have the `util' library (-lutil). */
#define HAVE_LIBUTIL 1

/* Define to 1 if you have the -luuid. */
#define HAVE_LIBUUID 1

/* Define to 1 if you have the `z' library (-lz). */
/* #undef HAVE_LIBZ */

/* Define to 1 if you have the <linux/blkpg.h> header file. */
#define HAVE_LINUX_BLKPG_H 1

/* Define to 1 if you have the <linux/cdrom.h> header file. */
#define HAVE_LINUX_CDROM_H 1

/* Define to 1 if you have the <linux/compiler.h> header file. */
#define HAVE_LINUX_COMPILER_H 1

/* Define to 1 if you have the <linux/falloc.h> header file. */
/* #undef HAVE_LINUX_FALLOC_H */

/* Define to 1 if you have the <linux/fd.h> header file. */
#define HAVE_LINUX_FD_H 1

/* Define to 1 if you have the <linux/major.h> header file. */
#define HAVE_LINUX_MAJOR_H 1

/* Define to 1 if you have the <linux/raw.h> header file. */
#define HAVE_LINUX_RAW_H 1

/* Define to 1 if you have the <linux/tiocl.h> header file. */
#define HAVE_LINUX_TIOCL_H 1

/* Define to 1 if you have the <linux/version.h> header file. */
#define HAVE_LINUX_VERSION_H 1

/* Define to 1 if you have the `llseek' function. */
#define HAVE_LLSEEK 1

/* Define to 1 if have llseek prototype */
/* #undef HAVE_LLSEEK_PROTOTYPE */

/* Define to 1 if you have the <locale.h> header file. */
#define HAVE_LOCALE_H 1

/* Define to 1 if you have the `lseek64' function. */
#define HAVE_LSEEK64 1

/* Define to 1 if have lseek64 prototype */
#define HAVE_LSEEK64_PROTOTYPE 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <mntent.h> header file. */
#define HAVE_MNTENT_H 1

/* Define to 1 if you have the `nanosleep' function. */
#define HAVE_NANOSLEEP 1

/* Define to 1 if you have the <ncurses.h> header file. */
/* #undef HAVE_NCURSES_H */

/* Define to 1 if you have the <ncurses/ncurses.h> header file. */
/* #undef HAVE_NCURSES_NCURSES_H */

/* Define to 1 if you have the <netinet/in.h> header file. */
#define HAVE_NETINET_IN_H 1

/* Define to 1 if you have the <net/if_dl.h> header file. */
/* #undef HAVE_NET_IF_DL_H */

/* Define to 1 if you have the <net/if.h> header file. */
#define HAVE_NET_IF_H 1

/* Define to 1 if you have the `openat' function. */
/* #undef HAVE_OPENAT */

/* Define to 1 if you have the `personality' function. */
#define HAVE_PERSONALITY 1

/* Define to 1 if you have the `posix_fadvise' function. */
#define HAVE_POSIX_FADVISE 1

/* Define to 1 if you have the `prctl' function. */
#define HAVE_PRCTL 1

/* Define to 1 if you have the <pty.h> header file. */
#define HAVE_PTY_H 1

/* Define to 1 if you have the <rpcsvc/nfs_prot.h> header file. */
/* #undef HAVE_RPCSVC_NFS_PROT_H */

/* Define to 1 if you have the `rpmatch' function. */
/* #undef HAVE_RPMATCH */

/* Define if struct sockaddr contains sa_len */
/* #undef HAVE_SA_LEN */

/* Define to 1 if you have the `security_get_initial_context' function. */
/* #undef HAVE_SECURITY_GET_INITIAL_CONTEXT */

/* Define to 1 if you have the <security/pam_misc.h> header file. */
/* #undef HAVE_SECURITY_PAM_MISC_H */

/* Define to 1 if you have the `setresgid' function. */
#define HAVE_SETRESGID 1

/* Define to 1 if you have the `setresuid' function. */
#define HAVE_SETRESUID 1

/* Define to 1 if you have the <slang/slcurses.h> header file. */
/* #undef HAVE_SLANG_SLCURSES_H */

/* Define to 1 if you have the <slcurses.h> header file. */
/* #undef HAVE_SLCURSES_H */

/* Define to 1 if you have the `srandom' function. */
#define HAVE_SRANDOM 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the `strnchr' function. */
/* #undef HAVE_STRNCHR */

/* Define to 1 if you have the `strndup' function. */
#define HAVE_STRNDUP 1

/* Define to 1 if you have the `strnlen' function. */
#define HAVE_STRNLEN 1

/* Define to 1 if you have the `strtoull' function. */
#define HAVE_STRTOULL 1

/* Define to 1 if `st_mtim.tv_nsec' is member of `struct stat'. */
/* #undef HAVE_STRUCT_STAT_ST_MTIM_TV_NSEC */

/* Define to 1 if `c_line' is member of `struct termios'. */
#define HAVE_STRUCT_TERMIOS_C_LINE 1

/* Define to 1 if you have the `sysconf' function. */
#define HAVE_SYSCONF 1

/* Define to 1 if you have the <sys/disklabel.h> header file. */
/* #undef HAVE_SYS_DISKLABEL_H */

/* Define to 1 if you have the <sys/disk.h> header file. */
/* #undef HAVE_SYS_DISK_H */

/* Define to 1 if you have the <sys/file.h> header file. */
#define HAVE_SYS_FILE_H 1

/* Define to 1 if you have the <sys/ioctl.h> header file. */
#define HAVE_SYS_IOCTL_H 1

/* Define to 1 if you have the <sys/io.h> header file. */
/* #undef HAVE_SYS_IO_H */

/* Define to 1 if you have the <sys/mkdev.h> header file. */
/* #undef HAVE_SYS_MKDEV_H */

/* Define to 1 if you have the <sys/prctl.h> header file. */
#define HAVE_SYS_PRCTL_H 1

/* Define to 1 if you have the <sys/queue.h> header file. */
#define HAVE_SYS_QUEUE_H 1

/* Define to 1 if you have the <sys/resource.h> header file. */
#define HAVE_SYS_RESOURCE_H 1

/* Define to 1 if you have the <sys/socket.h> header file. */
#define HAVE_SYS_SOCKET_H 1

/* Define to 1 if you have the <sys/sockio.h> header file. */
/* #undef HAVE_SYS_SOCKIO_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/swap.h> header file. */
#define HAVE_SYS_SWAP_H 1

/* Define to 1 if you have the <sys/syscall.h> header file. */
#define HAVE_SYS_SYSCALL_H 1

/* Define to 1 if you have the <sys/time.h> header file. */
#define HAVE_SYS_TIME_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <sys/un.h> header file. */
#define HAVE_SYS_UN_H 1

/* Define to 1 if you have the <sys/user.h> header file. */
#define HAVE_SYS_USER_H 1

/* Define to 1 if the target supports thread-local storage. */
/* #undef HAVE_TLS */

/* Does struct tm have a field tm_gmtoff? */
#define HAVE_TM_GMTOFF 1

/* Define to 1 if the system has the type `union semun'. */
/* #undef HAVE_UNION_SEMUN */

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* Define to 1 if you have the `unlinkat' function. */
/* #undef HAVE_UNLINKAT */

/* Define to 1 if you have the `unshare' function. */
/* #undef HAVE_UNSHARE */

/* Define to 1 if you have the `updwtmp' function. */
#define HAVE_UPDWTMP 1

/* Define to 1 if you have the `usleep' function. */
#define HAVE_USLEEP 1

/* Define to 1 if you want to use uuid daemon. */
#define HAVE_UUIDD 1

/* Define to 1 if you have the <uuid.h> header file. */
#define HAVE_UUID_H 1

/* Define to 1 if you have the <uuid/uuid.h> header file. */
/* #undef HAVE_UUID_UUID_H */

/* Do we have wide character support? */
#define HAVE_WIDECHAR 1

/* Do we have __progname? */
/* #undef HAVE___PROGNAME */

/* Define to 1 if you have the `__secure_getenv' function. */
/* #undef HAVE___SECURE_GETENV */

/* libblkid date string */
#define LIBBLKID_DATE "30-Jun-2010"

/* libblkid version string */
#define LIBBLKID_VERSION "2.18.0"

/* libmount version string */
#define LIBMOUNT_VERSION "2.18.0"

/* Should login chown /dev/vcsN? */
/* #undef LOGIN_CHOWN_VCS */

/* Should login stat() the mailbox? */
/* #undef LOGIN_STAT_MAIL */

/* Define to the sub-directory in which libtool stores uninstalled libraries.
   */
#define LT_OBJDIR ".libs/"

/* Do we need -lcrypt? */
#define NEED_LIBCRYPT 1

/* Should chsh allow only shells in /etc/shells? */
#define ONLY_LISTED_SHELLS 1

/* Name of package */
#define PACKAGE "util-linux-ng"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "kzak@redhat.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "util-linux-ng"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "util-linux-ng 2.18"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "util-linux-ng"

/* Define to the version of this package. */
#define PACKAGE_VERSION "2.18"

/* Should pg ring the bell on invalid keys? */
#define PG_BELL 1

/* Should chfn and chsh require the user to enter the password? */
#define REQUIRE_PASSWORD 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Is swapon() declared with two parameters? */
#define SWAPON_HAS_TWO_ARGS 1

/* Fallback syscall number for fallocate */
/* #undef SYS_fallocate */

/* Fallback syscall number for ioprio_get */
/* #undef SYS_ioprio_get */

/* Fallback syscall number for ioprio_set */
/* #undef SYS_ioprio_set */

/* Fallback syscall number for pivot_root */
/* #undef SYS_pivot_root */

/* Fallback syscall number for sched_getaffinity */
/* #undef SYS_sched_getaffinity */

/* Fallback syscall number for unshare */
/* #undef SYS_unshare */

/* Enable extensions on AIX 3, Interix.  */
#ifndef _ALL_SOURCE
# define _ALL_SOURCE 1
#endif
/* Enable GNU extensions on systems that have them.  */
#ifndef _GNU_SOURCE
# define _GNU_SOURCE 1
#endif
/* Enable threading extensions on Solaris.  */
#ifndef _POSIX_PTHREAD_SEMANTICS
# define _POSIX_PTHREAD_SEMANTICS 1
#endif
/* Enable extensions on HP NonStop.  */
#ifndef _TANDEM_SOURCE
# define _TANDEM_SOURCE 1
#endif
/* Enable general extensions on Solaris.  */
#ifndef __EXTENSIONS__
# define __EXTENSIONS__ 1
#endif


/* Should wall and write be installed setgid tty? */
#define USE_TTY_GROUP 1

/* Version number of package */
#define VERSION "2.18"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
#  define WORDS_BIGENDIAN 1
# endif
#endif

/* Number of bits in a file offset, on hosts where this is settable. */
#define _FILE_OFFSET_BITS 64

/* Define to 1 to make fseeko visible on some hosts (e.g. glibc 2.2). */
/* #undef _LARGEFILE_SOURCE */

/* Define for large files, on AIX-style hosts. */
/* #undef _LARGE_FILES */

/* Define to 1 if on MINIX. */
/* #undef _MINIX */

/* Define to 2 if the system does not provide POSIX.1 features except with
   this defined. */
/* #undef _POSIX_1_SOURCE */

/* Define to 1 if you need to in order for `stat' and other things to work. */
/* #undef _POSIX_SOURCE */

/* Define to empty if `const' does not conform to ANSI C. */
/* #undef const */

/* Define to empty if the keyword `volatile' does not work. Warning: valid
   code using `volatile' can become incorrect without. Disable with care. */
/* #undef volatile */
