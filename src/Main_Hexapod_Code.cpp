#include <Arduino.h>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Initialization  //////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <Servo.h>

#define CTRL0 9
#define CTRL1 10

// Array for A leg
const PROGMEM int16_t PosArrayA[][3] = {
    {48, 19, 36},
    {49, 17, 39},
    {49, 16, 41},
    {50, 15, 44},
    {51, 14, 46},
    {52, 13, 48},
    {53, 13, 50},
    {54, 12, 52},
    {54, 11, 53},
    {55, 11, 55},
    {56, 10, 56},
    {57, 10, 58},
    {58, 9, 59},
    {59, 9, 60},
    {60, 8, 62},
    {61, 8, 63},
    {62, 8, 64},
    {63, 7, 65},
    {64, 7, 66},
    {65, 7, 67},
    {66, 6, 68},
    {67, 6, 69},
    {68, 6, 69},
    {70, 6, 70},
    {71, 6, 71},
    {72, 5, 71},
    {73, 5, 72},
    {74, 5, 73},
    {76, 5, 73},
    {77, 5, 74},
    {78, 5, 74},
    {79, 5, 74},
    {81, 5, 75},
    {82, 5, 75},
    {83, 5, 75},
    {84, 5, 75},
    {86, 5, 76},
    {87, 5, 76},
    {88, 5, 76},
    {90, 5, 76},
    {91, 5, 76},
    {92, 5, 76},
    {94, 5, 76},
    {95, 5, 75},
    {96, 5, 75},
    {97, 5, 75},
    {99, 5, 75},
    {99, 3, 76},
    {99, 1, 78},
    {99, -1, 79},
    {99, -3, 81},
    {99, -4, 82},
    {98, -6, 84},
    {98, -8, 85},
    {98, -10, 86},
    {98, -12, 87},
    {98, -13, 88},
    {98, -15, 89},
    {98, -17, 90},
    {98, -18, 91},
    {98, -20, 92},
    {98, -22, 95},
    {98, -25, 98},
    {98, -27, 100},
    {99, -30, 103},
    {99, -32, 105},
    {99, -34, 108},
    {99, -37, 110},
    {99, -39, 112},
    {99, -42, 115},
    {99, -44, 117},
    {100, -47, 119},
    {100, -50, 121},
    {100, -53, 124},
    {100, -55, 126},
    {100, -58, 128},
    {100, -61, 130},
    {101, -64, 132},
    {101, -68, 134},
    {101, -71, 136},
    {101, -75, 138},
    {100, -75, 138},
    {98, -75, 138},
    {96, -75, 139},
    {95, -75, 139},
    {93, -75, 139},
    {91, -76, 139},
    {90, -76, 139},
    {88, -75, 139},
    {86, -75, 139},
    {84, -75, 139},
    {83, -75, 138},
    {81, -75, 138},
    {79, -75, 138},
    {78, -74, 137},
    {76, -74, 137},
    {75, -74, 136},
    {73, -73, 136},
    {71, -73, 135},
    {70, -73, 135},
    {68, -72, 134},
    {67, -72, 133},
    {66, -71, 133},
    {64, -71, 132},
    {63, -70, 131},
    {61, -69, 130},
    {60, -69, 129},
    {59, -68, 128},
    {58, -67, 127},
    {56, -67, 126},
    {55, -66, 125},
    {54, -65, 124},
    {53, -65, 123},
    {52, -64, 121},
    {51, -63, 120},
    {50, -62, 119},
    {49, -61, 117},
    {48, -61, 116},
    {47, -60, 115},
    {46, -59, 113},
    {45, -58, 112},
    {44, -57, 110},
    {44, -56, 109},
    {43, -55, 107},
    {42, -54, 106},
    {41, -53, 104},
    {41, -52, 102},
    {40, -51, 101},
    {40, -49, 99},
    {41, -47, 98},
    {41, -45, 96},
    {42, -43, 95},
    {43, -40, 93},
    {43, -38, 91},
    {44, -36, 89},
    {44, -34, 87},
    {45, -32, 85},
    {45, -30, 83},
    {45, -27, 81},
    {46, -25, 79},
    {46, -23, 77},
    {47, -21, 74},
    {47, -18, 72},
    {48, -16, 69},
    {48, -13, 66},
    {49, -11, 64},
    {49, -9, 61},
    {49, -6, 57},
    {49, -4, 56},
    {49, -3, 55},
    {49, -1, 54},
    {49, 0, 53},
    {49, 2, 51},
    {49, 4, 50},
    {48, 6, 48},
    {48, 7, 46},
    {48, 9, 45},
    {48, 11, 43},
    {48, 13, 41},
    {48, 15, 38},
    {47, 18, 36},
    {47, 20, 33},
};

