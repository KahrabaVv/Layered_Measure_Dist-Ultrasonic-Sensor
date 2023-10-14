/*
 * ultra.h
 *
 *  Created on: Oct 12, 2023
 *      Author: Kerolossamehel-shaip
 */
#include "std_types.h"
#ifndef ULTRA_H_
#define ULTRA_H_
void Ultrasonic_init(void);
void Ultrasonic_Trigger(void);
uint16 Ultrasonic_readDistance(void);
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRA_H_ */
