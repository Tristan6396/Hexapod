#include <Arduino.h>

////  Initialization  //////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

// Initial Angles and angle fixes
#include <Initial_Angles_&_Fixes.h>    // For the big hexapod
// #include <Initial_Angles_&_Fixes_(Mine).h>   // For my hexapod

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

// First and last places of arrays to go through
int first = 0;
int last = 160;

////  Custom Functions  ////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
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

////  Main Code  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(CTRL0, INPUT);
  pinMode(CTRL1, INPUT);

  // These are for the big hexapod
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

  // These are for my hexapod
  // Ashoulder.attach(53);
  // Aelbow.attach(52);
  // Awrist.attach(51);
  // Bshoulder.attach(50);
  // Belbow.attach(49);
  // Bwrist.attach(48);
  // Cshoulder.attach(47);
  // Celbow.attach(46);
  // Cwrist.attach(45);
  // Dshoulder.attach(44);
  // Delbow.attach(43);
  // Dwrist.attach(41);
  // Eshoulder.attach(40);
  // Eelbow.attach(39);
  // Ewrist.attach(38);
  // Fshoulder.attach(36);
  // Felbow.attach(37);
  // Fwrist.attach(35);

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
    delay(1000);
  }
}