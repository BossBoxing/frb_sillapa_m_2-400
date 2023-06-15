#include "ModelNano.h"  //Board Friend Robot Model Nano
int function = 0;

void setup() {
  beep();
  ok();
}

void loop() {
  if (function == 0) {
    delay(500);
    int p, d;
    while (SW_OK() == 1) {
      p = knob(1, 4);
      oled(1, 4, "Port = %d ", p);
      oledClear();
    }
    delay(500);
    while (SW_OK() == 1) {
      d = knob(1, 180);
      servo(p, d);
      oled(2, 4, "results = %d ", d);
      oledClear();
    }
    oledClear();
  }
  else if (function == 1) {
    oled(0, 0, "A0 = %d  ", analog(0));
    oled(0, 10, "A1 = %d  ", analog(1));
    oled(0, 20, "A2 = %d  ", analog(2));
    oled(0, 30, "A3 = %d  ", analog(3));
    oled(0, 40, "A7 = %d  ", analog(7));
    delay(100);
    oledClear();
  }
  else if (function == 2) {
    Pattern();
    STOP(900000);      //หยุดเป็นเวลา 900 วินาที
  }
  else if (function == 3) {
    Pattern();
    STOP(900000);      //หยุดเป็นเวลา 900 วินาที
  }
  else if (function == 4) {
    Pattern();
    STOP(900000);      //หยุดเป็นเวลา 900 วินาที
  }
  else if (function == 5) {
    Pattern();
    STOP(900000);      //หยุดเป็นเวลา 900 วินาที
  }
}
void ok() {
  XIO();
  servo(1, s1); delay(200);
  setTextSize(1);
  while (SW_OK() == 1) {
    function = knob(0, 5);
    setTextSize(5);
    oled(50, 20, "%d", function);
    oledClear();
    if (SW_OK() == 0)
    {
      setTextSize(1);
      oledClear();
      break;
    }
  }
  delay(200);
}
void STOP(int t) {
  motor(1, 0);  motor(2, 0);
  delay(t);
}
void Wait(){
  STOP(1);
  beep();
  while(SW_OK() == 1){
    STOP(1);
  }
  while(SW_OK() == 0){
    
  }
}
void OUT() {
  servo(1, s1); delay(50);
  for (int i = s1; i >= s2; i--) {
    servo(1, i);
    delay(10);
  }
  delay(100);
  servo(1, s1);
  delay(150);
}
void Fw(int Time) {
  motor(1, Fl);  motor(2, Fr);
  delay(Time);
}
void Fw_Slow(int Time) {
  motor(1, Fsl);  motor(2, Fsr);
  delay(Time);
}
void Fw_Slow_En(int cm) {
  encoder_reset(2);
  int en = encoder(2);
  int Cm = (cm / 0.038);
  while (en < Cm) {
    Fw_Slow(1);
    en = encoder(2);
  }
}
void Fw_En(int cm) {
  encoder_reset(2);
  int en = encoder(2);
  int Cm = (cm / 0.038);
  while (en < Cm) {
    Fw(1);
    en = encoder(2);
  }
}
void Bk(int Time) {
  motor(1, -Fl);  motor(2, -Fr);
  delay(Time);
}
void Bk_Slow(int Time) {
  motor(1, -Fsl);  motor(2, -Fsr);
  delay(Time);
}
void Bk_Slow_En(int cm) {
  encoder_reset(2);
  int en = encoder(2);
  int Cm = (cm / 0.038);
  while (en < Cm) {
    Bk_Slow(1);
    en = encoder(2);
  }
}
void Bk_En(int cm) {
  encoder_reset(2);
  int en = encoder(2);
  int Cm = (cm / 0.038);
  while (en < Cm) {
    Bk(1);
    en = encoder(2);
  }
}
void Turn_R(int Cm){
  STOP(pause_time);
  /*
  encoder_reset(2);
  int en = encoder(2);
  while (en < Cm) {
    motor(1,25); motor(2,-25);
    en = encoder(2);
  }*/
  motor(1,Tl); motor(2,-Tr);
  delay(Cm);
  STOP(pause_time);
}
void Turn_L(int Cm){
  STOP(pause_time);
  /*encoder_reset(3);
  int en = encoder(3);
  while (en < Cm) {
    motor(1,-25); motor(2,25);
    en = encoder(3);
  }*/
  motor(1,-Tl); motor(2,Tr);
  delay(Cm);
  STOP(pause_time);
}
void Track_Slow() {
  if (analog(0) < ref0) {
    motor(1, Fsl);  motor(2, 0);
  }
  else if (analog(2) < ref2) {
    motor(1, 0);  motor(2, Fsr);
  }
  else {
    Fw_Slow(1);
  }
}
void Track_Slow_Time(int Time) {
  int i = 0;
  while (i < Time) {
    Track_Slow();
    delay(1);
    i++;
  }
}
void Track_Slow_En(int cm) {
  encoder_reset(2);
  int en = encoder(2);
  int Cm = (cm / 0.038);
  while (en < Cm) {
    Track_Slow();
    en = encoder(2);
  }
}
void Track() {
  if (analog(0) < ref0) {
    motor(1, Fl);  motor(2, 35);
  }
  else if (analog(2) < ref2) {
    motor(1, 35);  motor(2, Fl);
  }
  else if ((analog(0) < ref0) && (analog(2) < ref2)) {
    Fw(1);
  }
  else {
    Fw(1);
  }
}
void Track_Time(int Time) {
  int i = 0;
  while (i < Time) {
    Track();
    delay(1);
    i++;
  }
}
void Track_En(int cm) {
  encoder_reset(2);
  int en = encoder(2);
  int Cm = (cm / 0.038);
  while (en < Cm) {
    Track();
    en = encoder(2);
  }
}
void Track_Check() {
  if (analog(0) < ref0) {
    motor(1, -Fsl);  motor(2, Fsr);
  }
  else if (analog(2) < ref2) {
    motor(1, Fsl);  motor(2, -Fsr);
  }
  else {
    motor(1,Fsl); motor(2,Fsr);
  }
}
void Track_Bk_Check() {
  if (analog(3) < ref3) {
    motor(1, Fsl);  motor(2, -Fsr);
  }
  else if (analog(7) < ref7) {
    motor(1, -Fsl);  motor(2, Fsr);
  }
  else {
    motor(1,-Fsl); motor(2,-Fsr);
  }
}
void Check_F() {
  int F = 0;
  while (analog(1) > ref1) {
    Track_Slow();
  }
  STOP(pause_time);
  Bk_Slow_En(5);
  STOP(pause_time);
  while ((analog(0) > ref0) || (analog(2) > ref2)) {Track_Check();}
  STOP(pause_time);
  
 // Bk_Slow_En(5);
 // STOP(100);
 // while ((analog(0) > ref0) || (analog(2) > ref2)) {Track_Check();}
 // STOP(200);
  
  Bk_Slow_En(5); // 4
  STOP(pause_time);
}
void Check_B() {
  int F = 0;
  STOP(pause_time);
  // Fw_Slow_En(4);
  STOP(pause_time);
  
  while ((analog(3) > ref3) || (analog(7) > ref7)) {Track_Bk_Check();}
  STOP(pause_time);
}
void Check_Out() {
  int F = 0;
  while (analog(1) > ref1) {
    Track_Slow();
  }
  STOP(pause_time);
  Bk_Slow_En(4);
  STOP(pause_time);
  while ((analog(0) > ref0) || (analog(2) > ref2)) {Track_Check();}
  //STOP(100);
  
 // Bk_Slow_En(5);
 // STOP(100);
 // while ((analog(0) > ref0) || (analog(2) > ref2)) {Track_Check();}
 // STOP(200);
  
  //Bk_Slow_En(14);
  STOP(pause_time);
}
void Check_Out_RY() {
  int F = 0;
  while (analog(1) > ref1) {
    Track_Slow();
  }
  STOP(pause_time);
  while ((analog(0) > ref0) || (analog(2) > ref2)) {Track_Check();}
  STOP(pause_time);
  Bk_Slow_En(15);
  STOP(pause_time);
  
  //STOP(100);
  
 // Bk_Slow_En(5);
 // STOP(100);
 // while ((analog(0) > ref0) || (analog(2) > ref2)) {Track_Check();}
 // STOP(200);
  
  //Bk_Slow_En(14);
  STOP(pause_time);
}

void R(int cm,int En){
  Track_Slow_En(8);
  Track_En(cm-8);
  Check_F();
  Turn_R(En);
}
void L(int cm,int En){
  Track_Slow_En(8);
  Track_En(cm-8);
  Check_F();
  Turn_L(En);
}
void Out(int cm){
  Track_Slow_En(8);
  Track_En(cm-8);
  Check_Out();
  Fw_Slow(50);
  STOP(50);
  OUT();
}
void Out_RY(int cm){
  Track_Slow_En(8);
  Track_En(cm-8);
  Check_Out_RY();
  OUT();
}
void F_Track_En(int cm){
  Track_Slow_En(8);
  Track_En(cm-20);
  Track_Slow_En(12);
  STOP(pause_time);
}

// Obstacle / ลูกระนาด
void R_Wave(int cm,int En){
  
  Fw_Slow_En(8);
  Fw_En(cm-8);
  Check_F();
  Turn_R(En);
}
void L_Wave(int cm,int En){
  Fw_Slow_En(8);
  Fw_En(cm-8);
  Check_F();
  Turn_L(En);
}
