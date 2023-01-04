int button1 = 2;
int button2 = 3;
int rq1 = 1;
int temp = 0;
void timer() {
  if (rq1 < 7) {
    rq1++;
  }
  else
    rq1 = 1;
}
void setup()
{
  for (int i = 5; i < 13; i++) {
    pinMode(i, OUTPUT);
  }
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);

  attachInterrupt(0, timer, LOW);
  Serial.begin(9600);
}

void loop()
{
  char a[30] = {12, 5, 6, 7, 8, 9, 10, 11, 12, 5, 6, 7, 8, 9, 10, 11, 12, 5, 6, 7, 8, 9, 10, 11, 12};
  if (digitalRead(button2) == 0) {
    if (temp > 2) {
      temp = 0;
    }
    else
      temp++;
  }
  if (temp == 0) {
    int dem = 1;
    for (int i = 1; i < 9; i++) {
      digitalWrite(a[i - 1], LOW);
      digitalWrite(a[i], HIGH);
      if (dem < rq1) {
        int tmp = i;
        int tmp2 = dem;
        while (tmp2 < rq1) {
          tmp++;
          digitalWrite(a[tmp], HIGH);
          tmp2++;
        }
      }
      delay(300);
      if (temp != 0) {

        for (int i = 16; i > 8; i--)
          digitalWrite(a[i + 1], LOW);
        break;
      }
    }

  }
  else if (temp == 1) {
    int dem = 1;
    for (int i = 16; i > 8; i--)
      digitalWrite(a[i + 1], LOW);
    for (int i = 16; i > 8; i--) {
      digitalWrite(a[i + 1], LOW);
      digitalWrite(a[i], HIGH);
      if (dem < rq1) {
        int tmp = i;
        int tmp2 = dem;
        int tmp3 = rq1;
        while (tmp2 < tmp3) {
          tmp--;
          digitalWrite(a[tmp], HIGH);
          tmp3--;
        }
      }

      delay(300);
      for (int i = 16; i > 8; i--)
        digitalWrite(a[i + 1], LOW);
    }
  }
  else if (temp == 2) {
    //Còn mỗi phần này
    int dem = 1;
    int n = 10;
    while (1) {
      for (int i = 1; i < n - rq1; i++) {
        //        if (i + rq1 == n - rq1) {
        //          break;
        //        }
        if (i != 1)
          digitalWrite(a[i - 1], LOW);
        digitalWrite(a[i], HIGH);
        if (dem < rq1) {
          int tmp = i;
          int tmp2 = dem;
          while (tmp2 < rq1) {
            tmp++;
            digitalWrite(a[tmp], HIGH);
            tmp2++;
          }
        }
        delay(300);
        if ( digitalRead(5) == 1 && digitalRead(6) == 1 && digitalRead(7) == 1 && digitalRead(8) == 1 && digitalRead(9) == 1 && digitalRead(10) == 1 && digitalRead(11) == 1 && digitalRead(12) == 1)
        {
          for (int i = 16; i > 8; i--)
            digitalWrite(a[i], LOW);
          break;
        }
      }
      if ( digitalRead(5) == 1 && digitalRead(6) == 1 && digitalRead(7) == 1 && digitalRead(8) == 1 && digitalRead(9) == 1 && digitalRead(10) == 1 && digitalRead(11) == 1 && digitalRead(12) == 1)
      {
        for (int i = 16; i > 8; i--)
          digitalWrite(a[i], LOW);
        break;
      }
      n = n - rq1;
    }
  }
}
