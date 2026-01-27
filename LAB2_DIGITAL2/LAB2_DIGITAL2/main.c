/*
 * LAB2_DIGITAL2.c
 *
 * Created: 27/1/2026 01:07:47
 * Author : yelena Cotzojay
 */ 



#define  F_CPU	16000000
#include "util/delay.h"
#include <avr/io.h>

#include "LDC/LDC.h"




//Prototipos de función
void initUART();

int main(void)
{
	initUART();
	initLDC8();
	LDC_CURSOR(1,1);
	LDC_write_char('H');
	LDC_write_char('O');
	LDC_write_char('L');
	LDC_write_char('A');
    /* Replace with your application code */
    while (1) 
    {
    }
}

//FUNCIONES
void initUART(){
	//Configurar pines PD0 (TX) y PD1 (TX)
	DDRD |= (1<<DDD1);
	DDRD &= ~(1<<DDD0);
	
	//Configurar UCSR0A
	UCSR0A=0;
	//Configuración UCSR0B: Habililitndo la interrupción al escribir:
	//-Habilibitar recepción
	//-Habilitación de transmisión
	UCSR0B |= (1<<RXCIE0)|(1<<RXEN0)| (1<< TXEN0);
	//Configurar UCSR0C
	UCSR0C |= (1<<UCSZ01) | (1<<UCSZ00);
	//Configurar UBRR0: UBRR0 = 103 -> 9600  @ 16MHz
	UBRR0 = 103;
}