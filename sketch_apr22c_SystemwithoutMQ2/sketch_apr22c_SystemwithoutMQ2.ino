/*
 * 温湿度OLED显示+门限开关+继电器开关
*/
#include <dht11.h>
dht11 DHT11;

#define BUZPIN 2
#define LSPIN 3
#define DHT11PIN 7  //DHT11引脚设在digital 7
#define JDQPIN 8


int button1PIN = 22;
int button2PIN = 23;
int button3PIN = 24;
int button4PIN = 25;


int redLEDPIN = 30;
int blueLEDPIN = 31;
int greenLEDPIN = 32;

int temMax = 30;
int temMin = 20;

boolean ledRedState=false;  // 记录LED状态
boolean button1State=true;  // 记录按键状态


#include <U8g2lib.h>//oled12864驱动库
//#include <Wire.h>//硬件 I2C (基于Arduino Wire库)

/* OLED构造函数 */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C  u8g2(U8G2_R0);

void setup() {
  Serial.begin(9600);  //设置波特率参数

  pinMode(button1PIN, INPUT_PULLUP);
  pinMode(LSPIN,INPUT);
  
  pinMode(redLEDPIN,OUTPUT);
  pinMode(blueLEDPIN,OUTPUT);
  pinMode(greenLEDPIN,OUTPUT);

  pinMode(JDQPIN,OUTPUT);
  pinMode(BUZPIN,OUTPUT);
  

  u8g2.enableUTF8Print();//引用utf-8Unicode
  u8g2.begin();   //初始化
  
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

  /*OLED屏幕打印*/
//  u8g2.setFont(u8g2_font_liqingtang);
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

  u8g2.setCursor(0,63);  //设置打印的光标位置.
  u8g2.print("温度最小");
  u8g2.print(temMin);
  
  u8g2.sendBuffer();  //发送buffer缓冲区的内容到显示器

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

  if(digitalRead(LSPIN)){
    digitalWrite(JDQPIN,LOW);
    
    }
  else{
    digitalWrite(JDQPIN,HIGH);
    
    }



//    //while(digitalRead(button1Pin)==HIGH){}
//  // 当按键按下时，点亮或熄灭LED
//  if(ledRedState==true)
//  {
//    digitalWrite(ledRedPin,LOW);
//    ledRedState=!ledRedState;
//  }
//  else
//  {
//    digitalWrite(ledRedPin,HIGH);
//    ledRedState=!ledRedState;
//  }
//  
  

  

}
