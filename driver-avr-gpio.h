#ifndef DRIVER_AVR_GPIO_H
#define DRIVER_AVR_GPIO_H

function set_pin(int pin, int state){
	digitalWrite(pin, state);
}

struct device_descriptor
{
	int &set_pin(int pin, int state);
	int pin;
	int state;
}

function init_avr_gpio(int pin)
{
	int avr_gpio = calloc( sizeof(struct device_descriptor) );
	if (avr_gpio !=0)
	{
		*(avr_gpio + 1) = pin;
	}
	return avr_gpio;
}
#endif // DRIVER_AVR_GPIO_H
