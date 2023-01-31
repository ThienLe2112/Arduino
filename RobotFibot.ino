#include<string.h>
// vitrimm=120 di dc 30cm
// vitrimm =75 xoay goc 90 do
int vitril = 0, vitrir = 0, vitrimml = 0, vitrimmr = 0, loil, loir;
#define in1 5
#define in2 6
#define in3 9
#define in4 10
int ss0;
int ss1;
int ss2;
int ss3;
int ss4;
#define dl1 12
#define dl2 13
#define dl3 4
#define dl4 11
void chayr() {
  if ( digitalRead(8) == 1) {
    vitrir--;
  }
  else
    vitrir++;

}
void chayl() {
  if ( digitalRead(7) == 1) {
    vitril++;
  }
  else
    vitril--;

}
void quayl(int nangluongl);
void quayr(int nangluongr);
int pid(int loi, int kp, int ki, int kd) {
  int dloi ;
  static int  loitr = 0, iloi = 0;
  long int temp;
  dloi = loi - loitr;
  iloi += loi;
  if (iloi >= 100) {
    iloi = 100;
  }
  if (iloi <= -100) {
    iloi = -100;
  }
  loitr = loi;
  temp = kp * loi + ki * iloi + kd * dloi;
  if (temp >= 255) {
    temp = 255;
  }
  if (temp <= -255) {
    temp = -255;
  }
  return temp;
}
void dithang(int vitril, int vitrir);
void xoay(int vitril, int vitrir, const char* xoay);
void motorstop() {
  digitalWrite(in1, 0);
  digitalWrite(in2, 0);
  digitalWrite(in3, 0);
  digitalWrite(in4, 0);
}
void setup() {
  attachInterrupt(1, chayr, RISING);
  attachInterrupt(0, chayl, RISING);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Vi tri left " ); Serial.println(vitril);
  Serial.print("Vi tri right " ); Serial.println(vitrir);
  ss0 = analogRead(A0);// sensor trái ngoài cùng
  ss1 = analogRead(A1);// sensor chéo trái
  ss2 = analogRead(A2);// sensor giữa
  ss3 = analogRead(A3);// sensor chéo phải
  ss4 = analogRead(A4);// sensor phải ngoài cùng
  dithang();
  //  if ( ss3 > 100) //khong co vat can
  //  {
  //
  //    xoay(vitril, vitrir, "phai");
  //    dithang(vitril, vitrir);
  //  }
  //  else if (ss2 > 100) {
  //    dithang(vitril, vitrir);
  //  }
  //  else {
  //    xoay(vitril, vitrir, "trai");
  //    dithang(vitril, vitrir);
  //  }
  delay(1000);
  motorstop();
  delay(1000);
}

void quayl(int nangluongl) {
  if (nangluongl >= 150) {
    nangluongl = 150;
  }
  if (nangluongl <= -150) {
    nangluongl = -150;
  }
  if (nangluongl > 0) {
    analogWrite(in3, nangluongl);
    analogWrite(in4, 0);
  }
  if (nangluongl < 0) {
    analogWrite(in3, 0);
    analogWrite(in4, -nangluongl);
  }
}
void quayr(int nangluongr) {
  if (nangluongr >= 150) {
    nangluongr = 150;
  }
  if (nangluongr <= -150) {
    nangluongr = -150;
  }
  if (nangluongr > 0) {
    analogWrite(in1, nangluongr);
    analogWrite(in2, 0);
  }
  if (nangluongr < 0) {
    analogWrite(in1, 0);
    analogWrite(in2, -nangluongr);
  }
}
void dithang() {
  int vitrimml = 120+vitril; int vitrimmr = 120+vitrir; // 120 để chạy được 30cm
  int loil, loir;
  loil = vitrimml - vitril;
  loir = vitrimmr - vitrir;
  while (loil < -5 || loil > 5) {
    attachInterrupt(1, chayr, RISING);
    attachInterrupt(0, chayl, RISING);
    Serial.print("Vi tri left " ); Serial.println(vitril);
    Serial.print("Vi tri right " ); Serial.println(vitrir);
    loil = vitrimml - vitril;
    loir = vitrimmr - vitrir;
    quayl(pid(loil, 3, 0, 1));
    quayr(pid(loir, 3, 0, 1));
  }
}
void xoay(int vitril, int vitrir, const char* ben) {
  if (ben == "phai") {
    int vitrixoayl = 75 + vitril;
    int vitrixoayr = -75 + vitrir;
    int loil, loir;
    loil = vitrixoayl - vitril;
    loir = vitrixoayr - vitrir;
    while (loil > -10 || loil < 10) {
      attachInterrupt(1, chayr, RISING);
      attachInterrupt(0, chayl, RISING);
      Serial.print("Vi tri left " ); Serial.println(vitril);
      Serial.print("Vi tri right " ); Serial.println(vitrir);
      loil = vitrixoayl - vitril;
      loir = vitrixoayr - vitrir;
      quayl(pid(loil, 3, 0, 1));
      quayr(pid(loir, 3, 0, 1));
    }
  }
  else if ( ben == "trai") {
    int vitrixoayl = -75 + vitril;
    int vitrixoayr = +75 + vitrir;
    int loil, loir;
    loil = vitrixoayl - vitril;
    loir = vitrixoayr - vitrir;
    while (loir > -10 || loir < 10) {
      attachInterrupt(1, chayr, RISING);
      attachInterrupt(0, chayl, RISING);
      Serial.print("Vi tri left " ); Serial.println(vitril);
      Serial.print("Vi tri right " ); Serial.println(vitrir);
      loil = vitrixoayl - vitril;
      loir = vitrixoayr - vitrir;
      quayl(pid(loil, 3, 0, 1));
      quayr(pid(loir, 3, 0, 1));
    }
  }
}
