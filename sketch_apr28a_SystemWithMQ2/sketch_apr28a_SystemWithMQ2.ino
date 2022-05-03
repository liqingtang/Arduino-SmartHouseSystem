/*
 * 温湿度OLED显示+门限开关+继电器开关
*/
#include <dht11.h>
dht11 DHT11;

#define BUZPIN 2
#define LSPIN 3
#define DHT11PIN 7  //DHT11引脚设在digital 7
#define JDQPIN 8

#define MQ2PIN (0)  //MQ2烟雾传感器引脚设在A0

int pin1 = 40;  //步进电机-蓝线
int pin2 = 41;  //粉
int pin3 = 42;  //黄
int pin4 = 44;  //橙

int button1PIN = 22;
int button2PIN = 23;
int button3PIN = 24;
int button4PIN = 25;

int redLEDPIN = 30;
int blueLEDPIN = 31;
int greenLEDPIN = 32;

int temMax = 30;
int temMin = 20;

float MQ2sensorValue; //记录MQ2传感器的值

int delaytime = 3; //步进电机延时(ms)

boolean ledRedState=false;  // 记录LED状态
boolean button1State=true;  // 记录按键状态


#include <U8g2lib.h>//oled12864驱动库


/* OLED构造函数 */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C  u8g2(U8G2_R0);

void setup() {
  Serial.begin(9600);  //设置波特率参数

  pinMode(button1PIN, INPUT_PULLUP);//按键-输入上拉模式
  pinMode(LSPIN,INPUT);//光纤传感器
  
  pinMode(redLEDPIN,OUTPUT);//发光二级管
  pinMode(blueLEDPIN,OUTPUT);
  pinMode(greenLEDPIN,OUTPUT);

  pinMode(JDQPIN,OUTPUT);//继电器
  pinMode(BUZPIN,OUTPUT);//蜂鸣器

    /*定义步进电机输出引脚*/
  for (int i = 40; i < 44; i++) {
    pinMode(i, OUTPUT);
  }
//  pinMode(pin1,OUTPUT);
//  pinMode(pin2,OUTPUT);
//  pinMode(pin3,OUTPUT);
//  pinMode(pin4,OUTPUT);

  u8g2.enableUTF8Print();//引用utf-8Unicode
  u8g2.begin();   //初始化

  Serial.println("Gas sensor warming up!");
  //delay(20000); //等待MQ传感器预热20s
  
}

void clockwise(int num)
{
  for (int count = 0; count < num; count++)
  {
    for (int i = 40; i < 44; i++)
    {
      digitalWrite(i, HIGH);
      delay(3);
      digitalWrite(i, LOW);
    }
  }
}

void anticlockwise(int num)
{
  for (int count = 0; count < num; count++)
  {
    for (int i = 43; i > 39; i--)
    {
      digitalWrite(i, HIGH);
      delay(3);
      digitalWrite(i, LOW);
    }
  }
}

