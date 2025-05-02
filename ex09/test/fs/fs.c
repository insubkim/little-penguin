#include <linux/module.h>	
#include <linux/kernel.h>	

#include <linux/sched.h>
#include <linux/fs_struct.h>
#include <linux/nsproxy.h>
#include <linux/mount.h>
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

static int misc_init(void)
{
    printk(KERN_INFO "PID: %d\n", current->pid);
    
    struct task_struct *c = current;

    struct fs_struct *fs = current->fs;
    
    //struct path root;
    
    //get_fs_root(fs, &root);

    //struct vsfmount *mnt= root->mnt;

    //struct dentry *mnt_root= mnt->mnt_root;


    struct nsproxy *proxy = c->nsproxy;
    struct mnt_namespace *mnt_ns = proxy->mnt_ns;
    struct mount *cur;
    //struct mnt_namespace *cur;
    
    list_for_each_entry(cur, &mnt_ns->mnt_ns_list, mnt_ns_list)
    {

        printk(KERN_INFO "PID: %d\n", current->pid);
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
