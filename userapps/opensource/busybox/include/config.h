/*
 * Automatically generated header file: don't edit
 */

#define AUTOCONF_INCLUDED

/* Version Number */
#define BB_VER "1.00"
#define BB_BT "2011.02.22-20:09+0000"

#define HAVE_DOT_CONFIG 1

/*
 * General Configuration
 */
#undef CONFIG_FEATURE_BUFFERS_USE_MALLOC
#define CONFIG_FEATURE_BUFFERS_GO_ON_STACK 1
#undef CONFIG_FEATURE_BUFFERS_GO_IN_BSS
#define CONFIG_FEATURE_VERBOSE_USAGE 1
#undef CONFIG_FEATURE_INSTALLER
#undef CONFIG_LOCALE_SUPPORT
#undef CONFIG_FEATURE_DEVFS
#undef CONFIG_FEATURE_DEVPTS
#undef CONFIG_FEATURE_CLEAN_UP
#define CONFIG_FEATURE_SUID 1
#undef CONFIG_FEATURE_SUID_CONFIG
#undef CONFIG_SELINUX

/*
 * Build Options
 */
#undef CONFIG_STATIC
#define CONFIG_LFS 1
#define USING_CROSS_COMPILER 1
#define CROSS_COMPILER_PREFIX "/opt/toolchains/uclibc-crosstools_gcc-3.4.2_uclibc-20050502/bin/mips-linux-uclibc-"
#define EXTRA_CFLAGS_OPTIONS ""

/*
 * Installation Options
 */
#undef CONFIG_INSTALL_NO_USR
#define PREFIX "./_install"

/*
 * Archival Utilities
 */
#undef CONFIG_AR
#define CONFIG_BUNZIP2 1
#undef CONFIG_CPIO
#undef CONFIG_DPKG
#undef CONFIG_DPKG_DEB
#define CONFIG_GUNZIP 1
#undef CONFIG_FEATURE_GUNZIP_UNCOMPRESS
#define CONFIG_GZIP 1
#undef CONFIG_RPM2CPIO
#undef CONFIG_RPM
#define CONFIG_TAR 1
#define CONFIG_FEATURE_TAR_CREATE 1
#undef CONFIG_FEATURE_TAR_BZIP2
#undef CONFIG_FEATURE_TAR_FROM
#define CONFIG_FEATURE_TAR_GZIP 1
#undef CONFIG_FEATURE_TAR_COMPRESS
#undef CONFIG_FEATURE_TAR_OLDGNU_COMPATABILITY
#define CONFIG_FEATURE_TAR_GNU_EXTENSIONS 1
#undef CONFIG_FEATURE_TAR_LONG_OPTIONS
#undef CONFIG_UNCOMPRESS
#undef CONFIG_UNZIP

/*
 * Common options for cpio and tar
 */
#undef CONFIG_FEATURE_UNARCHIVE_TAPE

/*
 * Coreutils
 */
#undef CONFIG_BASENAME
#undef CONFIG_CAL
#define CONFIG_CAT 1
#undef CONFIG_CHGRP
#define CONFIG_CHMOD 1
#define CONFIG_CHOWN 1
#define CONFIG_CHROOT 1
#undef CONFIG_CMP
#define CONFIG_CP 1
#define CONFIG_CUT 1
#define CONFIG_DATE 1
#define CONFIG_FEATURE_DATE_ISOFMT 1
#define CONFIG_DD 1
#define CONFIG_DF 1
#undef CONFIG_DIRNAME
#define CONFIG_DOS2UNIX 1
#define CONFIG_UNIX2DOS 1
#define CONFIG_DU 1
#define CONFIG_FEATURE_DU_DEFALT_BLOCKSIZE_1K 1
#define CONFIG_ECHO 1
#define CONFIG_FEATURE_FANCY_ECHO 1
#define CONFIG_ENV 1
#define CONFIG_EXPR 1
#define CONFIG_FALSE 1

/*
 * false (forced enabled for use with shell)
 */
