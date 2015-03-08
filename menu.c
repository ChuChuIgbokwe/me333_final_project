#include "NU32.h"          // config bits, constants, funcs for startup and UART
// include other module headers here

#define BUF_SIZE 200

int main() 
{
  char buffer[BUF_SIZE];
  NU32_Startup(); 			// cache on, min flash wait, interrupts on, LED/button init, UART init
  NU32_LED1 = 1;        // turn off the LEDs
  NU32_LED2 = 1;        
  __builtin_disable_interrupts();
  // initialize other modules here
  __builtin_enable_interrupts();

  while(1)
  {
    NU32_ReadUART1(buffer,BUF_SIZE);	    // we expect the next character to be a menu command
    NU32_LED2 = 1;                        // clear the error led
    switch (buffer[0]) {
      case 'd':                           // dummy command for demonstration purposes
      {
        int n = 0;
        NU32_ReadUART1(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n);
        sprintf(buffer,"%d\r\n", n + 1);       // return the number + 1
        NU32_WriteUART1(buffer);
        break;
      }
      case 'f':                           // dummy command for demonstration purposes
      {
        int n1 = 0, n2 = 0;
        NU32_ReadUART1(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n1);
        NU32_ReadUART1(buffer,BUF_SIZE);
        sscanf(buffer, "%d", &n2);
        sprintf(buffer,"%d\r\n", n1 + n2);       // return the number + 1
        NU32_WriteUART1(buffer);
        break;
      }
      case 'q':
      {
        // handle q for quit. Later you may want to return to idle state here 
        break;
      }
      default:
      {
        NU32_LED2 = 0;    // turn on LED2 to indicate an error
        break;
      }
    }
  }
  return 0;
}


