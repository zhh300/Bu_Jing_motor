#include "BuJin.h"


PWM_Counter pwm_ctr[4];  // 四路PWM计数器


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1){
    // 在此处添加脉冲计数逻辑
    if(pwm_ctr[0].remain_pulses > 0){
      pwm_ctr[0].remain_pulses--;
      if(pwm_ctr[0].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
	
	if(htim->Instance == TIM2){
    // 在此处添加脉冲计数逻辑
    if(pwm_ctr[1].remain_pulses > 0){
      pwm_ctr[1].remain_pulses--;
      if(pwm_ctr[1].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
	
	if(htim->Instance == TIM3){
    // 在此处添加脉冲计数逻辑
    if(pwm_ctr[2].remain_pulses > 0){
      pwm_ctr[2].remain_pulses--;
      if(pwm_ctr[2].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
	
	if(htim->Instance == TIM4){
    // 在此处添加脉冲计数逻辑
    if(pwm_ctr[3].remain_pulses > 0){
      pwm_ctr[3].remain_pulses--;
      if(pwm_ctr[3].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
}



void Set_PWM_Frequency(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t frequency) {
    uint32_t timer_clock = 1000000; // 定时器时钟=1MHz（Prescaler=71）
    uint32_t arr = (timer_clock / frequency) - 1;
    uint32_t ccr = (arr + 1) / 2 - 1;
    
    HAL_TIM_PWM_Stop(htim, Channel);       // 停止PWM
    htim->Instance->ARR = arr;             // 设置ARR
    __HAL_TIM_SET_COMPARE(htim, Channel, ccr); // 设置CCR
    HAL_TIM_PWM_Start(htim, Channel);      // 启动PWM
}

void Output_Pulse(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t pulse_num, uint32_t frequency)
{
    uint8_t index = 0;
    
    // 确定定时器索引
    if (htim->Instance == TIM1) index = 0;
    else if (htim->Instance == TIM2) index = 1;
    else if (htim->Instance == TIM3) index = 2;
    else if (htim->Instance == TIM4) index = 3;
    
    // 配置频率（保持原有频率设置逻辑）
    Set_PWM_Frequency(htim, Channel, frequency);
    
    // 初始化计数器
    pwm_ctr[index].htim = htim;
    pwm_ctr[index].channel = Channel;
    pwm_ctr[index].remain_pulses = pulse_num;
    
    // 带中断启动PWM
    HAL_TIM_PWM_Start_IT(htim, Channel);
}

void Bu_Jin_Init ()
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
}
