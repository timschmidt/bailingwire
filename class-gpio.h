#ifndef DEVICE_GPIO_H
#define DEVICE_GPIO_H

struct gpio
{
  bool operator()(const int &pin) const
  {
    return &pin
  }
  bool capabilities()() const
  {
	return "this many pins!";
  }
  
};

#endif // DEVICE_GPIO_H
