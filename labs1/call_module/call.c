#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Daul GPL");

extern void double_paut(void);

static int call_init(void)
{
    printk(KERN_ALERT "call init\n");
    printk(KERN_ALERT "double paut\n");
    double_paut();
    return 0;
}

static void call_exit(void)
{
    printk(KERN_ALERT "call exit\n");
}

module_init(call_init);
module_exit(call_exit);