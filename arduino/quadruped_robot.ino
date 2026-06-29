#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN 120
#define SERVOMAX 520
#define FL_HIP    0
#define FL_KNEE   1
#define FL_ANKLE  2
#define FR_HIP    3
#define FR_KNEE   4
#define FR_ANKLE  5
#define BL_HIP    6
#define BL_KNEE   7
#define BL_ANKLE  8
#define BR_HIP    9
#define BR_KNEE   10
#define BR_ANKLE  11
int angleToPulse(int angle)
{
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}
void setServo(uint8_t servo, int angle)
{
  pwm.setPWM(servo, 0, angleToPulse(angle));
}
void stand()
{
  for (int i = 0; i < 12; i++)
    setServo(i, 90);
}
void moveLeg(uint8_t hip, uint8_t knee, uint8_t ankle)
{
  setServo(knee, 60);
  setServo(ankle, 60);
  delay(200);
  setServo(hip, 120);
  delay(200);
  setServo(knee, 90);
  setServo(ankle, 90);
  delay(200);
  setServo(hip, 90);
  delay(200);
}
void walkForward()
{
  moveLeg(FL_HIP, FL_KNEE, FL_ANKLE);
  moveLeg(BR_HIP, BR_KNEE, BR_ANKLE);
  moveLeg(FR_HIP, FR_KNEE, FR_ANKLE);
  moveLeg(BL_HIP, BL_KNEE, BL_ANKLE);
}
void turnLeft()
{
  setServo(FL_HIP, 70);
  setServo(BL_HIP, 70);
  setServo(FR_HIP, 120);
  setServo(BR_HIP, 120);
  delay(500);
  stand();
}
void turnRight()
{
  setServo(FL_HIP, 120);
  setServo(BL_HIP, 120);
  setServo(FR_HIP, 70);
  setServo(BR_HIP, 70);
  delay(500);
  stand();
}
void setup()
{
  pwm.begin();
  pwm.setPWMFreq(50);
  delay(500);
  stand();
}
void loop()
{
  walkForward();
}
