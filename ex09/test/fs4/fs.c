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
#include <linux/rbtree.h>
#include <linux/seq_file.h>
#include <linux/fs.h>
#include <linux/mount.h>

static void dump_mnt(struct mount *mnt)
{
        char *buf = (char *)__get_free_page(GFP_KERNEL);
        if (!buf)
                return;

        /* mount 루트 → pathname 문자열 */
        struct path p = {
                .mnt    = &mnt->mnt,
                .dentry = mnt->mnt.mnt_root,
        };
        char *s = d_path(&p, buf, PAGE_SIZE);
        if (!IS_ERR(s))
                pr_info("[mnt] id=%d dev=%s path=%s type=%s\n",
                        mnt->mnt_id,
                        mnt->mnt_devname ? mnt->mnt_devname : "none",
                        s,
                        mnt->mnt.mnt_sb->s_type->name);

        free_page((unsigned long)buf);
}

static int misc_init(void)
{
    printk(KERN_INFO "PID: %d\n", current->pid);
    
    struct task_struct *c = current;

    struct nsproxy *proxy = c->nsproxy;
    struct mnt_namespace *ns = proxy->mnt_ns;
    struct mnt_namespace *cur;
    
        struct rb_node *node;

        /* 네임스페이스가 live로 바뀌는 것을 막는다 */
//        down_read(&namespace_sem);

        for (node = rb_first(&ns->mounts); node; node = rb_next(node)) {
                struct mount *mnt = rb_entry(node, struct mount, mnt_node);
                dump_mnt(mnt);
        }

  //      up_read(&namespace_sem);




    return 0;
}

void misc_exit(void)
{
    printk("end\n");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
