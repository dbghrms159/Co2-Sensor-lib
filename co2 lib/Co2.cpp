/*
 * Co2.cpp
 *
 *  Created on: 2018. 9. 12.
 *      Author: yuhogeun
 */

#include "Co2.h"

#define 	READ_SAMPLE_INTERVSL	0.05	//샘플 값 추출 간
#define 	READ_SAMPLE_TIMES		5		//추출할 샘플값의 갯수
#define		DC_GAIN					8.5		//증폭회로의 전압이
#define		ZERO_POINT_VOLTAGE		0.324	//이산화 탄소가 400ppm일때의 전압값
#define		REACTION_VOLTAGE		0.020	//이산화 탄소가 1000ppm일때 전압값

Co2::Co2(PinName pin) {
	// TODO Auto-generated constructor stub
	_analog_pin = pin;
}

float Co2::read_Analog(){
	AnalogIn pin(_analog_pin);
	return pin.read();
}	//Analog read data return

float Co2::get_AnalogData(){
	float analog_read = 1023 * read_Analog();
	analog_read = analog_read * 3.3 / 1024;
	analog_read = 1023 * analog_read /5.0 ;

	return analog_read;
}	// 0 ~ 1의 값을  0 ~ 1023 값으로 변

void Co2::sample_Co2Data(){
	int i;

	v = 0;

	//샘플 추출 5회
	for(i = 0; i < READ_SAMPLE_TIMES; i ++){
		v += get_AnalogData();

		wait(READ_SAMPLE_INTERVSL);
	}

	v = (v/READ_SAMPLE_TIMES) * 5 / 1024;

}	//샘플링데이터 평균을 구해값 전력 반

float Co2::get_PPM(){
	float co2Curve[3] = {2.602,	ZERO_POINT_VOLTAGE,(REACTION_VOLTAGE/(2.602-3))};
    //위의 두 값들은 곡선위에 존제합니다.

    //이 두점에서 라인이 생성이 되는데,

    //원래의 곡선과 가깝습니다.

    //번역된 부분으로 읽는데 잘 파악이 되지는 않네요, 센서값 곡선 그래프에 맞추어 계산을 하기 위한 설정값들이라고 생각하면 될듯합니다.

    //data format:{ x, y, slope}; point1: (lg400, 0.324), point2: (lg4000, 0.280)

    //slope = ( reaction voltage ) / (log400 –log1000)


	return pow(10,((v/DC_GAIN)-co2Curve[1])/co2Curve[2] + co2Curve[0]);
}
