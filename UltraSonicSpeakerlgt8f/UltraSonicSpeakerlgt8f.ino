#include <Arduino.h>

const byte outPin = 9; // timer1
const byte adc_pin = A0; // = 14 (pins_arduino.h)

//used ultrasonic carrier frequency
const long freq = 40000L;

//test
volatile int adcValue = 100;

void setup() {
  ADCSRA = 0;             // clear ADCSRA register
  ADCSRB = 0;             // clear ADCSRB register
  ADMUX = (1 << REFS0) | 0; //Select ADC Channel
  ADMUX |= (0 & 0x07);    // set A0 analog input pin
  // ADMUX |= (1 << REFS0);  // set reference voltage
  //ADMUX |= (1 << ADLAR);  // left align ADC value to 8 bits from ADCH register

  ADCSRA |= (1 << ADPS2); // 16 prescaler for 76.9 KHz

  ADCSRA |= (1 << ADATE); // enable auto trigger
  ADCSRA |= (1 << ADIE);  // enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN);  // enable ADC
  ADCSRA |= (1 << ADSC);  // start ADC measurements
  sei();

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(3, OUTPUT);
  
  
  TCCR1A = _BV(COM1A1) | _BV(COM1A0) | _BV(COM1B1) ;// | _BV(WGM11);
  TCCR1B = _BV(WGM13) | _BV(CS10);

  ICR1 = ((F_CPU) / freq / 2) - 1;
  OCR1A = ((ICR1 + 1) *(1.0/10.0)) - 1;//ICR1/4 ;
  OCR1B = ((ICR1 + 1) *(7.0/10.0)) - 1; //ICR1/3 ;
 
  TIMSK1 |= 1 << TOIE1; //overflow interrupt enable

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}

// ADC complete ISR
//TODO to understand why this interrupt does not fire
ISR(ADC_vect) {
  adcValue = 10;//ADCH;
}

ISR(TIMER1_OVF_vect) 
{
  //better clone ltg8f gives 12 bit precision here. Significant quality difference compared to arduino
  unsigned char adcl = ADCL; 
  unsigned char adch = ADCH;

  adcValue = ((adch << 8) | adcl); // Combine for full quality

  //Mapping adjusted with bit depth
  OCR1A = map(adcValue,0, 4100, ICR1 -1,((ICR1 + 1) / 2) + 10 - 1);
  OCR1B = map(adcValue,0, 4100, 0,((ICR1 + 1) / 2) - 10 - 1);
}