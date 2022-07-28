/*
 * Application.h
 *
 * Created: 7/28/2022 6:51:47 PM
 *  Author: NourhanAlrefaei
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "mcal/gpio/mcal_gpio.h"
#include "mcal/UART/uart.h"
#include "hal/char_lcd/hal_char_lcd.h"
#include "hal/dc_motor/hal_dc_motor.h"

void application_init(void);
void robot_move_forward(void);
void robot_move_backward(void);
void robot_move_right(void);
void robot_move_left(void);
void robot_stop(void);




#endif /* APPLICATION_H_ */