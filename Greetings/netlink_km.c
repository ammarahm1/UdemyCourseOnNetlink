#include <linux/module.h>
#include <linux/netlink.h>
#include <net/sock.h>
#include <linux/string.h>


#define NETLINK_TEST_PROTOCOL	31

static struct sock *nl_sk = NULL;

static void netlink_km_recv_msg(struct sk_buff *skb)
{
	
}

static void nlmsg_dump(struct nlmsghdr *nlh)
{
	printk(KERN_INFO "Message length: %u,Message type is %u, Message flags:%x, 
			Sequence number %u, Port ID %u" , nlmsg_len, nlmsg_type,
			nlmsg_flags, nlmsg_seq, nlmsg_pid);
}

static struct netlink_kernel_cfg cfg = {
	.input = netlink_km_recv_msg,
};



static int __init netlink_km_init(void) 
{
	nl_sk = netlink_kernel_create(&init_net, NETLINK_TEST_PROTOCOL, &cfg);
	if (!nl_sk) {
		printk(KERN_INFO "My netlink kernel module (%u) failed to load!\n",
				NETLINK_TEST_PROTOCOL);
		return -ENOMEM;
	}
	printk(KERN_INFO "My netlink kernel module is successfully loaded!\n");
	return 0;
}

static void __exit netlink_km_exit(void)
{
	printk(KERN_INFO "My netlink kernel module is removed!\n");
	netlink_kernel_release(nl_sk);
	nl_sk = NULL;
}

module_init(netlink_km_nit);
module_exit(netlink_km_exit);

MODULE_LICENSE("GPL")
