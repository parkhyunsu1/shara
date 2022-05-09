int cds = A0;

void setup(){
  Serial.begin(9600);
  
}

void loop(){
  if(Serial.available()){
    int received_data = Serial.read();
    if(received_data == 1){
      int cdsValue = analogRead(cds);
      delay(1);
      if(cdsValue>300){
        Serial.write(1);
      }
      else{
        Serial.write(0);
      }
    }
  }
}
