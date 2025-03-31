#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define USB_KEYBOARD_CLASS         0x03
#define USB_KEYBOARD_SUBCLASS      0x01
#define USB_KEYBOARD_PROTOCOL      0x01

#define USB_VENDOR_ID              0x062A
#define USB_PRODUCT_ID             0x4101
/*
static const struct usb_device_id usb_keyboard_id_table[] = {
    { USB_DEVICE(USB_VENDOR_ID,
                 USB_PRODUCT_ID) },
    { } 
};*/
/*
static const struct usb_device_id usb_keyboard_id_table[] = {
    { .match_flags = USB_DEVICE_ID_MATCH_DEVICE }, 
    { } 
};*/


static const struct usb_device_id usb_keyboard_id_table[] = {
    { USB_DEVICE(0x062A, 0x4101) }, 
    { } 
};


MODULE_DEVICE_TABLE(usb, usb_keyboard_id_table);

static int usb_keyboard_probe(struct usb_interface *interface,
                              const struct usb_device_id *id)
{
    printk(KERN_INFO "usb_keyboard_hotplug: USB Keyboard plugged in\n");
    return 0;
}

static void usb_keyboard_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "usb_keyboard_hotplug: USB Keyboard removed\n");
}


static struct usb_driver usb_keyboard_driver = {
    .name       = "usb_keyboard_hotplug",
    .id_table   = usb_keyboard_id_table,
    .probe      = usb_keyboard_probe,
    .disconnect = usb_keyboard_disconnect,
};


static int __init usb_keyboard_init(void)
{
    int ret = usb_register(&usb_keyboard_driver);
    if (ret)
        printk(KERN_ERR "usb_keyboard_hotplug: usb_register failed with error %d\n", ret);
    return ret;
}

static void __exit usb_keyboard_exit(void)
{
    usb_deregister(&usb_keyboard_driver);
}

module_init(usb_keyboard_init);
module_exit(usb_keyboard_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("inskim");
MODULE_DESCRIPTION("My USB Keyboard Hotplug Module");

