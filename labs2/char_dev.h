#include <linux/module.h>   
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/init.h>
#include <linux/ioctl.h>
#include <linux/slab.h>
#include <linux/uaccess.h>

//=======================字符设备驱动模板开始 ===========================//   
#define CHAR_DEV_DEVICE_NAME   "char_dev"           // 是应当连接到这个编号范围的设备的名字，出现在/proc/devices和sysfs中   
#define CHAR_DEV_NODE_NAME    "char_dev"            // 节点名，出现在/dev中   
#define CHAR_DEV_CLASS_NAME   "char_dev_class"      //出现在/sys/devices/virtual/和/sys/class/中   

#ifndef CHAR_DEV_SIZE
#define CHAR_DEV_SIZE 4096
#endif

struct char_dev
{
    char *data;
    unsigned int size;
    struct cdev _cdev;
};

struct class *char_dev_class;       // class结构用于自动创建设备结点    
static int major = 0;               // 0表示动态分配主设备号，可以设置成未被系统分配的具体的数字。   
// static struct cdev char_dev_cdev;   // 定义一个cdev结构 
static struct char_dev * char_devp;