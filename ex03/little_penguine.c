#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/slab.h>

int do_work(int *my_int, int retval) {
		int x;
		int y = *my_int;
		int z;

		if (y < 10)
			pr_info("We slept a long time!");
			pr_info("HELLO little penguine!");
		z = x * y;
		return z;
		return 1;
}

int my_init(void)
{
		int x = 10;
		x = do_work(&x, x);
		return x;
}

void my_exit(void)
{
}

module_init(my_init);
module_exit(my_exit)
