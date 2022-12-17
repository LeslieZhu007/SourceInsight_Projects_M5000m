#include <linux/module.h>
#include <linux/init.h>
#include <linux/vmalloc.h>
#include <linux/security.h>
#include <linux/mm.h>

#include <linux/slab.h>

static int __init vmalloctopageinit_func(void);
static void __exit vmalloctopageexit_func(void);

#define VMALLOC_MAXSIZE 102400
char* pAddrs=NULL;

static int __init vmalloctopageinit_func(void)
{
	pAddrs = (char *)vmalloc(VMALLOC_MAXSIZE);
	if (NULL==pAddrs)
	{
		printk("system calling vmalloc failed!\n");
	} else
	{
		printk("system calling vmalloc succeeded!\n");
		printk("address returned is: 0x%lx!\n",(unsigned long)pAddrs);

		struct page *topage = NULL;
		
		topage = vmalloc_to_page(pAddrs);

		printk("topage address:0x%lx\n",topage);


		topage = vmalloc_to_page(pAddrs+4096);


		printk("topage address offset:0x%lx\n",topage);
	}

	return 0;
}



static void __exit vmalloctopageexit_func(void)
{
	if(NULL!=pAddrs)
	{
		vfree(pAddrs);
		printk("Exiting kernel normally");
	}
}

MODULE_LICENSE("GPL");
module_init(vmalloctopageinit_func);
module_exit(vmalloctopageexit_func);


