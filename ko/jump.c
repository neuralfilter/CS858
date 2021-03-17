#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/kernel.h>   
#include <linux/proc_fs.h>
#include <linux/uaccess.h>
#define BUFSIZE  100
 
 
MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Liran B.H");
 
static int irq=20;
module_param(irq,int,0660);
 
static int mode=1;
module_param(mode,int,0660);
 
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
 
static ssize_t myread(struct file *file, char __user *ubuf,size_t count, loff_t *ppos) 
{
	char buf[BUFSIZE];
	int len=0;
	if(*ppos > 0 || count < BUFSIZE)
		return 0;
	len += sprintf(buf,"irq = %d\n",irq);
	len += sprintf(buf + len,"mode = %d\n",mode);
	
	if(copy_to_user(ubuf,buf,len))
		return -EFAULT;
	*ppos = len;
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
