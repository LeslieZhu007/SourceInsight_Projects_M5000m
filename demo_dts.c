#include <linux/init.h>
#include <linux/module.h>
#include <linux/of.h>


static int __init demo_dts_init(void)
{
	struct device_node *node = NULL;
	struct property *property;
	int lenp;
	node = of_find_node_by_path("/demo@114001e0");
	if(node == NULL)
	{
		printk("find node error\n");
		return -EINVAL;
	}

	property = of_find_property(node, "a-string-property", &lenp);
	if(property == NULL)
	{
		printk("find key value error\n");
		return -EINVAL;
	}

	printk("a-string-property = %s,lenp = %d\n",property->value,lenp);




	property = of_find_property(node, "a-string-list-property", &lenp);
	if(property == NULL)
	{
		printk("find key value error\n");
		return -EINVAL;
	}

	printk("list1 = %s,lenp = %d\n",property->value,lenp);
	printk("list2 = %s,lenp = %d\n",property->value+6,lenp);
	printk("list3 = %s,lenp = %d\n",property->value+12,lenp);



	property = of_find_property(node, "a-array-property", &lenp);
	if(property == NULL)
	{
		printk("find key value error\n");
		return -EINVAL;
	}

	printk("num1 = %x,lenp = %d\n",__be32_to_cpup(*(int *)property->value,lenp)); //大小端
	printk("num2 = %x,lenp = %d\n",__be32_to_cpup(*(int *)property->value+1,lenp));
	printk("num3 = %x,lenp = %d\n",__be32_to_cpup(*(int *)property->value+2,lenp));
	

	property = of_find_property(node, "a-mux-property", &lenp);
	if(property == NULL)
	{
		printk("find key value error\n");
		return -EINVAL;
	}

	printk("num1 = %s,lenp = %d\n",property->value,lenp)); //大小端
	printk("num2 = %x,lenp = %d\n",__be32_to_cpup((__be32 *)(property->value)+4),lenp);
	
	
	for (i = 0; i < 5; i++)
	{
		printk("num3 = %x,lenp = %d\n",property->value+20+i,lenp));
	}	


	return 0;
}


static void __exit demo_dts_exit(void)
{

}


module_init(demo_dts_init);
module_exit(demo_dts_exit);
MODULE_LICENSE("GPL");




