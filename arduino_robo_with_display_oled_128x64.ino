//#define TRIGGER A1
//#define ECHO A0
//
//#define MA1 2
//#define MA2 3
//
//#define MB1 4
//#define MB2 5

#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define OLED_WIDTH 128
#define OLED_HEIGHT 64

#define OLED_ADDR 0x3C

Adafruit_SSD1306 lcd(OLED_WIDTH, OLED_HEIGHT);

void back() {
//  digitalWrite(MA1, HIGH);
//  digitalWrite(MA2, LOW);
//   
//  digitalWrite(MB1, LOW);
//  digitalWrite(MB2, HIGH);

    PORTD = PORTD | (1 << PD2);
    PORTD = PORTD &~ (1 << PD3);
    
    PORTD = PORTD &~ (1 << PD4);
    PORTD = PORTD | (1 << PD5);
}

void front() {
//  digitalWrite(MA1, LOW);
//  digitalWrite(MA2, HIGH);
//   
//  digitalWrite(MB1, HIGH);
//  digitalWrite(MB2, LOW);

    PORTD = PORTD &~ (1 << PD2);
    PORTD = PORTD | (1 << PD3);
    
    PORTD = PORTD | (1 << PD4);
    PORTD = PORTD &~ (1 << PD5);
}

void stop() {
//  digitalWrite(MA1, LOW);
//  digitalWrite(MA2, LOW);
//   
//  digitalWrite(MB1, LOW);
//  digitalWrite(MB2, LOW);

    PORTD = PORTD &~ (1 << PD2);
    PORTD = PORTD &~ (1 << PD3);
    
    PORTD = PORTD &~ (1 << PD4);
    PORTD = PORTD &~ (1 << PD5);
}

void right() {
//  digitalWrite(MA1, LOW);
//  digitalWrite(MA2, HIGH);
//   
//  digitalWrite(MB1, LOW);
//  digitalWrite(MB2, HIGH);

    PORTD = PORTD &~ (1 << PD2);
    PORTD = PORTD | (1 << PD3);
    
    PORTD = PORTD &~ (1 << PD4);
    PORTD = PORTD | (1 << PD5);
}

void left() {
//  digitalWrite(MA1, HIGH);
//  digitalWrite(MA2, LOW);
//   
//  digitalWrite(MB1, HIGH);
//  digitalWrite(MB2, LOW);

    PORTD = PORTD | (1 << PD2);
    PORTD = PORTD &~ (1 << PD3);
    
    PORTD = PORTD | (1 << PD4);
    PORTD = PORTD &~ (1 << PD5);
}

float detect() {
//  digitalWrite(TRIGGER, 1);
    PORTC = PORTC | (1 << PC1);
    delayMicroseconds(2);
//  digitalWrite(TRIGGER, 0);
    PORTC = PORTC &~ (1 << PC1);
    return (pulseIn(A0, 1) * 0.01715);
}

void setup() {
//  pinMode(MA1, OUTPUT);
//  pinMode(MA2, OUTPUT);
//   
//  pinMode(MB1, OUTPUT);
//  pinMode(MB2, OUTPUT);

    DDRD = DDRD | (1 << DDD2);
    DDRD = DDRD | (1 << DDD3);
    DDRD = DDRD | (1 << DDD4);
    DDRD = DDRD | (1 << DDD5);
   
//  pinMode(ECHO, INPUT);
//  pinMode(TRIGGER, OUTPUT);
//  pinMode(13, OUTPUT);
//  digitalWrite(13,0);

    DDRC = DDRC &~ (1 << DDC0);
    DDRC = DDRC | (1 << DDC1);
    DDRB = DDRB | (1 << PB5);
    PORTB = PORTB &~ (1 << PB5);

    lcd.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR);
    float v = 0;
    while(1) {
      float d = detect();
      lcd.clearDisplay();
      lcd.drawRoundRect(0, 0, 128, 64, 8, WHITE);
      lcd.setTextColor(WHITE);
      lcd.setTextSize(1);
      lcd.setCursor(16, 8);
      lcd.print("DISTANCE: ");
      lcd.print(d);
      lcd.print(" cm");
      lcd.setCursor(16, 28);
      lcd.print("SPEED: ");
      lcd.print(v);
      lcd.print(" cm/s");
      lcd.display();

      float ds[] = {0, 0};
      
      if(d < 20) {
        stop();
        delay(100);
        back();
        delay(400);
        stop();
        delay(100);
        
        right();
        delay(300);
        stop();
        delay(100);
        ds[0] = detect();
        
        left();
        delay(600);
        stop();
        delay(100);
        ds[1] = detect();
        
        right();
        delay(300);
        stop();
        delay(100);
        
        if(ds[0] > ds[1] && ds[0] > 20) {
          right();
          delay(300);
        }else if(ds[0] < ds[1] && ds[1] > 20) {
          left();
          delay(300);
        }
        stop();
      }
        
      if( d > 20){
        front();
        v = (d - detect()) / 2;
      }else {
        stop();
      }
    }
}
