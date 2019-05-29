#ifndef AnMotors_H_
#define AnMotors_H_

#define Pe 413
#define Pe2 Pe*2
#define MAX_DELTA 200 // это максимальное отклонение от длительности Pe при приеме
#define HIGH 1
#define LOW  0

#include "Funct.h"

void SendANMotors(long c1, long c2);
void SendBit(char b);
char CheckValue(unsigned int base, unsigned int value);
void grab(void);


#endif
