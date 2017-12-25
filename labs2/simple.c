#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/ioctl.h>
#include <linux/mm.h>
#include <asm/uaccess.h>
#include <linux/blkdev.h>
 
 
MODULE_DESCRIPTION("a simple char device driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("luke_swpu");

#define CDRIVER_NAME "simple_chrdev"

int CDRIVER_MAJOR=0;
int CDRIVER_MINOR=0;
int count=1;
 
static struct class *simple_class;
 
loff_t simple_llseek(struct file *filp,loff_t off,int whence);
long simple_ioctl(struct file *filp,unsigned int cmd,unsigned long arg);
int simple_open(struct inode *inode,struct file *filp);
int simple_release(struct inode *inode,struct file *filp);

static ssize_t simple_read(struct file *filp, __user char *buffer, size_t count, loff_t *ppos)
{
    int ret;
    int data = 0xdc; //sizoef(int)==4
 
    ret=copy_to_user(buffer, (char *)&data, sizeof(data)); 
    //copy_from_user
    if(ret<0)
    {
        printk("ret =%d \n",ret);
        return ret;
    }
    return sizeof(data);
}
 
extern struct file_operations simple_fops;
struct cdev *simple_cdev;
dev_t simple_dev;
static struct device *dev;
 
 
struct file_operations simple_fops=
{
 .owner=THIS_MODULE,
 .llseek=simple_llseek,
 .open=simple_open,
 .release=simple_release,
 .ioctl=simple_ioctl,
 .read=simple_read,
};
/*open*/
int simple_open(struct inode *inode,struct file *filp)
{
//do sth you want
//DEVICE INIT
    return 0;
}
/*llseek*/
loff_t simple_llseek(struct file *filp,loff_t off,int whence)
{
//do sth you want
    return 0;
}
 
/*ioctl*/
long simple_ioctl(struct file *filp,unsigned int cmd,unsigned long arg)
{
//do sth you want
    return 0;
}
 
int simple_release(struct inode *inode,struct file *filp)
{
    printk("simple device is released\n");
    //module_put(THIS_MODULE);
    return 0;
}
 
 
static int skeleton_init_module(void)
{
    int ret;
    printk( KERN_DEBUG "Module skeleton init\n" );
    /*register major and minor*/
    if(CDRIVER_MAJOR!=0)
    {
        simple_dev=MKDEV(CDRIVER_MAJOR,CDRIVER_MINOR);
        ret=register_chrdev_region(simple_dev,count,CDRIVER_NAME);
    }
    else
    {
        /*dynamic assign major*/
        ret=alloc_chrdev_region(&simple_dev,CDRIVER_MINOR,count,CDRIVER_NAME);
        CDRIVER_MAJOR=MAJOR(simple_dev);
    }
    if(ret<0)
    {
        printk(KERN_ERR"cannot get major %d \n",CDRIVER_MAJOR);
        return -1;
    }
    /*register character device driver*/
    simple_cdev=cdev_alloc();
    if(simple_cdev!=NULL)
    {
        cdev_init(simple_cdev,&simple_fops);
        simple_cdev->ops=&simple_fops;
        simple_cdev->owner=THIS_MODULE;
        if(cdev_add(simple_cdev,simple_dev,count)!=0)
        {
            printk(KERN_NOTICE "something wrong when adding simple_cdev!\n");
        }
        else
        {
            printk("success adding simple_cdev!\n");
        }
    }
    else
    {
        printk(KERN_ERR "register simple_dev error!\n");
        return -1;
    }
    simple_class = class_create(THIS_MODULE, "simple");
     
    if (IS_ERR(simple_class))
    {
        printk( KERN_DEBUG "class_create error\n" );
        return -1;
    }
    printk(KERN_ERR "devno is %d \n",simple_dev);
 //   dev=device_create(simple_class, NULL, simple_dev,"simple");
 //2.6.26ртион╙
    dev=device_create(simple_class, NULL, simple_dev,NULL,"simple");
   //DEVICE INITILIAZE
    return 0;
}
 
static void skeleton_exit_module(void)
{
    printk( KERN_DEBUG "Module skeleton exit\n" );
    device_destroy(simple_class, simple_dev);
    class_destroy(simple_class);
 
    cdev_del(simple_cdev);
    unregister_chrdev_region(simple_dev,count);
}
 
module_init(skeleton_init_module);
module_exit(skeleton_exit_module);
