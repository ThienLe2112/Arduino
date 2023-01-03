// Le Quang Anh   11/22/2022

#define motorTrai_in1   5
#define motorTrai_in2   6
#define motorPhai_in3   9
#define motorPhai_in4   10
#define doLine_Truoc_Trai   4
#define doLine_Truoc_Phai   7
#define doLine_Sau_Phai     11
#define doLine_Sau_Trai     8

// m chinh lai chan tu dong  11 den dong 13 nha =))))
#define SS_CanBang_Trai     A0
#define SS_KhoangCach_Trai  A1
#define SS_KhoangCach_Giua  A2
#define SS_KhoangCach_Phai  A3
#define SS_CanBang_Phai     A4
// macro for sumo battle
#define MAX_SPEED           255
#define MIN_SPEED           50
#define NORMAL_SPEED        150
#define PhatHien_DoiThu     1
#define KILL                (chayThang(MAX_SPEED,0))
#define VACH        1
//macro for maze
#define WALL

void setup() {
  // put your setup code here, to run once:
  pinMode(motorTrai_in1, OUTPUT);
  pinMode(motorTrai_in2, OUTPUT);
  pinMode(motorTrai_in1, OUTPUT);
  pinMode(motorTrai_in2, OUTPUT);
  pinMode(doLine_Truoc_Trai, INPUT);
  pinMode(doLine_Truoc_Phai, INPUT);
  pinMode(doLine_Sau_Trai, INPUT);
  pinMode(doLine_Sau_Phai, INPUT);
  pinMode(SS_KhoangCach_Giua, INPUT);
  pinMode(SS_KhoangCach_Trai, INPUT);
  pinMode(SS_KhoangCach_Phai, INPUT);
  pinMode(SS_CanBang_Trai, INPUT);
  pinMode(SS_CanBang_Phai, INPUT);
  Serial.begin(9600);
  Serial.println("Oke");
}

void loop() {
  // put your main code here, to run repeatedly:
  chayThang(NORMAL_SPEED, 0);

  if (digitalRead(SS_KhoangCach_Giua) == PhatHien_DoiThu )
  {
    do {
      digitalRead(SS_KhoangCach_Giua);
      Serial.println("KILL");
      KILL;

    }
    while (digitalRead(SS_KhoangCach_Giua) == PhatHien_DoiThu);
  }
  else if (digitalRead(SS_KhoangCach_Trai) == PhatHien_DoiThu)
  {
    reTrai(MAX_SPEED, 100);
    Serial.println("reTrai(MAX_SPEED, 100)");
    do
    {
      digitalRead(SS_KhoangCach_Giua);

      if (digitalRead(SS_KhoangCach_Giua) == PhatHien_DoiThu )
      {
        Serial.println("KILL");
        break;
      }
    }
    while (digitalRead(SS_KhoangCach_Giua) == PhatHien_DoiThu);
    KILL;
  }
  else if (digitalRead(SS_KhoangCach_Phai) == PhatHien_DoiThu)
  {
    rePhai(MAX_SPEED, 100);
    Serial.println("rePhai(MAX_SPEED, 100)");
    do
    {
      digitalRead(SS_KhoangCach_Giua);

      if (digitalRead(SS_KhoangCach_Giua) == PhatHien_DoiThu )
      {
        Serial.println("KILL");
        break;
      }
    }
    while (digitalRead(SS_KhoangCach_Giua) == PhatHien_DoiThu);
    Serial.println("KILL");

    KILL;
  }
  else if (digitalRead(doLine_Sau_Phai) == VACH || digitalRead(doLine_Sau_Trai) == VACH )
  {
    chayThang(MAX_SPEED, 0);
  }
  else if (digitalRead(doLine_Truoc_Phai) == VACH || digitalRead(doLine_Truoc_Trai) == VACH)
  {
    goBack(MAX_SPEED, 100);
    rePhai(MAX_SPEED, 300);
  }
}

void chayThang(int speed, int timeout)
{
  analogWrite(motorTrai_in1, speed);
  analogWrite(motorTrai_in2, 0);
  analogWrite(motorPhai_in3, 0);
  analogWrite(motorPhai_in4, speed);
  delay(timeout);
}
void rePhai(int speed, int timeout)
{
  analogWrite(motorTrai_in1, speed);
  analogWrite(motorTrai_in2, 0);
  analogWrite(motorPhai_in3, speed);
  analogWrite(motorPhai_in4, 0);
  delay(timeout);
}
void reTrai(int speed, int timeout)
{
  analogWrite(motorTrai_in1, 0);
  analogWrite(motorTrai_in2, speed);
  analogWrite(motorPhai_in3, 0);
  analogWrite(motorPhai_in4, speed);
  delay(timeout);
}
void goBack(int speed, int timeout)
{
  analogWrite(motorTrai_in1, 0);
  analogWrite(motorTrai_in2, speed);
  analogWrite(motorPhai_in3, speed);
  analogWrite(motorPhai_in4, 0);
  delay(timeout);
}

