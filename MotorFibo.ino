#include <Arduino_FreeRTOS.h>
#include<string.h>
// vitrimm=120 di dc 30cm
// vitrimm =75 xoay goc 90 do
int vitril = 0, vitrir = 0, vitrimml = 0, vitrimmr = 0, loil, loir;
#define in1 5
#define in2 6
#define in3 9
#define in4 10
int ss1;
int ss2;
int ss3;
int ss4;
int ss0;
#define dl1 8
#define dl2 13
#define dl3 4
#define dl4 7
void chayr() {
  if ( digitalRead(12) == 1) {
    vitrir--;
  }
  else
    vitrir++;

}
void chayl() {
  if ( digitalRead(11) == 1) {
    vitril++;
  }
  else
    vitril--;

}
void quayl(int nangluongl) {
  if (nangluongl >= 150) {
    nangluongl = 150;
  }
  if (nangluongl <= -150) {
    nangluongl = -150;
  }
  if (nangluongl > 0) {
    analogWrite(in3, 0);
    analogWrite(in4, nangluongl);
  }
  if (nangluongl < 0) {
    analogWrite(in3, -nangluongl);
    analogWrite(in4, 0);
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
    analogWrite(in1, 0);
    analogWrite(in2, nangluongr);
  }
  if (nangluongr < 0) {
    analogWrite(in1, -nangluongr);
    analogWrite(in2, 0);
  }
}
void quayc(int nangluongc) {
  if (nangluongc >= 150) {
    nangluongc = 150;
  }
  if (nangluongc <= -150) {
    nangluongc = -150;
  }
  if (nangluongc > 0) {
    analogWrite(in1, 0);
    analogWrite(in2, nangluongc);
    analogWrite(in3, 0);
    analogWrite(in4, nangluongc);

  }
  if (nangluongc < 0) {
    analogWrite(in1, -nangluongc);
    analogWrite(in2, 0);
    analogWrite(in3, -nangluongc);
    analogWrite(in4, 0);

  }
}
void xoay(int goc) {
  switch (goc) {
    case 90: {
        vitrimml += 75;
        vitrimmr -= 75;
        quayl(pid(loil, 3, 0, 1));
        quayr(pid(loir, 3, 0, 1));
        break;
      }

    case -90: {
        vitrimml -= 75;
        vitrimmr += 75;
        quayl(pid(loil, 3, 0, 1));
        quayr(pid(loir, 3, 0, 1));
        break;
      }



  }
}
void stopmotor() {
  analogWrite(in1, 0);
  analogWrite(in2, 0);
  analogWrite(in3, 0);
  analogWrite(in4, 0);
}
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
void dithang(int nangluong) {
  vitrimml = 120;
  loil = vitrimml - vitril;
  vitrimmr = 120;
  loir = vitrimmr - vitrir;
  quayl(pid(loil, 3, 0, 1));
  quayr(pid(loir, 3, 0, 1));
}

void setup() {
  attachInterrupt(1, chayr, RISING);
  attachInterrupt(0, chayl, RISING);
  Serial.begin(9600);
}

void loop() {
  Serial.print("Vi tri left " ); Serial.println(vitril);
  Serial.print("Vi tri right " ); Serial.println(vitrir);
  ss0 = analogRead(A0);
  ss1 = analogRead(A1);
  ss2 = analogRead(A2);
  ss3 = analogRead(A3);
  ss4 = analogRead(A4);
  vitrimml = 120; vitrimmr = 120;
  loil = vitrimml - vitril;
  loir = vitrimmr - vitrir;
  while (loil < -5 || loil > 5) {
    attachInterrupt(1, chayr, RISING);
    attachInterrupt(0, chayl, RISING);
    Serial.print("Vi tri left " ); Serial.println(vitril);
    Serial.print("Vi tri right " ); Serial.println(vitrir);
    vitrimml = 120; vitrimmr = 120;
    loil = vitrimml - vitril;
    loir = vitrimmr - vitrir;
    quayl(pid(loil, 3, 0, 1));
    quayr(pid(loir, 3, 0, 1));
  }
  if (ss3 > 100) {
    int vitrixoayl = 75 + vitril;
    int vitrixoayr = -75 + vitrir;
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
  //  Serial.println("SS0 " + String(ss1));
  //  Serial.println("SS1 " + String(ss2));
  //  Serial.println("SS2 " + String(ss3));
  //  Serial.println("SS3 " + String(ss4));
  //  Serial.println("SS4 " + String(ss5));
  //  if (ss4 > 50) {
  //    stopmotor();
  //    do {
  //
  //      ss1 = analogRead(A0);
  //      Serial.println("Quay phai");
  //    } while (ss4 > 50);
  //    Serial.println("Dung lai");
  //    stopmotor();
  //  }
  //  else if (ss2 < 50) {
  //    do
  //    }

}
