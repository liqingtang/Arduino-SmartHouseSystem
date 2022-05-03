void setup() {
  pinMode(8,OUTPUT);
}

void loop() {
  digitalWrite(8,HIGH);
  delay(5000);
  digitalWrite(8,LOW);//低电平触发
  delay(1000);
}
