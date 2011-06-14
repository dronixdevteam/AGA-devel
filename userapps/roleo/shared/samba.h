#define ETC_SMB_CONF_DEFAULT		"/etc/samba/smb.conf.default"
#define VAR_SMB_CONF			"/var/samba/smb.conf"
//#define VAR_MOUNTS_SMB_CONF		"/var/mounts/sda1/var/smb.conf"
#define SMBD_LOCK_FILE			"/var/locks/smbd.pid"
#define NMBD_LOCK_FILE			"/var/locks/nmbd.pid"
#define MAX_STRING_SIZE			64
#define MAX_ROOTSHARE_SIZE		100
#define MAX_ROW_SIZE			1024
#define MAX_SAMBA_SECTION_SIZE		1024
#define MAX_SMB_UPDATE_SIZE		1024

int SetSambaConf(char *ArgWorkName, char *ArgServerName, char *ArgServerDesc, int ArgRootShare);
int GetSambaConf();
int GetSambaStart();
int SetSambaRsiConf(int ArgState, char *ArgWorkName, char *ArgServerName, char *ArgServerDesc, int ArgRootShare);
int configureOtherSambaMounts();
int appendToTextFile(char *strFilename, char *strPrint);
