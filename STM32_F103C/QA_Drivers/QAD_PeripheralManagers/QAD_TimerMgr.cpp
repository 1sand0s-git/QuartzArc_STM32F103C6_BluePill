/* ----------------------------------------------------------------------- */
/*                                                                         */
/*   Quartz Arc                                                            */
/*                                                                         */
/*   STM32 F103C6 Blue Pill                                                */
/*                                                                         */
/*   System: Driver                                                        */
/*   Role: Timer Management Driver                                         */
/*   Filename: QAD_TimerMgr.cpp                                            */
/*   Date: 27th November 2021                                              */
/*   Created By: Benjamin Rosser                                           */
/*                                                                         */
/*   This code is covered by Creative Commons CC-BY-NC-SA license          */
/*   (C) Copyright 2021 Benjamin Rosser                                    */
/*                                                                         */
/* ----------------------------------------------------------------------- */

//Includes
#include "QAD_TimerMgr.hpp"


	//------------------------------------------
	//------------------------------------------
	//------------------------------------------


  //-------------------------
  //-------------------------
	//QAD_TimerMgr Constructors

//QAD_TimerMgr::QAD_TimerMgr
//QAD_TimerMgr Constructor
//
//Fills out details for the system's Tiemr peripherals
//As this is a private method in a singleton class, this method will be called the first time the class's get() method is called
QAD_TimerMgr::QAD_TimerMgr() {

  for (uint8_t i=0; i < QAD_Timer_PeriphCount; i++) {
  	m_sTimers[i].eState   = QAD_Timer_Unused;
  	m_sTimers[i].bEncoder = true;
  	m_sTimers[i].bADC     = false; //NEEDS TO BE UPDATED
  }

  //Set Timer Periph ID
  m_sTimers[QAD_Timer1].eTimer  = QAD_Timer1;
  m_sTimers[QAD_Timer2].eTimer  = QAD_Timer2;
  m_sTimers[QAD_Timer3].eTimer  = QAD_Timer3;

	//Set clock speeds
	m_sTimers[QAD_Timer1].uClockSpeed  = HAL_RCC_GetPCLK2Freq();
	m_sTimers[QAD_Timer2].uClockSpeed  = HAL_RCC_GetPCLK1Freq() * 2;
	m_sTimers[QAD_Timer3].uClockSpeed  = HAL_RCC_GetPCLK1Freq() * 2;

	//Set types
	m_sTimers[QAD_Timer1].eType  = QAD_Timer_16bit;
	m_sTimers[QAD_Timer2].eType  = QAD_Timer_16bit;
	m_sTimers[QAD_Timer3].eType  = QAD_Timer_16bit;

	//Set channel counts
	m_sTimers[QAD_Timer1].uChannels  = 4;
	m_sTimers[QAD_Timer2].uChannels  = 4;
	m_sTimers[QAD_Timer3].uChannels  = 4;

	//Set Instances
	m_sTimers[QAD_Timer1].pInstance  = TIM1;
	m_sTimers[QAD_Timer2].pInstance  = TIM2;
	m_sTimers[QAD_Timer3].pInstance  = TIM3;

	//Set Update IRQs
	m_sTimers[QAD_Timer1].eIRQ_Update  = TIM1_UP_IRQn;
	m_sTimers[QAD_Timer2].eIRQ_Update  = TIM2_IRQn;
	m_sTimers[QAD_Timer3].eIRQ_Update  = TIM3_IRQn;

}


  //-------------------------------
  //-------------------------------
  //QAD_TimerMgr Management Methods

//QAD_TimerMgr::imp_registerTimer
//QAD_TimerMgr Management Method
//
//To be called from static method registerTimer()
//Used to register a Timer peripheral as being used by a driver
//eTimer - The timer peripheral to be registered. A member of QAD_Timer_Periph
//eState - The purpose the timer is to be used for. A member of QAD_Timer_State
//         QAD_Timer_InUse_IRQ     - Specifies timer as being used to trigger regular update IRQ
//         QAD_Timer_InUse_Encoder - Specifies timer as being used in rotary encoder mode
//         QAD_Timer_InUse_PWM     - Specifies timer as being used to generate PWM signals
//         QAD_Timer_InUse_ADC     - Specifies timer as being used to trigger ADC conversions
//Returns QA_OK if registration is successful.
//        QA_Fail if eState is set to QAD_Timer_Unused.
//        QA_Error_PeriphBusy if selected Timer is already in use
QA_Result QAD_TimerMgr::imp_registerTimer(QAD_Timer_Periph eTimer, QAD_Timer_State eState) {
  if (m_sTimers[eTimer].eState)
  	return QA_Error_PeriphBusy;

  if (!eState)
  	return QA_Fail;

  m_sTimers[eTimer].eState = eState;
  return QA_OK;
}


//QAD_TimerMgr::imp_deregisterTimer
//QAD_TimerMgr Management Method
//
//To be called from static method registerTimer()
//Used to deregister a Timer peripheral to mark it as no longer being used by a driver
//eTimer - The Timer peripheral to be deregistered. A member of QAD_Timer_Periph
void QAD_TimerMgr::imp_deregisterTimer(QAD_Timer_Periph eTimer) {
  m_sTimers[eTimer].eState = QAD_Timer_Unused;
}


