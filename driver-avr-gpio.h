#ifndef DRIVER_AVR_GPIO_H
#define DRIVER_AVR_GPIO_H

function set_pin(pin, state){
	digitalWrite(pin, state);
}

struct function_pointers
{
	int &set_pin;
	int pin
}

// calloc memory sufficient for a copy of the driver struct, populate it with all the state for that instance, and return a pointer to the memory address of the struct
function init_avr_328_gpio()
{
	return calloc( sizeof(struct function_pointers) );
}
#endif // DRIVER_AVR_GPIO_H