// Array for B leg
const PROGMEM int16_t PosArrayB[][3] = {
    {63, 7, 65},
    {64, 7, 66},
    {65, 7, 67},
    {66, 6, 68},
    {67, 6, 68},
    {68, 6, 69},
    {69, 6, 70},
    {70, 6, 71},
    {72, 6, 71},
    {73, 5, 72},
    {74, 5, 72},
    {75, 5, 73},
    {76, 5, 73},
    {78, 5, 74},
    {79, 5, 74},
    {80, 5, 75},
    {82, 5, 75},
    {83, 5, 75},
    {84, 5, 75},
    {85, 5, 75},
    {87, 5, 76},
    {88, 5, 76},
    {89, 5, 76},
    {91, 5, 76},
    {92, 5, 76},
    {93, 5, 76},
    {95, 5, 75},
    {96, 5, 75},
    {97, 5, 75},
    {98, 5, 75},
    {100, 5, 75},
    {101, 5, 74},
    {102, 5, 74},
    {104, 5, 73},
    {105, 5, 73},
    {106, 5, 72},
    {107, 5, 72},
    {108, 6, 71},
    {110, 6, 71},
    {111, 6, 70},
    {112, 6, 69},
    {113, 6, 68},
    {114, 6, 68},
    {115, 7, 67},
    {116, 7, 66},
    {117, 7, 65},
    {118, 8, 64},
    {118, 6, 65},
    {118, 4, 67},
    {118, 2, 69},
    {118, 0, 70},
    {118, -1, 72},
    {118, -3, 73},
    {117, -5, 74},
    {117, -7, 75},
    {117, -8, 77},
    {117, -10, 78},
    {117, -12, 79},
    {117, -13, 80},
    {117, -15, 81},
    {117, -16, 82},
    {117, -19, 85},
    {117, -21, 87},
    {118, -23, 90},
    {118, -26, 92},
    {118, -28, 95},
    {119, -30, 97},
    {119, -33, 99},
    {119, -35, 102},
    {120, -38, 104},
    {120, -40, 106},
    {121, -42, 108},
    {121, -45, 110},
    {122, -47, 112},
    {122, -50, 114},
    {122, -52, 116},
    {123, -55, 118},
    {123, -58, 120},
    {124, -60, 121},
    {124, -63, 123},
    {125, -66, 125},
    {124, -67, 126},
    {123, -67, 127},
    {121, -68, 128},
    {120, -69, 129},
    {119, -69, 130},
    {118, -70, 131},
    {116, -70, 132},
    {115, -71, 132},
    {113, -72, 133},
    {112, -72, 134},
    {110, -72, 135},
    {109, -73, 135},
    {107, -73, 136},
    {106, -74, 136},
    {104, -74, 137},
    {103, -74, 137},
    {101, -75, 138},
    {99, -75, 138},
    {98, -75, 138},
    {96, -75, 139},
    {94, -75, 139},
    {93, -75, 139},
    {91, -76, 139},
    {89, -76, 139},
    {87, -75, 139},
    {86, -75, 139},
    {84, -75, 139},
    {82, -75, 138},
    {81, -75, 138},
    {79, -75, 138},
    {77, -74, 137},
    {76, -74, 137},
    {74, -74, 136},
    {73, -73, 136},
    {71, -73, 135},
    {70, -72, 135},
    {68, -72, 134},
    {67, -72, 133},
    {65, -71, 132},
    {64, -70, 132},
    {62, -70, 131},
    {61, -69, 130},
    {60, -69, 129},
    {59, -68, 128},
    {57, -67, 127},
    {56, -67, 126},
    {55, -66, 125},
    {56, -63, 123},
    {56, -60, 121},
    {57, -58, 120},
    {57, -55, 118},
    {58, -52, 116},
    {58, -50, 114},
    {58, -47, 112},
    {59, -45, 110},
    {59, -42, 108},
    {60, -40, 106},
    {60, -38, 104},
    {61, -35, 102},
    {61, -33, 99},
    {61, -30, 97},
    {62, -28, 95},
    {62, -26, 92},
    {62, -23, 90},
    {63, -21, 87},
    {63, -19, 85},
    {63, -16, 82},
    {63, -15, 81},
    {63, -13, 80},
    {63, -12, 79},
    {63, -10, 78},
    {63, -8, 77},
    {63, -7, 75},
    {63, -5, 74},
    {62, -3, 73},
    {62, -1, 72},
    {62, 0, 70},
    {62, 2, 69},
    {62, 4, 67},
    {62, 6, 65},
    {62, 8, 64},
};

