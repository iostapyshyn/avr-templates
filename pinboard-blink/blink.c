#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRB |= (1 << PB3);
    while (1) {
        PORTB |= (1 << PB3);
        _delay_ms(500);
        PORTB &= ~(1 << PB3);
        _delay_ms(500);
    }
}