//QAD_TimerMgr::imp_findTimer
//QAD_TimerMgr Management Method
//
//To be called from static method findTimer()
//Used to find an available timer with the selected counter type (16bit or 32bit)
//If a 16bit counter type is selected, a 32bit timer can be returned due to 32bit timers having 16bit support
//eType - A member of QAD_Timer_Type to select if a 16bit or 32bit counter is required
//Returns QAD_TimerNone if no available timer is found, or another member of QAD_Timer_Periph for the available timer that has been found
QAD_Timer_Periph QAD_TimerMgr::imp_findTimer(QAD_Timer_Type eType) {

	for (uint8_t i=0; i<QAD_Timer_PeriphCount; i++) {
		if ((eType <= m_sTimers[i].eType) && (!m_sTimers[i].eState))
			return m_sTimers[i].eTimer;
	}
	return QAD_TimerNone;
}


//QAD_TimerMgr::imp_findTimerEncoder
//QAD_TimerMgr Management Method
//
//To be called from static method findTimerEncoder()
//Used to find an available timer with rotary encoder support
//Returns QAD_TimerNone if no available timer is found, or another member of QAD_Timer_Periph for the available timer that has been found
QAD_Timer_Periph QAD_TimerMgr::imp_findTimerEncoder(void) {

	for (uint8_t i=0; i<QAD_Timer_PeriphCount; i++) {
		if ((!m_sTimers[i].eState) && (m_sTimers[i].bEncoder))
			return m_sTimers[i].eTimer;
	}
	return QAD_TimerNone;
}


//QAD_TimerMgr::imp_findTimerADC
//QAD_TimerMgr Management Method
//
//To be called from static method findTimerADC()
//Used to find an available timer with ADC conversion triggering support
//Returns QAD_TimerNone if no available timer is found, or another member of QAD_Timer_Periph for the available timer that has been found
QAD_Timer_Periph QAD_TimerMgr::imp_findTimerADC(void) {

	for (uint8_t i=0; i<QAD_Timer_PeriphCount; i++) {
		if ((!m_sTimers[i].eState) && (m_sTimers[i].bADC))
			return m_sTimers[i].eTimer;
	}
	return QAD_TimerNone;
}


  //--------------------------
  //--------------------------
  //QAD_TimerMgr Clock Methods


//QAD_TimerMgr::imp_enableClock
//QAD_TimerMgr Clock Method
//
//To be called by enableClock()
//Used to enable the clock for a specific Timer peripheral
//eTimer - the Timer peripheral to enable the clock for
void QAD_TimerMgr::imp_enableClock(QAD_Timer_Periph eTimer) {
  switch (eTimer) {
    case (QAD_Timer1):
    	__HAL_RCC_TIM1_CLK_ENABLE();
      __HAL_RCC_TIM1_FORCE_RESET();
      __HAL_RCC_TIM1_RELEASE_RESET();
      break;
    case (QAD_Timer2):
    	__HAL_RCC_TIM2_CLK_ENABLE();
			__HAL_RCC_TIM2_FORCE_RESET();
			__HAL_RCC_TIM2_RELEASE_RESET();
      break;
    case (QAD_Timer3):
    	__HAL_RCC_TIM3_CLK_ENABLE();
			__HAL_RCC_TIM3_FORCE_RESET();
			__HAL_RCC_TIM3_RELEASE_RESET();
      break;
    case (QAD_TimerNone):
    	break;
  }
}


//QAD_TimerMgr::imp_disableClock
//QAD_TimerMgr Clock Method
//
//To be called by disableClock()
//Used to disable the clock for a specific Timer peripheral
//eTimer - The timer peripheral to disable the clock for
void QAD_TimerMgr::imp_disableClock(QAD_Timer_Periph eTimer) {
  switch (eTimer) {
    case (QAD_Timer1):
    	__HAL_RCC_TIM1_CLK_DISABLE();
      break;
    case (QAD_Timer2):
    	__HAL_RCC_TIM2_CLK_DISABLE();
      break;
    case (QAD_Timer3):
    	__HAL_RCC_TIM3_CLK_DISABLE();
      break;
    case (QAD_TimerNone):
    	break;
  }
}


  //---------------------------
  //---------------------------
  //QAD_TimerMgr Status Methods


//QAD_TimerMgr::imp_getTimersActive
//QAD_TimerMgr Status Method
//
//To be called by getTimersActive()
//Returns the number of Timer peripherals that are currently in-use (registered/active)
uint8_t QAD_TimerMgr::imp_getTimersActive(void) {
  uint8_t uCount = 0;
  for (uint8_t i=0; i<QAD_Timer_PeriphCount; i++) {
  	if (m_sTimers[i].eState)
  		uCount++;
  }
  return uCount;
}


//QAD_TimerMgr::getTimersInactive
//QAD_TimerMgr Status Method
//
//To be called by getTimersInactive()
//Returns the number of Timer peripherals that are currently not being used (deregistered/inactive)
uint8_t QAD_TimerMgr::imp_getTimersInactive(void) {
  uint8_t uCount = 0;
  for (uint8_t i=0; i<QAD_Timer_PeriphCount; i++) {
  	if (!m_sTimers[i].eState)
  		uCount++;
  }
  return uCount;
}

