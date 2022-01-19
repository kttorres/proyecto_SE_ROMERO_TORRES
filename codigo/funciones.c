#include "funciones.h"

#define N_PIXELS  60 // Número de leds
#define LED_PIN    6  // NeoPixel LED strand is connected to this pin (PD6)
//------------------A-BCDEFG  (Segmentos del display) el PIN PB6 y PB7 no se utiliza ya que en arduino están ocupados por un reloj
#define Num0 0b10111110
#define Num1 0b00110000
#define Num2 0b10101101
#define Num3 0b10111001
#define Num4 0b00110011
#define Num5 0b10011011
#define Num6 0b10011111
#define Num7 0b10110000
#define Num8 0b10111111
#define Num9 0b10111011

volatile bool secuencia = true;
uint16_t Vconv_display = 0;
uint16_t Vconv_leds = 0;
uint16_t Vconv_brillo = 0;
uint8_t unidades = 0;
uint8_t decenas = 0;
uint8_t centenas = 0;
uint8_t displaySelecter = 1;
Adafruit_NeoPixel tiraLed = Adafruit_NeoPixel(N_PIXELS+1, LED_PIN, NEO_GRB + NEO_KHZ800); //

//Interrupciones
//ISR se encuentra ya definida en la librería de Adafruit
//por eso no se define en esta ya que ocasionaría un error

ISR(INT0_vect){
 secuencia = true;
}

ISR(INT1_vect){
 secuencia = false;
}

ISR(ADC_vect){ //ENCERAR EL BIT 4 DEL REG ADCSRA &=~(1<<ADIF)
   //Se muestra en el display el porcentaje de volúmen
   displayV();
}

void SecLeds1(){  //Primera secuencia incremental normal
   Vconv_leds = conversionLed();
   tiraLed.clear(); //SE ELIMINA LOS VALORES PREVIOS DE LA TIRA LED
   for(uint16_t i=0; i<Vconv_leds;i++){ //Se recorren para la cantidad de leds que se deben encender según la conversión ADC
      if(i<N_PIXELS*0.1){ //Color para el 10% de los leds totales
   tiraLed.setPixelColor(i,0,25,225); //AZUL
      }
      else if((N_PIXELS*0.1<=i)&(i<N_PIXELS*0.6)){ //Color para los leds totales entre 10 y 60 %
   tiraLed.setPixelColor(i,0,255,25); //VERDE
      }
      else if((N_PIXELS*0.6<=i)&(i<N_PIXELS*0.85)){ //Color para los leds totales entre 60 y 85 %
   tiraLed.setPixelColor(i,120,225,0); //AMARILLO
      }
      else{ //Color para el resto de leds totales
   tiraLed.setPixelColor(i,255,0,0); //ROJO
      }
   }
   delay(3); // si no se agrega un pequeño delay ocurren errores.
   tiraLed.show();
}

void SecLeds2(){  //Segunda secuencia incremental desde las esquinas
   Vconv_leds = conversionLed();
   tiraLed.clear(); //SE ELIMINA LOS VALORES PREVIOS DE LA TIRA LED
   //Se recorren los leds desde el inicio hasta la mitad del total de los leds que deben encenderse según el ADC y se refleja la misma secuencia en la otra mitad
   for(uint16_t i=0; i<Vconv_leds/2;i++){
      if(i<N_PIXELS*0.05){ //Color para los leds de entre (0-5)% y (95-100)% de la tira led
   tiraLed.setPixelColor(i,0,25,255); //AZUL
   tiraLed.setPixelColor(N_PIXELS-i-1,0,25,225);//AZUL
      }
      else if((N_PIXELS*0.05<=i)&(i<N_PIXELS*0.3)){ //Color para los leds entre (5-30)% y (70-95)% de la tira led
   tiraLed.setPixelColor(i,0,255,25); //VERDE
   tiraLed.setPixelColor(N_PIXELS-i-1,0,255,25);//VERDE
      }
      else if((N_PIXELS*0.3<=i)&(i<N_PIXELS*0.425)){ //Color para los leds entre (30-42.5)% y (57.5-70)% de la tira led
   tiraLed.setPixelColor(i,120,225,0); //AMARILLO
   tiraLed.setPixelColor(N_PIXELS-i-1,120,225,0);//AMARILLO
      }
      else{ //Color para el resto de los leds totales
   tiraLed.setPixelColor(i,255,0,0); //ROJO
   tiraLed.setPixelColor(N_PIXELS-i-1,255,0,0);//ROJO
      }
   }
   delay(3); // si no se agrega un pequeño delay ocurren errores.
   tiraLed.show();
}

void escogerSecuencia(){
   if(secuencia){
   SecLeds1();
      }
      else{
   SecLeds2();
      }
}

void mostrarNum(uint8_t numero){
   switch(numero){
      case 0:
   PORTB = Num0;
   PORTC = 0b1; //Segemento A
   break;
      case 1:
   PORTB = Num1;
   PORTC = 0b0; //Segemento A
   break;
      case 2:
   PORTB = Num2;
   PORTC = 0b1; //Segemento A
   break;
      case 3:
   PORTB = Num3;
   PORTC = 0b1; //Segemento A
   break;
      case 4:
   PORTB = Num4;
   PORTC = 0b0; //Segemento A
   break;
      case 5:
   PORTB = Num5;
   PORTC = 0b1; //Segemento A
   break;
      case 6:
   PORTB = Num6;
   PORTC = 0b1; //Segemento A
   break;
      case 7:
   PORTB = Num7;
   PORTC = 0b1; //Segemento A
   break;
      case 8:
   PORTB = Num8;
   PORTC = 0b1; //Segemento A
   break;
      case 9:
   PORTB = Num9;
   PORTC = 0b1; //Segemento A
   break;
   }
}

void displayV(){
   //Separamos unidades
   Vconv_display = conversionDisplay();
   unidades = Vconv_display%10;
   decenas = (Vconv_display/10)%10;
   centenas = Vconv_display/100;
   //Seleccionamos display
   displaySelecter = displaySelecter<<1;
   if (displaySelecter==32){
      displaySelecter=1;
   }
   PORTD = ~displaySelecter;
   //Mostramos el número
   switch (displaySelecter){
      case 1:
   mostrarNum(unidades);
   break;
      case 2:
   mostrarNum(decenas);
   break;
      case 4:
   mostrarNum(centenas);
   break;
   }
}

uint16_t conversionDisplay(){ //Conversión ADC conveniente para el display.
   while(ADCSRA & (1<< ADSC)); // ADSC DISABLED? 
   Vconv_display= ADC/10.1488; // Convierte el rango de 0-1024 a 0-100 (Porcentaje de volumen)
   return Vconv_display;
}

uint16_t conversionLed(){ //Conversión ADC conveniente para la tiraLed.
   while(ADCSRA & (1<< ADSC)); // ADSC DISABLED? 
   Vconv_leds= ADC*N_PIXELS/1023; // Convierte el rango de 0-1024 a 0-N_PIXELS (Leds que se encenderán)
   return Vconv_leds; 
}

void brilloLeds(){ //Conversión ADC conveniente para la tiraLed.
   while(ADCSRA & (1<< ADSC)); // ADSC DISABLED? 
   Vconv_brillo= ADC/8.06; // Convierte en el rango para el nivel de brillo
   tiraLed.setBrightness(Vconv_brillo); //Modifica el brillo de la tira led
}
