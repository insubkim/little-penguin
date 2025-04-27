#include <linux/module.h>	
#include <linux/kernel.h>	

#include <linux/list.h>

typedef struct node {
    int data;
    struct list_head list_h;
}   t_node;

// 출처 https://secmem.tistory.com/242
static int misc_init(void)
{
   
    LIST_HEAD(list);

    t_node node1;
    t_node node2;
    t_node node3;
    t_node node4;

    t_node *now;

    printk("start\n");


    node1.data = 1;
    node2.data = 2;
    node3.data = 3;
    node4.data = 4;

    
    INIT_LIST_HEAD(&list);
    list_add(&node1.list_h, &list);
    list_add(&node2.list_h, &list);
    list_add(&node3.list_h, &list);

    list_del(&node2.list_h);
    list_replace(&node3.list_h, &node4.list_h);

    list_for_each_entry(now, &list, list_h)
    {
        printk("data [%d]\n", now->data);

    }


    return 0;
}

void misc_exit(void)
{
    printk("end\n");
}

module_init(misc_init);
module_exit(misc_exit);

MODULE_LICENSE("GPL");
