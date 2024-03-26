// Set initial center angles
int valA1 = 110; // Ashoulder
int valA2 = 90; // Aelbow
int valA3 = 80; // Awrist

int valB1 = 100; // Bshoulder
int valB2 = 90;  // Belbow
int valB3 = 80;  // Bwrist

int valC1 = 85; // Cshoulder
int valC2 = 90; // Celbow
int valC3 = 80; // Cwrist

int valD1 = 105; // Dshoulder
int valD2 = 90; // Delbow
int valD3 = 100; // Dwrist

int valE1 = 100;  // Eshoulder
int valE2 = 90; // Eelbow
int valE3 = 90; // Ewrist

int valF1 = 75; // Fshoulder
int valF2 = 90; // Felbow
int valF3 = 100; // Fwrist



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

int shoulderMult = 1;
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