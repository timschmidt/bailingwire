#ifndef DRIVER_AVR_GPIO_H
#define DRIVER_AVR_GPIO_H

function set_pin(int pin, int state){
	digitalWrite(pin, state);
}

struct function_pointers
{
	int &set_pin;
	int pin;
	int state;
}

function init_avr_gpio()
{
	return calloc( sizeof(struct function_pointers) );
}
#endif // DRIVER_AVR_GPIO_H
