#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/* 7
   -
 6| |5
   -4
 0| |3
   -   .2
   1                   
*/

//                               76543210
const uint8_t seg_digits[] = { 0b11101011, // 0
                               0b00101000, // 1
                               0b10110011, // 2
                               0b10111010, // 3
                               0b01111000, // 4
                               0b11011010, // 5
                               0b11011011, // 6
                               0b10101000, // 7
                               0b11111011, // 8
                               0b11111010, // 9
};

void seg_select(int seg) {
    PORTA &= ~((1 << PA0) | (1 << PA1) | (1 << PA2));
    PORTA |= (1 << seg);
}

void seg_init() {
    DDRA |= (1 << PA0) | (1 << PA1) | (1 << PA2);
    DDRB = 0xFF;
}

void seg_putdigit(int digit) {
    PORTB = seg_digits[digit];
}

int seg = 0;
ISR(TIMER1_OVF_vect) {
    seg_select(seg++ % 3);
    TCNT1 = F_CPU / 2 / 1024;
}

int main() {
    seg_init();
    
    TCNT1 = F_CPU / 2 / 1024;
    TCCR1A = 0x00;
    TCCR1B = (1 << CS10) | (1 << CS12);
    TIMSK = (1 << TOIE1);

    sei();
    
    while (1) {
        for (int i = 0; i < 10; i++) {
            seg_putdigit(i);
            _delay_ms(500);
        }
    }
}
