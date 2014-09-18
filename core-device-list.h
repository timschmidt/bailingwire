#ifndef CORE_DEVICE_LIST_H
#define CORE_DEVICE_LIST_H

int device_count;
int *device_list;

function init_device_list()
{
    device_list = calloc( 1 );
    // store the root device
};

function add_device( int driver )
{
	// realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
	int new_device_list = realloc(device_list, device_count + 1);
	if (new_device_list != 0) device_list = new_device_list;
	*(device_list + device_count) = initialize_driver(driver);
	device_count++;
};

function remove_device( struct *device )
{
	// moves device-to-be-removed to the last position, realloc's *device_list to (devices * 1 byte), updating device_list, and stores the new device's data in the last position.
	
};

#endif // CORE_DEVICE_LIST_H
