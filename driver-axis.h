#ifndef DRIVER_AXIS_H
#define DRIVER_AXIS_H

// consumes: pointer to: one actuator, one sensor, one feedback device, and one control loop
// returns: pointer to: one axis

function home(){
	
}

struct device_descriptor
{
	int &home();
	int *actuator;
	int *feedback;
	int *control_loop;
	int *endstop;
	int *native_units;
	double length;
	
}

function init_axis()
{
	int axis = calloc( sizeof(struct device_descriptor) );
	if (axis !=0)
	{
		// populate struct
	}
	return axis;
}

#endif // DRIVER_AXIS_H
