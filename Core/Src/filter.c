/*
 * filter.c
 *
 *  Created on: Feb 6, 2023
 *      Author: npedu002
 */

#include "filter.h"

uint16_t AvgFilter(uint16_t inData){
	//몇번 필터하느냐에 따라 정밀도가 달라짐
	static uint16_t filterBuffer[100];
	static uint16_t sumValue = 0;
	static uint8_t bufPos = 0;
	// 합계에서 현재위치의 버퍼값을 빼기
	sumValue -= filterBuffer[bufPos];
	// 현재위치의 버퍼값 생성
	filterBuffer[bufPos]= inData;
	// 합계에서 현재위치의 버퍼값을 더하기
	sumValue += filterBuffer[bufPos];
	//덧셈을 줄이기 위하여 이러한 방식을 씀
	bufPos++;
	bufPos %= 100;
	//100이 되면 0이되도록
	return sumValue /100;
	//100개의 buffer니까 100을 나눠주면 평균값이 나옴
}

double Kalman(double measurement) {
    // Kalman filter setup
    static double P = 1.0;
    static double varP = 0.0001;  // pow(0.01, 2)
    static double R = 0.25;//pow(0.5, 2);
    static double K = 1.0;
    static double X = 20.0;

    // Kalman Simple Filter(수식 치환)
    P = P + varP;
    K = P / (P + R);
    X = (K * measurement) + (1 - K) * X;
    P = (1 - K) * P;

    return X;
}

