#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "hello"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
.owner = THIS_MODULE,
.read = proc_read,
};

int proc_init(void)
{
       proc_create(PROC_NAME, 0666, NULL, &proc_ops);
       return 0;
}

void proc_exit(void)
{
       remove_proc_entry(PROC_NAME, NULL);
}