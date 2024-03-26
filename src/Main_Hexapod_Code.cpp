#include <Arduino.h>

// Bugs:
// - changing between gaits mid walking seems to be possible but sometimes does weird stuff, though this may just be something to do with pattern 3
// - Pattern 0 gets its default values changed so is a 'stop' instead of a 'return to origin'

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

#define CTRL0 9
#define CTRL1 10

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

int maxnum = sizeof(PosArrayA) / sizeof(int) / 3;
int tempval;

int pos = 0; // variable to store the servo position

// First and last places of arrays to go through
int first = 1;
int last = 480;

// Some useful offsets to set gaits here
// Tripod Gait
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

// UPdates SERVo motor angles based on speed and starting offsets
void upServ()
{
  if (a <= last)
  {
    // Just read the array and go to those angles

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

  if (i <= last)
  {
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
    //
    delay(15); // waits 15 ms for the servo to reach the position

    i = i + speed;
    if (i >= last)
    {
      i = first;
    }
  }
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
  upServ();
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
  upServ();
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
  upServ();
}

////  Main Code  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void setup()
{
  pinMode(CTRL0, INPUT);
  pinMode(CTRL1, INPUT);

  // These are for the big hexapod
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
  }
  else if (control == 2)
  {
    // *** Read the angles one at a time and go there ***
    pattern2();
  }
  else if (control == 3)
  {
    pattern3();
  }
  else
  {
    // Just sit there and don't move.
    pattern0();
    delay(1000);
  }
}