#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

MODULE_LICENSE("Daul GPL");

static int number = 10;
static char name[20] = "Name";

int my_proc_read(char *buf, char **start, off_t offset, int count, int *eof, void *data)
{
    int len = 0;
    len += sprintf(buf, "Number = %d\n", number);
    len += sprintf(buf, "Name   = %s\n", name);
    return len;
}

static int hello_init(void)
{
    printk("hello init\n");
    hello_file = proc_create("hello_proc", 0, NULL, NULL);
    return 0;
}

static void hello_exit(void)
{
    remove_proc_entry("hello_proc", NULL);
    printk("hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
