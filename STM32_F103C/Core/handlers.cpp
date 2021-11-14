/* ----------------------------------------------------------------------- */
/*                                                                         */
/*   Quartz Arc                                                            */
/*                                                                         */
/*   STM32 F103C6 Blue Pill                                                */
/*                                                                         */
/*   System: Core                                                          */
/*   Role: Exception & Interrupt Handlers                                  */
/*   Filename: handlers.cpp                                                */
/*   Date: 14th November 2021                                              */
/*   Created By: Benjamin Rosser                                           */
/*                                                                         */
/*   This code is covered by Creative Commons CC-BY-NC-SA license          */
/*   (C) Copyright 2021 Benjamin Rosser                                    */
/*                                                                         */
/* ----------------------------------------------------------------------- */

//Includes
#include "handlers.hpp"


	//------------------------------------------
	//------------------------------------------
	//------------------------------------------


  //---------------------------
  //---------------------------
  //Exception Handler Functions

//NMI_Handler
//Exception Handler Function
void  NMI_Handler(void) {

}


//HardFault_Handler
//Exception Handler Function
void  HardFault_Handler(void) {
  while (1) {}
}


//MemManage_Handler
//Exception Handler Function
void  MemManage_Handler(void) {
  while (1) {}
}


//BusFault_Handler
//Exception Handler Function
void  BusFault_Handler(void) {
  while (1) {}
}


//UsageFault_Handler
//Exception Handler Function
void  UsageFault_Handler(void) {
  while (1) {}
}


//SVC_Handler
//Exception Handler Function
void  SVC_Handler(void) {

}


//DebugMon_Handler
//Exception Handler Function
void  DebugMon_Handler(void) {

}


//PendSV_Handler
//Exception Handler Function
void  PendSV_Handler(void) {

}


//SysTick_Handler
//Exception Handler Function
void  SysTick_Handler(void) {
  HAL_IncTick();
}


	//------------------------------------------
	//------------------------------------------
	//------------------------------------------

  //---------------------------
	//---------------------------
	//Interrupt Handler Functions

