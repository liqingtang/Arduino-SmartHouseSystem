/*
使用电位器（可调电阻）控制灯的亮度
Arduino通过模拟输入口A0读入经过电位器分压的电压，程序通过判断电压的大小，来调节LED的闪烁频率。 
呼吸频率修改，即是修改每次亮度改变后的延时长短。
因此我们将原来的延时函数中固定的参数替换为变量time，通过time的变化，来调节LED呼吸频率的变化。

*/
int ledPin = 9; //
int pot = A0;
void setup() {
  
  // put your setup code here, to run once:
}

void loop() {
  //LEd逐渐变亮
  for(int fadeValue = 0;fadeValue <= 255;fadeValue += 5)
  {
    analogWrite(ledPin,fadeValue);
    int time = analogRead(pot)/5;//读取电位器输出电压 ÷5是未来缩短延时时间
    delay(time);
    
  }

  for(int fadeValue = 255;fadeValue >=0;fadeValue -=5)
  {
      analogWrite(ledPin,fadeValue);
      delay(analogRead(pot)/5);//同上
  }
  // put your main code here, to run repeatedly:

}
