#include <linux/module.h>	
#include <linux/kernel.h>	

#include <linux/sched.h>

static int misc_init(void)
{
    printk(KERN_INFO,  "PID: %d\n", current->pid);

    return 0;
}

void misc_exit(void)
{
    printk("end\n");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
