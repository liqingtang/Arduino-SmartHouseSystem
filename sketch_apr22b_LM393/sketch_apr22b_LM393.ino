void setup()

{

pinMode(3,INPUT);

pinMode(13,OUTPUT);

}

void loop() {

if (digitalRead(3)) {   //光线不到阈值，D0输出高电平if（1），运行if后的

digitalWrite(13,HIGH);//开灯

}

else {               //光线达到阈值，D0输出低电平，if（0），运行else后的

digitalWrite(13,LOW);//关灯

delay(300);

}

}
