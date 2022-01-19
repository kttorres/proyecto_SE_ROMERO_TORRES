#include "config.h"

void interrupt_TIMER0_Init(){
 cli();
 TCCR0B = 1; // SIN Prescalador
 TIMSK0 = 1; //HB TIMER POR DESBORDAMIENTO
 sei();
}

void interrupt_INT0_Init(){
 cli(); //DESHABILITO INT
 EICRA |= (1<<ISC01)|(1<<ISC00); // INT0 FLANCO DE SUBIDA
 EIMSK |= (1<<INT0); // HAB PIN0
 sei(); //HAB ILITO INT
}

void interrupt_INT1_Init(){
 cli(); //DESHABILITO INT
 EICRA |= (1<<ISC11)|(1<<ISC10); // INT1 FLANCO DE SUBIDA
 EIMSK |= (1<<INT1); // HAB PIN1
 sei(); //HAB iLITO INT
}

void ADC_Init(){
 ADCSRA = 0b10101111; //ADC activado modo automático y preescalador 128
 ADCSRB= 0b100; //Modo Timer0 por desbordamiento
 DIDR0 |= (1<<ADC3D); //ENABLE ANALOG MODE ADC3 y ADC2
 ADMUX = 0b01000011;  //AVCC- AREF y ADC3 (micrófono)
}

void setUpp(){
   DDRB  = 0b00111111; //SALIDA PINES B (display BCDEFG) PB7 y PB6 no se toman dado que en arduino dichos pines están ocupados por un reloj
   DDRD = 0b01010011; //SALIDA PINES D(0,1,4:display;6:leds) - ENTRADA (2-3:botones)
   DDRC = 0b1; //SALIDA PIN AD0 (display A)
}  

