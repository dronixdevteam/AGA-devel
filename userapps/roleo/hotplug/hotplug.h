#define SMBD "/bin/smbd"
#define NMBD "/bin/nmbd"
#define SMBSEMFILE "/var/smb.sem"
#define ETCSMBCONF "/etc/samba/smb.conf"
#define VARSMBCONF "/var/samba/smb.conf"
//#define SDA1VARSMBCONF "/var/mounts/sda1/var/smb.conf"
#define ETCSMBCONFDEF "/etc/samba/smb.conf.default"

#define SMBDLOCKFILE "/var/locks/smbd.pid"
#define NMBDLOCKFILE "/var/locks/nmbd.pid"
#define LOGFILE "/var/hotplug.log"
#define MOUNT "/bin/mount"
#define MOUNTNTFS3G "/sbin/mount.ntfs-3g"
#define UMOUNT "/bin/umount"
#define MOUNTDIR "/var/mounts"
#define PIDDIR "/var/run"
#define ORIGINALHOTPLUG "/bin/original_hotplug"
#define MAX_SMB_UPDATE_SIZE 1024

int writeLog(char *logRow);
