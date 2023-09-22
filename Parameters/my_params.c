#include <linux/init.h>
#include <linux/module.h>

MODULE_LICENSE("Dual BSD/GPL");

static unsigned int gpio_nr = 12;
static char *device_name = "testdevice";

module_param(gpio_nr, uint, S_IRUGO);
module_param(device_name, charp, S_IRUGO);

MODULE_PARM_DESC(gpio_nr, "Nr of gpio");
MODULE_PARM_DESC(device_name, "device name to use");

static int hello_init(void)
{
    printk("gpio nr = %d\n", gpio_nr);
    printk("device name = %s \n", device_name);
    printk(KERN_ALERT "Hello, world\n");
    return 0;
}

static void hello_exit(void)
{
    printk(KERN_ALERT "Goodbye, cruel world\n");
}

module_init(hello_init);
module_exit(hello_exit);