void loop() {
  u8g2.clearBuffer();   // 清空显示设备内部缓冲区
  Serial.println("\n");
  /*检查程序*/
  int chk = DHT11.read(DHT11PIN);
  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK:
                Serial.println("OK");
                break;
    case DHTLIB_ERROR_CHECKSUM:
                Serial.println("Checksum error");
                break;
    case DHTLIB_ERROR_TIMEOUT:
                Serial.println("Time out error");
                break;
    default:
                Serial.println("Unknown error");
                break;
  }
  Serial.print("Humidity (%): ");
  Serial.println((float)DHT11.humidity, 2);   //串口打印湿度

  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);  //串口打印温度
  
  //delay(500);//延时

  /*OLED屏幕打印设置*/
  u8g2.setFont(u8g2_font_liqingtang);
  u8g2.setFontDirection(0); //旋转图像预设值
  u8g2.clearBuffer();
  float tem = (float)DHT11.temperature;
  u8g2.setCursor(0,16);  //设置打印的光标位置
  u8g2.print("温度 ");
  u8g2.print(tem);
  u8g2.print(" oC");
  
  u8g2.setCursor(0,32);  //设置打印的光标位置.
  u8g2.print("湿度 ");
  u8g2.print((float)DHT11.humidity);
  u8g2.print(" %");

  u8g2.setCursor(0,48);  //设置打印的光标位置.
  u8g2.print("温度最大");
  u8g2.print(temMax);
  u8g2.print("最小");
  u8g2.print(temMin);
  

  MQ2sensorValue = analogRead(MQ2PIN);  //从ANLOG 0读取输入的值
  Serial.print("MQ2 Sensor Value: ");
  Serial.print(MQ2sensorValue);
  if(MQ2sensorValue > 300){
    Serial.print(" | Smoke detected!");
    }
  Serial.println("");

  u8g2.setCursor(0,62);  //设置打印的光标位置.
  u8g2.print("烟雾浓度 ");
  u8g2.print(MQ2sensorValue);
  
  u8g2.sendBuffer();  //发送buffer缓冲区的内容到显示器


  /*温度判断逻辑*/
  if(tem <= temMin){
    digitalWrite(BUZPIN,HIGH);
    digitalWrite(blueLEDPIN,HIGH);
    digitalWrite(greenLEDPIN,LOW);
    }
  else if(tem >= temMax){
    digitalWrite(BUZPIN,HIGH);
    digitalWrite(redLEDPIN,HIGH);
    digitalWrite(greenLEDPIN,LOW);   
    }
  else{
    digitalWrite(BUZPIN,LOW);
    digitalWrite(greenLEDPIN,HIGH);
    digitalWrite(blueLEDPIN,LOW);
    digitalWrite(redLEDPIN,LOW);  
    }

  /*光强判断逻辑，继电器低电平触发*/
  if(digitalRead(LSPIN)){ //光线传感器不够阈值则输出高电平，if（1）
    digitalWrite(JDQPIN,LOW); //低电平触发，开灯
    anticlockwise(64);
    delay(10);
    }
  else{
    digitalWrite(JDQPIN,HIGH);
    clockwise(64);
    delay(10);
    }
  /*烟雾浓度判断逻辑*/
  if((MQ2sensorValue > 300) || (tem >= temMax) || (tem <= temMin)){
    digitalWrite(BUZPIN,HIGH);
    //此处最好可以加上屏显报警
    }
  else{
    digitalWrite(BUZPIN,LOW);
    }

  /*调用自定义函数,注意28BYJ-48输出轴减速比64:1*/
//  DS8Pai1();//单双8拍,64步走一圈,步距角5.625°,顺时针
//  DS8Pai2();//逆时针
//  clockwise(512);
//  delay(10);
//  anticlockwise(512);
}

//void DS8Pai1(){
//  digitalWrite(pin1,HIGH);  //单双8拍
//  delay(delaytime);       //1
//  digitalWrite(pin2,HIGH);
//  delay(delaytime);       //12
//  digitalWrite(pin1,LOW);
//  delay(delaytime);       //2
//  digitalWrite(pin3,HIGH);
//  delay(delaytime);       //23
//  digitalWrite(pin2,LOW);
//  delay(delaytime);       //3
//  digitalWrite(pin4,HIGH);
//  delay(delaytime);       //34
//  digitalWrite(pin3,LOW);
//  delay(delaytime);       //4
//  digitalWrite(pin1,HIGH);
//  delay(delaytime);       //41
//  digitalWrite(pin4,LOW);
//  }
//
//void DS8Pai2(){
//  digitalWrite(pin4,HIGH);  //单双8拍
//  delay(delaytime);       //4
//  digitalWrite(pin3,HIGH);
//  delay(delaytime);       //43
//  digitalWrite(pin4,LOW);
//  delay(delaytime);       //3
//  digitalWrite(pin2,HIGH);
//  delay(delaytime);       //32
//  digitalWrite(pin3,LOW);
//  delay(delaytime);       //2
//  digitalWrite(pin1,HIGH);
//  delay(delaytime);       //21
//  digitalWrite(pin2,LOW);
//  delay(delaytime);       //1
//  digitalWrite(pin4,HIGH);
//  delay(delaytime);       //14
//  digitalWrite(pin1,LOW);
//  }
//
