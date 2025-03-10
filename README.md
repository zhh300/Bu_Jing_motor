# STM32基于定时器产生pwm波控制步进电机
## CubeMX配置
### 1.1 系统时钟配置

​时钟源：选择HSE（外部晶振）或HSI（内部RC），通过PLL倍频至72MHz。

​时钟树：确保系统时钟（SYSCLK）为72MHz。

### 1.2 定时器配置

使用4个独立定时器（TIM1、TIM2、TIM3、TIM4），每个定时器配置1个PWM通道：

    TIM1：CH1（PA8）
    TIM2：CH1（PA0）
    TIM3：CH1（PA6）
    TIM4：CH1（PB6）

每个定时器参数：

    Prescaler (预分频器): 71（定时器时钟 = 72MHz / (71+1) = 1MHz）
    Counter Period (ARR): 999（初始频率 = 1MHz / 1000 = 1kHz）
    Pulse (CCR): 499（占空比50% = (999+1)/2 -1）
    
配置每个定时器的中断

## 代码
### 数据结构体：
    typedef struct {
        volatile uint32_t remain_pulses;  // 剩余脉冲数
        TIM_HandleTypeDef *htim;          // 对应定时器
        uint32_t channel;                 // PWM通道
    } PWM_Counter;

extern PWM_Counter pwm_ctr[4];        // 四路PWM控制器
### 函数功能：
#### 设置pwm频率
    void Set_PWM_Frequency(TIM_HandleTypeDef *htim, 
                          uint32_t Channel, 
                          uint32_t frequency);
#### 设置脉冲数目以及频率
    void Output_Pulse(TIM_HandleTypeDef *htim,
                     uint32_t Channel,
                     uint32_t pulse_num,
                     uint32_t frequency);
#### pwm启动初始化
    void Bu_Jin_Init ();
