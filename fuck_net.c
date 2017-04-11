#include <linux/version.h>

#if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,32))
#error **********************************************************************
#error * FUCK_NET works on kernel 2.6.32 or newer. Please update your kernel *
#error **********************************************************************
#endif

#if(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,18))
#if(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,33))
#include <generated/autoconf.h>
#else
#include <linux/autoconf.h>
#endif
#else
#include <linux/config.h>
#endif
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/kernel.h>
#include <linux/socket.h>
#include <linux/skbuff.h>
#include <linux/rtnetlink.h>
#include <linux/in.h>
#include <linux/inet.h>
#include <linux/in6.h>
#include <linux/init.h>
#include <linux/filter.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/list.h>
#include <linux/netdevice.h>
#include <linux/etherdevice.h>
#include <linux/proc_fs.h>
#include <linux/if_arp.h>
#include <linux/if_vlan.h>
#include <net/xfrm.h>
#include <net/sock.h>
#include <asm/io.h>		/* needed for virt_to_phys() */
#ifdef CONFIG_INET
#include <net/inet_common.h>
#endif
#include <net/ip.h>
#include <net/ipv6.h>
#include <linux/pci.h>
#include <asm/shmparam.h>

#include "linux/fuck_net.h"

#ifndef UTS_RELEASE
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,33))
#include <linux/utsrelease.h>
#else
#include <generated/utsrelease.h>
#endif
#endif

#ifdef UTS_UBUNTU_RELEASE_ABI
#if (LINUX_VERSION_CODE <= KERNEL_VERSION(3,0,0))
#undef UTS_UBUNTU_RELEASE_ABI
#else
#define UBUNTU_VERSION_CODE (LINUX_VERSION_CODE & ~0xFF)
#endif
#endif

#if(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31))
#define I82599_HW_FILTERING_SUPPORT
#endif

struct proc_dir_entry *fuck_proc_dir = NULL,*fuck_proc_dev_dir = NULL, *fuck_proc_stats_dir = NULL;

static rwlock_t fuck_proc_lock =
#if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,39))
  RW_LOCK_UNLOCKED
#else
  __RW_LOCK_UNLOCKED(fuck_proc_lock)
#endif
;

#define PROC_DEV                "dev"
#define PROC_STATS              "stats"

static void fuck_proc_term(void)
{
  write_lock(&fuck_proc_lock); 

    if (fuck_proc_dir != NULL) {
          remove_proc_entry(PROC_STATS, fuck_proc_dir);
    remove_proc_entry(PROC_DEV, fuck_proc_dir);
    
      remove_proc_entry("pf_fuck",
#if(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
			init_net.
#endif
			proc_net);
       
    }
 

  write_unlock(&fuck_proc_lock);
}

static void fuck_proc_init(void)
{
     fuck_proc_dir = proc_mkdir("pf_fuck",
#if(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,24))
			     init_net.
#endif
			     proc_net);

  if (fuck_proc_dir != NULL) {
#if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,30))
    fuck_proc_dir->owner = THIS_MODULE;
#endif

    fuck_proc_dev_dir   = proc_mkdir(PROC_DEV, fuck_proc_dir);
    fuck_proc_stats_dir = proc_mkdir(PROC_STATS, fuck_proc_dir);
  }
}

static int packet_rcv(struct sk_buff *skb, struct net_device *dev,
		      struct packet_type *pt
#if(LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,16))
		      , struct net_device *orig_dev
#endif
		      )
{
  int rc = 0;
  u_int8_t skb_reference_in_use = 0;

  if (skb->pkt_type != PACKET_LOOPBACK ) {
    //printk("[PF_FUCK] (call skb_ring_handler)skb->pkt_type=%d\n",skb->pkt_type);
  }
else
{ 
           // printk("[PF_FUCK] (not call skb_ring_handler) skb->pkt_type=%d\n",skb->pkt_type);
}
  if (!skb_reference_in_use)
    kfree_skb(skb);

  return rc;
}

static struct proto fuck_proto;
static struct packet_type prot_hook;

void register_device_handler(void) 
{
  prot_hook.func = packet_rcv;
  prot_hook.type = htons(ETH_P_ALL);
  dev_add_pack(&prot_hook);
}

void unregister_device_handler(void) 
{
  dev_remove_pack(&prot_hook); /* Remove protocol hook */
}

static struct proto fuck_proto = {
    .name = "PF_FUCK",
    .owner = THIS_MODULE,
    .obj_size = sizeof(struct fuck_sock),
};

int fuck_release(struct socket* sock) {
    struct sock *sk = sock->sk;
    
	if (sk) {
        sock->sk = NULL;
        sock_put(sk);
    }
    return 0;
}
static struct proto_ops fuck_ops = {
    .family = PF_FUCK,
    .owner = THIS_MODULE,
    .release = fuck_release,
    .connect = sock_no_connect,
    .socketpair = sock_no_socketpair,
    .accept = sock_no_accept,
    .getname = sock_no_getname,
    .listen = sock_no_listen,
    .shutdown = sock_no_shutdown,
    .sendpage = sock_no_sendpage,
};

static int fuck_create(struct net *net, struct socket *sock, int protocol,
		       int kern)
{
    int err = 0;
	err = -EPERM;
out:
    return err;
}

static struct net_proto_family fuck_family_ops = {
  .family = PF_FUCK,
  .create = fuck_create,
  .owner = THIS_MODULE,
};

static int __init fuck_init(void)
{
    int rc;
    
	printk("[PF_FUCK] Welcoame to PF_FUCK %s\n"
    "(C) 2016 zk2013\n",
    FUCK_VERSION);
    /* int proto_register(struct proto *prot, int alloc_slab)
    prot->slab = kmem_cache_create(prot->name, prot->obj_size, 0,
					SLAB_HWCACHE_ALIGN | prot->slab_flags,
					NULL); */
                    
     if((rc = proto_register(&fuck_proto, 0)) != 0)
        return(rc);
    
    fuck_proc_init();
    
    sock_register(&fuck_family_ops);
    
    register_device_handler();
     
	return 0;
}
// i wrong write __init so oops 
static void __exit fuck_exit(void)
{
	printk("fuck_exit\n");
    unregister_device_handler();
    fuck_proc_term();
    sock_unregister(PF_FUCK);
    proto_unregister(&fuck_proto);
}

module_init(fuck_init);
module_exit(fuck_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("zk2013");
MODULE_ALIAS_NETPROTO(PF_FUCK);
/*
#define MODULE_ALIAS_NETPROTO(proto) \
	MODULE_ALIAS("net-pf-" __stringify(proto))
*/
