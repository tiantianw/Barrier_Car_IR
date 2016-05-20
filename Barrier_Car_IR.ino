int SNUM[3] ;     //3个传感器


int INA1 = 2;      //电机A1正反转控制端
int PWMA1 = 3;    //电机A1调速端
int INA2 = 4;      //电机A2正反转控制端
int PWMA2 = 5;     //电机A2调速端
int INB1 = 7;      //电机B1正反转控制端
int PWMB1 = 6;     //电机B1调速端
int INB2 = 8;      //电机B2正反转控制端
int PWMB2 = 9;     //电机B2调速端

void motospd(int sp1, int sp2) {
  if (sp1 > 0) {
    digitalWrite(INA1, HIGH);
    digitalWrite(INA2, HIGH);
  }
  else {
    digitalWrite(INA1, LOW);
    digitalWrite(INA2, LOW);
  }
  if (sp2 > 0) {
    digitalWrite(INB1, HIGH);
    digitalWrite(INB2, HIGH);
  }
  else {
    digitalWrite(INB1, LOW);
    digitalWrite(INB2, LOW);
  }

  analogWrite(PWMA1, abs (sp1));
  analogWrite(PWMA2, abs (sp1));
  analogWrite(PWMB1, abs (sp2));
  analogWrite(PWMB2, abs (sp2));
}

void setup() {
  pinMode(11, INPUT); //配置左传感器IO口为输入
  pinMode(12, INPUT); //配置中传感器IO口为输入
  pinMode(13, INPUT); //配置右传感器IO口为输入

  Serial.begin(9600); //打开串口，初始化

  pinMode(INA1, OUTPUT); //配置电机驱动IO口为输出
  pinMode(PWMA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(PWMA2, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(PWMB1, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(PWMB2, OUTPUT);
}

void loop() {
  SNUM[0] = digitalRead(11);//左传感器赋值
  SNUM[1] = digitalRead(12); //中传感器赋值
  SNUM[2] = digitalRead(13); //右传感器赋值
  //  for (int i = 0; i < 3; i++)
  //  {
  //    Serial.print(SNUM[i]);//串口输出每个传感器的值，打开串口可显示传感器检测结果
  //  }
  if ((SNUM[0] == 1) && (SNUM[1] == 1) && (SNUM[2] == 1)) //所有传感器都没有检测到障碍
    motospd(200, 200);                         //直行
  if ((SNUM[0] == 0) && (SNUM[1] == 1) && (SNUM[2] == 1)) //左传感器检测到障碍物
    motospd(75, -65);                          //右转
  if ((SNUM[0] == 1) && (SNUM[1] == 1) && (SNUM[2] == 0)) //右传感器检测到障碍物
    motospd(-65, 75);                           //左转
  if ((SNUM[0] == 1) && (SNUM[1] == 0) && (SNUM[2] == 1)) //中传感器检测到障碍物
  { motospd(-70, -70);                        //后退
    delay(800);
    motospd(-40, 50);
  }
  delay(300);
}