// Array for C leg
const PROGMEM int16_t PosArrayC[][3] = {
    {83, 5, 75},
    {84, 5, 75},
    {85, 5, 75},
    {86, 5, 76},
    {88, 5, 76},
    {89, 5, 76},
    {90, 5, 76},
    {92, 5, 76},
    {93, 5, 76},
    {94, 5, 76},
    {96, 5, 75},
    {97, 5, 75},
    {98, 5, 75},
    {99, 5, 75},
    {101, 5, 74},
    {102, 5, 74},
    {103, 5, 74},
    {104, 5, 73},
    {106, 5, 73},
    {107, 5, 72},
    {108, 5, 71},
    {109, 6, 71},
    {110, 6, 70},
    {112, 6, 69},
    {113, 6, 69},
    {114, 6, 68},
    {115, 7, 67},
    {116, 7, 66},
    {117, 7, 65},
    {118, 8, 64},
    {119, 8, 63},
    {120, 8, 62},
    {121, 9, 60},
    {122, 9, 59},
    {123, 10, 58},
    {124, 10, 56},
    {125, 11, 55},
    {126, 11, 53},
    {126, 12, 52},
    {127, 13, 50},
    {128, 13, 48},
    {129, 14, 46},
    {130, 15, 44},
    {131, 16, 41},
    {131, 17, 39},
    {132, 19, 36},
    {133, 20, 33},
    {133, 18, 36},
    {132, 15, 38},
    {132, 13, 41},
    {132, 11, 43},
    {132, 9, 45},
    {132, 7, 46},
    {132, 6, 48},
    {131, 4, 50},
    {131, 2, 51},
    {131, 0, 53},
    {131, -1, 54},
    {131, -3, 55},
    {131, -4, 56},
    {131, -6, 57},
    {131, -9, 61},
    {131, -11, 64},
    {132, -13, 66},
    {132, -16, 69},
    {133, -18, 72},
    {133, -21, 74},
    {134, -23, 77},
    {134, -25, 79},
    {135, -27, 81},
    {135, -30, 83},
    {135, -32, 85},
    {136, -34, 87},
    {136, -36, 89},
    {137, -38, 91},
    {137, -40, 93},
    {138, -43, 95},
    {139, -45, 96},
    {139, -47, 98},
    {140, -49, 99},
    {140, -51, 101},
    {139, -52, 102},
    {139, -53, 104},
    {138, -54, 106},
    {137, -55, 107},
    {136, -56, 109},
    {136, -57, 110},
    {135, -58, 112},
    {134, -59, 113},
    {133, -60, 115},
    {132, -61, 116},
    {131, -61, 117},
    {130, -62, 119},
    {129, -63, 120},
    {128, -64, 121},
    {127, -65, 123},
    {126, -65, 124},
    {125, -66, 125},
    {124, -67, 126},
    {122, -67, 127},
    {121, -68, 128},
    {120, -69, 129},
    {119, -69, 130},
    {117, -70, 131},
    {116, -71, 132},
    {114, -71, 133},
    {113, -72, 133},
    {112, -72, 134},
    {110, -73, 135},
    {109, -73, 135},
    {107, -73, 136},
    {105, -74, 137},
    {104, -74, 137},
    {102, -74, 137},
    {101, -75, 138},
    {99, -75, 138},
    {97, -75, 138},
    {96, -75, 139},
    {94, -75, 139},
    {92, -75, 139},
    {90, -76, 139},
    {89, -76, 139},
    {87, -75, 139},
    {85, -75, 139},
    {84, -75, 139},
    {82, -75, 138},
    {80, -75, 138},
    {79, -75, 138},
    {79, -71, 136},
    {79, -68, 134},
    {79, -64, 132},
    {80, -61, 130},
    {80, -58, 128},
    {80, -55, 126},
    {80, -53, 124},
    {80, -50, 121},
    {80, -47, 119},
    {81, -44, 117},
    {81, -42, 115},
    {81, -39, 112},
    {81, -37, 110},
    {81, -34, 108},
    {81, -32, 105},
    {81, -30, 103},
    {82, -27, 100},
    {82, -25, 98},
    {82, -22, 95},
    {82, -20, 92},
    {82, -18, 91},
    {82, -17, 90},
    {82, -15, 89},
    {82, -13, 88},
    {82, -12, 87},
    {82, -10, 86},
    {82, -8, 85},
    {82, -6, 84},
    {81, -4, 82},
    {81, -3, 81},
    {81, -1, 79},
    {81, 1, 78},
    {81, 3, 76},
    {81, 5, 75},
};

