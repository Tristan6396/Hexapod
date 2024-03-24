#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Initialization  //////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>

#define CTRL0 9
#define CTRL1 10

// Import arrays
#include <A_Array.h>
#include <B_Array.h>
#include <C_Array.h>
#include <D_Array.h>
#include <E_Array.h>
#include <F_Array.h>

// Servo myservo;  // create servo object to control a servo
Servo Ashoulder;
Servo Aelbow;
Servo Awrist;
Servo Bshoulder;
Servo Belbow;
Servo Bwrist;
Servo Cshoulder;
Servo Celbow;
Servo Cwrist;
Servo Dshoulder;
Servo Delbow;
Servo Dwrist;
Servo Eshoulder;
Servo Eelbow;
Servo Ewrist;
Servo Fshoulder;
Servo Felbow;
Servo Fwrist;

int control = 0;

int maxnum = sizeof(PosArrayA) / sizeof(int) / 3;
int tempval;

int pos = 0; // variable to store the servo position

// Set initial center angles
int valA1 = 80; // Ashoulder
int valA2 = 80; // Aelbow
int valA3 = 90; // Awrist

int valB1 = 100; // Bshoulder
int valB2 = 80;  // Belbow
int valB3 = 80;  // Bwrist

int valC1 = 90; // Cshoulder
int valC2 = 90; // Celbow
int valC3 = 90; // Cwrist

int valD1 = 80; // Dshoulder
int valD2 = 90; // Delbow
int valD3 = 90; // Dwrist

int valE1 = 90;  // Eshoulder
int valE2 = 110; // Eelbow
int valE3 = 100; // Ewrist

int valF1 = 90; // Fshoulder
int valF2 = 90; // Felbow
int valF3 = 90; // Fwrist

// Tell how far away from initialAngle (90 degrees) the servos starting positions are
int initialAngle = 90;
int Ashoulderoffset = valA1 - initialAngle;
int Aelbowoffset = valA2 - initialAngle;
int Awristoffset = valA3 - initialAngle;
int Bshoulderoffset = valB1 - initialAngle;
int Belbowoffset = valB2 - initialAngle;
int Bwristoffset = valB3 - initialAngle;
int Cshoulderoffset = valC1 - initialAngle;
int Celbowoffset = valC2 - initialAngle;
int Cwristoffset = valC3 - initialAngle;
int Dshoulderoffset = valD1 - initialAngle;
int Delbowoffset = valD2 - initialAngle;
int Dwristoffset = valD3 - initialAngle;
int Eshoulderoffset = valE1 - initialAngle;
int Eelbowoffset = valE2 - initialAngle;
int Ewristoffset = valE3 - initialAngle;
int Fshoulderoffset = valF1 - initialAngle;
int Felbowoffset = valF2 - initialAngle;
int Fwristoffset = valF3 - initialAngle;

int first = 0;
int last = 160;

//=============================================================================//
// *** set an offset for the shoulder ***
//
// This also "converts" the Matlab angles to Arduino angles
// zero input angle should be towards the +x axis
// 90 degrees is straight towards +y
// these are the same as the Arduino angles

//=============================================================================//
// *** set an offset for the elbow ***
//
// This also "converts" the Matlab angles to Arduino angles
// zero input (matlab) angle should be straight out parallel to the base.
// negative angles are "up", away from the plate
// large positive angles are not possible mechanically.

//=============================================================================//
// *** set an offset for the wrist ***
//
// This also "converts" the Matlab angles to Arduino angles
// zero input (matlab) angle should be straight out from the join.
// 180 input will be "scratching its armpit"

int shoulderMult = 1.5;
int shoulderOffset = 0;

int fixAshoulder(int input)
{
  int a1 = ((input - 90) * shoulderMult) + 90;
  int out = a1 + Ashoulderoffset - shoulderOffset;
  return out;
}
int fixAelbow(int input)
{
  int out = 90 - input + Aelbowoffset;
  return out;
}
int fixAwrist(int input)
{
  int out = input + Awristoffset;
  return out;
}

