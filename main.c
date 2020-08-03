#define F_CPU 2000000L
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define SW3 0b00000100 // pause
#define SW2 0b00001000 // resume

//volatile unsigned char d;
unsigned char i;
unsigned char j = 1;

ISR(INT0_vect)
{
  PORTB = (1 << i);
  j = 1;
}

ISR(INT1_vect)
{
  PORTB = (1 << i);
  _delay_ms(5000);
  j = 0;
}

int main(void)
{
  DDRB = 0xFF; // Set PORTB for output

  DDRD = 0x00;        // set PORTD for input
  PORTD = 0b00000100; // pause PD2 INT0
  PORTD = 0b00001000; // resume PD3 INT1

  EIMSK = 0b00000011; // External Interrupt Mask Register
  EICRA = 0b00001010; // External Interrupt Control Register
  sei();

  while (1)
  {
    if (j)
    {
      for (i = 0; i <= 7; i++)
      {
        PORTB = (1 << i); // LEDs blinking left to right
        _delay_ms(300);
      }
    }
    else
    {
      PORTB = (1 << i);
    }
  }
}
