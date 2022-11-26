/***************************************************************************************
$ @ Copyright    : 
$ @ Author       : Krone
$ @ Data         : Do not edit
$ @ LastEditor   : 
$ @ LastData     : 
$ @ Describe     : 
*****************************************************************************************/
#include "bsp_gpio.h"
#include "main.h"


uint16_t phasecw[4] ={0x0200,0x0100,0x0080,0x0040}; /*   D-C-B-A  ?? */
uint16_t phaseccw[4]={0x0040,0x0080,0x0100,0x0200}; /*	 A-B-C-D   ?? */
/*---------------------------------????????????---------------------------------------------------*/
/* IN4: PB9  d */
/* IN3: PB8  c */
/* IN2: PB7  b */ 
/* IN1: PB6  a */

void Moto_Init(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 RCC_APB2PeriphClockCmd(MOTOR_CLK,ENABLE);

	 GPIO_InitStructure.GPIO_Pin = MOTOR_IN1_PIN | MOTOR_IN2_PIN | MOTOR_IN3_PIN | MOTOR_IN4_PIN ;//????INT1??????
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	 GPIO_Init(GPIOB,&GPIO_InitStructure);
	 GPIO_ResetBits(MOTOR_PORT, MOTOR_IN1_PIN | MOTOR_IN2_PIN |MOTOR_IN3_PIN |MOTOR_IN4_PIN );
}
// ??
void Motor_Forward_Ration(void)  
{  
    int i;  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(MOTOR_PORT, phaseccw[i]);  
        delay(1);  
    }  
}
// ??
void Motor_Reverse_Rotation(void)  
{  
	uint8_t i;  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(MOTOR_PORT, phasecw[i]);  
        delay_ms(1);  
    }  
}
//??
void MotorStop(void) 
{  
    GPIO_Write(MOTOR_PORT, 0x0000);  
}

//??????????????
//direction??,1???,0???
//angle??,??0-360??????
void Motor_Ctrl_Direction_Angle(int direction, int angle)
{
	uint16_t i;

	if(direction == 1)
	{								
		for(i = 0; i < 64*angle/45; i++) 
		{
			/* ?? */
			Motor_Forward_Ration();
		}
		MotorStop();//??
  	}
	else
	{
		for(i = 0; i < 64*angle/45; i++) 
		{
			/* ?? */
			Motor_Reverse_Rotation(); 
		}
		 MotorStop();//??
	}
}