int fixBshoulder(int input)
{
  int a1 = ((input - 90) * shoulderMult) + 90;
  int out = a1 + Bshoulderoffset - shoulderOffset;
  return out;
}
int fixBelbow(int input)
{
  int out = 90 - input + Belbowoffset;
  return out;
}
int fixBwrist(int input)
{
  int out = input + Bwristoffset;
  return out;
}

int fixCshoulder(int input)
{
  int a1 = ((input - 90) * shoulderMult) + 90;
  int out = a1 + Cshoulderoffset - shoulderOffset;
  return out;
}
int fixCelbow(int input)
{
  int out = 90 - input + Celbowoffset;
  return out;
}
int fixCwrist(int input)
{
  int out = input + Cwristoffset;
  return out;
}

int fixDshoulder(int input)
{
  int a1 = ((input + 90) * shoulderMult) - 90;
  int out = 180 + a1 + Dshoulderoffset + shoulderOffset;
  return out;
}
int fixDelbow(int input)
{
  int out = 90 + input + Delbowoffset;
  return out;
}
int fixDwrist(int input)
{
  int out = 180 - input + Dwristoffset;
  return out;
}

int fixEshoulder(int input)
{
  int a1 = ((input + 90) * shoulderMult) - 90;
  int out = 180 + a1 + Eshoulderoffset + shoulderOffset;
  return out;
}
int fixEelbow(int input)
{
  int out = 90 + input + Eelbowoffset;
  return out;
}
int fixEwrist(int input)
{
  int out = 180 - input + Ewristoffset;
  return out;
}

