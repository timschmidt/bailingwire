#ifndef DRIVER_ULN2003_STEPPER_H
#define DRIVER_ULN2003_STEPPER_H

function step(int direction)
{
	analogWrite(gpio, brightness);
}

struct function_pointers
{
	int &step(int direction);
	int *gpio_1;
	int *gpio_2;
	int *gpio_3;
	int *gpio_4;
	int direction;
	int steps_per_revolution;
	long long position;
}

// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, and return a pointer to the memory address of the struct
function init_uln2003_stepper()
{
	int uln2003 = calloc( sizeof(struct function_pointers) );
	if (uln2003 = 0)
	{
		//fail - out of memory
	}
	return uln2003;
}

#endif // DRIVER_ULN2003_STEPPER_H
