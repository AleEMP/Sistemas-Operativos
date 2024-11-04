#include <linux/module.h> /* Needed by all modules */
#include <linux/kernel.h> /* Needed for KERN_INFO */
int init_module(void)
{
printk(KERN_INFO "Hola Alejandra\n");
/*
* A non 0 return means init_module failed; module can't be loaded.
*/
return 0;
}
void cleanup_module(void)
{
printk(KERN_INFO "Adios Alejandra\n");
}

MODULE_LICENSE("GPL");
