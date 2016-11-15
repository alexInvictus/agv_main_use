#ifndef _KS103_H
#define _KS103_H
#include "myiic2.h"
#include "sys.h"
#include "delay.h"

u8 KS103_ReadOneByte(u8 address, u8 reg);
void KS103_WriteOneByte(u8 address,u8 reg,u8 command);
u16 Wave_test(void);
#endif