// Array for D leg
const PROGMEM int16_t PosArrayD[][3] = {
    {-83, 5, 75},
    {-84, 5, 75},
    {-85, 5, 75},
    {-86, 5, 76},
    {-88, 5, 76},
    {-89, 5, 76},
    {-90, 5, 76},
    {-92, 5, 76},
    {-93, 5, 76},
    {-94, 5, 76},
    {-96, 5, 75},
    {-97, 5, 75},
    {-98, 5, 75},
    {-99, 5, 75},
    {-101, 5, 74},
    {-102, 5, 74},
    {-103, 5, 74},
    {-104, 5, 73},
    {-106, 5, 73},
    {-107, 5, 72},
    {-108, 5, 71},
    {-109, 6, 71},
    {-110, 6, 70},
    {-112, 6, 69},
    {-113, 6, 69},
    {-114, 6, 68},
    {-115, 7, 67},
    {-116, 7, 66},
    {-117, 7, 65},
    {-118, 8, 64},
    {-119, 8, 63},
    {-120, 8, 62},
    {-121, 9, 60},
    {-122, 9, 59},
    {-123, 10, 58},
    {-124, 10, 56},
    {-125, 11, 55},
    {-126, 11, 53},
    {-126, 12, 52},
    {-127, 13, 50},
    {-128, 13, 48},
    {-129, 14, 46},
    {-130, 15, 44},
    {-131, 16, 41},
    {-131, 17, 39},
    {-132, 19, 36},
    {-133, 20, 33},
    {-133, 18, 36},
    {-132, 15, 38},
    {-132, 13, 41},
    {-132, 11, 43},
    {-132, 9, 45},
    {-132, 7, 46},
    {-132, 6, 48},
    {-131, 4, 50},
    {-131, 2, 51},
    {-131, 0, 53},
    {-131, -1, 54},
    {-131, -3, 55},
    {-131, -4, 56},
    {-131, -6, 57},
    {-131, -9, 61},
    {-131, -11, 64},
    {-132, -13, 66},
    {-132, -16, 69},
    {-133, -18, 72},
    {-133, -21, 74},
    {-134, -23, 77},
    {-134, -25, 79},
    {-135, -27, 81},
    {-135, -30, 83},
    {-135, -32, 85},
    {-136, -34, 87},
    {-136, -36, 89},
    {-137, -38, 91},
    {-137, -40, 93},
    {-138, -43, 95},
    {-139, -45, 96},
    {-139, -47, 98},
    {-140, -49, 99},
    {-140, -51, 101},
    {-139, -52, 102},
    {-139, -53, 104},
    {-138, -54, 106},
    {-137, -55, 107},
    {-136, -56, 109},
    {-136, -57, 110},
    {-135, -58, 112},
    {-134, -59, 113},
    {-133, -60, 115},
    {-132, -61, 116},
    {-131, -61, 117},
    {-130, -62, 119},
    {-129, -63, 120},
    {-128, -64, 121},
    {-127, -65, 123},
    {-126, -65, 124},
    {-125, -66, 125},
    {-124, -67, 126},
    {-122, -67, 127},
    {-121, -68, 128},
    {-120, -69, 129},
    {-119, -69, 130},
    {-117, -70, 131},
    {-116, -71, 132},
    {-114, -71, 133},
    {-113, -72, 133},
    {-112, -72, 134},
    {-110, -73, 135},
    {-109, -73, 135},
    {-107, -73, 136},
    {-105, -74, 136},
    {-104, -74, 137},
    {-102, -74, 137},
    {-101, -75, 138},
    {-99, -75, 138},
    {-97, -75, 138},
    {-96, -75, 139},
    {-94, -75, 139},
    {-92, -75, 139},
    {-90, -76, 139},
    {-89, -76, 139},
    {-87, -75, 139},
    {-85, -75, 139},
    {-84, -75, 139},
    {-82, -75, 138},
    {-80, -75, 138},
    {-79, -75, 138},
    {-79, -71, 136},
    {-79, -68, 134},
    {-79, -64, 132},
    {-80, -61, 130},
    {-80, -58, 128},
    {-80, -55, 126},
    {-80, -53, 124},
    {-80, -50, 121},
    {-80, -47, 119},
    {-81, -44, 117},
    {-81, -42, 115},
    {-81, -39, 112},
    {-81, -37, 110},
    {-81, -34, 108},
    {-81, -32, 105},
    {-81, -30, 103},
    {-82, -27, 100},
    {-82, -25, 98},
    {-82, -22, 95},
    {-82, -20, 92},
    {-82, -18, 91},
    {-82, -17, 90},
    {-82, -15, 89},
    {-82, -13, 88},
    {-82, -12, 87},
    {-82, -10, 86},
    {-82, -8, 85},
    {-82, -6, 84},
    {-81, -4, 82},
    {-81, -3, 81},
    {-81, -1, 79},
    {-81, 1, 78},
    {-81, 3, 76},
    {-81, 5, 75},
};

