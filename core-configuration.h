#ifndef CORE_CONFIGURATION_H
#define CORE_CONFIGURATION_H

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

new_device()
{
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

function register_device(){
	last_device();
	new_device();
	
	
};

#endif // CORE_CONFIGURATION_H
