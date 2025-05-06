#include <linux/module.h>	
#include <linux/kernel.h>	

#include <linux/sched.h>
#include <linux/nsproxy.h>
//task struct
//https://elixir.bootlin.com/linux/v4.3/source/include/linux/sched.h#L1378
//fs_struct
//https://elixir.bootlin.com/linux/v4.7/source/include/linux/fs_struct.h#L26
//path
//https://elixir.bootlin.com/linux/v4.7/source/include/linux/path.h#L7
//vsfmount
//https://elixir.bootlin.com/linux/v4.7/source/include/linux/mount.h#L66
//dentry
//https://elixir.bootlin.com/linux/v4.7/source/include/linux/dcache.h#L83
//nsproxy
//https://elixir.bootlin.com/linux/v6.14.4/source/include/linux/nsproxy.h#L32
//mnt_namespace
//https://elixir.bootlin.com/linux/v6.14.4/source/fs/mount.h#L8 

#include "/root/linux-6.14/fs/mount.h"

static int misc_init(void)
{
    printk(KERN_INFO "PID: %d\n", current->pid);
    
    struct task_struct *c = current;

    struct nsproxy *proxy = c->nsproxy;
    struct mnt_namespace *mnt_ns = proxy->mnt_ns;
    struct mnt_namespace *cur;
    
    list_for_each_entry(cur, &mnt_ns->mnt_ns_list, mnt_ns_list)
    {
        	struct mount *mnt;
	        char buf[256];
	        char *p;

            mnt = cur->root;
            //struct dentry *mnt_mountpoint = mnt->mnt_mountpoint;
            printk(KERN_INFO "mount : %s\n", mnt->mnt_devname);
            //printk(KERN_INFO "dentry name: %.*s\n",
            //        mnt_mountpoint->d_name.len,
            //        mnt_mountpoint->d_name.name);
            //p = dentry_path_raw(cur->root->mnt_mountpoint, buf, sizeof(buf));
            //if (p)
            //    printk(KERN_INFO "PID: %s\n", cur->root->buf);
       //     list_for_each_entry(mnt, &cur->root->mnt_list, mnt_list)
       //     {
       //         p = dentry_path_raw(mnt->mnt_mountpoint, buf, sizeof(buf));
       //         printk(KERN_INFO "mount points: %s\n", p);
       //     }
    }

    return 0;
}

void misc_exit(void)
{
    printk("end\n");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
