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
