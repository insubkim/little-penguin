#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <asm/uaccess.h>
#include <linux/debugfs.h>

//https://www.kernel.org/doc/html/v6.15-rc3/filesystems/debugfs.html

static int my_open(struct inode *inode, struct file *file)
{
        printk(KERN_INFO "my_open CALLED !\n");
    return 0;
}

static ssize_t my_read (struct file *file, char __user *user, size_t size, loff_t *loff)
{
        printk(KERN_INFO "my_read CALLED !\n");

        char *s = "inskim";
        size_t err = 0;

        size = min_t(size_t, size, 6);
        err = copy_to_user(user, s, size);

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

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = my_read,
    .write = my_write
};

struct dentry* g_log_dir;

static int debugfs_init(void)
{
	printk(KERN_INFO "debugfs_init!\n");
	
	struct dentry* log_dir = debugfs_create_dir ("fortytwo", NULL);
	if (log_dir == NULL)
	{
		printk(KERN_INFO "debugfs - dir create failed [%d]!\n", ENODEV);
		return 1;	
	}
	
	g_log_dir = log_dir;

	int value = 42;

	struct dentry *id = debugfs_create_file("id", 0777, log_dir, (void*)&value, &fops);
	struct dentry *jiffies = debugfs_create_file("jiffies", 0444, log_dir, (void*)&value, &fops);
	struct dentry *foo = debugfs_create_file("foo", 0444, log_dir, (void*)&value, &fops);

	if ((id == NULL) || (jiffies == NULL) || (foo == NULL))
	{
		printk(KERN_INFO "debugfs - file create failed [%d]!\n", ENODEV);
		return 1;	
	}
	
	return 0;
}

static void debugfs_exit(void)
{
	if (g_log_dir)
		debugfs_remove_recursive(g_log_dir);
	printk(KERN_INFO "debugfs_exit!\n");
}

module_init(debugfs_init);
module_exit(debugfs_exit);

MODULE_LICENSE("GPL");
