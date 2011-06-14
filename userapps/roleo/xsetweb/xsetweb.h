#define IPTABLES "/bin/iptables"
#define COMMON_PARMS "-p tcp --dport 81 -j ACCEPT"

void usage(char *strname);
int main(int argc, char*argv[]);
int configure_xsetweb();
