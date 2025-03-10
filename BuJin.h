#ifndef __BUJIN_H__
#define __BUJIN_H__

#include "main.h"
#include "tim.h"


//控制结构体 
typedef struct {
    volatile uint32_t remain_pulses;  // 剩余脉冲数
    TIM_HandleTypeDef *htim;          // 对应定时器
    uint32_t channel;                 // PWM通道
} PWM_Counter;

extern PWM_Counter pwm_ctr[4];        // 四路PWM控制器

/* 函数声明 */
void Set_PWM_Frequency(TIM_HandleTypeDef *htim, 
                      uint32_t Channel, 
                      uint32_t frequency);

void Output_Pulse(TIM_HandleTypeDef *htim,
                 uint32_t Channel,
                 uint32_t pulse_num,
                 uint32_t frequency);

void Bu_Jin_Init ();




#endif /* __BUJIN_H__ */
