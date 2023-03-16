#include <util/atomic.h>
class SimplePID {
  private:
    float kp, kd, ki, umax;
    float eprev, eintegral;
  public:
    SimplePID() : kp(1), kd(0), ki(0), umax(255), eprev(0.0), eintegral(0.0) {}
    void setParams(float kpIn, float kdIn, float kiIn, float umaxIn) {
      kp = kpIn; kd = kdIn; ki = kiIn, umax = umaxIn;
    }
    void  evalu(int value, int target, float deltaT, int &pwr, int &dir) {
      int e = target - value;

      float dedt = (e - eprev) / (deltaT);
      float u = kp * e + kd * dedt + ki * eintegral;
      pwr = (int)fabs(u);
      if (pwr > umax) {
        pwr = umax;
      }
      dir = 1;
      if (u < 0) {
        dir = -1;
      }
      eprev = e;
    }
};
#define NMOTORS 2
#define ENCA 0
#define ENCB 7
const int enca[] = {0, 1};
const int encb[] = {7, 8};
const int in1[] = {5, 9};
const int in2[] = {6, 10};
long prevT = 0;
int pos = 0;
volatile int posi[] = {0, 0};
SimplePID pid[NMOTORS];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  for (int k = 0; k < NMOTORS; k++) {
    pinMode(enca[k], INPUT);
    pinMode(encb[k], INPUT);
    pinMode(in1[k], OUTPUT);
    pinMode(in2[k], OUTPUT);
    pid[k].setParams(1, 0, 0, 255);

  }
  attachInterrupt(digitalPinToInterrupt(enca[0]), readEncoder<0>, RISING);
  attachInterrupt(digitalPinToInterrupt(enca[1]), readEncoder<1>, RISING);

}

void loop() {
  // put your main code here, to run repeatedly:
  int target[NMOTORS];
  target[0] = 750 * sin(prevT / 1e6);
  target[1] = -750 * sin(prevT / 1e6);
  long currT = micros();
  float deltaT = ((float)(currT - prevT)) / (1.0e6);
  prevT = currT;
  int pos[NMOTORS];
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    for (int k = 0; k < NMOTORS; k++) {
      pos[k] = posi[k];
    }
  }
  //loop through the motors
  for (int k = 0; k < NMOTORS; k++) {
    int pwr, dir;
    pid[k].evalu(pos[k],target[k],deltaT,pwr,dir);
    //signal the motor
    setMotor(dir, in1[k], in2[k]);
  }
}
void setMotor(int dir, int in1, int in2) {
  if (dir == 1) {
    digitalWrite(in1, 100);
    digitalWrite(in2, 0);
  }
  else if (dir == -1) {
    digitalWrite(in1, 0);
    digitalWrite(in2, 100);
  }
  else {
    digitalWrite(in1, 0);
    digitalWrite(in2, 0);
  }
}
template <int j>
void readEncoder() {
  int b = digitalRead(encb[j]);
  if (b > 0) {
    posi[j]++;
  }
  else {
    posi[j]--;
  }
}
