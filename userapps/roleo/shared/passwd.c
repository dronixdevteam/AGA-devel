#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <time.h>
#include <unistd.h>

#include "passwd.h"

#define PASSWD_FILE "/etc/passwd"

// DA BUSYBOX...

extern char * safe_strncpy(char *dst, const char *src, size_t size)
{
    dst[size-1] = '\0';
    return strncpy(dst, src, size-1);
}

extern char *pw_encrypt(const char *clear, const char *salt)
{
    static char cipher[128];
    char *cp;
		
    cp = (char *) crypt(clear, salt);
    /* if crypt (a nonstandard crypt) returns a string too large,
	truncate it so we don't overrun buffers and hope there is
	enough security in what's left */
    safe_strncpy(cipher, cp, sizeof(cipher));
    return cipher;
}

static int i64c(int i)
{
    if (i <= 0)
        return ('.');
    if (i == 1)
        return ('/');
    if (i >= 2 && i < 12)
        return ('0' - 2 + i);
    if (i >= 12 && i < 38)
        return ('A' - 12 + i);
    if (i >= 38 && i < 63)
        return ('a' - 38 + i);
    return ('z');
}

static char *crypt_make_salt(void)
{
    time_t now;
    static unsigned long x;
    static char result[3];

    time(&now);
    x += now + getpid() + clock();
    result[0] = i64c(((x >> 18) ^ (x >> 6)) & 077);
    result[1] = i64c(((x >> 12) ^ x) & 077);
    result[2] = '\0';
    return result;
}

// MAIN FUNCTIONS

char *crypt_passwd(char *Password)
{
    return pw_encrypt(Password, crypt_make_salt());
}

int append_user(char *User, char *Password, uid_t Uid, gid_t Gid, 
    char *Gecos, char *Home, char *Shell)
{
    struct passwd pw;
    FILE *etcpasswd;

    char salt[3];
    char *strCPassword;
    
    strCPassword = pw_encrypt(Password, crypt_make_salt());

    /* create a passwd struct */
    pw.pw_name = User;
    pw.pw_passwd = strCPassword;
    pw.pw_uid = Uid;
    pw.pw_gid = Gid;
    pw.pw_gecos = Gecos;
    pw.pw_dir = Home;
    pw.pw_shell = Shell;

    /* make sure everything is kosher and setup uid && gid */
    etcpasswd = fopen(PASSWD_FILE, "a");
    if (etcpasswd == NULL) {
	return -1;
    }
    fseek(etcpasswd, 0, SEEK_END);

    /* add to passwd */
    if (putpwent(&pw, etcpasswd) == -1) {
	return -2;
    }
    fclose(etcpasswd);

    return 0;
}