#undef CONFIG_FOLD
#define CONFIG_HEAD 1
#define CONFIG_FEATURE_FANCY_HEAD 1
#undef CONFIG_HOSTID
#undef CONFIG_ID
#undef CONFIG_INSTALL
#undef CONFIG_LENGTH
#define CONFIG_LN 1
#undef CONFIG_LOGNAME
#define CONFIG_LS 1
#define CONFIG_FEATURE_LS_FILETYPES 1
#define CONFIG_FEATURE_LS_FOLLOWLINKS 1
#define CONFIG_FEATURE_LS_RECURSIVE 1
#define CONFIG_FEATURE_LS_SORTFILES 1
#define CONFIG_FEATURE_LS_TIMESTAMPS 1
#define CONFIG_FEATURE_LS_USERNAME 1
#define CONFIG_FEATURE_LS_COLOR 1
#undef CONFIG_MD5SUM
#define CONFIG_MKDIR 1
#undef CONFIG_MKFIFO
#define CONFIG_MKNOD 1
#define CONFIG_MV 1
#define CONFIG_OD 1
#undef CONFIG_PRINTF
#define CONFIG_PWD 1
#undef CONFIG_REALPATH
#define CONFIG_RM 1
#define CONFIG_RMDIR 1
#undef CONFIG_SEQ
#undef CONFIG_SHA1SUM
#define CONFIG_SLEEP 1
#undef CONFIG_FEATURE_FANCY_SLEEP
#define CONFIG_SORT 1
#define CONFIG_STTY 1
#define CONFIG_SYNC 1
#define CONFIG_TAIL 1
#define CONFIG_FEATURE_FANCY_TAIL 1
#define CONFIG_TEE 1
#define CONFIG_FEATURE_TEE_USE_BLOCK_IO 1
#define CONFIG_TEST 1

/*
 * test (forced enabled for use with shell)
 */
#undef CONFIG_FEATURE_TEST_64
#define CONFIG_TOUCH 1
#undef CONFIG_TR
#define CONFIG_TRUE 1

/*
 * true (forced enabled for use with shell)
 */
#define CONFIG_TTY 1
#define CONFIG_UNAME 1
#undef CONFIG_UNIQ
#define CONFIG_USLEEP 1
#undef CONFIG_UUDECODE
#undef CONFIG_UUENCODE
#undef CONFIG_WATCH
#define CONFIG_WC 1
#define CONFIG_WHO 1
#undef CONFIG_WHOAMI
#undef CONFIG_YES

/*
 * Common options for cp and mv
 */
#undef CONFIG_FEATURE_PRESERVE_HARDLINKS

/*
 * Common options for ls and more
 */
#define CONFIG_FEATURE_AUTOWIDTH 1

/*
 * Common options for df, du, ls
 */
#undef CONFIG_FEATURE_HUMAN_READABLE

/*
 * Console Utilities
 */
#undef CONFIG_CHVT
#undef CONFIG_CLEAR
#undef CONFIG_DEALLOCVT
#undef CONFIG_DUMPKMAP
#undef CONFIG_LOADFONT
#undef CONFIG_LOADKMAP
#undef CONFIG_OPENVT
#undef CONFIG_RESET
#undef CONFIG_SETKEYCODES

/*
 * Debian Utilities
 */
#undef CONFIG_MKTEMP
#undef CONFIG_PIPE_PROGRESS
#undef CONFIG_READLINK
#undef CONFIG_RUN_PARTS
#undef CONFIG_START_STOP_DAEMON
#undef CONFIG_WHICH

/*
 * Editors
 */
#define CONFIG_AWK 1
#define CONFIG_FEATURE_AWK_MATH 1
#undef CONFIG_PATCH
#define CONFIG_SED 1
#define CONFIG_VI 1
#define CONFIG_FEATURE_VI_COLON 1
#define CONFIG_FEATURE_VI_YANKMARK 1
#define CONFIG_FEATURE_VI_SEARCH 1
#define CONFIG_FEATURE_VI_USE_SIGNALS 1
#define CONFIG_FEATURE_VI_DOT_CMD 1
#define CONFIG_FEATURE_VI_READONLY 1
#define CONFIG_FEATURE_VI_SETOPTS 1
#define CONFIG_FEATURE_VI_SET 1
#define CONFIG_FEATURE_VI_WIN_RESIZE 1
#define CONFIG_FEATURE_VI_OPTIMIZE_CURSOR 1

