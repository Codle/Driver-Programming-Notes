#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/slab.h>

#define STRLEN 1024

MODULE_LICENSE("Daul GPL");

static char global_buffer[STRLEN] = "Hello World\0"; 
struct proc_dir_entry *hello_file;  

int open_procmem(struct inode *inode, struct file *filp)  
{  
    filp->private_data = global_buffer;
    return 0;  
}  

ssize_t read_procmem(struct file *filp, char __user *buff, size_t size, loff_t *offp)
{
    long offset = (long)offp;
    printk("proc read, size is %d\n", (int)size);
    printk("offset is %ld\n", offset);
    if( offset < strlen(buff) )
    {
        copy_to_user(buff, (void *)filp->private_data, size);
        printk("buff is %s\n", buff);
        return strlen(buff);
    }
    else
        return 0;
}

ssize_t write_procmem(struct file *filp, const char __user *buff, size_t size, loff_t *offp)
{
    ssize_t ret;
    printk("proc write, size is %d\n", (int)size);
    ret = copy_from_user(filp->private_data, buff, size);
    return ret;
}

static struct file_operations proc_fops =
{
    .open = open_procmem,
    .read = read_procmem,
    .write = write_procmem,
    .owner = THIS_MODULE,
};

static int hello_init(void)
{
    printk("hello init\n");
    hello_file = proc_create("hello_proc", 0x644, NULL, &proc_fops);
    return 0;
}

static void hello_exit(void)
{
    remove_proc_entry("hello_proc", NULL);
    printk("hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
