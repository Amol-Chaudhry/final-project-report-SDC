//
//  MotionCode.ino
//
//  Created by AmolChaudhry on 02/08/19.
//

//Right DC Motor
const int RightEnable = 10;
const int RightHigh = 8;
const int RightLow =9;

 //Left DC Motor
const int LeftEnable = 5;
const int LeftHigh = 6;
const int LeftLow =7;

const int DigitalPin0 = 0;       //Raspberry pin 21    LSB
const int DigitalPin1 = 1;       //Raspberry pin 22
const int DigitalPin2 = 2;       //Raspberry pin 23
const int DigitalPin3 = 3;       //Raspberry pin 24    MSB

int a, b, c, d, data;

void setup()
{
    pinMode(DigitalPin0, INPUT_PULLUP);
    pinMode(DigitalPin1, INPUT_PULLUP);
    pinMode(DigitalPin2, INPUT_PULLUP);
    pinMode(DigitalPin3, INPUT_PULLUP);
    
    pinMode(RightEnable, OUTPUT);
    pinMode(RightHigh, OUTPUT);
    pinMode(RightLow, OUTPUT);
    pinMode(LeftEnable, OUTPUT);
    pinMode(LeftHigh, OUTPUT);
    pinMode(LeftLow, OUTPUT);
}

void MoveForward()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable, 255);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable, 255);
}


void MoveBackward()
{
    digitalWrite(RightHigh, HIGH);
    digitalWrite(RightLow, LOW);
    analogWrite(RightEnable,255);
    
    digitalWrite(LeftHigh, HIGH);
    digitalWrite(LeftLow, LOW);
    analogWrite(LeftEnable, 255);
}

void GetData()
{
    a = digitalRead(DigitalPin0);
    b = digitalRead(DigitalPin1);
    c = digitalRead(DigitalPin2);
    d = digitalRead(DigitalPin3);
    data = 8*d+4*c+2*b+a;
}

void StopCar()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable, 0);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable, 0);
}

void LeftLevel3()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable, 240);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable, 70);
}

void LeftLevel2()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable, 240);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable, 110);
}

void LeftLevel1()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable, 240);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable, 180);
}

void RightLevel3()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable,63);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable,240);
}

void RightLevel2()
{

    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable,112);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable,240);
}

void RightLevel1()
{
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(RightEnable,168);
    
    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable,240);
}

void LaneEndUTurn()
{
    analogWrite(LeftEnable, 0);
    analogWrite(RightEnable, 0);
    delay(500);

    analogWrite(LeftEnable, 230);
    analogWrite(RightEnable, 230);
    delay(900);

    analogWrite(LeftEnable, 0);
    analogWrite(RightEnable, 0);
    delay(500);

    digitalWrite(LeftHigh, HIGH);
    digitalWrite(LeftLow, LOW);
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(LeftEnable, 250);
    analogWrite(RightEnable, 250);
    delay(650);

    analogWrite(LeftEnable, 0);
    analogWrite(RightEnable, 0);
    delay(500);

    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(LeftEnable, 250);
    analogWrite(RightEnable, 250);
    delay(1000);

    analogWrite(LeftEnable, 0);
    analogWrite(RightEnable, 0);
    delay(500);

    digitalWrite(LeftHigh, HIGH);
    digitalWrite(LeftLow, LOW);
    digitalWrite(RightHigh, LOW);
    digitalWrite(RightLow, HIGH);
    analogWrite(LeftEnable, 250);
    analogWrite(RightEnable, 250);
    delay(800);

    analogWrite(LeftEnable, 0);
    analogWrite(RightEnable, 0);
    delay(900);

    digitalWrite(LeftHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    digitalWrite(RightHigh, LOW);
    digitalWrite(LeftLow, HIGH);
    analogWrite(LeftEnable, 130);
    analogWrite(RightEnable, 130);
    delay(350);
}



void loop() 
{
    GetData();
    
    if(data==0){
        MoveForward();
    }
    else if(data==1){
       RightLevel1();
    }
    else if(data==2){
       RightLevel2();
    }
    else if(data==3){
       RightLevel3();
    }
    else if(data==4){
       LeftLevel1();
    }
    else if(data==5){
       LeftLevel2();
    }
    else if(data==6){
       LeftLevel3();
    }
    else if (data==7){
       LaneEndUTurn();
    }
    else if (data>7){
       StopCar();
    }
}
