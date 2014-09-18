#ifndef CORE_DEVICE_LIST_H
#define CORE_DEVICE_LIST_H

int *device_list;

function init_device_list()
{
    device_list = calloc( 1 );
    // store the root device
};

function add_device(int device_type, int driver, int parent)
{
	// realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
	
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
	
	/* This will point to each parent device as it traverses the list of parents */
	struct parents *parent;
	
    device->next = calloc( sizeof(struct device_list) );

    device = device->next;

    if ( device == 0 )
    {
        printf( "Out of memory" );
        return 0;
    }
    /* initialize the new memory */
    device->next		= 0;
    device->device_type = device_type;
    device->driver      = driver;
    device->parent      = parent;
    return 0;
};

function remove_device(struct *device)
{
	// moves device-to-be-removed to the last position, realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
};

#endif // CORE_DEVICE_LIST_H
