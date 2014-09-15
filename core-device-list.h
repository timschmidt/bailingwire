#ifndef CORE_DEVICE_LIST_H
#define CORE_DEVICE_LIST_H

//  - change name to core-device-list.h?
//  - populate the list

struct device_list
{
  int device_type;
  int driver;
  struct parents
  {
	  int device;
	  struct parents *next;
  };
  struct device_list *next;
};

/* This won't change, or we would lose the list in memory */
struct device_list *root_device;
/* This will point to each device as it traverses the list */
struct device_list *device;

function init_device_list()
{
    root_device = cmalloc( sizeof(struct device_list) );
    root_device->next = 0;
    device = root_device;
};

function next_device()
{    
    if ( device != 0 ) {
        while ( device->next != 0)
        {
            device = device->next;
        }
    }
};

function last_device()
{
	while ( device != 0 ) {
        while ( device->next != 0)
        {
            device = device->next;
        }
    }
};

function add_device(int device_type, int driver, int parent)
{
	last_device();
	
    /* Creates a device at the end of the list */
    device->next = cmalloc( sizeof(struct device_list) );

    device = device->next;

    if ( device == 0 )
    {
        printf( "Out of memory" );
        return 0;
    }
    /* initialize the new memory */
    device->next = 0;

    return 0;
};

function remove_device(struct *device)
{
	// point the previous device at the next device (special cases: removing the root device - point root at next device, removing the last device - point next at 0)
	free(device);
};

function add_parent(struct *device, struct *parent)
{
	
	
};

function remove_parent(struct *device, struct *parent)
{
	// point the previous parent at the next parent (special cases: removing the root parent - point root at next parent, removing the last parent - point next at nop function)
	free(parent);
};

#endif // CORE_DEVICE_LIST_H