/*
 * Finding Utilities
 */
#define CONFIG_FIND 1
#define CONFIG_FEATURE_FIND_MTIME 1
#define CONFIG_FEATURE_FIND_PERM 1
#define CONFIG_FEATURE_FIND_TYPE 1
#define CONFIG_FEATURE_FIND_XDEV 1
#define CONFIG_FEATURE_FIND_NEWER 1
#define CONFIG_FEATURE_FIND_INUM 1
#define CONFIG_GREP 1
#define CONFIG_FEATURE_GREP_EGREP_ALIAS 1
#define CONFIG_FEATURE_GREP_FGREP_ALIAS 1
#define CONFIG_FEATURE_GREP_CONTEXT 1
#undef CONFIG_XARGS

/*
 * Init Utilities
 */
#define CONFIG_INIT 1
#define CONFIG_FEATURE_USE_INITTAB 1
#define CONFIG_FEATURE_INITRD 1
#undef CONFIG_FEATURE_INIT_COREDUMPS
#undef CONFIG_FEATURE_EXTRA_QUIET
#define CONFIG_HALT 1
#undef CONFIG_POWEROFF
#define CONFIG_REBOOT 1
#define CONFIG_MESG 1

/*
 * Login/Password Management Utilities
 */
#undef CONFIG_USE_BB_PWD_GRP
#undef CONFIG_ADDGROUP
#undef CONFIG_DELGROUP
#undef CONFIG_ADDUSER
#undef CONFIG_DELUSER
#define CONFIG_GETTY 1
#define CONFIG_FEATURE_U_W_TMP 1
#define CONFIG_LOGIN 1
#define CONFIG_FEATURE_SECURETTY 1
#undef CONFIG_PASSWD
#undef CONFIG_SU
#undef CONFIG_SULOGIN
#undef CONFIG_VLOCK

/*
 * Common options for adduser, deluser, login, su
 */
#undef CONFIG_FEATURE_SHADOWPASSWDS

/*
 * Linux Ext2 FS Progs
 */
#define CONFIG_CHATTR 1
#define CONFIG_E2FSCK 1
#define CONFIG_FSCK 1
#define CONFIG_LSATTR 1
#define CONFIG_MKE2FS 1
#define CONFIG_TUNE2FS 1
#define CONFIG_E2LABEL 1
#define CONFIG_FINDFS 1

/*
 * Miscellaneous Utilities
 */
#undef CONFIG_ADJTIMEX
#define CONFIG_CROND 1
#undef CONFIG_FEATURE_CROND_CALL_SENDMAIL
#define CONFIG_CRONTAB 1
#undef CONFIG_DC
#define CONFIG_DEVFSD 1
#undef CONFIG_DEVFSD_MODLOAD
#undef CONFIG_DEVFSD_FG_NP
#undef CONFIG_DEVFSD_VERBOSE
#undef CONFIG_LAST
#undef CONFIG_HDPARM
#define CONFIG_MAKEDEVS 1
#undef CONFIG_MT
#undef CONFIG_RX
#define CONFIG_STRINGS 1
#undef CONFIG_TIME
#undef CONFIG_WATCHDOG
#define CONFIG_SYSINFO 1

/*
 * Linux Module Utilities
 */
#define CONFIG_INSMOD 1
#undef CONFIG_FEATURE_2_4_MODULES
#define CONFIG_FEATURE_2_6_MODULES 1
#define CONFIG_LSMOD 1
#undef CONFIG_MODPROBE
#define CONFIG_RMMOD 1
#undef CONFIG_FEATURE_CHECK_TAINTED_MODULE

/*
 * Networking Utilities
 */
