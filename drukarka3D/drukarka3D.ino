#define X_MIN_PIN           3
#ifndef X_MAX_PIN
  #define X_MAX_PIN         2
#endif
#define Y_MIN_PIN          14
#define Y_MAX_PIN          15
#define Z_MIN_PIN          18
#define Z_MAX_PIN          19

// krańcówki
int button1;
int button2;
int button3;

int stepp;
int stepx=0;
int stepy=0;
int stepz=0;

int flag=0;
String a;

//---------------
// ----Servos----
//---------------
#ifdef IS_RAMPS_13
  #define SERVO0_PIN        7 
#else
  #define SERVO0_PIN       11
#endif
#define SERVO1_PIN          6
#define SERVO2_PIN          5
#define SERVO3_PIN          4


//-----------------
// ----Steppers----
//-----------------
#define X_STEP_PIN         54
#define X_DIR_PIN          55
#define X_ENABLE_PIN       38
#define X_CS_PIN           53

#define Y_STEP_PIN         60
#define Y_DIR_PIN          61
#define Y_ENABLE_PIN       56
#define Y_CS_PIN           49

#define Z_STEP_PIN         46
#define Z_DIR_PIN          48
#define Z_ENABLE_PIN       62
#define Z_CS_PIN           40


void setup() {
  pinMode(X_MAX_PIN,INPUT);
  digitalWrite(X_MAX_PIN,HIGH);
  
  pinMode(Y_MAX_PIN,INPUT);
  digitalWrite(Y_MAX_PIN,HIGH);
  
  pinMode(Z_MAX_PIN,INPUT);
  digitalWrite(Z_MAX_PIN,HIGH);
  
  pinMode(X_STEP_PIN,OUTPUT);
  pinMode(X_DIR_PIN ,OUTPUT);
  pinMode(X_ENABLE_PIN ,OUTPUT);
  pinMode(X_CS_PIN ,OUTPUT);
  
  digitalWrite(X_ENABLE_PIN,LOW);
  digitalWrite(X_CS_PIN,HIGH);
  digitalWrite(X_DIR_PIN,LOW);

  pinMode(Y_STEP_PIN,OUTPUT);
  pinMode(Y_DIR_PIN ,OUTPUT);
  pinMode(Y_ENABLE_PIN ,OUTPUT);
  pinMode(Y_CS_PIN ,OUTPUT);
  
  digitalWrite(Y_ENABLE_PIN,LOW);
  digitalWrite(Y_CS_PIN,HIGH);
  digitalWrite(Y_DIR_PIN,LOW);

  pinMode(Z_STEP_PIN,OUTPUT);
  pinMode(Z_DIR_PIN ,OUTPUT);
  pinMode(Z_ENABLE_PIN ,OUTPUT);
  pinMode(Z_CS_PIN ,OUTPUT);
  
  digitalWrite(Z_ENABLE_PIN,LOW);
  digitalWrite(Z_CS_PIN,HIGH);
  digitalWrite(Z_DIR_PIN,LOW);
  
  Serial.begin(57600);
  Serial.setTimeout(50);  
}


void loop() {
  button1 = digitalRead(X_MAX_PIN);  
  //Serial.print(button1);
   button2 = digitalRead(Y_MAX_PIN);
  //Serial.print(button2);
   button3 = digitalRead(Z_MAX_PIN);
  //Serial.println(button3);

// poruszanie ramieniem w gore

if(button1==0 && stepx>0){
    digitalWrite(X_STEP_PIN,HIGH);
    stepx = stepx-1;
 }// po dojechaniu do krancowki wykonujemy 1000 krokow w dol
 else if(button1==1){     
      digitalWrite(X_DIR_PIN,HIGH);     
      stepx = 1000;
      digitalWrite(X_STEP_PIN,HIGH);
 }

if(button2==0 && stepy>0){
    digitalWrite(Y_STEP_PIN,HIGH);
    stepy = stepy-1;
 }
else if(button2==1){
      digitalWrite(Y_DIR_PIN,HIGH);   
      stepy = 1000;
      digitalWrite(Y_STEP_PIN,HIGH);
  }

if(button3==0 && stepz>0){
    digitalWrite(Z_STEP_PIN,HIGH);
    stepz = stepz-1;
  }
else if(button3==1){
      digitalWrite(Z_DIR_PIN,HIGH);
      stepz = 1000;
      digitalWrite(Z_STEP_PIN,HIGH);
  }

// zatrzymanie glowicy

delayMicroseconds(400);
digitalWrite(X_STEP_PIN,LOW);
digitalWrite(Y_STEP_PIN,LOW);
digitalWrite(Z_STEP_PIN,LOW);
delayMicroseconds(400);

// sterowanie z klawiatury

while(Serial.available()>0){
  a=Serial.readString();
  sscanf(a.c_str(),"x%d y%d z%d\n",&stepx,&stepy,&stepz);        //wysylanie do arduino
  flag = 1;
  if (stepx>0){
    digitalWrite(X_DIR_PIN,HIGH); 
  }
  else{
    digitalWrite(X_DIR_PIN,LOW);
    stepx = -stepx;       //gdy wprowadzamy wartosc ujemna
  }
  
  if (stepy>0){
    digitalWrite(Y_DIR_PIN,HIGH); 
  }
  else{
    digitalWrite(Y_DIR_PIN,LOW);
    stepy = -stepy;
  }
   if (stepz>0){
    digitalWrite(Z_DIR_PIN,HIGH); 
  }
  else{
    digitalWrite(Z_DIR_PIN,LOW);
    stepz = -stepz; 
    }
            
  /*  stepx=stepp;
  }
  else{
    if (stepp<0){
      digitalWrite(X_DIR_PIN,LOW); 
      digitalWrite(Y_DIR_PIN,LOW); 
      digitalWrite(Z_DIR_PIN,LOW);       
      stepx=-stepp;
    }
  }*/
 }
 
if (stepx==0 && stepy==0 && stepz==0 && flag==1){
  Serial.println("ok");
  flag = 0;
  }
 
 //Serial.print(stepx); Serial.print(" ");
 //Serial.print(stepy); Serial.print(" ");
 //Serial.println(stepz);
}
