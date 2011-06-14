#define IPTABLES "/bin/iptables"

void getword(char *word, char *line, char stop);
char *makeword(char *line, char stop);
char *fmakeword(FILE *f, char stop, int *cl);
char x2c(char *what);
void unescape_url(char *url);
void plustospace(char *str);
int rind(char *s, char c);
int getline(char *s, int n, FILE *f);
void send_fd(FILE *f, FILE *fd);
int fileExists(char *filename);
int fileCopy(char *sourceFile, char *destFile);
char *trim(char *input);
int appendToTextFile(char *strFilename, char *strPrint);
int verifyWANAccess(int tcpport);
