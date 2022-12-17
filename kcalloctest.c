#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>

static int __init kcallocinit_func(void);
static void __exit kcallocexit_func(void);


#define MEM_MAX_SIZE 102400
char *pmem = NULL;


/*
typedef enum {
	GFP_KERNEL,
	GFP_ATOMIC,
	__GFP_HIGHMEM,
	__GFP_HIGH
} gfp_t;
*/


static int __init kcallocinit_func(void)
{
	pmem=(char*)kcalloc(4, MEM_MAX_SIZE, GFP_KERNEL);
	if(pmem == NULL)
	{
		printk("kcalloc failed!\n");
	} else
	{
		printk("pmem address is ==> 0x%lx\n",(unsigned long)pmem);
		printk("pmem size is ==> %d\n",(unsigned int)ksize(pmem));
		printk("address offset is:%d\n",*(pmem+100));
		printk("address offset is:%d\n",*(pmem+10000));

	}
	return 0;
}



static void __exit kcallocexit_func(void)
{
	if(NULL!=pmem)
	{
		kfree(pmem);
		printk("kfree called successfully");
	}

	printk("kernel module exited normally\n");
}

MODULE_LICENSE("GPL");
module_init(kcallocinit_func);
module_exit(kcallocexit_func);