#undef CONFIG_FEATURE_IPV6
#define CONFIG_ARPING 1
#define CONFIG_SENDARP 1
#define CONFIG_TFTPD 1
#define CONFIG_FTPGET 1
#define CONFIG_FTPPUT 1
#define CONFIG_HOSTNAME 1
#define CONFIG_HTTPD 1
#undef CONFIG_FEATURE_HTTPD_USAGE_FROM_INETD_ONLY
#define CONFIG_FEATURE_HTTPD_BASIC_AUTH 1
#undef CONFIG_FEATURE_HTTPD_AUTH_MD5
#undef CONFIG_FEATURE_HTTPD_RELOAD_CONFIG_SIGHUP
#undef CONFIG_FEATURE_HTTPD_SETUID
#undef CONFIG_FEATURE_HTTPD_CONFIG_WITH_MIME_TYPES
#define CONFIG_FEATURE_HTTPD_CGI 1
#undef CONFIG_FEATURE_HTTPD_SET_REMOTE_PORT_TO_ENV
#define CONFIG_FEATURE_HTTPD_ENCODE_URL_STR 1
#define CONFIG_IFCONFIG 1
#define CONFIG_FEATURE_IFCONFIG_STATUS 1
#undef CONFIG_FEATURE_IFCONFIG_SLIP
#undef CONFIG_FEATURE_IFCONFIG_MEMSTART_IOADDR_IRQ
#define CONFIG_FEATURE_IFCONFIG_HW 1
#define CONFIG_FEATURE_IFCONFIG_BROADCAST_PLUS 1
#define CONFIG_IFUPDOWN 1
#undef CONFIG_FEATURE_IFUPDOWN_IP
#define CONFIG_FEATURE_IFUPDOWN_IP_BUILTIN 1
#define CONFIG_FEATURE_IFUPDOWN_IPV4 1
#undef CONFIG_FEATURE_IFUPDOWN_IPV6
#undef CONFIG_FEATURE_IFUPDOWN_IPX
#undef CONFIG_FEATURE_IFUPDOWN_MAPPING
#undef CONFIG_INETD
#undef CONFIG_IP
#undef CONFIG_IPCALC
#undef CONFIG_IPADDR
#undef CONFIG_IPLINK
#undef CONFIG_IPROUTE
#undef CONFIG_IPTUNNEL
#undef CONFIG_NAMEIF
#define CONFIG_NC 1
#define CONFIG_NETSTAT 1
#define CONFIG_NSLOOKUP 1
#define CONFIG_PING 1
#define CONFIG_FEATURE_FANCY_PING 1
#define CONFIG_ROUTE 1
#define CONFIG_TELNET 1
#define CONFIG_FEATURE_TELNET_TTYPE 1
#define CONFIG_FEATURE_TELNET_AUTOLOGIN 1
#define CONFIG_TELNETD 1
#undef CONFIG_FEATURE_TELNETD_INETD
#define CONFIG_TFTP 1
#define CONFIG_FEATURE_TFTP_GET 1
#define CONFIG_FEATURE_TFTP_PUT 1
#undef CONFIG_FEATURE_TFTP_BLOCKSIZE
#undef CONFIG_FEATURE_TFTP_DEBUG
#define CONFIG_TRACEROUTE 1
#define CONFIG_FEATURE_TRACEROUTE_VERBOSE 1
#define CONFIG_VCONFIG 1
#define CONFIG_WGET 1
#define CONFIG_FEATURE_WGET_STATUSBAR 1
#define CONFIG_FEATURE_WGET_AUTHENTICATION 1
#define CONFIG_FEATURE_WGET_IP6_LITERAL 1

/*
 * udhcp Server/Client
 */
#undef CONFIG_UDHCPD
#undef CONFIG_UDHCPC

/*
 * Process Utilities
 */
#define CONFIG_FREE 1
#define CONFIG_KILL 1
#define CONFIG_KILLALL 1
#define CONFIG_PIDOF 1
#define CONFIG_PS 1
#define CONFIG_RENICE 1
#define CONFIG_TOP 1
#define FEATURE_CPU_USAGE_PERCENTAGE 1
#define CONFIG_UPTIME 1
#define CONFIG_SYSCTL 1

/*
 * Another Bourne-like Shell
 */
