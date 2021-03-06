/* ----------------------------------------------------------------------- */
/*                                                                         */
/*   Quartz Arc                                                            */
/*                                                                         */
/*   STM32 F103C6 Blue Pill                                                */
/*                                                                         */
/*   System: Core                                                          */
/*   Role: System Initialization                                           */
/*   Filename: boot.cpp                                                    */
/*   Date: 14th November 2021                                              */
/*   Created By: Benjamin Rosser                                           */
/*                                                                         */
/*   This code is covered by Creative Commons CC-BY-NC-SA license          */
/*   (C) Copyright 2021 Benjamin Rosser                                    */
/*                                                                         */
/* ----------------------------------------------------------------------- */

//Includes
#include "boot.hpp"


	//------------------------------------------
	//------------------------------------------
	//------------------------------------------

  //------------------------------
  //------------------------------
  //System Initialization Function

//SystemInitialize
//System Initialization Function
//
//Used to initialize flash prefetch, NVIC and SysTick, as well as oscillators, PLLs, system clocks, bus clocks and some peripheral clocks.
//Also enables all GPIOs
//
//Returns QA_OK if successful, or QA_Fail if initialized failed
QA_Result SystemInitialize(void) {

	//----------------------------
	//Enable Flash Prefetch Buffer
	__HAL_FLASH_PREFETCH_BUFFER_ENABLE();


	//--------------------------
	//Set NVIC Priority Grouping
	HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);


	//------------
	//Init SysTick
	HAL_InitTick(TICK_INT_PRIORITY);

  //---------------------
  //Configure Oscillators
  //
	RCC_OscInitTypeDef RCC_OscInit = {0};
  RCC_OscInit.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInit.HSEState       = RCC_HSE_ON;
  RCC_OscInit.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInit.PLL.PLLState   = RCC_PLL_ON;
  RCC_OscInit.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
  RCC_OscInit.PLL.PLLMUL     = RCC_PLL_MUL9;

  if (HAL_RCC_OscConfig(&RCC_OscInit) != HAL_OK) {
  	return QA_Fail;
  }


  //-------------------
  //Enable SysCfg Clock
  __HAL_RCC_SYSCFG_CLK_ENABLE();


  //--------------------------
  //Configure CPU & Bus Clocks
  //
  RCC_ClkInitTypeDef RCC_ClkInit = {0};
  RCC_ClkInit.ClockType       = RCC_CLOCKTYPE_HCLK |
  		                          RCC_CLOCKTYPE_SYSCLK |
																RCC_CLOCKTYPE_PCLK1 |
																RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInit.SYSCLKSource    = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInit.AHBCLKDivider   = RCC_SYSCLK_DIV1;
  RCC_ClkInit.APB1CLKDivider  = RCC_HCLK_DIV2;
  RCC_ClkInit.APB2CLKDivider  = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInit, FLASH_LATENCY_1) != HAL_OK) {
  	return QA_Fail;
  }


  //----------------------------
  //Initialize Peripheral Clocks
  RCC_PeriphCLKInitTypeDef RCC_PeriphClkInit = {0};
  RCC_PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USB;
  RCC_PeriphClkInit.UsbClockSelection    = RCC_USBCLKSOURCE_PLL_DIV1_5;

  if (HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphClkInit) != HAL_OK) {
  	return QA_Fail;
  }


  //------------------
  //Enable GPIO Clocks
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();


  //----------------
  //Enable DMA Clock
  __HAL_RCC_DMA1_CLK_ENABLE();


  //Return
  return QA_OK;
}


