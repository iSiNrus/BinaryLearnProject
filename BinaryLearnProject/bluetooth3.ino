#include <SoftwareSerial.h>
#include <Time.h>

const int data_pin_2 = 2;
const int sh_pin_2 = 4;
const int st_pin_2 = 3;

const int data_pin_1 = 5;
const int sh_pin_1 = 7;
const int st_pin_1 = 6;

byte desyt[11] = {
    0b01111101, // 0
    0b00110000, // 1
    0b01101110, // 2
    0b01111010, // 3
    0b00110011, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011, // 9
    0b00000000,
};

// единици
byte digits[11] = {
    0b01111101, // 0
    0b00110000, // 1
    0b01101110, // 2
    0b01111010, // 3
    0b00110011, // 4
    0b01011011, // 5
    0b01011111, // 6
    0b01110000, // 7
    0b01111111, // 8
    0b01111011, // 9
    0b00000000,
};



int Led0 = A0;
int Led1 = A1;
int Led2 = A2;
int Led3 = A3;
int Led4 = A4;
int Led5 = A5;
int gRxPin = 10;
int gTxPin = 11;
String val;
int value = 0;
SoftwareSerial BTSerial(gRxPin, gTxPin);

void ed(byte v){
    for(int i=0; i<8; i++){
        digitalWrite(sh_pin_2, LOW);
        digitalWrite(data_pin_2, v & (1 << i ));
        digitalWrite(sh_pin_2, HIGH);
    }
    digitalWrite(st_pin_2, HIGH); 
    digitalWrite(st_pin_2, LOW);

}
// десятки
void des(byte v){
    for(int i=0; i<8; i++){
        digitalWrite(sh_pin_1, LOW);
        digitalWrite(data_pin_1, v & (1 << i ));
        digitalWrite(sh_pin_1, HIGH);
    }
    digitalWrite(st_pin_1, HIGH); 
    digitalWrite(st_pin_1, LOW);
}


void setup() {
  BTSerial.begin(38400);
  Serial.begin(38400);
  delay(500);

  pinMode(Led0, OUTPUT);
  pinMode(Led1, OUTPUT);
  pinMode(Led2, OUTPUT);
  pinMode(Led3, OUTPUT);
  pinMode(Led4, OUTPUT);
  pinMode(Led5, OUTPUT);


  pinMode(data_pin_2, OUTPUT);
  pinMode(sh_pin_2, OUTPUT);
  pinMode(st_pin_2, OUTPUT);
  pinMode(data_pin_1, OUTPUT);
  pinMode(sh_pin_1, OUTPUT);
  pinMode(st_pin_1, OUTPUT);

}

void loop() {
 
  while (BTSerial.available()) {
    delay(10);
    char c =  BTSerial.read();
    val += c;
    Serial.println(val);
  }
  
  if (val.length() > 0) {
    Serial.println(val);
    if (val == "0") {
    analogWrite(Led0, 255);
    value = value+1;
    
   }
   else if (val =="10") {
    analogWrite(Led0, 0);
    value = value -1;
   }
   
   else if (val == "1") {
    analogWrite(Led1, 255);
    value = value +2;
   }
    else if (val == "11"){
    analogWrite(Led1, 0);
    value = value -2;
    }
    else if (val == "2"){
    analogWrite(Led2, 255);
    value = value +4;
    }
    else if (val == "12"){
    analogWrite(Led2, 0);
    value = value - 4;
    }
    else if (val == "3"){
    analogWrite(Led3, 255);
    value = value + 8;
    }
    else if (val == "13"){
    analogWrite(Led3, 0);
    value = value - 8;
    }
    else if (val == "4"){
    analogWrite(Led4, 255);
    value = value + 16;
    }
    else if (val == "14"){
    analogWrite(Led4, 0);
    value = value - 16;
    }
    else if (val == "5"){
    analogWrite(Led5, 255);
    value = value + 32;
    }
    else if (val == "15"){
    analogWrite(Led5, 0);
    value = value - 32;
    }    
   }

    
   int  a = value % 10;
    int b = value / 10;
    
    des(desyt[b]);
    ed(digits[a]);  
  val = "";
  }
