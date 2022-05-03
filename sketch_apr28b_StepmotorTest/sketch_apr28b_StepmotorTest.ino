int pin1 = 40;  //蓝
int pin2 = 41;  //粉
int pin3 = 42;  //黄
int pin4 = 44;  //橙

int delaytime = 100; //(ms)

void setup() {
  /*定义为输出引脚*/
  pinMode(pin1,OUTPUT);
  pinMode(pin2,OUTPUT);
  pinMode(pin3,OUTPUT);
  pinMode(pin4,OUTPUT);
  
}

void loop() {
  /*调用不同的自定义函数,28BYJ-48输出轴减速比64:1*/
//  D2PaiDown();//单2拍,蓝黄共下线圈,顺时针,16步一圈,转子步距角22.5°
//  D2PaiUp();//单2拍,粉橙共上线圈,逆时针,16步一圈,步距角22.5°
  D4Pai();//单4拍,32步走一圈,步距角11.25°
//  D4Pai2();//单4拍,用for循环
//  S4Pai();//双4拍,32步走一圈,步距角11.25度
//  DS8Pai();//单双8拍,64步走一圈,步距角5.625°
//  DS8Pai2();//逆时针
//  TEST1243();//测试,应为来回摆动  
}

void D2PaiDown(){
  digitalWrite(pin1,HIGH);//单2拍，蓝黄共下线圈
  delay(delaytime);
  digitalWrite(pin1,LOW);
  digitalWrite(pin3,HIGH);
  delay(delaytime);
  digitalWrite(pin3,LOW);
  }

void D2PaiUp(){
  digitalWrite(pin2,HIGH);  //单2拍，粉橙共上
  delay(delaytime);
  digitalWrite(pin2,LOW);
  digitalWrite(pin4,HIGH);
  delay(delaytime);
  digitalWrite(pin4,LOW); 
  }

void D4Pai(){
  digitalWrite(pin1,HIGH);  //单4拍
  delay(delaytime);
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,HIGH);
  delay(delaytime);
  digitalWrite(pin2,LOW);
  digitalWrite(pin3,HIGH);
  delay(delaytime);
  digitalWrite(pin3,LOW);
  digitalWrite(pin4,HIGH);
  delay(delaytime);
  digitalWrite(pin4,LOW);  
  }

void D4Pai2(){
    /*采用for循环，精简代码*/
  for(int i=40;i<=43;i++){
    digitalWrite(i,HIGH);
    delay(delaytime);
    digitalWrite(i,LOW);
    }
  }

void S4Pai(){
  digitalWrite(pin1,HIGH);  //双4拍
  digitalWrite(pin2,HIGH);
  delay(delaytime);       //12
  digitalWrite(pin1,LOW);
  digitalWrite(pin3,HIGH);
  delay(delaytime);       //23
  digitalWrite(pin2,LOW);
  digitalWrite(pin4,HIGH);
  delay(delaytime);       //34
  digitalWrite(pin3,LOW);
  digitalWrite(pin1,HIGH);
  delay(delaytime);       //41
  digitalWrite(pin4,LOW);
  }

void DS8Pai(){
  digitalWrite(pin1,HIGH);  //单双8拍
  delay(delaytime);       //1
  digitalWrite(pin2,HIGH);
  delay(delaytime);       //12
  digitalWrite(pin1,LOW);
  delay(delaytime);       //2
  digitalWrite(pin3,HIGH);
  delay(delaytime);       //23
  digitalWrite(pin2,LOW);
  delay(delaytime);       //3
  digitalWrite(pin4,HIGH);
  delay(delaytime);       //34
  digitalWrite(pin3,LOW);
  delay(delaytime);       //4
  digitalWrite(pin1,HIGH);
  delay(delaytime);       //41
  digitalWrite(pin4,LOW);
  }

void TEST1243(){
  digitalWrite(pin1,HIGH);//单4拍,测试1243是什么效果
  delay(delaytime);       //1
  digitalWrite(pin1,LOW);
  digitalWrite(pin2,HIGH);
  delay(delaytime);       //2
  digitalWrite(pin2,LOW);
  digitalWrite(pin4,HIGH);
  delay(delaytime);       //4
  digitalWrite(pin4,LOW);
  digitalWrite(pin3,HIGH);
  delay(delaytime);       //3
  digitalWrite(pin3,LOW);
  }

void DS8Pai2(){
  digitalWrite(pin4,HIGH);  //单双8拍
  delay(delaytime);       //4
  digitalWrite(pin3,HIGH);
  delay(delaytime);       //43
  digitalWrite(pin4,LOW);
  delay(delaytime);       //3
  digitalWrite(pin2,HIGH);
  delay(delaytime);       //32
  digitalWrite(pin3,LOW);
  delay(delaytime);       //2
  digitalWrite(pin1,HIGH);
  delay(delaytime);       //21
  digitalWrite(pin2,LOW);
  delay(delaytime);       //1
  digitalWrite(pin4,HIGH);
  delay(delaytime);       //14
  digitalWrite(pin1,LOW);
  }
