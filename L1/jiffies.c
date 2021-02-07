#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/jiffies.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#define BUFFER_SIZE 128
#define PROC_NAME "jiffies"

ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos);

static struct file_operations proc_ops = {
.owner = THIS_MODULE,
.read = proc_read,
};

/* method that runs on init */
int proc_init(void)
{
       proc_create(PROC_NAME, 0666, NULL, &proc_ops);
       return 0;
}


/* method that runs on exit */
void proc_exit(void)
{
       remove_proc_entry(PROC_NAME, NULL);
}


ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
       /* each time the file is read the function is called repeatedly until all data is collected*/
       int rv = 0;
       char buffer[BUFFER_SIZE];
       static int completed = 0;
       if (completed) {
              completed = 0;
              return 0;
       }
       completed = 1;
       /* prints the value of jiffies at the time the file is read */
       rv = sprintf(buffer, "%lu\n", jiffies);
       copy_to_user(usr_buf, buffer, rv);
       return rv;
}

/* macros that call their corresponding method */
module_init(proc_init);
module_exit(proc_exit);
