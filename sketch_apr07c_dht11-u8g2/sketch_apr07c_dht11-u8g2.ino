/*
 *创建三个函数，后续调用
*/
//double Fahrenheit(double celsius)
//{
//        return 1.8 * celsius + 32;
//}    //摄氏温度度转化为华氏温度
//
//double Kelvin(double celsius)
//{
//        return celsius + 273.15;
//}     //摄氏温度转化为开氏温度

//// 露点（点在此温度时，空气饱和并产生露珠）,使用戈夫 -格雷奇( Goff-Gratch) 公式
//// 参考: http://wahiduddin.net/calc/density_algorithms.htm
//double dewPoint(double celsius, double humidity)
//{
//        double A0= 373.15/(273.15 + celsius);
//        double SUM = -7.90298 * (A0-1);
//        SUM += 5.02808 * log10(A0);
//        SUM += -1.3816e-7 * (pow(10, (11.344*(1-1/A0)))-1) ;
//        SUM += 8.1328e-3 * (pow(10,(-3.49149*(A0-1)))-1) ;
//        SUM += log10(1013.246);
//        double VP = pow(10, SUM-3) * humidity;
//        double T = log(VP/0.61078);   // temp var
//        return (241.88 * T) / (17.558-T);
//}
//
//// 快速计算露点，速度是5倍dewPoint()
//// 参考: http://en.wikipedia.org/wiki/Dew_point
//double dewPointFast(double celsius, double humidity)
//{
//        double a = 17.271;
//        double b = 237.7;
//        double temp = (a * celsius) / (b + celsius) + log(humidity/100);
//        double Td = (b * temp) / (a - temp);
//        return Td;
//}

#include <dht11.h>
dht11 DHT11;

#define DHT11PIN 7
#include <Arduino.h>//【new】
#include <U8g2lib.h>//oled12864必备【new】
#include <Wire.h>//硬件 I2C (基于Arduino Wire库)【new】
#define rst  2
U8G2_SSD1306_128X64_NONAME_F_HW_I2C  u8g2(U8G2_R0 , rst);
//U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

void setup()
{
  Serial.begin(9600);  //设置波特率参数
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();

  u8g2.enableUTF8Print();//中文显示
  u8g2.begin();//【new】
}

void loop()
{
  u8g2.clearBuffer();           // 清空显示设备内部缓冲区【new】
  
  Serial.println("\n");

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
  Serial.println((float)DHT11.humidity, 2);

  Serial.print("Temperature (oC): ");
  Serial.println((float)DHT11.temperature, 2);

//  Serial.print("Temperature (oF): ");
//  Serial.println(Fahrenheit(DHT11.temperature), 2);
//
//  Serial.print("Temperature (K): ");
//  Serial.println(Kelvin(DHT11.temperature), 2);
//
//  Serial.print("Dew Point (oC): ");
//  Serial.println(dewPoint(DHT11.temperature, DHT11.humidity));
//
//  Serial.print("Dew PointFast (oC): ");
//  Serial.println(dewPointFast(DHT11.temperature, DHT11.humidity));

  delay(2000);//延时2秒

  int tem = (float)DHT11.temperature;
  int hum = (float)DHT11.humidity;
  
  u8g2.setFont(u8g2_font_unifont_t_chinese1);
  u8g2.setFontDirection(0);//咱不知道为啥旋转图像
  u8g2.clearBuffer();
  u8g2.setCursor(0, 15);//设置打印的光标位置
  u8g2.print("当前温度：");
  u8g2.print(tem);
  u8g2.print("℃");
  
  u8g2.setCursor(0, 35);
  u8g2.print("湿度：");
  u8g2.print(hum);
  u8g2.print("%");
  u8g2.sendBuffer();//发送buffer缓冲区的内容到显示器
  delay(2000);
  
}
//[/mw_shl_code]
