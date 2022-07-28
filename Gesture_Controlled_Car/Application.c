/*
 * Gesture_Controlled_Car.c
 *
 * Created: 7/28/2022 6:36:40 PM
 * Author : NourhanAlrefaei
 */ 

#define F_CPU 16000000UL
#include "Application.h"

/**********************************Hardware Components******************************/
dc_motor_t motor1={.relay2.port_name=PORT_C,.relay2.pin=PIN_3,.relay1.port_name=PORT_C,
.relay1.pin=PIN_4};

dc_motor_t motor2={.relay1.port_name=PORT_C,.relay1.pin=PIN_5,.relay2.port_name=PORT_C,
.relay2.pin=PIN_6};

char_lcd_t lcd={.lcd_rs_port=PORT_B,.lcd_rs_pin=PIN_1,.lcd_rw_port=PORT_B,.lcd_rw_pin=PIN_2,
	.lcd_en_port=PORT_B,.lcd_en_pin=PIN_3,.lcd_data_port=PORT_A,
.lcd_data_pin4=PIN_4,.lcd_data_pin5=PIN_5,.lcd_data_pin6=PIN_6,.lcd_data_pin7=PIN_7};


int main(void)
{
    application_init();
    uint8_type char_received=0;
    gpio_pin_direction_initialize(PORT_C,PIN_7,DIRECTION_OUTPUT);
    while (1) 
    {
		gpio_write_pin(PORT_C,PIN_7,VALUE_HIGH);
		_delay_ms(1000);
		gpio_write_pin(PORT_C,PIN_7,VALUE_LOW);
		_delay_ms(1000);
		
		char_received=MUART_voidRecieveByteSynch();
		switch(char_received)
		{
			case 'f':
			lcd_send_command(&lcd,_LCD_CLEAR);
			lcd_send_string_data_pos(&lcd,0,0,"Move Forward");
			MUART_Send_String("Move Forward\n");
			robot_move_forward();
			break;
			case 'b':
			lcd_send_command(&lcd,_LCD_CLEAR);
			lcd_send_string_data_pos(&lcd,0,0,"Move Backward");
			MUART_Send_String("Move Backward\n");
			robot_move_backward();
			break;
			case 'r':
			lcd_send_command(&lcd,_LCD_CLEAR);
			lcd_send_string_data_pos(&lcd,0,0,"Move Right");
			MUART_Send_String("Move Right\n");
			robot_move_right();
			break;
			case 'l':
			lcd_send_command(&lcd,_LCD_CLEAR);
			lcd_send_string_data_pos(&lcd,0,0,"Move left");
			MUART_Send_String("Move left\n");
			robot_move_left();
			break;
			case 's':
			lcd_send_command(&lcd,_LCD_CLEAR);
			lcd_send_string_data_pos(&lcd,0,0,"Stop Robot");
			MUART_Send_String("Stop Robot\n");
			robot_stop();
			break;
			default:break;
		}
    }
}

void application_init(void)
{
	dc_motor_initialize(&motor1);
	dc_motor_initialize(&motor2);
	lcd_initialize(&lcd);
	MUART_voidInitializeUART();
}
void robot_move_forward(void)
{
	dc_motor_rotate_right(&motor1);
	dc_motor_rotate_right(&motor2);
}
void robot_move_backward(void)
{
	dc_motor_rotate_left(&motor1);
	dc_motor_rotate_left(&motor2);
}
void robot_move_right(void)
{
	dc_motor_rotate_right(&motor1);
	dc_motor_stop(&motor2);
}
void robot_move_left(void)
{
	dc_motor_rotate_right(&motor2);
	dc_motor_stop(&motor1);
}
void robot_stop(void)
{
	dc_motor_stop(&motor1);
	dc_motor_stop(&motor2);
}