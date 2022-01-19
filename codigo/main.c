#include "funciones.h"
/*
Sistemas Embebidos P105
Proyecto: Vúmetro
Karen Thamara Torres Medina
Giovanny Andrés Romero Vizueta
*/

//Main
int main(void)
 {
   setUpp();
   ADC_Init();  //Inicializa ADC
   interrupt_INT0_Init(); //Interrupción externa Bt1
   interrupt_INT1_Init(); //Interruoción externa Bt2
   interrupt_TIMER0_Init(); //interrupción por timer 
   tiraLed.begin();
   tiraLed.show(); // Initialize all pixels to 'off'
   
   /*
   Se colocaron ambas funciones en el while ya que al ubicarlas 
   en las interrupciones en conjunto con displayV() ocurrían errores de frecuencia
   */

   while (1){	
      escogerSecuencia();
      brilloLeds();
   }
   return 0;
 }