#define CONFIG_FEATURE_SH_IS_ASH 1
#undef CONFIG_FEATURE_SH_IS_HUSH
#undef CONFIG_FEATURE_SH_IS_LASH
#undef CONFIG_FEATURE_SH_IS_MSH
#undef CONFIG_FEATURE_SH_IS_NONE
#define CONFIG_ASH 1

/*
 * Ash Shell Options
 */
#define CONFIG_ASH_JOB_CONTROL 1
#define CONFIG_ASH_ALIAS 1
#define CONFIG_ASH_MATH_SUPPORT 1
#undef CONFIG_ASH_MATH_SUPPORT_64
#undef CONFIG_ASH_GETOPTS
#undef CONFIG_ASH_CMDCMD
#undef CONFIG_ASH_MAIL
#define CONFIG_ASH_OPTIMIZE_FOR_SIZE 1
#undef CONFIG_ASH_RANDOM_SUPPORT
#undef CONFIG_HUSH
#undef CONFIG_LASH
#define CONFIG_MSH 1

/*
 * Bourne Shell Options
 */
#undef CONFIG_FEATURE_SH_EXTRA_QUIET
#define CONFIG_FEATURE_SH_STANDALONE_SHELL 1
#define CONFIG_FEATURE_COMMAND_EDITING 1
#define CONFIG_FEATURE_COMMAND_HISTORY 15
#undef CONFIG_FEATURE_COMMAND_SAVEHISTORY
#define CONFIG_FEATURE_COMMAND_TAB_COMPLETION 1
#undef CONFIG_FEATURE_COMMAND_USERNAME_COMPLETION
#define CONFIG_FEATURE_SH_FANCY_PROMPT 1

/*
 * System Logging Utilities
 */
#define CONFIG_SYSLOGD 1
#undef CONFIG_FEATURE_ROTATE_LOGFILE
#define CONFIG_FEATURE_REMOTE_LOG 1
#define CONFIG_FEATURE_IPC_SYSLOG 1
#define CONFIG_FEATURE_IPC_SYSLOG_BUFFER_SIZE 16
#define CONFIG_LOGREAD 1
#undef CONFIG_FEATURE_LOGREAD_REDUCED_LOCKING
#define CONFIG_KLOGD 1
#define CONFIG_LOGGER 1

/*
 * Linux System Utilities
 */
#define CONFIG_DMESG 1
#undef CONFIG_FBSET
#undef CONFIG_FDFLUSH
#undef CONFIG_FDFORMAT
#define CONFIG_FDISK 1
#define FDISK_SUPPORT_LARGE_DISKS 1
#define CONFIG_FEATURE_FDISK_WRITABLE 1
#undef CONFIG_FEATURE_AIX_LABEL
#undef CONFIG_FEATURE_SGI_LABEL
#undef CONFIG_FEATURE_SUN_LABEL
#undef CONFIG_FEATURE_OSF_LABEL
#define CONFIG_FEATURE_FDISK_ADVANCED 1
#undef CONFIG_FREERAMDISK
#undef CONFIG_FSCK_MINIX
#undef CONFIG_MKFS_MINIX
#undef CONFIG_GETOPT
#define CONFIG_HEXDUMP 1
#undef CONFIG_HWCLOCK
#define CONFIG_LOSETUP 1
#define CONFIG_LEDCTRL 1
#define CONFIG_MKSWAP 1
#define CONFIG_MORE 1
#define CONFIG_FEATURE_USE_TERMIOS 1
#undef CONFIG_PIVOT_ROOT
#define CONFIG_RDATE 1
#define CONFIG_SWAPONOFF 1
#define CONFIG_MOUNT 1
#define CONFIG_NFSMOUNT 1
#define CONFIG_UMOUNT 1
#define CONFIG_FEATURE_MOUNT_FORCE 1

/*
 * Common options for mount/umount
 */
#define CONFIG_FEATURE_MOUNT_LOOP 1
#undef CONFIG_FEATURE_MTAB_SUPPORT

/*
 * Debugging Options
 */
#undef CONFIG_DEBUG