// Array for E leg
const PROGMEM int16_t PosArrayE[][3] = {
    {-63, 7, 65},
    {-64, 7, 66},
    {-65, 7, 67},
    {-66, 6, 68},
    {-67, 6, 68},
    {-68, 6, 69},
    {-69, 6, 70},
    {-70, 6, 71},
    {-72, 6, 71},
    {-73, 5, 72},
    {-74, 5, 72},
    {-75, 5, 73},
    {-76, 5, 73},
    {-78, 5, 74},
    {-79, 5, 74},
    {-80, 5, 75},
    {-82, 5, 75},
    {-83, 5, 75},
    {-84, 5, 75},
    {-85, 5, 75},
    {-87, 5, 76},
    {-88, 5, 76},
    {-89, 5, 76},
    {-91, 5, 76},
    {-92, 5, 76},
    {-93, 5, 76},
    {-95, 5, 75},
    {-96, 5, 75},
    {-97, 5, 75},
    {-98, 5, 75},
    {-100, 5, 75},
    {-101, 5, 74},
    {-102, 5, 74},
    {-104, 5, 73},
    {-105, 5, 73},
    {-106, 5, 72},
    {-107, 5, 72},
    {-108, 6, 71},
    {-110, 6, 71},
    {-111, 6, 70},
    {-112, 6, 69},
    {-113, 6, 68},
    {-114, 6, 68},
    {-115, 7, 67},
    {-116, 7, 66},
    {-117, 7, 65},
    {-118, 8, 64},
    {-118, 6, 65},
    {-118, 4, 67},
    {-118, 2, 69},
    {-118, 0, 70},
    {-118, -1, 72},
    {-118, -3, 73},
    {-117, -5, 74},
    {-117, -7, 75},
    {-117, -8, 77},
    {-117, -10, 78},
    {-117, -12, 79},
    {-117, -13, 80},
    {-117, -15, 81},
    {-117, -16, 82},
    {-117, -19, 85},
    {-117, -21, 87},
    {-118, -23, 90},
    {-118, -26, 92},
    {-118, -28, 95},
    {-119, -30, 97},
    {-119, -33, 99},
    {-119, -35, 102},
    {-120, -38, 104},
    {-120, -40, 106},
    {-121, -42, 108},
    {-121, -45, 110},
    {-122, -47, 112},
    {-122, -50, 114},
    {-122, -52, 116},
    {-123, -55, 118},
    {-123, -58, 120},
    {-124, -60, 121},
    {-124, -63, 123},
    {-125, -66, 125},
    {-124, -67, 126},
    {-123, -67, 127},
    {-121, -68, 128},
    {-120, -69, 129},
    {-119, -69, 130},
    {-118, -70, 131},
    {-116, -70, 132},
    {-115, -71, 132},
    {-113, -72, 133},
    {-112, -72, 134},
    {-110, -72, 135},
    {-109, -73, 135},
    {-107, -73, 136},
    {-106, -74, 136},
    {-104, -74, 137},
    {-103, -74, 137},
    {-101, -75, 138},
    {-99, -75, 138},
    {-98, -75, 138},
    {-96, -75, 139},
    {-94, -75, 139},
    {-93, -75, 139},
    {-91, -76, 139},
    {-89, -76, 139},
    {-87, -75, 139},
    {-86, -75, 139},
    {-84, -75, 139},
    {-82, -75, 138},
    {-81, -75, 138},
    {-79, -75, 138},
    {-77, -74, 137},
    {-76, -74, 137},
    {-74, -74, 136},
    {-73, -73, 136},
    {-71, -73, 135},
    {-70, -72, 135},
    {-68, -72, 134},
    {-67, -72, 133},
    {-65, -71, 132},
    {-64, -70, 132},
    {-62, -70, 131},
    {-61, -69, 130},
    {-60, -69, 129},
    {-59, -68, 128},
    {-57, -67, 127},
    {-56, -67, 126},
    {-55, -66, 125},
    {-56, -63, 123},
    {-56, -60, 121},
    {-57, -58, 120},
    {-57, -55, 118},
    {-58, -52, 116},
    {-58, -50, 114},
    {-58, -47, 112},
    {-59, -45, 110},
    {-59, -42, 108},
    {-60, -40, 106},
    {-60, -38, 104},
    {-61, -35, 102},
    {-61, -33, 99},
    {-61, -30, 97},
    {-62, -28, 95},
    {-62, -26, 92},
    {-62, -23, 90},
    {-63, -21, 87},
    {-63, -19, 85},
    {-63, -16, 82},
    {-63, -15, 81},
    {-63, -13, 80},
    {-63, -12, 79},
    {-63, -10, 78},
    {-63, -8, 77},
    {-63, -7, 75},
    {-63, -5, 74},
    {-62, -3, 73},
    {-62, -1, 72},
    {-62, 0, 70},
    {-62, 2, 69},
    {-62, 4, 67},
    {-62, 6, 65},
    {-62, 8, 64},
};

