#include <stdio.h>
#include <linux/if_ether.h>

#include "fuck_net.h"

static char logo[] = 
" ___   _   _    ___   _  __    _  _   ___   _____\n\
 | __| | | | |  / __| | |/ /   | \| | | __| |_   _|\n\
 | _|  | |_| | | (__  | ' <    | .` | | _|    | |  \n\
 |_|    \___/   \___| |_|\_\   |_|\_| |___|   |_|   ";

void banner() {
    printf("%s\n",logo);
}

void pf_fuck_create() {
    int fd = socket(PF_FUCK,SOCK_RAW,htons(ETH_P_ALL));
    if (fd < 0) {
        #ifdef FUCK_DEBUG
        printf("open PF_FUCK sock fail\n");
        #endif
    }
    close(fd);
}

int main(int argc, char** argv) {
    banner();
    pf_fuck_create();
	return 0;
}
