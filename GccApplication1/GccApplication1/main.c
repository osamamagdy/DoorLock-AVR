/*
* GccApplication1.c
*
* Created: 7/10/2020 7:54:03 PM
* Author : Osama Magdy
*/
#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include "lcd.h"
#include <avr/eeprom.h>
#include <string.h>
#define rows PORTA

#define col (PINA>>4)

const char pass[5] = {'1','1','5','2','0'};


void get_key(char * lcd_data , char * curr )
{
	while(1)
	{
		/// We Exit this infinite loop by pressing one of the Keys through return of the function
		for (char i = 1 ; i <=8 ; i = i<<1)
		{
			_delay_ms(10);
			rows = i ;
			if (rows==1)
			{
				switch (col)
				{
					case 1 :
					lcd_data[*curr]='1';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
					
					case 2 :
					lcd_data[*curr]='2';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
					
					case 4 :
					lcd_data[*curr]='3' ;
					(*curr) =(*curr) +1 ;
					while(col != 0);
					return;
				}
			}
			
			else if (rows==2)
			{
				switch (col)
				{
					case 1 :
					lcd_data[*curr]='4';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
					
					case 2 :
					lcd_data[*curr]='5';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
					
					case 4 :
					lcd_data[*curr]='6';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
				}
			}
			
			else if (rows==4)
			{
				switch (col)
				{
					case 1 :
					lcd_data[*curr]='7';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
					
					case 2 :
					lcd_data[*curr]='8';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
					
					case 4 :
					lcd_data[*curr]='9';
					(*curr) =(*curr) +1  ;
					while(col != 0);
					return;
				}
			}
			
			else if (rows==8)
			{
				switch (col)
				{
					case 1 :
					memset(lcd_data , '\0',16);
					LCDClear();
					LCDHome();
					*curr=0;
					while(col != 0);
					return;
					
					case 2 :
					lcd_data[*curr]='0';
					(*curr) =(*curr) +1 ;
					while(col != 0);
					return;
					
					case 4 :
					while(col != 0);
					compare_data(lcd_data , *curr);    // This has to be AFTER the above while loop as in compare data we set the buzzer (pin 7 of the same port) to high.
													   //And this will make col never reaches zero as PINA register reads the value written in PORTA if DDRA is set as OUTPUT
													   //It looks like you write '1' and read it over and over
													   // There are 3 possible solutions, Rearrange their order like we did here, in compare data you can set the port to zero again but this may give give you a fault idk,
													   // or you may use another port for the buzzer but this ain't efficient as you can use only one port to do all the job.
					return;
				}
			}
			
			
		}
	}
}



void compare_data(char * lcd_data , char curr)
{
	if (curr==5)
	{
		if (lcd_data[0]==pass[0] && lcd_data[1]==pass[1] && lcd_data[2]==pass[2] && lcd_data[3]==pass[3] && lcd_data[4]==pass[4] )
		{
			LCDClear();
			LCDWriteString("Access Granted");
			LCDWriteStringXY(0 ,1 ,"Hello Osama ^_^");
			_delay_ms(2000);
		}
		else
		{
			LCDClear();
			LCDWriteString("Access Denied");
			PORTA=0x80;
			_delay_ms(2000);
		}
	}
	else
	{
		LCDClear();
		LCDWriteString("Access Denied");
		PORTA=0x80;
		_delay_ms(2000);
	}
	
}







int main(void)
{
	DDRA = 0x8F;
	char lcd_word [16];
	memset(lcd_word , '\0',16);
	
	PORTA = 0x00;
	InitLCD(LS_BLINK);
	LCDClear();
	char curr = 0 ;
	/* Replace with your application code */
	while (1)
	{
		
		LCDClear();
		LCDWriteString(lcd_word);
		get_key(lcd_word,&curr);
		
		
		
	}
}


