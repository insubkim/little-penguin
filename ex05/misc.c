#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */


static int my_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "my_open CALLED !\n");
    try_module_get(THIS_MODULE);
    return 0;
}

static ssize_t my_read (struct file *file, char __user *user, size_t size, loff_t *loff)
{
	printk(KERN_INFO "my_read CALLED !\n");
    return 0;
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
    .name = "fortytwo",
    .fops = &my_fops
};

static int misc_init(void)
{
    return misc_register(&my_driver);
}

static void misc_exit(void)
{
    misc_deregister(&my_driver);
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
