#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/module.h>	
#include <linux/kernel.h>	
#include <asm/uaccess.h>

#include <linux/mount.h>
#include <linux/nsproxy.h>
#include <linux/sched.h>
#include <linux/dcache.h>
#include <linux/path.h>
#include <linux/init.h>
#include <linux/slab.h>


static int my_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "my_open CALLED !\n");
    return 0;
}


/*
struct vfsmount {
	struct dentry *mnt_root;	
	struct super_block *mnt_sb;	
	int mnt_flags;
} __randomize_layout;
*/

/*
struct dentry {
	unsigned int d_flags;		
	seqcount_t d_seq;		
	struct hlist_bl_node d_hash;	
	struct dentry *d_parent;	
	struct qstr d_name;
	struct inode *d_inode;		
	unsigned char d_iname[DNAME_INLINE_LEN];	

	
	struct lockref d_lockref;	
	const struct dentry_operations *d_op;
	struct super_block *d_sb;	
	unsigned long d_time;		
	void *d_fsdata;			

	union {
		struct list_head d_lru;		
		wait_queue_head_t *d_wait;	
	};
	struct list_head d_child;	
	struct list_head d_subdirs;	
	union {
		struct hlist_node d_alias;	
		struct hlist_bl_node d_in_lookup_hash;	
	 	struct rcu_head d_rcu;
	} d_u;
} __randomize_layout;
 */

/*
static void iter_filesystem(void)
{
    struct mount *mnt;
    struct path path;
    int ret = kern_path("/", LOOKUP_DIRECTORY, &path); 
    
    list_for_each_entry(mnt, &path->d_sb->smounts, mnt_list) {
        printk("Mount point: %s\n", mnt->mnt_root->d_name.name); // Access mount point
        printk("Filesystem type: %s\n", mnt->mnt_sb->s_type->name); // Access filesystem type
    }
}
*/

static void iter_mnt(void)
{
    struct mnt_namespace *ns = current->nsproxy->mnt_ns;
    struct mnt_namespace *mnt;

    list_for_each_entry(mnt, ns->list, list) {
        /*char buf[1024] = {0,};
        struct path p = {
            .mnt    = &mnt->mnt,
            .dentry = mnt->mnt.mnt_root,
        };
        char *path_str = d_path(&p, buf, sizeof(buf));
        if (!IS_ERR(path_str)) {
            pr_info("Mount point: %s\n", path_str);
            pr_info("Filesystem type: %s\n",
                    mnt->mnt.mnt_sb->s_type->name);
        }*/
    }
}


static ssize_t my_read (struct file *file, char __user *user, size_t size, loff_t *loff)
{
	printk(KERN_INFO "my_read CALLED !\n");
	printk(KERN_INFO "my_read loff [%lld]!\n", *loff);
		
	char *s = "inskim";
	size_t err = 0;	

	if (*loff > 6)
		return 0;
    size = min_t(size_t, size, 7 - *loff);	
	err = copy_to_user(user, s + *loff, size);
	*loff += size;	
	
	if (err != 0)
		printk(KERN_INFO "my_read - copy_to_user return err[%zu] !\n", err);
	

	return size;
}

static ssize_t my_write (struct file *file, const char __user *user, size_t size, loff_t *loff)
{
	printk(KERN_INFO "my_write CALLED !\n");
    return 0;
}

static int my_release (struct inode *inode, struct file *file)
{
	printk(KERN_INFO "my_release CALLED !\n");
    return 0;
}

static struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write
};

static struct miscdevice my_driver = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "mymount",
    .fops = &my_fops
};

static int misc_init(void)
{
    //iter_filesystem();
    iter_mnt();
    
    return misc_register(&my_driver);
}

static void misc_exit(void)
{
    misc_deregister(&my_driver);
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