// Array for F leg
const PROGMEM int16_t PosArrayF[][3] = {
    {-48, 19, 36},
    {-49, 17, 39},
    {-49, 16, 41},
    {-50, 15, 44},
    {-51, 14, 46},
    {-52, 13, 48},
    {-53, 13, 50},
    {-54, 12, 52},
    {-54, 11, 53},
    {-55, 11, 55},
    {-56, 10, 56},
    {-57, 10, 58},
    {-58, 9, 59},
    {-59, 9, 60},
    {-60, 8, 62},
    {-61, 8, 63},
    {-62, 8, 64},
    {-63, 7, 65},
    {-64, 7, 66},
    {-65, 7, 67},
    {-66, 6, 68},
    {-67, 6, 69},
    {-68, 6, 69},
    {-70, 6, 70},
    {-71, 6, 71},
    {-72, 5, 71},
    {-73, 5, 72},
    {-74, 5, 73},
    {-76, 5, 73},
    {-77, 5, 74},
    {-78, 5, 74},
    {-79, 5, 74},
    {-81, 5, 75},
    {-82, 5, 75},
    {-83, 5, 75},
    {-84, 5, 75},
    {-86, 5, 76},
    {-87, 5, 76},
    {-88, 5, 76},
    {-90, 5, 76},
    {-91, 5, 76},
    {-92, 5, 76},
    {-94, 5, 76},
    {-95, 5, 75},
    {-96, 5, 75},
    {-97, 5, 75},
    {-99, 5, 75},
    {-99, 3, 76},
    {-99, 1, 78},
    {-99, -1, 79},
    {-99, -3, 81},
    {-99, -4, 82},
    {-98, -6, 84},
    {-98, -8, 85},
    {-98, -10, 86},
    {-98, -12, 87},
    {-98, -13, 88},
    {-98, -15, 89},
    {-98, -17, 90},
    {-98, -18, 91},
    {-98, -20, 92},
    {-98, -22, 95},
    {-98, -25, 98},
    {-98, -27, 100},
    {-99, -30, 103},
    {-99, -32, 105},
    {-99, -34, 108},
    {-99, -37, 110},
    {-99, -39, 112},
    {-99, -42, 115},
    {-99, -44, 117},
    {-100, -47, 119},
    {-100, -50, 121},
    {-100, -53, 124},
    {-100, -55, 126},
    {-100, -58, 128},
    {-100, -61, 130},
    {-101, -64, 132},
    {-101, -68, 134},
    {-101, -71, 136},
    {-101, -75, 138},
    {-100, -75, 138},
    {-98, -75, 138},
    {-96, -75, 139},
    {-95, -75, 139},
    {-93, -75, 139},
    {-91, -76, 139},
    {-90, -76, 139},
    {-88, -75, 139},
    {-86, -75, 139},
    {-84, -75, 139},
    {-83, -75, 138},
    {-81, -75, 138},
    {-79, -75, 138},
    {-78, -74, 137},
    {-76, -74, 137},
    {-75, -74, 137},
    {-73, -73, 136},
    {-71, -73, 135},
    {-70, -73, 135},
    {-68, -72, 134},
    {-67, -72, 133},
    {-66, -71, 133},
    {-64, -71, 132},
    {-63, -70, 131},
    {-61, -69, 130},
    {-60, -69, 129},
    {-59, -68, 128},
    {-58, -67, 127},
    {-56, -67, 126},
    {-55, -66, 125},
    {-54, -65, 124},
    {-53, -65, 123},
    {-52, -64, 121},
    {-51, -63, 120},
    {-50, -62, 119},
    {-49, -61, 117},
    {-48, -61, 116},
    {-47, -60, 115},
    {-46, -59, 113},
    {-45, -58, 112},
    {-44, -57, 110},
    {-44, -56, 109},
    {-43, -55, 107},
    {-42, -54, 106},
    {-41, -53, 104},
    {-41, -52, 102},
    {-40, -51, 101},
    {-40, -49, 99},
    {-41, -47, 98},
    {-41, -45, 96},
    {-42, -43, 95},
    {-43, -40, 93},
    {-43, -38, 91},
    {-44, -36, 89},
    {-44, -34, 87},
    {-45, -32, 85},
    {-45, -30, 83},
    {-45, -27, 81},
    {-46, -25, 79},
    {-46, -23, 77},
    {-47, -21, 74},
    {-47, -18, 72},
    {-48, -16, 69},
    {-48, -13, 66},
    {-49, -11, 64},
    {-49, -9, 61},
    {-49, -6, 57},
    {-49, -4, 56},
    {-49, -3, 55},
    {-49, -1, 54},
    {-49, 0, 53},
    {-49, 2, 51},
    {-49, 4, 50},
    {-48, 6, 48},
    {-48, 7, 46},
    {-48, 9, 45},
    {-48, 11, 43},
    {-48, 13, 41},
    {-48, 15, 38},
    {-47, 18, 36},
    {-47, 20, 33},
};

int control = 0;

int maxnum = sizeof(PosArrayA) / sizeof(int) / 3;
int tempval;

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

//=============================================================================//
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

//=============================================================================//

// *** Go to the first position in the array and stop ***

void pattern0()
{
  // initial position for servos

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
//=============================================================================//
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
//=============================================================================//
// *** get the control angles from the array ***

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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////  Main Code  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//===============================================
void setup()
{
  // put your setup code here, to run once:

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

  // initial position for servos

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
  Serial.print(",   shoulder:   ");
  Serial.print(valD1);
  Serial.print(",   elbow:   ");
  Serial.print(valD2);
  Serial.print(",   wrist:   ");
  Serial.println(valD3);

  delay(5000); // waits 5 s for the servo to reach the position
}

//================================================
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
    // *** Not used (for now)
    //    pattern3();
    delay(10);
  }
  else
  {
    // Just sit there and don't move.
    pattern0();
    delay(5000);
  }
}