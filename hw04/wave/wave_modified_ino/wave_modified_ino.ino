/*
  Use this sketch to test the SoftSysSynth.
 
  Remove the speaker and run a resistor from the emitter of the transistor to ground
  (effectively bypassing the decoupling capacitor and the speaker).
 
  Then run a wire from the emitter to A0.
 
  When you run this sketch, open the serial monitor.  The input is on the left.
  The value at A0 is on the right.  With the 0.7 V offset, the value at A0 should
  equal the input value minus ~36.
  Author: Allen Downey
 
  Based on http://arduino.cc/en/Tutorial/AnalogInput
  Created by David Cuartielles, modified by Tom Igoe.
 
  License: Public Domain
 */
 
 
int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 5;       // select the pin for the LED
int sensorValue = 0;  // variable to store the value coming from the sensor
int buttonPin1 = 2;
int buttonPin2 = 3;
int counter = 0;
 
void setup() {
  Serial.begin(9600);
 
  pinMode(buttonPin1, INPUT); 
  pinMode(buttonPin2, INPUT); 
 
  pinMode(ledPin, OUTPUT);
 
  DDRB = B00111111;
  DDRD = B11000000;
  
  //Implementing intterupts
  cli();//stop interrupts

  //set timer0 interrupt at 2kHz
  TCCR0A = 0;// set entire TCCR0A register to 0
  TCCR0B = 0;// same for TCCR0B
  TCNT0  = 0;//initialize counter value to 0
  // set compare match register for 2khz increments
  OCR0A = 124;// = (16*10^6) / (2000*64) - 1 (must be <256)
  // turn on CTC mode
  TCCR0A |= (1 << WGM01);
  // Set CS01 and CS00 bits for 64 prescaler
  TCCR0B |= (1 << CS01) | (1 << CS00);   
  // enable timer compare interrupt
  TIMSK0 |= (1 << OCIE0A);

//set timer1 interrupt at 1Hz
  TCCR1A = 0;// set entire TCCR1A register to 0
  TCCR1B = 0;// same for TCCR1B
  TCNT1  = 0;//initialize counter value to 0
  // set compare match register for 1hz increments
  OCR1A = 15624;// = (16*10^6) / (1*1024) - 1 (must be <65536)
  // turn on CTC mode
  TCCR1B |= (1 << WGM12);
  // Set CS10 and CS12 bits for 1024 prescaler
  TCCR1B |= (1 << CS12) | (1 << CS10);  
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

//set timer2 interrupt at 8kHz
  TCCR2A = 0;// set entire TCCR2A register to 0
  TCCR2B = 0;// same for TCCR2B
  TCNT2  = 0;//initialize counter value to 0
  // set compare match register for 8khz increments
  OCR2A = 249;// = (16*10^6) / (8000*8) - 1 (must be <256)
  // turn on CTC mode
  TCCR2A |= (1 << WGM21);
  // Set CS21 bit for 8 prescaler
  TCCR2B |= (1 << CS21);   
  // enable timer compare interrupt
  TIMSK2 |= (1 << OCIE2A);


  sei();//allow interrupts
}
 
ISR(TIMER1_COMPA_vect){//timer1 interrupt 1Hz toggles pin 13 (LED)
//generates pulse wave of frequency 1Hz/2 = 0.5kHz (takes two cycles for full wave- toggle high then toggle low)
  counter += 8;
  if (counter > 255) counter = 0;
  Serial.print(counter);
  Serial.print(", ");
 
  // write to the digital pins 
  writeByte(counter);
 
  /*if (toggle1){
    digitalWrite(13,HIGH);
    toggle1 = 0;
  }
  else{
    digitalWrite(13,LOW);
    toggle1 = 1;
  }*/
}
 
int reverse(int b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}
 
void writeByte(int x) {
  //76543210
  int xreverse=  reverse(x);
 
  int Dbits= B00000011;
  //11000000
  int Bbits= B11111100;
  //00111111
 
  PORTD= (xreverse >> 6) & Dbits ;
  PORTB= (xreverse << 2) & Bbits ;
}
 

void loop() {
//  counter += 8;
//  if (counter > 255) counter = 0;
//  Serial.print(counter);
//  Serial.print(", ");
// 
//  // write to the digital pins 
//  writeByte(counter);
// 
  // read the value from the sensor:
  sensorValue = analogRead(sensorPin);
  Serial.println(sensorValue >> 2);
 
  int button1 = digitalRead(buttonPin1);
  int button2 = digitalRead(buttonPin2);
 
  // if either button is pressed, turn on the LED
  if (button1 ^ button2) {
      digitalWrite(ledPin, HIGH); 
  } else {         
      digitalWrite(ledPin, LOW);
  }
 
  delay(400); 
}
