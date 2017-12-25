#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Daul GPL");

static int paut = 9600;

static void double_paut(void)
{
    paut = paut*2;
}

static int hello_init(void)
{
    printk(KERN_ALERT "hello init\n");
    printk(KERN_ALERT "paut is %d\n", paut);
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "paut is %d\n", paut);
    printk(KERN_ALERT "hello exit\n");
}

EXPORT_SYMBOL(double_paut);
module_param(paut, int, S_IRUGO);
module_init(hello_init);
module_exit(hello_exit);
