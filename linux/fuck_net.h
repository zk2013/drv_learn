#ifndef __FUCK_NET_H
#define __FUCK_NET_H

#ifdef __KERNEL__
#include <linux/in6.h>
#else
#include <netinet/in.h>
#endif /* __KERNEL__ */

#define PF_FUCK          28      /* Packet Ring */
#define SOCK_FUCK        PF_FUCK
#define FUCK_VERSION    "1.0.0"

#ifdef __KERNEL__

struct pf_fuck_sock {
    int         fuck_pid;
    u_int32_t   fuck_id;
};

struct fuck_sock {
   struct sock sk; 
   struct pf_fuck_sock* pf_fuck_sk;
};
#endif /* __KERNEL__ */

#endif /* __FUCK_NET_H */