// Accelleration in Marlin is accomplished by scaling the interrupt timer shared by all axes, uniformly scaling the pre-computed stepping ratios.  How to accomplish per-axis accelleration curves without incurring a per-tick re-evaluation of each axis's acceleration curve function?

// use promises to evaluate dynamic ladder-logic style constraints?  Better models?
// command / function list:
//  - call a per-coordinate system auto probing for axis _ (how are endstops / sensors specified?)
//  - calling convention for device drivers?

// test memory consumption / efficiency / api
// c linked lists: https://gist.github.com/obedrios/2957439
// cpp linked lists: https://gist.github.com/obedrios/3008397
// c calloc / free: http://www.cplusplus.com/reference/cstdlib/calloc/ http://www.cplusplus.com/reference/cstdlib/free/
// cpp new / delete: http://www.cplusplus.com/reference/new/operator%20new/


void setup() {
	buffer = calloc(6 * 32); // buffer 6x 32byte commands
	int *current_command = &buffer;
}

void loop() {
	// call core-idleloop();
}
