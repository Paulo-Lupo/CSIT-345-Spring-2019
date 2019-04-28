#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/list.h>

/* Creates a structure of type birthday for the linked list */
typedef struct birthday {
    int month;
    int day;
    int year;
    struct list_head list;
} Bday;

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void) {

    printk(KERN_INFO "Loading Module test and Creating linked list\n");
    /* Creates 3 birthdays */
    Bday *person_one, *person_two, *person_three, *ptr;
    
    /* Allocates memory in the kernel for each person's birthday*/
    person_one = kmalloc(sizeof(*person_one), GFP_USER);  
    person_two = (Bday*)kmalloc(sizeof(Bday), GFP_USER); 
    person_three = (Bday*)kmalloc(sizeof(Bday), GFP_USER); 
   
  
    /* Change the values and the "next" pointers of each birthday*/
    person_one->month = 7;
    person_one->day = 14;
    person_one->year = 1999;


    person_two->month = 10;
    person_two->day = 5;
    person_two->year = 1993;

    person_three->month = 3;    
    person_three->day = 27;
    person_three->year = 1978;


    INIT_LIST_HEAD(&person_one->list);
    list_add_tail(&person_one->list, &birthday_list);
    list_add_tail(&person_two->list, &birthday_list); 
    list_add_tail(&person_three->list, &birthday_list);
    
    /* Traversing the linked list of birthdays */
    printk(KERN_INFO "Traversing linked list\n");
    list_for_each_entry(ptr, &birthday_list, list) 
    {
         printk(KERN_INFO "Adding birthday: %d/%d/%d\n", ptr->month, ptr->day, ptr->year);
    }    

    printk(KERN_INFO "Finished loading the module\n");
    return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) 
{
    Bday *ptr, *next;
    printk(KERN_INFO "Removing Module and deleting the linked list\n");
    
    /* removes each entry of the linked list of birthday */
    list_for_each_entry_safe(ptr, next, &birthday_list, list) 
    {
        printk(KERN_INFO "Removing birthday: %d/%d/%d\n", ptr->month, ptr->day, ptr->year);
        list_del(&ptr->list);
        kfree(ptr);
    }
    
    printk(KERN_INFO "Finished deleting the modue\n");
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
