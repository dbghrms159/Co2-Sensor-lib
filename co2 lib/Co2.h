/*
 * Co2.h
 *
 *  Created on: 2018. 9. 12.
 *      Author: yuhogeun
 */

#ifndef SRC_CO2_H_
#define SRC_CO2_H_

#include "mbed.h"

class Co2 {
private:
	PinName	_analog_pin;
	float read_Analog();
	float get_AnalogData();
	float v;
public:
	Co2(PinName);
	void sample_Co2Data();
	float get_PPM();
};

#endif /* SRC_CO2_H_ */
