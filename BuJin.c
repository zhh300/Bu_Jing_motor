#include "BuJin.h"


PWM_Counter pwm_ctr[4];  // ��·PWM������


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if(htim->Instance == TIM1){
    // �ڴ˴������������߼�
    if(pwm_ctr[0].remain_pulses > 0){
      pwm_ctr[0].remain_pulses--;
      if(pwm_ctr[0].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
	
	if(htim->Instance == TIM2){
    // �ڴ˴������������߼�
    if(pwm_ctr[1].remain_pulses > 0){
      pwm_ctr[1].remain_pulses--;
      if(pwm_ctr[1].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
	
	if(htim->Instance == TIM3){
    // �ڴ˴������������߼�
    if(pwm_ctr[2].remain_pulses > 0){
      pwm_ctr[2].remain_pulses--;
      if(pwm_ctr[2].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
	
	if(htim->Instance == TIM4){
    // �ڴ˴������������߼�
    if(pwm_ctr[3].remain_pulses > 0){
      pwm_ctr[3].remain_pulses--;
      if(pwm_ctr[3].remain_pulses == 0){
        HAL_TIM_PWM_Stop(htim, TIM_CHANNEL_1);
      }
    }
  }
}



void Set_PWM_Frequency(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t frequency) {
    uint32_t timer_clock = 1000000; // ��ʱ��ʱ��=1MHz��Prescaler=71��
    uint32_t arr = (timer_clock / frequency) - 1;
    uint32_t ccr = (arr + 1) / 2 - 1;
    
    HAL_TIM_PWM_Stop(htim, Channel);       // ֹͣPWM
    htim->Instance->ARR = arr;             // ����ARR
    __HAL_TIM_SET_COMPARE(htim, Channel, ccr); // ����CCR
    HAL_TIM_PWM_Start(htim, Channel);      // ����PWM
}

void Output_Pulse(TIM_HandleTypeDef *htim, uint32_t Channel, uint32_t pulse_num, uint32_t frequency)
{
    uint8_t index = 0;
    
    // ȷ����ʱ������
    if (htim->Instance == TIM1) index = 0;
    else if (htim->Instance == TIM2) index = 1;
    else if (htim->Instance == TIM3) index = 2;
    else if (htim->Instance == TIM4) index = 3;
    
    // ����Ƶ�ʣ�����ԭ��Ƶ�������߼���
    Set_PWM_Frequency(htim, Channel, frequency);
    
    // ��ʼ��������
    pwm_ctr[index].htim = htim;
    pwm_ctr[index].channel = Channel;
    pwm_ctr[index].remain_pulses = pulse_num;
    
    // ���ж�����PWM
    HAL_TIM_PWM_Start_IT(htim, Channel);
}

void Bu_Jin_Init ()
{
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_TIM_Base_Start_IT(&htim3);
	HAL_TIM_Base_Start_IT(&htim4);
}
