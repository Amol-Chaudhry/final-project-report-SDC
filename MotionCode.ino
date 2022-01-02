//
//  MotionCode.ino
//
//  Created by AmolChaudhry on 02/08/19.
//

const int EnableLeft = 5;
const int HighLeft = 6;       // LEFT SIDE MOTOR
const int LowLeft =7;

const int EnableRight = 10;
const int HighRight = 8;       //RIGHT SIDE MOTOR
const int LowRight =9;

const int D0 = 0;       //Raspberry pin 21    LSB
const int D1 = 1;       //Raspberry pin 22
const int D2 = 2;       //Raspberry pin 23
const int D3 = 3;       //Raspberry pin 24    MSB

int a,b,c,d,data;


void setup() {

pinMode(EnableLeft, OUTPUT);
pinMode(HighLeft, OUTPUT);
pinMode(LowLeft, OUTPUT);


pinMode(EnableRight, OUTPUT);
pinMode(HighRight, OUTPUT);
pinMode(LowRight, OUTPUT);

pinMode(D0, INPUT_PULLUP);
pinMode(D1, INPUT_PULLUP);
pinMode(D2, INPUT_PULLUP);
pinMode(D3, INPUT_PULLUP);


}

void Data()
{
   a = digitalRead(D0);
   b = digitalRead(D1);
   c = digitalRead(D2);
   d = digitalRead(D3);

   data = 8*d+4*c+2*b+a;
}

void Forward()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,255);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,255);
  
}


void Backward()
{
  digitalWrite(HighLeft, HIGH);
  digitalWrite(LowLeft, LOW);
  analogWrite(EnableLeft,255);

  digitalWrite(HighRight, HIGH);
  digitalWrite(LowRight, LOW);
  analogWrite(EnableRight,255);
  
}

void Stop()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,0);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,0);
  
}

void Left1()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,160);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,255);
  
}

void Left2()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,90);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,255);
  
}


void Left3()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,50);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,255);
  
}

void Right1()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,255);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,160);  //200
  
}
void Right2()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,255);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,90);   //160
  
}

void Right3()
{
  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft,255);

  digitalWrite(HighRight, LOW);
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableRight,50);   //100
  
}

void UTurn()
{
  analogWrite(EnableLeft, 0);
  analogWrite(EnableRight, 0);
  delay(400);

  analogWrite(EnableLeft, 250);
  analogWrite(EnableRight, 250);    //forward
  delay(1000);

  analogWrite(EnableLeft, 0);
  analogWrite(EnableRight, 0);
  delay(400);

  digitalWrite(HighLeft, HIGH);
  digitalWrite(LowLeft, LOW);
  digitalWrite(HighRight, LOW);   //   left
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableLeft, 255);
  analogWrite(EnableRight, 255);
  delay(700);

  analogWrite(EnableLeft, 0);
  analogWrite(EnableRight, 0);
  delay(400);

  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  digitalWrite(HighRight, LOW);   // forward
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableLeft, 255);
  analogWrite(EnableRight, 255);
  delay(900);

  analogWrite(EnableLeft, 0);
  analogWrite(EnableRight, 0);
  delay(400);

  digitalWrite(HighLeft, HIGH);
  digitalWrite(LowLeft, LOW);
  digitalWrite(HighRight, LOW);    //left
  digitalWrite(LowRight, HIGH);
  analogWrite(EnableLeft, 255);
  analogWrite(EnableRight, 255);
  delay(700);


  analogWrite(EnableLeft, 0);
  analogWrite(EnableRight, 0);
  delay(1000);



  digitalWrite(HighLeft, LOW);
  digitalWrite(LowLeft, HIGH);
  digitalWrite(HighRight, LOW);
  digitalWrite(LowLeft, HIGH);
  analogWrite(EnableLeft, 150);
  analogWrite(EnableRight, 150);
  delay(300);
}



void loop() 
{
  Data();
  if(data==0)
   {
     Forward();
   }
   
  else if(data==1)
   {
     Right1();
   }
     
  else if(data==2)
   {
     Right2();
   }
     
  else if(data==3)
   {
     Right3();
   }
     
  else if(data==4)
   {
     Left1();
   }
    
  else if(data==5)
   {
     Left2();
   }
    
  else if(data==6)
   {
     Left3();
   }
  
  else if (data==7)
   {
     UTurn();
   }
    
  else if (data>7)
   {
     Stop();
   }
   



}
