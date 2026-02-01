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
#include "UART/UART.h"

volatile uint16_t ADC1=0;
volatile uint16_t ADC2=0;
uint8_t POT=0;
uint8_t entero=0;
uint8_t decimal=0;
volatile uint8_t contadorUART=0;

//Prototipos de funciones
void setup();
void decimales ();


void setup(){
	cli();	//Desabilitar interrupciones
	
	//inicializar el ADC
	//orientación a la derecha
	//5V de referencia
	//Prescaler de 128
	ADC_init(0, 2, 1, 128);
	INIT_UART(103);	// Desired Baud Rate 9600
	
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
		//muestra el valor del potenciometro 1 en la LCD
		LDC_CURSOR(1,1);
		char buffer[32];
		decimales();
		sprintf(buffer, "S1: %d.%02dV", entero, decimal);
		LDC_write_string(buffer);
		
		//muestra el valor del potenciometro 2 en la LCD
		LDC_CURSOR(1,2);	//Setear el cursor para la primera línea segunda columna
		sprintf(buffer, "S2: %3d", ADC2);
		LDC_write_string(buffer);
		
		//muestra el valor del contador por medio de la comunicación serial
		LDC_CURSOR(11,1);	//Setear el cursor para la primera linea onceava columna
		sprintf(buffer, "S3:%3d", contadorUART);
		LDC_write_string(buffer);
		
	
		//Muestra el valor de los potenciometros en la terminal
		sprintf(buffer, "S1: %d.%02dV  S2: %u\r\n",
		entero, decimal, ADC2);
		writeString(buffer);
	
		_delay_ms(100);
		
    }
}

//FUNCIONES
void decimales(){
	float conversion=((ADC1*5.0f)/1023.0f);
	entero = (uint8_t)conversion;
	float parte_decimal = conversion - (float)entero;
	decimal = (uint8_t)(parte_decimal * 100.0f);
}

//VECTOR DE INTERRUPCIÓN
ISR(ADC_vect)
{
	POT ++;
	switch(POT){
		case(1):
		ADC_CANAL(7);
		ADC1=ADC;
		break;
		
		case (2):
		ADC_CANAL(6);
		ADC2=ADC;
		break;
		
		case(3):
		POT=0;
		break;
		
		default:
		break;
		
	}
	
	ADCSRA |= (1 << ADSC);	//Iniciar nueva conversión

	}
	

ISR (USART_RX_vect){
	char caracter = UDR0;
	//WriteChar(caracter);	//Envía de vuelta el mismo carácter resibido
	switch(caracter){
		case ('+'):
		contadorUART++;
		break;
		
		case('-'):
		contadorUART --;
		break;
		
		default:
		break;
		
	}
}
	
	


