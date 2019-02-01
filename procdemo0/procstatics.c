#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/fs.h>		// for basic filesystem
#include <linux/proc_fs.h>	// for the proc filesystem
#include <linux/seq_file.h>	// for sequence files
#include <linux/jiffies.h>	// for jiffies
#include <linux/slab.h>		// for kzalloc, kfree
#include <linux/uaccess.h>	// for copy_from_user

#define M_STATIC_SPACE_SIZE (4*1024) 
// global var
static char *str = NULL;
 
// seq_operations -> show
static int jif_show(struct seq_file *m, void *v)
{
	seq_printf(m, "current kernel time is %llu\n", (unsigned long long) get_jiffies_64());
	seq_printf(m, "str is %s\n", str);
 
	printk("read %s !\n",str);
	return 0; //!! must be 0, or will show nothing T.T
}
 
// file_operations -> write
static ssize_t jif_write(struct file *file, const char __user *buffer, size_t count, loff_t *f_pos)
{
	//分配临时缓冲区
	
	if( NULL == str)
	{
		str = kzalloc(M_STATIC_SPACE_SIZE, GFP_KERNEL);
		
		if( NULL == str)
		{
			return -ENOMEM;			
		}
	}
 
	//将用户态write的字符串拷贝到内核空间
	//copy_to|from_user(to,from,cnt)
	if (copy_from_user(str, buffer, count)) {
		return -EFAULT;
	}
 
	printk("write %s !\n",buffer);
	return count;
}
 
// seq_operations -> open
static int jif_open(struct inode *inode, struct file *file)
{
	return single_open(file, jif_show, NULL);
}
 
static const struct file_operations jif_fops = 
{
	.owner		= THIS_MODULE,
	.open		= jif_open,
	.read		= seq_read,
	.write 		= jif_write,
	.llseek		= seq_lseek,
	.release	= single_release,
};
 
// module init
static int __init jif_init(void)
{
	struct proc_dir_entry* jif_file;
 
	jif_file = proc_create("jif", 0, NULL, &jif_fops);
	if (NULL == jif_file)
	{
	    return -ENOMEM;
	}
 
	return 0;
}
 
// module exit
static void __exit jif_exit(void)
{
	remove_proc_entry("jif", NULL);
	kfree(str);
}
 
module_init(jif_init);
module_exit(jif_exit);
 
MODULE_AUTHOR("aran");
MODULE_LICENSE("GPL");
