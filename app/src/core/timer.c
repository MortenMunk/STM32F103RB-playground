#include "core/timer.h"
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

// PA5 IS APPARENTLY NOT DRIVEN BY A TIMER ON MY BOARD, SO I WILL HAVE TO TRUST
// THE CODE, UNTIL I GET MY HANDS ON A BREADBOARD AND EXTERNAL LED, CONNECTED TO
// AVAILABLE PIN WITH A TIMER

// PRESCALER COMES FROM MHZ
#define PRESCALER (64)
#define ARR_VALUE (1000)

// freq = sys_freq / ((prescaled_val - 1) * (arr - 1))

void timer_setup(void) {
  rcc_periph_clock_enable(RCC_TIM2);

  // TIMER CONFIG
  timer_set_mode(TIM2, TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);

  // PWM SETUP
  timer_set_oc_mode(TIM2, TIM_OC1, TIM_OCM_PWM1);

  // PWM OUTPUT
  timer_enable_counter(TIM2);
  timer_enable_oc_output(TIM2, TIM_OC1);

  // SETUP FREQ AND RESOLUTION
  timer_set_prescaler(TIM2, PRESCALER - 1);
  timer_set_period(TIM2, ARR_VALUE - 1);
}

void timer_pwm_set_duty_cycle(float duty_cycle) {
  // duty cycle = (ccr / arr) * 100
  // duty cycle / 100 = crr /arr
  // ccr = arr * (duty cycle / 100)

  const float raw_value = (float)ARR_VALUE * (duty_cycle / 100.0f);
  timer_set_oc_value(TIM2, TIM_OC1, (uint32_t)raw_value);
}
