#include <avr/io.h>


void init_adc(void)
{
    ADMUX &= ~(1<<REFS0);
	ADMUX &= ~(1<<REFS1);
    ADCSRA |= (1<<ADPS2);
	ADCSRA &= (~(1<<ADPS0));
	ADCSRA &= (~(1<<ADPS1));
	ADCSRA |= (1<<ADEN);

}

uint16_t adc_read4(void){
	ADMUX &= 0xC0;
	ADMUX |= (1<<MUX2);
	ADCSRA |= (1<<ADSC);
	while( ADCSRA & (1<<ADSC) ){
		
	}
	return ADCW;
}


int main(void)
{   
	init_adc();
	
	uint16_t val;
	
    DDRB |= (1 << DDB1);
    // PB1 is now an output

    OCR1A = 0x01FF;
    // set PWM for 50% duty cycle @ 10bit


    TCCR1A |= (1 << COM1A1);
    // set none-inverting mode

    TCCR1A |= (1 << WGM11) | (1 << WGM10);
    // set 10bit phase corrected PWM Mode

    TCCR1B |= (1 << CS11);
    // set prescaler to 8 and starts PWM


	
	int volt,pwm;


    while (1)
    {
       val=adc_read4();
		
		
		pwm = (val/1024.0)*510;
		
		OCR1A = pwm;
		
		
    }
}