#define MOUNTDIR	"/var/mounts"
#define MOUNT		"/bin/mount"
#define MOUNTNTFS3G	"/sbin/mount.ntfs-3g"
#define UMOUNT		"/bin/umount"
#define HOTPLUG		"/sbin/hotplug"
#define ECHO		"/bin/echo"
#define FSCK		"/sbin/fsck"
#define FSCK_OUT	"/var/fsck.out"
#define FDISK		"/bin/sfdisk"
#define MKFS		"/sbin/mkfs.ext2"
#define FDISK_MKFS_OUT	"/var/fdisk_mkfs.out"
#define OUT_END		"--- OPERATION COMPLETED ---"

typedef struct {
    char dev[64];
    int mounted;
    char point[64];
    char fstype[16];
} partition;

typedef struct {
    char dev[64];
    int in_use;
} disk;

int GetDisks();
int GetPartitionsAndMounts();
int ExecMount(char *device);
int ExecUmount(char *device, int kill);
int ExecFsck(char *device);
int ExecFdisk(char *device);
int ExecFormat(char *device);
int readDisks(disk *arrayDisk, int diskNum);
int readMounts(partition *arrayPartition, int partNum);
int readPartitions(partition *arrayPartition, int partNum);
int appendToTextFile(char *strFilename, char *strPrint);
void GetFsckVar();
void GetFsckRefresh(int secs);
void GetFsckStatus(char *device);
void GetFsckOut(char *device);
void GetFdiskVar();
void GetFdiskRefresh(int secs);
void GetFdiskStatus(char *device);
void GetFdiskOut(char *device);

// util.c
int fileExists(char *filename);
