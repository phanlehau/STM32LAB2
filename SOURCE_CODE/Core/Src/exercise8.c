#include "exercise8.h"



int index_led = 0;
int led_buffer [4];
GPIO_TypeDef* LED_PORT[4] = {EN1_GPIO_Port, EN2_GPIO_Port, EN3_GPIO_Port, EN4_GPIO_Port};
uint16_t LED_PIN[4] = {EN1_Pin, EN2_Pin, EN3_Pin, EN4_Pin};
int hour = 15 , minute = 8 , second = 50;
int timer_counter[3];
int timer_flag[3];
int TIMER_CYCLE = 10;
const uint8_t seven_seg_digits[] = {
  0b00111111, // So 0
  0b00000110, // So 1
  0b01011011, // So 2
  0b01001111, // So 3
  0b01100110, // So 4
  0b01101101, // So 5
  0b01111101, // So 6
  0b00000111, // So 7
  0b01111111, // So 8
  0b01101111  // So 9
};


void setTimer (int number ,int duration ) {
timer_counter[number] = duration / TIMER_CYCLE ;
timer_flag[number] = 0;
}
void timer_run () {
for(int i = 0;i<=2;i++)
{
if( timer_counter[i] > 0) {
timer_counter[i]--;
if( timer_counter[i] == 0) timer_flag[i] = 1;
}
}
}

void display7SEG(int number) {
  if(number < 0 || number > 9) return; // Kiem tra so hop le

  uint8_t digit = seven_seg_digits[number]; // Lay trang thai tu bang tra cuu

  HAL_GPIO_WritePin(LED_1_GPIO_Port, LED_1_Pin, (digit & 0x01) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_2_GPIO_Port, LED_2_Pin, (digit & 0x02) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_3_GPIO_Port, LED_3_Pin, (digit & 0x04) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_4_GPIO_Port, LED_4_Pin, (digit & 0x08) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_5_GPIO_Port, LED_5_Pin, (digit & 0x10) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_6_GPIO_Port, LED_6_Pin, (digit & 0x20) ? GPIO_PIN_RESET : GPIO_PIN_SET);
  HAL_GPIO_WritePin(LED_7_GPIO_Port, LED_7_Pin, (digit & 0x40) ? GPIO_PIN_RESET : GPIO_PIN_SET);
}
void update7SEG ( int index ) {
switch ( index ) {
case 0:
    display7SEG(led_buffer[0]);
break ;
case 1:
    display7SEG(led_buffer[1]);
break ;
case 2:
    display7SEG(led_buffer[2]);
break ;
case 3:
    display7SEG(led_buffer[3]);
break ;
default :
break ;
}
}
void updateClockBuffer()
{
	if(hour >= 10 && minute >= 10)
	{
		led_buffer [0] = hour / 10;
		led_buffer [1] = hour % 10;
		led_buffer [2] = minute / 10;
		led_buffer [3] = minute % 10;
	}
	else if(minute < 10)
	{
		led_buffer [0] = hour / 10;
		led_buffer [1] = hour % 10;
		led_buffer [2] = 0;
		led_buffer [3] = minute;
	}
	else if(hour < 10)
	{
		led_buffer [0] = 0;
		led_buffer [1] = hour;
		led_buffer [2] = minute / 10;
		led_buffer [3] = minute % 10 ;
	}
	else
	{
		led_buffer [0] = 0;
		led_buffer [1] = hour;
		led_buffer [2] = 0;
		led_buffer [3] = minute;
	}
}

void init_exercise8(){
	  HAL_GPIO_TogglePin(EN4_GPIO_Port, EN4_Pin);
	  HAL_GPIO_TogglePin(EN3_GPIO_Port, EN3_Pin);
	  HAL_GPIO_TogglePin(EN2_GPIO_Port, EN2_Pin);
	  HAL_GPIO_TogglePin(EN1_GPIO_Port, EN1_Pin);
	  setTimer(0,1000) ;
	  setTimer(1,250) ;
	  setTimer(2,1000) ;
	  updateClockBuffer();
}

void exercise8_run(){
	// hien thi led 7 doan
	if(timer_flag[1] == 1)
			{
				if(index_led <=0)
				{
				HAL_GPIO_WritePin ( LED_PORT[3] , LED_PIN[3] , GPIO_PIN_SET);
				HAL_GPIO_WritePin ( LED_PORT[0] , LED_PIN[0] , GPIO_PIN_RESET);
				update7SEG(index_led++);
				}
				else
				{
				HAL_GPIO_WritePin ( LED_PORT[index_led-1] , LED_PIN[index_led-1] , GPIO_PIN_SET);
				HAL_GPIO_WritePin ( LED_PORT[index_led] , LED_PIN[index_led] , GPIO_PIN_RESET);
				update7SEG(index_led++);
				}
			   if(index_led >=4) index_led = 0;
		  setTimer(1,250) ;
			}
	// cap nhat thoi gian
		  if(timer_flag[0] == 1)
			{
		  second ++;
		  if ( second >= 60) {
		  second = 0;
		  minute ++;
		  }
		  if( minute >= 60) {
		  minute = 0;
		  hour++;
		  }
		  if( hour >=24) {
		  hour = 0;
		  }
		  updateClockBuffer () ;
		  setTimer(0,1000) ;
			}
	// cap nhat den led
		  if(timer_flag[2] == 1)
			{
				HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
				HAL_GPIO_TogglePin(DOT_GPIO_Port, DOT_Pin);
		  setTimer(2,1000) ;
			}
}


