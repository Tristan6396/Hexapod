#include <Arduino.h>

// To switch between hexapods, change the 'Initial_Angles_&_Fixes.h' file the code calls, and change the pin designations under 'void setup'

// Bugs:
// - changing between gaits mid walking seems to be possible but sometimes does weird stuff, though this may just be something to do with pattern 3 (fixed?)
// - Pattern 0 gets its default values changed so is a 'stop' instead of a 'return to origin' (fixed?)
// - something is wrong with how I'm fixing the elbow angle resulting ni one side being higher than the other

// Add:
// - reverse (add another servo update function that simply goes in reverse? would also be useful when turning)
// - a way to smoothly change between gaits without large jerks
// - turning
// - sensors
// - strafing
// -

////  Initialization  //////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>

#define CTRL1 9
#define CTRL10 10
#define CTRL100 11

// Import arrays
#include <Straight_A_Array.h>
#include <Straight_B_Array.h>
#include <Straight_C_Array.h>
#include <Straight_D_Array.h>
#include <Straight_E_Array.h>
#include <Straight_F_Array.h>

// Initial Angles and angle fixes
// #include <Initial_Angles_&_Fixes.h>    // For the big hexapod
#include <Initial_Angles_&_Fixes_(Mine).h> // For my hexapod

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
int control1 = 0;
int control10 = 0;
int control100 = 0;

int maxnum = sizeof(PosArrayA) / sizeof(int) / 3;
int tempval;

int pos = 0; // variable to store the servo position

// First and last places of arrays to go through
int first = 1;
int last = 480;

// Some useful offsets to set gaits here
// Tripod Gait Default
int aMult = 0;
int bMult = 3;
int cMult = 0;
int dMult = 3;
int eMult = 0;
int fMult = 3;

int a = first + ((last / 6) * aMult);
int b = first + ((last / 6) * bMult);
int c = first + ((last / 6) * cMult);
int d = first + ((last / 6) * dMult);
int e = first + ((last / 6) * eMult);
int f = first + ((last / 6) * fMult);
int i = first;

int speed = 8;
int aMultNew;
int bMultNew;
int cMultNew;
int dMultNew;
int eMultNew;
int fMultNew;

////  Custom Functions  ////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// *** get the control bits ***
void getcontrol()
{
  // Read the control pins
  control1 = digitalRead(CTRL1);
  control10 = digitalRead(CTRL10);
  control100 = digitalRead(CTRL100);
  control = (control1) + (control10 * 10) + (control100 * 100);
}

// *** Go to the initial positions of each servo ***
void pattern0()
{
  Ashoulder.write(Ashoulderoffset + 90);
  Aelbow.write(Aelbowoffset + 90);
  Awrist.write(Awristoffset + 90);

  Bshoulder.write(Bshoulderoffset + 90);
  Belbow.write(Belbowoffset + 90);
  Bwrist.write(Bwristoffset + 90);

  Cshoulder.write(Cshoulderoffset + 90);
  Celbow.write(Celbowoffset + 90);
  Cwrist.write(Cwristoffset + 90);

  Dshoulder.write(Dshoulderoffset + 90);
  Delbow.write(Delbowoffset + 90);
  Dwrist.write(Dwristoffset + 90);

  Eshoulder.write(Eshoulderoffset + 90);
  Eelbow.write(Eelbowoffset + 90);
  Ewrist.write(Ewristoffset + 90);

  Fshoulder.write(Fshoulderoffset + 90);
  Felbow.write(Felbowoffset + 90);
  Fwrist.write(Fwristoffset + 90);
}

