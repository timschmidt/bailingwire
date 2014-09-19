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
function init_simple_led(int gpio)
{
	int simple_led = calloc( sizeof(struct function_pointers) );
	if (simple_led !=0)
	{
		*(simple_led + 1) = gpio;
	}
	return simple_led;
}
#endif // DRIVER_SIMPLE_LED_H
