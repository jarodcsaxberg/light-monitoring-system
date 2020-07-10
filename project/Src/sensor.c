#include <_ansi.h>
#include <_syslist.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/times.h>
#include <limits.h>
#include <signal.h>
#include <stdint.h>
#include <stdio.h>
#include "retarget.h"
#include "main.h"
#include <string.h>
#include <stdlib.h>

#include "sensor.h"

extern TIM_HandleTypeDef htim2;
extern ADC_HandleTypeDef hadc1;

volatile uint8_t captureDone = 0;

float calculate_freq() {
  uint32_t captures[2];
  uint32_t diffCapture = 0;
  float freq = 0;

  HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*) captures, 2);

  while(1){
    if(captureDone){
      if(captures[1] >= captures[0]) {
        diffCapture = captures[1] - captures[0];
      }
      else {
        diffCapture = (htim2.Instance->ARR - captures[0]) + captures[1];
      }

      freq = HAL_RCC_GetHCLKFreq() / (htim2.Instance->PSC + 1);
      freq = (float) freq / diffCapture;

      captureDone = 0;
      break;
    }
  }
  
  return freq;
}

uint32_t calculate_period() {
  uint32_t captures[2];
  uint32_t diffCapture = 0;

  HAL_TIM_IC_Start_DMA(&htim2, TIM_CHANNEL_1, (uint32_t*) captures, 2);

  while(1){
    if(captureDone){
      if(captures[1] >= captures[0]) {
        diffCapture = captures[1] - captures[0];
      }
      else {
        diffCapture = (htim2.Instance->ARR - captures[0]) + captures[1];
      }
      captureDone = 0;
      break;
    }
  }
  
  return diffCapture;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
    captureDone = 1;
  }
}

uint32_t read_temp(void) {
  static uint32_t first_time_up = 1;
  static ADC_ChannelConfTypeDef sConfig = {0};
  uint32_t rawTemp;
  uint32_t vref;
  uint32_t temp;
    
  if (first_time_up) {
    sConfig.Channel = ADC_CHANNEL_TEMPSENSOR;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_47CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    first_time_up = 0;
  }
  sConfig.Rank = ADC_REGULAR_RANK_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
      Error_Handler();
  }
  HAL_ADC_Start(&hadc1); 
  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  rawTemp = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  /* sConfig.Rank = ADC_REGULAR_RANK_2; */
  /* if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) { */
  /*     Error_Handler(); */
  /* } */
  vref = read_vrefint();
  temp = (__HAL_ADC_CALC_TEMPERATURE(vref,
                                     rawTemp,
                                     ADC_RESOLUTION_12B));
  return temp;
}

uint32_t read_vrefint(void) {
  static uint32_t first_time_up = 1;
  static ADC_ChannelConfTypeDef sConfig = {0};
  uint32_t rawVintref;

  if (first_time_up) {
    sConfig.Channel = ADC_CHANNEL_VREFINT;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_47CYCLES_5;
    sConfig.SingleDiff = ADC_SINGLE_ENDED;
    sConfig.OffsetNumber = ADC_OFFSET_NONE;
    sConfig.Offset = 0;
    first_time_up = 0;
  }
  sConfig.Rank = ADC_REGULAR_RANK_1;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
      Error_Handler();
  }
  HAL_ADC_Start(&hadc1); 
  HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
  rawVintref = HAL_ADC_GetValue(&hadc1);
  HAL_ADC_Stop(&hadc1);
  sConfig.Rank = ADC_REGULAR_RANK_2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
      Error_Handler();
  }
  return(__HAL_ADC_CALC_VREFANALOG_VOLTAGE(rawVintref, ADC_RESOLUTION_12B));
}