void readStraightArrays()
{
  // Reads the arrays based on speed and starting offsets
  if (a <= last)
  {

    valA1 = pgm_read_word_near(&PosArrayA[a][0]);
    valA2 = pgm_read_word_near(&PosArrayA[a][1]);
    valA3 = pgm_read_word_near(&PosArrayA[a][2]);

    //   These printouts were for debugging
    //  Serial.print("Direct from the array a:   ");
    //  Serial.print(a);
    //  Serial.print(",   shoulder:   ");
    //  Serial.print(valA1);
    //  Serial.print(",   elbow:   ");
    //  Serial.print(valA2);
    //  Serial.print(",   wrist:   ");
    //  Serial.println(valA3);

    a = a + speed;
    if (a > last)
    {
      a = first;
    }
  }
  if (b <= last)
  {
    valB1 = pgm_read_word_near(&PosArrayB[b][0]);
    valB2 = pgm_read_word_near(&PosArrayB[b][1]);
    valB3 = pgm_read_word_near(&PosArrayB[b][2]);
    b = b + speed;
    if (b > last)
    {
      b = first;
    }
  }
  if (c <= last)
  {
    valC1 = pgm_read_word_near(&PosArrayC[c][0]);
    valC2 = pgm_read_word_near(&PosArrayC[c][1]);
    valC3 = pgm_read_word_near(&PosArrayC[c][2]);
    c = c + speed;
    if (c > last)
    {
      c = first;
    }
  }
  if (d <= last)
  {
    valD1 = pgm_read_word_near(&PosArrayD[d][0]);
    valD2 = pgm_read_word_near(&PosArrayD[d][1]);
    valD3 = pgm_read_word_near(&PosArrayD[d][2]);
    d = d + speed;
    if (d > last)
    {
      d = first;
    }
  }
  if (e <= last)
  {
    valE1 = pgm_read_word_near(&PosArrayE[e][0]);
    valE2 = pgm_read_word_near(&PosArrayE[e][1]);
    valE3 = pgm_read_word_near(&PosArrayE[e][2]);
    e = e + speed;
    if (e > last)
    {
      e = first;
    }
  }
  if (f <= last)
  {
    valF1 = pgm_read_word_near(&PosArrayF[f][0]);
    valF2 = pgm_read_word_near(&PosArrayF[f][1]);
    valF3 = pgm_read_word_near(&PosArrayF[f][2]);
    f = f + speed;
    if (f > last)
    {
      f = first;
    }
  }
}

void fixAngles()
{
  // Modify to convert the "Matlab" angles into "Servo" angles
  valA1 = fixAshoulder(valA1);
  valA2 = fixAelbow(valA2);
  valA3 = fixAwrist(valA3);

  valB1 = fixBshoulder(valB1);
  valB2 = fixBelbow(valB2);
  valB3 = fixBwrist(valB3);

  valC1 = fixCshoulder(valC1);
  valC2 = fixCelbow(valC2);
  valC3 = fixCwrist(valC3);

  valD1 = fixDshoulder(valD1);
  valD2 = fixDelbow(valD2);
  valD3 = fixDwrist(valD3);

  valE1 = fixEshoulder(valE1);
  valE2 = fixEelbow(valE2);
  valE3 = fixEwrist(valE3);

  valF1 = fixFshoulder(valF1);
  valF2 = fixFelbow(valF2);
  valF3 = fixFwrist(valF3);
}

void smoothResponse()
{
  // Gets rid of jerkiness for when changing gaits
  // Currently does nothing
  // Maybe make a function like in fixAngles?
  valA1 = valA1;
  valA2 = valA2;
  valA3 = valA3;

  valB1 = valB1;
  valB2 = valB2;
  valB3 = valB3;

  valC1 = valC1;
  valC2 = valC2;
  valC3 = valC3;

  valD1 = valD1;
  valD2 = valD2;
  valD3 = valD3;

  valE1 = valE1;
  valE2 = valE2;
  valE3 = valE3;

  valF1 = valF1;
  valF2 = valF2;
  valF3 = valF3;
}

void gaitCheck()
{
  // Check if gait was switched and offsets legs accordingly
  if ((aMult != aMultNew) || (bMult != bMultNew) || (cMult != cMultNew) || (dMult != dMultNew) || (eMult != eMultNew) || (fMult != fMultNew))
  {
    a = first + ((last / 6) * aMult);
    b = first + ((last / 6) * bMult);
    c = first + ((last / 6) * cMult);
    d = first + ((last / 6) * dMult);
    e = first + ((last / 6) * eMult);
    f = first + ((last / 6) * fMult);
  }
}

