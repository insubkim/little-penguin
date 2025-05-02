#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

/* Notifier callback for USB hotplug events */
static int usb_hotplug_notify(struct notifier_block *nb, unsigned long action, void *data)
{
    struct usb_device *udev = data;

    switch (action) {
    case USB_DEVICE_ADD:
        printk(KERN_INFO "USB Hotplug: Device added (%s)\n", dev_name(&udev->dev));
        break;
    case USB_DEVICE_REMOVE:
        printk(KERN_INFO "USB Hotplug: Device removed (%s)\n", dev_name(&udev->dev));
        break;
    default:
        printk(KERN_INFO "USB Hotplug: Unknown event (action %lu) for device (%s)\n",
               action, dev_name(&udev->dev));
        break;
    }
    return NOTIFY_OK;
}

/* Define the notifier block */
static struct notifier_block usb_hotplug_nb = {
    .notifier_call = usb_hotplug_notify,
};

/* Module initialization function */
static int __init usb_hotplug_init(void)
{
    usb_register_notify(&usb_hotplug_nb);
    printk(KERN_INFO "USB Hotplug: Module loaded\n");
    return 0;
}

/* Module exit function */
static void __exit usb_hotplug_exit(void)
{
    usb_unregister_notify(&usb_hotplug_nb);
    printk(KERN_INFO "USB Hotplug: Module unloaded\n");
}

module_init(usb_hotplug_init);
module_exit(usb_hotplug_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Kernel module that logs USB hotplug events");

