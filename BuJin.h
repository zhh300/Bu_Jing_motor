#ifndef __BUJIN_H__
#define __BUJIN_H__

#include "main.h"
#include "tim.h"


//���ƽṹ�� 
typedef struct {
    volatile uint32_t remain_pulses;  // ʣ��������
    TIM_HandleTypeDef *htim;          // ��Ӧ��ʱ��
    uint32_t channel;                 // PWMͨ��
} PWM_Counter;

extern PWM_Counter pwm_ctr[4];        // ��·PWM������

/* �������� */
void Set_PWM_Frequency(TIM_HandleTypeDef *htim, 
                      uint32_t Channel, 
                      uint32_t frequency);

void Output_Pulse(TIM_HandleTypeDef *htim,
                 uint32_t Channel,
                 uint32_t pulse_num,
                 uint32_t frequency);

void Bu_Jin_Init ();




#endif /* __BUJIN_H__ */
