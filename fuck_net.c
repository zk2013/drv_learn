#include <linux/version.h>

#if(LINUX_VERSION_CODE < KERNEL_VERSION(2,6,32))
#error **********************************************************************
#error * FUCK_NET works on kernel 2.6.32 or newer. Please update your kernel *
#error **********************************************************************
#endif

#include <linux/init.h>
#include <linux/kernel.h>

static int __init fuck_init(void)
{
	printk("fuck_init\n");
	return 0;
}

static void __init fuck_exit(void)
{
	printk("fuck_exit\n");
}

module_init(fuck_init);
module_exit(fuck_exit);
