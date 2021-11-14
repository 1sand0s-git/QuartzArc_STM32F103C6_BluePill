/* ----------------------------------------------------------------------- */
/*                                                                         */
/*   Quartz Arc                                                            */
/*                                                                         */
/*   STM32 F103C6 Blue Pill                                                */
/*                                                                         */
/*   System: Core                                                          */
/*   Role: System Initialization                                           */
/*   Filename: boot.hpp                                                    */
/*   Date: 14th November 2021                                              */
/*   Created By: Benjamin Rosser                                           */
/*                                                                         */
/*   This code is covered by Creative Commons CC-BY-NC-SA license          */
/*   (C) Copyright 2021 Benjamin Rosser                                    */
/*                                                                         */
/* ----------------------------------------------------------------------- */

//Prevent Recursive Inclusion
#ifndef __BOOT_HPP_
#define __BOOT_HPP_

//Includes
#include "setup.hpp"


	//------------------------------------------
	//------------------------------------------
	//------------------------------------------

  //------------------------------
  //System Initialization Function

QA_Result SystemInitialize(void);


//Prevent Recursive Inclusion
#endif /* __BOOT_HPP */
