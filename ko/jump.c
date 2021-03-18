//https://devarea.com/linux-kernel-development-creating-a-proc-file-and-interfacing-with-user-space/#.YFKLuZNKi3I
//https://github.com/kmcallister/alameda/blob/master/ko/jump.c

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#define BUFSIZE  100
 
static struct proc_dir_entry *ent;
 
static ssize_t mywrite(struct file *file, const char __user *buf, size_t len, loff_t *data) 
{
	void (*fun)(void);

    if (len < sizeof(fun))
        return -EINVAL;

    if (copy_from_user(&fun, buf, sizeof(fun)))
        return -EFAULT;

    printk("jump.ko: Jumping to %p\n", fun);
    fun();

    return len;
}

static struct file_operations myops = 
{
	.owner = THIS_MODULE,
	.write = mywrite,
};
 
static int simple_init(void)
{
	ent=proc_create("jump",0664,NULL,&myops);
	printk(KERN_ALERT "hello...\n");
	return 0;
}
 
static void simple_cleanup(void)
{
	proc_remove(ent);
	printk(KERN_WARNING "bye ...\n");
}
 
module_init(simple_init);
module_exit(simple_cleanup);

MODULE_AUTHOR("Keegan McAllister");
MODULE_DESCRIPTION("Incredibly insecure kernel module for testing exploitation techniques");
MODULE_LICENSE("Dual BSD/GPL");

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liran B.H");