int fixFshoulder(int input)
{
  int a1 = ((input + 90) * shoulderMult) - 90;
  int out = 180 + a1 + Fshoulderoffset + shoulderOffset;
  return out;
}
int fixFelbow(int input)
{
  int out = 90 + input + Felbowoffset;
  return out;
}
int fixFwrist(int input)
{
  int out = 180 - input + Fwristoffset;
  return out;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Custom Functions  ////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// *** get the control bits ***
void getcontrol()
{
  int start;
  // Read the 2 control pins and then maybe do something..
  control = 0;
  start = digitalRead(CTRL0);
  control = control + start;
  start = digitalRead(CTRL1);
  control = control + 2 * start;
}

// *** Go to the initial positions of each servo ***
void pattern0()
{
  Ashoulder.write(valA1);
  Aelbow.write(valA2);
  Awrist.write(valA3);

  Bshoulder.write(valB1);
  Belbow.write(valB2);
  Bwrist.write(valB3);

  Cshoulder.write(valC1);
  Celbow.write(valC2);
  Cwrist.write(valC3);

  Dshoulder.write(valD1);
  Delbow.write(valD2);
  Dwrist.write(valD3);

  Eshoulder.write(valE1);
  Eelbow.write(valE2);
  Ewrist.write(valE3);

  Fshoulder.write(valF1);
  Felbow.write(valF2);
  Fwrist.write(valF3);
}

// *** Move exactly according to the array ***
void pattern1()
{
  for (int i = first; i <= last - 1; i++)
  {
    // Just read the array and go to those angles

    valA1 = pgm_read_word_near(&PosArrayA[i][0]);
    valA2 = pgm_read_word_near(&PosArrayA[i][1]);
    valA3 = pgm_read_word_near(&PosArrayA[i][2]);

    valB1 = pgm_read_word_near(&PosArrayB[i][0]);
    valB2 = pgm_read_word_near(&PosArrayB[i][1]);
    valB3 = pgm_read_word_near(&PosArrayB[i][2]);

    valC1 = pgm_read_word_near(&PosArrayC[i][0]);
    valC2 = pgm_read_word_near(&PosArrayC[i][1]);
    valC3 = pgm_read_word_near(&PosArrayC[i][2]);

    valD1 = pgm_read_word_near(&PosArrayD[i][0]);
    valD2 = pgm_read_word_near(&PosArrayD[i][1]);
    valD3 = pgm_read_word_near(&PosArrayD[i][2]);

    valE1 = pgm_read_word_near(&PosArrayE[i][0]);
    valE2 = pgm_read_word_near(&PosArrayE[i][1]);
    valE3 = pgm_read_word_near(&PosArrayE[i][2]);

    valF1 = pgm_read_word_near(&PosArrayF[i][0]);
    valF2 = pgm_read_word_near(&PosArrayF[i][1]);
    valF3 = pgm_read_word_near(&PosArrayF[i][2]);

    // These printouts were for debugging
    //    Serial.print("Direct from the array i:   ");
    //    Serial.print(i);
    //    Serial.print(",   shoulder:   ");
    //    Serial.print(PosArrayA[i][0]);
    //    Serial.print(",   elbow:   ");
    //    Serial.print(PosArrayA[i][1]);
    //    Serial.print(",   wrist:   ");
    //    Serial.print(PosArrayA[i][2]);
    //    Serial.print(",   shoulder:   ");
    //    Serial.print(valA1);
    //    Serial.print(",   elbow:   ");
    //    Serial.print(valA2);
    //    Serial.print(",   wrist:   ");
    //    Serial.println(valA3);

    // Modify to convert the "Matlab" angles into "Servo" angles
    valA1 = fixAshoulder(valA1);
    valA2 = fixAelbow(valA2);
    valA3 = fixAwrist(valA3);
    Ashoulder.write(valA1); // tell servo to go to position in variable 'pos'
    Aelbow.write(valA2);    // tell servo to go to position in variable 'pos'
    Awrist.write(valA3);    // tell servo to go to position in variable 'pos'

    valB1 = fixBshoulder(valB1);
    valB2 = fixBelbow(valB2);
    valB3 = fixBwrist(valB3);
    Bshoulder.write(valB1); // tell servo to go to position in variable 'pos'
    Belbow.write(valB2);    // tell servo to go to position in variable 'pos'
    Bwrist.write(valB3);    // tell servo to go to position in variable 'pos'

    valC1 = fixCshoulder(valC1);
    valC2 = fixCelbow(valC2);
    valC3 = fixCwrist(valC3);
    Cshoulder.write(valC1); // tell servo to go to position in variable 'pos'
    Celbow.write(valC2);    // tell servo to go to position in variable 'pos'
    Cwrist.write(valC3);    // tell servo to go to position in variable 'pos'

    valD1 = fixDshoulder(valD1);
    valD2 = fixDelbow(valD2);
    valD3 = fixDwrist(valD3);
    Dshoulder.write(valD1); // tell servo to go to position in variable 'pos'
    Delbow.write(valD2);    // tell servo to go to position in variable 'pos'
    Dwrist.write(valD3);    // tell servo to go to position in variable 'pos'

    valE1 = fixEshoulder(valE1);
    valE2 = fixEelbow(valE2);
    valE3 = fixEwrist(valE3);
    Eshoulder.write(valE1); // tell servo to go to position in variable 'pos'
    Eelbow.write(valE2);    // tell servo to go to position in variable 'pos'
    Ewrist.write(valE3);    // tell servo to go to position in variable 'pos'

    valF1 = fixFshoulder(valF1);
    valF2 = fixFelbow(valF2);
    valF3 = fixFwrist(valF3);
    Fshoulder.write(valF1); // tell servo to go to position in variable 'pos'
    Felbow.write(valF2);    // tell servo to go to position in variable 'pos'
    Fwrist.write(valF3);    // tell servo to go to position in variable 'pos'

    //
    // The writing to the screen takes a long time and makes the motion not as smooth
    // Use this for debugging
    //
    //    Serial.print("Servo angles i:   ");
    //    Serial.print(i);
    //    Serial.print(",   shoulder:   ");
    //    Serial.print(valD1);
    //    Serial.print(",   elbow:   ");
    //    Serial.print(valD2);
    //    Serial.print(",   wrist:   ");
    //    Serial.println(valD3);
    //
    // If the delay is too long or too short the movement is jerky.
    // This probably depends on the number of servos you are controlling
    //
    delay(15); // waits 15 ms for the servo to reach the position
  }
}

// *** Read the angles one at a time and go there ***
void pattern2()
{
  Serial.print("Enter value for shoulder: ");
  delay(500);
  while (Serial.available() == 0)
  {
  }
  delay(500);
  valD1 = Serial.parseInt();

  delay(500);
  Serial.print("Enter value for elbow: ");
  delay(500);
  while (Serial.available() == 0)
  {
  }
  delay(500);
  valD2 = Serial.parseInt();

  delay(500);
  Serial.print("Enter value for wrist: ");
  delay(500);
  while (Serial.available() == 0)
  {
  }
  delay(500);
  valD3 = Serial.parseInt();

  Serial.print("Before fixing :");
  Serial.print("  shoulder:   ");
  Serial.print(valD1);
  Serial.print(",   elbow:   ");
  Serial.print(valD2);
  Serial.print(",   wrist:   ");
  Serial.println(valD3);
  valD1 = fixDshoulder(valD1);
  valD2 = fixDelbow(valD2);
  valD3 = fixDwrist(valD3);

  Serial.print("After fixing :");
  Serial.print("  shoulder:   ");
  Serial.print(valD1);
  Serial.print(",   elbow:   ");
  Serial.print(valD2);
  Serial.print(",   wrist:   ");
  Serial.println(valD3);

  Dshoulder.write(valD1); // tell servo to go to position in variable 'pos'
  Delbow.write(valD2);    // tell servo to go to position in variable 'pos'
  Dwrist.write(valD3);    // tell servo to go to position in variable 'pos'
}

// *** [unused] ***
void pattern3()
{
  // code
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Main Code  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(CTRL0, INPUT);
  pinMode(CTRL1, INPUT);

  Ashoulder.attach(53);
  Aelbow.attach(52);
  Awrist.attach(51);
  Bshoulder.attach(50);
  Belbow.attach(49);
  Bwrist.attach(48);
  Cshoulder.attach(47);
  Celbow.attach(46);
  Cwrist.attach(45);
  Dshoulder.attach(44);
  Delbow.attach(43);
  Dwrist.attach(41);
  Eshoulder.attach(40);
  Eelbow.attach(39);
  Ewrist.attach(38);
  Fshoulder.attach(36);
  Felbow.attach(37);
  Fwrist.attach(35);

  Serial.begin(9600);
  Serial.setTimeout(10);

  Serial.print("Going to starting location.  Array size = ");
  Serial.println(maxnum);

  // go to initial position for each servo
  Ashoulder.write(valA1);
  Aelbow.write(valA2);
  Awrist.write(valA3);

  Bshoulder.write(valB1);
  Belbow.write(valB2);
  Bwrist.write(valB3);

  Cshoulder.write(valC1);
  Celbow.write(valC2);
  Cwrist.write(valC3);

  Dshoulder.write(valD1);
  Delbow.write(valD2);
  Dwrist.write(valD3);

  Eshoulder.write(valE1);
  Eelbow.write(valE2);
  Ewrist.write(valE3);

  Fshoulder.write(valF1);
  Felbow.write(valF2);
  Fwrist.write(valF3);

  control = 0;
  Serial.print("control = ");
  Serial.println(control);
  // Serial.print(",   shoulder:   ");
  // Serial.print(valD1);
  // Serial.print(",   elbow:   ");
  // Serial.print(valD2);
  // Serial.print(",   wrist:   ");
  // Serial.println(valD3);

  delay(10000); // waits 10 s for the hexapod to get set down
}

void loop()
{
  // put your main code here, to run repeatedly:
  // read control bits again to see if you are in the middle of changing something
  getcontrol();
  Serial.print("control = ");
  Serial.println(control);
  delay(10);
  // if you are changing, then set to something else...
  if (control == 1)
  {
    // *** get the control angles from the array ***
    pattern1();
    // delay(5000);
  }
  else if (control == 2)
  {
    // *** Read the angles one at a time and go there ***
    pattern2();
    delay(5000);
  }
  else if (control == 3)
  {
    // Currently unused
    pattern3();
    // delay(10);   // if needed
  }
  else
  {
    // Just sit there and don't move.
    pattern0();
    delay(5000);
  }
}