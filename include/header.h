

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/ioctl.h>
#include <string.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <time.h>
#include <net/if.h>
#include <dirent.h>
#define SUCCESS 0
#define ERROR -1

#define F1 17
#define F2 18
#define F3 19
#define F4 20

#define ENTER   0x0f             
#define CANCEL  0x0c

#define RES32 5                 // No.of menu items to be displayed at once
#define UprOffset 0             // Title row to be displayed
#define MAX_MENU_ENTRIES 200
#define MAX_ENTRY_LENGTH 21
#define FALSE 0
#define TRUE  1


typedef struct
{
    short start;
    short maxEntries;
    char selectedIndex;
    char title[20];
    char menu[MAX_MENU_ENTRIES][MAX_ENTRY_LENGTH];

}MENU_T;

