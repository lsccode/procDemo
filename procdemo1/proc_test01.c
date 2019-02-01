#include <linux/module.h>
#include <linux/sched.h> //jiffies
#include <linux/proc_fs.h>
#include <linux/uaccess.h> //copy_to|from_user()
#include <linux/slab.h>
 
static char *str = NULL;
 
//proc�ļ��Ķ�����
static int my_proc_read(char *page, char **start, off_t off, int count, int *eof, void *data)
{
	int ret = 0;
	ret = sprintf(page, "current kernel time is %ld\n", jiffies);
	ret += sprintf(page+ret, "str is %s\n", str);
 
	return ret;
}
 
//proc�ļ���д����
static int my_proc_write(struct file *filp, const char __user *buf, unsigned long count, void *data)
{
	//������ʱ������
	char *tmp = kzalloc((count+1), GFP_KERNEL);
	if (!tmp)
		return -ENOMEM;
 
	//���û�̬write���ַ����������ں˿ռ�
	//copy_to|from_user(to,from,cnt)
	if (copy_from_user(tmp, buf, count)) {
		kfree(tmp);
		return -EFAULT;
	}
 
	//��str�ľɿռ��ͷţ�Ȼ��tmp��ֵ��str
	kfree(str);
	str = tmp;
 
	return count;
}
 
 
static int __init my_init(void)
{
	struct proc_dir_entry *file;
 
	//����proc�ļ�
	file = create_proc_entry("jif", 0666, NULL);
	if (!file) {
		printk("Cannot create /proc/jif\n");
		return -1;
	}
 
	//�������õ��ļ��Ͷ�д����������һ��
	file->read_proc = my_proc_read;
	file->write_proc = my_proc_write;
 
	return 0;
}
 
static void __exit my_exit(void)
{
	//ɾ��proc�ļ�
	remove_proc_entry("jif", NULL);
	kfree(str);
}
 
module_init(my_init);
module_exit(my_exit);
MODULE_AUTHOR("aran");
MODULE_LICENSE("GPL");
