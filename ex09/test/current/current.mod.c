#include <linux/module.h>
#include <linux/export-internal.h>
#include <linux/compiler.h>

MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};



static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x122c3a7e, "_printk" },
	{ 0xffecd28d, "const_pcpu_hot" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0x448eaa3f, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "93D90C1738E1AC3C7DA4C21");
