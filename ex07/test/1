#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/mutex.h>
#include <linux/module.h>	/* Needed by all modules */
#include <linux/kernel.h>	/* Needed for KERN_INFO */
#include <asm/uaccess.h>
#include <linux/debugfs.h>
#include <linux/path.h>
#include <linux/namei.h>

//https://www.kernel.org/doc/html/v6.15-rc3/filesystems/debugfs.html



static int debugfs_init(void)
{
    	struct path path;
    	int ret = kern_path("/sys/kernel/debug/fortytwo", LOOKUP_DIRECTORY, &path);
    	if (ret)
		pr_err("Failed to lookup /sys/kernel/debug/fortytwo err %d\n", ret);
    	else
        	debugfs_remove_recursive(path.dentry);
	return 0;
}

static void debugfs_exit(void)
{
	printk(KERN_INFO "debugfs_exit!\n");
}

module_init(debugfs_init);
module_exit(debugfs_exit);

MODULE_LICENSE("GPL");
