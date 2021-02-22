/*
 * File:   main.c
 * Author: Andrés González Olea A01039725; Angel Francisco Figueroa A00820475; Dalia Lizeth Hurtado A01281887; Ricardo Plata Galaviz A00821598
 *
 * Created on February 17, 2021, 8:03 PM
 */

//++++++++++++++++++++++++LIBRARIEs/HEADEAs SECTION++++++++++++++++++++++++++++ 
#include "device_config.h"               // calls a header file where the default configuration is set

//++++++++++++++++++++++++++++DIRECTIVEs SECTION+++++++++++++++++++++++++++++++
#define _XTAL_FREQ 1000000               // sets de delay function
#define ONE_SECOND 1000                  // sets de variable one_second the numeric val 

//++++++++++++++++++++++++++++DATA TYPEs SECTION+++++++++++++++++++++++++++++++ 
//Enumeration is a user defined data type in C. It is mainly used to assign 
//names to integral constants, the names make a program easy to read and 
//maintain. 

enum por_dir{ output, input };           // output = 0, input = 1 
enum por_ACDC{ digital, analog };        // digital = 0, analog = 1
enum resistor_state{ set_ON, res_ON };   // set_ON = 0, res_ON = 1
enum led_state{ led_OFF, led_ON };       // led_OFF = 0, led_ON = 1
enum butto_state{ pushed, no_pushed };   // pushed = 0, no_pushed = 1

//+++++++++++++++++ISRs SECTION++++++++++++++++++++++++++++++++++ 
void __interrupt ( high_priority ) high_isr( void );  //ISR for high-priority 

void __interrupt ( low_priority ) low_isr( void );    //ISR for low-priority

//++++++++++++++++++++++++FUNCTIONs DECLARATION++++++++++++++++++++++++++++++++ 
void portsInit( void );                   // Ports configuration function.

//+++++++++++++++++++++++++++++Main Function+++++++++++++++++++++++++++++++++++
void main( void ) {
	// CONFIGURATIONS**********************************************************
	portsInit();                          // calls the function of ports configuration.
	while( 1 ) {                          //loop that helps to repeat infinite the actions
		if( PORTBbits.RB4 == pushed )     // If button is pushed then:
			LATAbits.LATA7 = led_OFF;     // Turn on the RA7 LED.
		else // Otherwise
			LATAbits.LATA7 = led_ON;      // Turn off the RA7 LED.
		LATAbits.LATA4 = led_ON;          // Turns on the pin we want (set 1)
		__delay_ms( ONE_SECOND );         // waits one second to continue
		LATAbits.LATA4 = led_OFF;         // Turn off the pin we want (set 0)
		__delay_ms( ONE_SECOND );         // waits one second to continue
	}
}

//++++++++++++++++++++++++FUNCTIONs SECTION++++++++++++++++++++++++++++++++ 
void portsInit( void ) {				  // Functions that starts with no parameters and no returns
	ANSELA = digital;                     // Sets PortA as digital
	TRISAbits.TRISA4 = output;            // Sets RA4 as an output
	TRISAbits.TRISA7 = output;            // Sets RA7 as an output
	ANSELB = digital;                     // Sets PortB as digital
	TRISBbits.TRISB4 = input;			  // Sets RB4 as an output
}