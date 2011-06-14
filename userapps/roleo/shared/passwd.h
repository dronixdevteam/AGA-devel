#define PASSWD_FILE "/etc/passwd"

// DA BUSYBOX...

extern char * safe_strncpy(char *dst, const char *src, size_t size);
extern char *pw_encrypt(const char *clear, const char *salt);
extern int i64c(int i);
extern char *crypt_make_salt(void);
char *crypt_passwd(char *Password);
int append_user(char *User, char *Password, uid_t Uid, gid_t Gid,
    char *Gecos, char *Home, char *Shell);
