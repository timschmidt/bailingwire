#ifndef DRIVER_8754_I2C_GPIO_H
#define DRIVER_8754_I2C_GPIO_H

function set_pin(*device_descriptor, state){
	// craft & issue i2c packet
	int pin = *(device_descriptor + 1);
}

struct device_descriptor
{
	int &set_pin(int *device_descriptor, state);
	int pin;
	int state;
}

function init_8754_i2c_gpio(int pin)
{
	int i2c_gpio = calloc( sizeof(struct device_descriptor) );
	if (i2c_gpio !=0)
	{
		*(i2c_gpio + 1) = pin;
	}
	return i2c_gpio;
}

#endif // DRIVER_8754_I2C_GPIO_H
