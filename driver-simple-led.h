#ifndef DRIVER_SIMPLE_LED_H
#define DRIVER_SIMPLE_LED_H

function set_led(int gpio, float brightness){
	analogWrite(gpio, brightness);
}

struct function_pointers
{
	int &set_led(brightness);
	int *gpio;
	float brightness;
}

// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, and return a pointer to the memory address of the struct
function init_simple_led()
{
	return calloc( sizeof(struct function_pointers) );
}
#endif // DRIVER_SIMPLE_LED_H
