#include <linux/init.h>
#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/string.h>

MODULE_LICENSE("Dual BSD/GPL");

static struct kobject *dummy_kobj;

static ssize_t dummy_show(struct kobject *kobj, struct kobj_attribute *attr, char *buffer){
    return sprintf(buffer, "You have read from /sys/kernel/%s%s \n", kobj->name, attr->attr.name); 
}

static ssize_t dummy_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buffer, size_t count){
    printk(buffer, "sysfs_test - YOu wrote '%s' /kernel/%s%s \n", buffer, kobj->name, attr->attr.name);    
    return count;
}

static struct kobj_attribute dummy_attr = __ATTR(dummy, 0660, dummy_show, dummy_store);

static int hello_init(void)
{   printk("sysfs_test - Ceating /sys/kernel/hello/dummy");
    dummy_kobj = kobject_create_and_add("hello", kernel_kobj);
    if(!dummy_kobj){
        printk("sysfs_test - Error creating");
        return -ENOMEM;
    }

    if(sysfs_create_file(dummy_kobj, &dummy_attr.attr)){
        printk("sysfs_test - error creating");
        kobject_put(dummy_kobj);
        return -ENOMEM;
    }

    return 0;
}

static void hello_exit(void)
{
    printk("Sysfs_test - deleting /sys/kernel/hello/dummy \n");
    sysfs_remove_file(dummy_kobj, &dummy_attr.attr);
    kobject_put(dummy_kobj);
}

module_init(hello_init);
module_exit(hello_exit);