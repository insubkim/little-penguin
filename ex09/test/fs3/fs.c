#include <linux/module.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/nsproxy.h>
#include <linux/ns_common.h>
#include <linux/rbtree.h>

#include "/root/linux-6.14/fs/mount.h"

MODULE_LICENSE("GPL");

//#include <linux/mount.h>

static void dump_mnt(struct mount *mnt, struct seq_file *seq)
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
        {
            if (!seq)
                pr_info("[mnt] id=%d dev=%s path=%s type=%s\n",
                        mnt->mnt_id,
                        mnt->mnt_devname ? mnt->mnt_devname : "none",
                        s,
                        mnt->mnt.mnt_sb->s_type->name);
            else 
                seq_printf(seq, "%s %s\m", mnt->mnt_devname, s);
        }
                //	seq_printf(m, "%-15s %s\n", mnt->mnt_devname, p);

        free_page((unsigned long)buf);
}

static int print_mounts(struct seq_file *seq)
{
    printk(KERN_INFO "print mount start! : [%d]\n", current->pid);

    struct task_struct *c = current;

    struct nsproxy *proxy = c->nsproxy;
    struct mnt_namespace *ns = proxy->mnt_ns;

    struct rb_node *node;

    /* 네임스페이스가 live로 바뀌는 것을 막는다 */
//    down_read(&namespace_sem);

    for (node = rb_first(&ns->mounts); node; node = rb_next(node)) {
            struct mount *mnt = rb_entry(node, struct mount, mnt_node);
            dump_mnt(mnt, seq);
    }

//    up_read(&namespace_sem);

    return 0;
}

static int mymounts_show(struct seq_file *m, void *v)
{
    return print_mounts(m); 
}

static int mymounts_open(struct inode *inode, struct file *file)
{
	return single_open(file, mymounts_show, NULL);
}

static const struct proc_ops mymounts_fops = {
	.proc_open = mymounts_open,
	.proc_read = seq_read,
	.proc_lseek = seq_lseek,
	.proc_release = single_release,
};

static int __init mymounts_init(void)
{
    print_mounts(0x00);
	proc_create("mymounts", 0666, NULL, &mymounts_fops);
	return 0;
}

static void __exit mymounts_exit(void)
{
	remove_proc_entry("mymounts", NULL);
}

module_init(mymounts_init);
module_exit(mymounts_exit);
