
int pin_switch = 13;
int pin_led1 = 8;
int pin_led2 = 9;

boolean buttonStatel = false;
boolean buttonSwitch_State_old = LOW;
boolean buttonSwitch_State_new = LOW;
boolean statusLED = LOW;

void setup(){
  Serial.begin(9600);
  pinMode(pin_led1,OUTPUT);
  pinMode(pin_led2,OUTPUT);
  digitalWrite(pin_led1,LOW);
  digitalWrite(pin_led2,LOW);
  pinMode(pin_switch,INPUT);
}

void loop(){
  if(Serial.available()){
    int received_data = Serial.read();
    if(received_data ==1){
      digitalWrite(pin_led2,HIGH);delay(500);
      digitalWrite(pin_led2,LOW);
    }
  }
  buttonSwitch_State_new = digitalRead(pin_switch);delay(1);
  if(buttonSwitch_State_new != buttonSwitch_State_old){
    if( buttonSwitch_State_new == HIGH){
      if(statusLED == LOW){
        Serial.write(1);
        digitalWrite(pin_led1,HIGH);
        statusLED = HIGH;
      }
      else{
        Serial.write(0);
        digitalWrite(pin_led1,LOW);
        statusLED = LOW;
      }
    }
    buttonSwitch_State_old= buttonSwitch_State_new;
  }
}
