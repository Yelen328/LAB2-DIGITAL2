/*UNIVERSIDAD DEL VALLE DE GUATEMALA
 * LAB2_DIGITAL2
 * Created: 27/1/2026 01:07:47
 * Author : yelena Cotzojay
 */ 


#define  F_CPU	16000000
#include "util/delay.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>


#include "LDC/LDC.h"
#include "ADC/ADC.h"

volatile uint8_t ADC1=0;
volatile uint8_t ADC2=0;
uint8_t POT=0;

uint8_t entero=0;
uint8_t decimal=0;


//Prototipos de funciones
void setup();
void decimales ();


void setup(){
	cli();	//Desabilitar interrupciones
	
	//inicializar el ADC
	ADC_init(1, 2, 1, 128);
	
	//Inicializar LCD
	initLDC8();
	
	sei();		//Habilita cambios de interrupción
	ADCSRA |= (1 << ADSC); // Iniciar primera conversión
}

int main(void)
{	
	setup();
    while (1) 
    {
		LDC_CURSOR(1,1);
		char buffer[32];
		decimales();
		sprintf(buffer, "P1: %d.%02dV", entero, decimal);
		LDC_write_string(buffer);
		
		_delay_ms(100);
		
    }
}

//FUNCIONES
void decimales(){
	float conversion=((ADC1*5.0f)/255.0f);
	entero = (uint8_t)conversion;
	float parte_decimal = conversion - (float)entero;
	decimal = (uint8_t)(parte_decimal * 100.0f);
}

//VECTOR DE INTERRUPCIÓN
ISR(ADC_vect)
{
	ADC_CANAL(7);
	ADC1=ADCH;
	ADCSRA |= (1 << ADSC);	//Iniciar nueva conversión

	}
	
	


