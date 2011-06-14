#define ETCSMBCONF "/etc/samba/smb.conf"
#define ETCBFTPDCONFDEFAULT "/etc/bftpd.conf.default"
#define VARBFTPDCONF "/var/bftpd.conf"
#define ETCPASSWD "/etc/passwd"
#define ETCGROUP "/etc/group"
#define MOUNT "/bin/mount"
#define SAMBA_ENABLED "/var/samba/samba_enabled"
//#define MAX_STRING_SIZE 256
#define MAX_PWD_UPDATE_SIZE 256
#define MAX_MOUNT_CMD_SIZE 256
#define MAC_LENGTH	18
#define IP_LENGTH		16
#define NAME_LENGTH		256
#define PASSWORD_LENGTH		256
#define DIR_LENGTH		256
#define UDHCPD_FILE		"/var/udhcpd_static_leases.conf"
#define MAX_UDHCPD_ROW_SIZE	64
#define MAX_BLANK_RSI_SIZE	64
#define MAX_FTPD_ROW_SIZE	512
#define ADSLCTL_CONF		"/bin/adslctl configure"
#define WLCTL			"/bin/wlctl"
#define VARPROFILE		"/var/profile"
#define DRIVERS_DIR		"/lib/modules/2.6.8.1/kernel/drivers"
#define USB_MEDIA_DRIVERS_DIR	"/lib/modules/2.6.8.1/kernel/drivers/usb/media"
#define IPTABLES		"/bin/iptables"
#define COMMON_PARMS		"-p tcp --dport 81 -j ACCEPT"

void usage(char *strname);
int main(int argc, char*argv[]);
int configure_bftpd();
int configure_samba();
int configure_udhcpd();
int configure_adslctl();
int configure_antdiv();
int configure_printer();
int execute_profile();
int AddDefaultFtpdEntries();
int configure_webcam();
