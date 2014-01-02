#define F_CPU (1000000L)
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include <inttypes.h>

#define MAX_LEDs 5          // max number of LEDs on at one time
#define NUM_LEDs 10         // total number of LEDs
#define BLINK_DELAY 500     // delay between blinks (in milliseconds)

// Pins in use (name):   PB0,PB1,PB2,PB3,PB4,PB5,PB6,PB7,PC0,PC1
// Pins in use (number): 08, 09, 16, 23, 24, 26, 27, 28, 30, 03

volatile uint8_t pinarray[NUM_LEDs] = {PB0, PB1, PB2, PB3, 
                                    PB4, PB5, PB6, PB7, 
                                    PC0, PC1};
volatile uint8_t* portarray[NUM_LEDs] = {&PORTB, &PORTB, &PORTB, &PORTB, 
                                    &PORTB, &PORTB, &PORTB, &PORTB, 
                                    &PORTC, &PORTC};

void turnAllOff(void) {
    int i;
    for (i=0;i<NUM_LEDs;i++) {
        *portarray[i] &= ~ _BV(pinarray[i]);
    }
}

void turnAllOn(void) {
    int i;
    for (i=0;i<NUM_LEDs;i++) {
        *portarray[i] |= _BV(pinarray[i]);
    }
}

int main (void) {
    DDRB |= 0xFF; // set all PORTB pins for output
    DDRC |= 0xFF; // set all PORTC pins for output

    int numLEDs = 0;
    int led = 0;
    int i;

    turnAllOff();
    for (;;) {
        // blinky lights forever!

        numLEDs = (int)((double)rand() / ((double)RAND_MAX + 1) * MAX_LEDs) + 1;

        for (i=0;i<numLEDs;i++) {
            led = (int)((double)rand() / ((double)RAND_MAX + 1) * NUM_LEDs);
            *portarray[led] |= _BV(pinarray[led]);
        }
        _delay_ms(BLINK_DELAY);
        turnAllOff();
    }
}
