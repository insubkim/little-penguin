#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/usb.h>

#define USB_KEYBOARD_CLASS         0x03
#define USB_KEYBOARD_SUBCLASS      0x01
#define USB_KEYBOARD_PROTOCOL      0x01

/* USB 장치 테이블: 모든 USB 키보드(boot interface)를 대상으로 함 */
static const struct usb_device_id usb_keyboard_id_table[] = {
    { USB_INTERFACE_INFO(USB_KEYBOARD_CLASS,
                         USB_KEYBOARD_SUBCLASS,
                         USB_KEYBOARD_PROTOCOL) },
    { } /* 테이블 종료 */
};
MODULE_DEVICE_TABLE(usb, usb_keyboard_id_table);

/* USB 키보드가 연결되었을 때 호출되는 probe 함수 */
static int usb_keyboard_probe(struct usb_interface *interface,
                              const struct usb_device_id *id)
{
    printk(KERN_INFO "usb_keyboard_hotplug: USB Keyboard plugged in\n");
    return 0;
}

/* USB 키보드가 제거되었을 때 호출되는 disconnect 함수 */
static void usb_keyboard_disconnect(struct usb_interface *interface)
{
    printk(KERN_INFO "usb_keyboard_hotplug: USB Keyboard removed\n");
}

/* USB 드라이버 구조체 등록 */
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
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("USB Keyboard Hotplug Module");