void upServ()
{
  // UPdates SERVo motor angles
  if (i <= last)
  {

    Ashoulder.write(valA1); // tell servo to go to position in variable 'pos'
    Aelbow.write(valA2);    // tell servo to go to position in variable 'pos'
    Awrist.write(valA3);    // tell servo to go to position in variable 'pos'

    Bshoulder.write(valB1); // tell servo to go to position in variable 'pos'
    Belbow.write(valB2);    // tell servo to go to position in variable 'pos'
    Bwrist.write(valB3);    // tell servo to go to position in variable 'pos'

    Cshoulder.write(valC1); // tell servo to go to position in variable 'pos'
    Celbow.write(valC2);    // tell servo to go to position in variable 'pos'
    Cwrist.write(valC3);    // tell servo to go to position in variable 'pos'

    Dshoulder.write(valD1); // tell servo to go to position in variable 'pos'
    Delbow.write(valD2);    // tell servo to go to position in variable 'pos'
    Dwrist.write(valD3);    // tell servo to go to position in variable 'pos'

    Eshoulder.write(valE1); // tell servo to go to position in variable 'pos'
    Eelbow.write(valE2);    // tell servo to go to position in variable 'pos'
    Ewrist.write(valE3);    // tell servo to go to position in variable 'pos'

    Fshoulder.write(valF1); // tell servo to go to position in variable 'pos'
    Felbow.write(valF2);    // tell servo to go to position in variable 'pos'
    Fwrist.write(valF3);    // tell servo to go to position in variable 'pos'

    //
    // The writing to the screen takes a long time and makes the motion not as smooth
    // Use this for debugging
    //
    //  Serial.print("Servo angles i:   ");
    //  Serial.print(i);
    //  Serial.print(",   shoulder:   ");
    //  Serial.print(valA1);
    //  Serial.print(",   elbow:   ");
    //  Serial.print(valA2);
    //  Serial.print(",   wrist:   ");
    //  Serial.println(valA3);
    //
    // If the delay is too long or too short the movement is jerky.
    // This probably depends on the number of servos you are controlling

    delay(15); // waits 15 ms for the servo to reach the position

    i = i + speed;
    if (i >= last)
    {
      i = first;
    }
  }
}

// *** Move forward fast ***
void pattern1()
{
  speed = 8;
  aMultNew = 0;
  bMultNew = 3;
  cMultNew = 0;
  dMultNew = 3;
  eMultNew = 0;
  fMultNew = 3;
}

// *** Move forward slow ***
void pattern2()
{
  speed = 2;
  aMultNew = 0;
  bMultNew = 3;
  cMultNew = 0;
  dMultNew = 3;
  eMultNew = 0;
  fMultNew = 3;
}

// *** DANCE MODE ***
void pattern3()
{
  speed = 8;
  aMultNew = 0;
  bMultNew = 0;
  cMultNew = 0;
  dMultNew = 0;
  eMultNew = 0;
  fMultNew = 0;
}

////  Main Code  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(CTRL1, INPUT);
  pinMode(CTRL10, INPUT);
  pinMode(CTRL100, INPUT);

  // // These are for the big hexapod
  // Ashoulder.attach(28);
  // Aelbow.attach(30);
  // Awrist.attach(32);
  // Bshoulder.attach(38);
  // Belbow.attach(40);
  // Bwrist.attach(42);
  // Cshoulder.attach(48);
  // Celbow.attach(50);
  // Cwrist.attach(52);
  // Dshoulder.attach(49);
  // Delbow.attach(51);
  // Dwrist.attach(53);
  // Eshoulder.attach(39);
  // Eelbow.attach(41);
  // Ewrist.attach(43);
  // Fshoulder.attach(29);
  // Felbow.attach(31);
  // Fwrist.attach(33);

  // These are for my hexapod
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

  delay(5000); // waits 5s for the hexapod to get set down
}

void loop()
{
  // read control bits again to see if you are in the middle of changing something

  getcontrol();
  Serial.print("control = ");
  Serial.println(control);
  delay(10);

// Controls include 0, 1, 10, 11, 100, 101, 110, 111
  if (control == 1)
  {
    pattern1(); // Sets speed and gait offsets

    readStraightArrays(); // Read array based on spd and offsets
    fixAngles();          // Fix angles from MATLAB to our servos
    smoothResponse();     // Smooth any changes that are too sudden
    upServ();             // Update servos to new position
    gaitCheck();          // Check for updated gait offsets and switch if needed
  }

  else if (control == 10)
  {
    pattern2(); // Sets speed and gait offsets

    readStraightArrays(); // Read array based on spd and offsets
    fixAngles();          // Fix angles from MATLAB to our servos
    smoothResponse();     // Smooth any changes that are too sudden
    upServ();             // Update servos to new position
    gaitCheck();          // Check for updated gait offsets and switch if needed
  }

  else if (control == 11)
  {
    pattern3(); // Sets speed and gait offsets

        readStraightArrays(); // Read array based on spd and offsets
    fixAngles();          // Fix angles from MATLAB to our servos
    smoothResponse();     // Smooth any changes that are too sudden
    upServ();             // Update servos to new position
    gaitCheck();          // Check for updated gait offsets and switch if needed
  }

  else
  {
    // Just sit there and don't move.
    pattern0();
    delay(1000);
  }
}