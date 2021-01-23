#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"

ssize t proc read(struct file *file, char __user *usr_buf,
       size_t count, loff_t *pos);

static struct file_operations proc_ops = {
       .owner = THIS_MODULE,
       .read = proc_read,
};

int simple_init(void)
{
       printk(KERN_INFO "Loading Module\n");
       // printk(KERN_INFO "%lu\n", jiffies);
       // printk(KERN_INFO "%lu\n", HZ);
       proc_create(PROC_NAME, 0666, NULL, &proc_ops);

       return 0;
}


void simple_exit(void) {
	printk(KERN_INFO "Removing Module\n");
       remove_proc_entry(PROC_NAME, NULL);
}

module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

