/*****************************************************************************
 *	    File: Lab08.c
 *  Lab Name: RS232 Communication Server
 *    Author: Dr. Greg Nordstrom
 *   Created: 12/30/17
 *  Mod Date: 3/28/19, 1/17/21
 *  Modified:
 *   ModDate:
 * 
 * Processor: ATmega128A (on the ReadyAVR board)
 *
 * This program implements a communication server. Normally the server
 * simply echoes what was sent. However, there are two cases where
 * different behavior occurs:
 *    1. Pressing the ESC causes a soft reset (redisplays the title text)
 *    2. Typing the letters 'end' contiguously displays 'Bye' and halts
 *
 *****************************************************************************/

// define CPU speed (7.3728 MHz for the ATmega128A)
#define F_CPU 7372800UL

#include "UARTLibrary.h" // Double quotes for local library.

#define CR          0x0D
#define LF          0x0A
#define ESC         0x1B

#include <avr/io.h>
#include <util/delay.h>

#define BAUDRATE 9600 // standard values from 1200 to 115200
#define DATABITS    8 // 5-8
#define STOPBITS    1 // 1,2
#define PARITY      0 // 0=none, 1=odd, 2=even

void statusMessage();
volatile unsigned char Data;
volatile unsigned char count;

int main(void)
{
	//Set Delay value
	const char Delay = 75;
	//Initialize PORTA
	DDRA = (1 << DDA7);
	PORTA = 0xFF;


	uart_init(BAUDRATE, DATABITS, STOPBITS, PARITY);
	
	//Display message
	statusMessage();	
	//Loop (Receive, blink, echo, repeat)
	while(1){
		//Receive
		Data = uart_rx();
		//Blink
		PORTA = 0x7F;
		_delay_ms(Delay);
		PORTA = 0xFF;
		//Ech0		
		if (Data == CR){
			uart_tx(Data); uart_tx(LF);
			count = 0;
		}
		else if (Data == ESC){
			statusMessage();
			count = 0;
		}
		else if (Data == 'e'){
			uart_tx(Data);
			count = 1;
		}
		else if ((Data == 'n') && (count == 1)){
			uart_tx(Data);
			count++;
			
		}
		else if ((Data == 'd') && (count == 2)){
			uart_tx(Data);
			uart_tx(CR); uart_tx(LF);
			uart_tx(CR); uart_tx(LF);
			uart_tx('B'); uart_tx('y');uart_tx('e');
			//Stop responding to inputs until hard reset
			while(1){
			}
		}
		else{
			uart_tx(Data);
		}
		
	}
	return 0;
}

//Would be better with arrays
void statusMessage(){
	
			uart_tx(CR); uart_tx(LF);uart_tx(CR); uart_tx(LF);
			
			uart_tx('R');uart_tx('S');uart_tx('2');uart_tx('3');uart_tx('2');uart_tx(' ');
			
			uart_tx('C');uart_tx('o');uart_tx('m');uart_tx('m');uart_tx('u');uart_tx('n');uart_tx('i');
			uart_tx('c');uart_tx('a');uart_tx('t');uart_tx('i');uart_tx('o');uart_tx('n');uart_tx('s');uart_tx(' ');
			
			uart_tx('S');uart_tx('e');uart_tx('r');uart_tx('v');uart_tx('e');uart_tx('r');uart_tx('\r'); uart_tx('\n');
			
			uart_tx('S'); uart_tx('t');uart_tx('a');uart_tx('t');uart_tx('u');uart_tx('s');uart_tx(':');uart_tx(' ');
			uart_tx('A');uart_tx('c');uart_tx('t');uart_tx('i');uart_tx('v');uart_tx('e');uart_tx('\r'); uart_tx('\n');
			
			uart_tx('T'); uart_tx('r');uart_tx('i');uart_tx('s');uart_tx('t');uart_tx('e');uart_tx('n');uart_tx(' ');
			uart_tx('M');uart_tx('i');uart_tx('l');uart_tx('l');uart_tx('s');uart_tx('a');uart_tx('p');uart_tx('s');uart_tx('\r'); uart_tx('\n');
			
			uart_tx('E');uart_tx('E');uart_tx('C');uart_tx('E');uart_tx('3');uart_tx('6');uart_tx('2');uart_tx('4');uart_tx('\r'); uart_tx('\n');
			
			uart_tx('F');uart_tx('a');uart_tx('l');uart_tx('l');uart_tx(' ');uart_tx('2');uart_tx('0');uart_tx('2');uart_tx('3');uart_tx('\r'); uart_tx('\n');
			
			uart_tx(CR); uart_tx(LF);uart_tx(CR); uart_tx(LF);
}