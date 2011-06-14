#define MAX_STRING_SIZE                 64
#define MAX_WEBCAM_SECTION_SIZE		1024
#define MAX_WEBCAM_UPDATE_SIZE		1024
#define PROC_BUS_USB_DEVICES		"/proc/bus/usb/devices"
#define IPTABLES			"/bin/iptables"

int GetWebcamConf();
int GetWebcamViewConf();
int SetWebcamRsiConf(int ArgEnable, char *ArgModulePath, int ArgWAN, char *ArgCaption,
    int ArgWidth, int ArgHeight, int ArgFps, int ArgQuality, int ArgTcpport, int ArgOldTcpport);
int DetectSupportedCam(char *DriverName);
int DetectCam(char *DriverName);
void GetDriverName(char *DriverName, char *DriverPath);

// util.c
int fileExists(char *filename);
int verifyWANAccess(int tcpport);
