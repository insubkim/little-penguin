#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <asm/uaccess.h>
#include <linux/debugfs.h>
#include <linux/jiffies.h>

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

        size = min_t(size_t, size, 7);
        err = copy_to_user(user, s, size);

        if (err != 0)
                printk(KERN_INFO "my_read - copy_to_user return err[%zu] !\n", err);


        return size;
}

static ssize_t jiffies_read (struct file *file, char __user *user, size_t size, loff_t *loff)
{
        printk(KERN_INFO "mjiffies_read CALLED !\n");

        char s[256] = {0,};
        size_t err = 0;
	
	u64 jiffies = get_jiffies_64();
        
        printk(KERN_INFO "jiffies CALLED %llu!\n", jiffies);
	
	int len = 0;
	int i = 0;
	
	while (jiffies > 0)
	{
		s[i++] = jiffies % 10 + '0';
		jiffies /= 10;
	}

	len = i;
	
	i = 0;
	int j = len - 1;
	while (j > i)
	{
		char c = s[j];
		s[j] = s[i];
		s[i] = c;
		i++; j--;
	}
	

	size = min_t(size_t, size, len);
        err = copy_to_user(user, s, size);

        if (err != 0)
                printk(KERN_INFO "jiffies - copy_to_user return err[%zu] !\n", err);


        return size;
}

char	g_foo[4096];
int	g_foo_len;

static ssize_t foo_read (struct file *file, char __user *user, size_t size, loff_t *loff)
{
        printk(KERN_INFO "foo_read CALLED !\n");

        size_t err = 0;

        printk(KERN_INFO "foo_read *loff [%lld] !\n", *loff);
	// mutex lock
	if (*loff > g_foo_len)
		return 0;

        size = min_t(size_t, size, g_foo_len - *loff);
        err = copy_to_user(user, g_foo + *loff, size);
	// mutex unlock
	*loff += size - err;

        if (err != 0)
                printk(KERN_INFO "foo_read - copy_to_user return err[%zu] !\n", err);

        return size;
}

static ssize_t my_write (struct file *file, const char __user *user, size_t size, loff_t *loff)
{
        printk(KERN_INFO "my_write CALLED !\n");
    	return 0;
}

static ssize_t foo_write (struct file *file, const char __user *user, size_t size, loff_t *loff)
{
        printk(KERN_INFO "foo_write CALLED !\n");

	size_t err = 0;

	// mutex lock
	if (*loff > sizeof(g_foo))
	{
        	printk(KERN_INFO "foo_write size 0 loff[%lld] g_foo size[%zu] !\n", *loff, sizeof(g_foo));
		return 0;
	}

       	printk(KERN_INFO "foo_write size loff[%lld] g_foo size[%zu] !\n", *loff, sizeof(g_foo));
        size = min_t(size_t, size, sizeof(g_foo) - *loff);	
        printk(KERN_INFO "foo_write size [%zu] !\n", size);
	err = copy_from_user(g_foo, user, size);
	// mutex unlock
        printk(KERN_INFO "foo_write err byte [%zu] !\n", err);
        printk(KERN_INFO "foo_write g_foo [%s] !\n", g_foo);
	*loff += size - err;
	g_foo_len += size - err;
        printk(KERN_INFO "foo_write *loff [%lld] !\n", *loff);
	if (err != 0)
                printk(KERN_INFO "foo_read - copy_to_user return err[%zu] !\n", err);

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

static struct file_operations fops_jiffies = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = jiffies_read,
    .write = my_write
};

static struct file_operations fops_foo = {
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_release,
    .read = foo_read,
    .write = foo_write
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
	struct dentry *jiffies = debugfs_create_file("jiffies", 0444, log_dir, (void*)&value, &fops_jiffies);
	struct dentry *foo = debugfs_create_file("foo", 0744, log_dir, (void*)&value, &fops_foo);

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
