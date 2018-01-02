#include <linux/proc_fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/ioctl.h>

#define MY_IOC_MAGIC 's'

#define MY_IOCRESET _IO(MY_IOC_MAGIC, 0)

#define MY_IOC_MAXNR 1

void my_ioctl(struct inode *inode, struct file *flip, unsigned int cmd, unsigned int arg)
{
    int err = 0, tmp;
    int retval = 0;
    if (_IOC_TYPE(cmd) != MY_IOC_MAGIC) return -ENOTTY;
    if (_IOC_NR(cmd) > MY_IOC_MAXNR) return -ENOTTY;

    if (_IOC_DIR(cmd) & _IOC_READ)
        err = !access_ok(VERIFY_WRITE, (void __user *)arg, _IOC_SIZE(cmd));
    else if (_IOC_DIR(cmd) & _IOC_WRITE)
        err = !access_ok(VERIFY_READ, (void __user *)arg, _IOC_SIZE(cmd));
    if (err) return -EFAULT;

    swicth(cmd)
    {
        case MY_IOCRESET:
            break;
        
        default:
            return -ENOTTY;
    }
}

static file_operations fops=
{
    .owner = THIS_MODULE;
    .ioctl = my_ioctl;
}



module_init();
module_exit();