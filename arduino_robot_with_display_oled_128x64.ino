
//
//#define TRIGGER A1
//#define ECHO A0
//
//#define MA1 2
//#define MA2 3
//
//#define MB1 4
//#define MB2 5

#include<MicroLCD.h>

LCD_SSD1306 lcd;

void back() {
//    digitalWrite(MA1, HIGH);
//    digitalWrite(MA2, LOW);
//   
//    digitalWrite(MB1, LOW);
//    digitalWrite(MB2, HIGH);

    PORTD = PORTD | (1 << PD2);
    PORTD = PORTD &~ (1 << PD3);
    
    PORTD = PORTD &~ (1 << PD4);
    PORTD = PORTD | (1 << PD5);
}

void front() {
//    digitalWrite(MA1, LOW);
//    digitalWrite(MA2, HIGH);
//   
//    digitalWrite(MB1, HIGH);
//    digitalWrite(MB2, LOW);

    PORTD = PORTD &~ (1 << PD2);
    PORTD = PORTD | (1 << PD3);
    
    PORTD = PORTD | (1 << PD4);
    PORTD = PORTD &~ (1 << PD5);
}

void stop() {
//    digitalWrite(MA1, LOW);
//    digitalWrite(MA2, LOW);
//   
//    digitalWrite(MB1, LOW);
//    digitalWrite(MB2, LOW);

    PORTD = PORTD &~ (1 << PD2);
    PORTD = PORTD &~ (1 << PD3);
    
    PORTD = PORTD &~ (1 << PD4);
    PORTD = PORTD &~ (1 << PD5);
}

void right() {
//    digitalWrite(MA1, LOW);
//    digitalWrite(MA2, HIGH);
//   
//    digitalWrite(MB1, LOW);
//    digitalWrite(MB2, HIGH);

    PORTD = PORTD &~ (1 << PD2);
    PORTD = PORTD | (1 << PD3);
    
    PORTD = PORTD &~ (1 << PD4);
    PORTD = PORTD | (1 << PD5);
}

void left() {
//    digitalWrite(MA1, HIGH);
//    digitalWrite(MA2, LOW);
//   
//    digitalWrite(MB1, HIGH);
//    digitalWrite(MB2, LOW);

    PORTD = PORTD | (1 << PD2);
    PORTD = PORTD &~ (1 << PD3);
    
    PORTD = PORTD | (1 << PD4);
    PORTD = PORTD &~ (1 << PD5);
}

float detect() {
//    digitalWrite(TRIGGER, 1);
    PORTC = PORTC | (1 << PC1);
    delayMicroseconds(2);
//    digitalWrite(TRIGGER, 0);
    PORTC = PORTC &~ (1 << PC1);
    return (pulseIn(A0, 1) * 0.01715);
}

void setup() {
//    pinMode(MA1, OUTPUT);
//    pinMode(MA2, OUTPUT);
//   
//    pinMode(MB1, OUTPUT);
//    pinMode(MB2, OUTPUT);

    DDRD = DDRD | (1 << DDD2);
    DDRD = DDRD | (1 << DDD3);
    DDRD = DDRD | (1 << DDD4);
    DDRD = DDRD | (1 << DDD5);
   
//    pinMode(ECHO, INPUT);
//    pinMode(TRIGGER, OUTPUT);
//    pinMode(13, OUTPUT);
//    digitalWrite(13,0);

    DDRC = DDRC &~ (1 << DDC0);
    DDRC = DDRC | (1 << DDC1);
    DDRB = DDRB | (1 << PB5);
    PORTB = PORTB &~ (1 << PB5);

    lcd.begin();
    float v = 0;
    while(1) {
      float d = detect();
      lcd.setCursor(0, 0);
      lcd.setFontSize(FONT_SIZE_MEDIUM);
      lcd.print("Distancia:");
      lcd.setCursor(0, 2);
      lcd.print(d);
      lcd.print("cm   ");
      lcd.setCursor(0, 4);
      lcd.print("Velocidade:");
      lcd.setCursor(0, 6);
      lcd.print(v);
      lcd.print("cm/s  ");
      
      if(d < 10) {
        stop();
        delay(200);
        back();
        delay(200);
        if(rand() % 2 == 0) {
          right();
        }else {
          left();
        }
        delay(200);
        stop();
      }
        
      if( d > 10){
        front();
      }else {
        stop();
      }

      v = (d - detect()) / 2;
    }
}
