# Intro

This is a github repository originally published by Tristan Lee. Pretty much none of this work is fully mine. I'll try to fill out any credits as they come up. Most of the code I think is based on the textbook in our robotics class. Please feel free to add more info to this document as necessary.

The uploaded matlab and arduino code are both for my personal hexapod robot. You will likely have to adjust initial positions and make sure servo designations align with those I've set up.


# Contributors

Advisor: Dr. Hakes

Contributors: Tristan Lee, Connor O'Keefe, Seth VanMatre


# Info

The main code can be found in the source (src) folder in this repository. It's meant to run in Visual Studio Code with the PlatformIO extension on an Arduino Mega 2560. You can use this platform to upload to both Github and Arduino in one spot. I'm still learning it myself, so not everything will be perfect, and you may have to look up a tutorial if unfamiliar. The main differences from the basic arduino IDE are that the functions and variables must be defined in order, and there's much better error handling and feedback. If you want to upload from the basic arduino IDE, just copy and paste the whole code (everything but "#include <Arduino.h>") into an empty arduino document and upload as normal.

The MATLAB code can be opened directly from your local copy of this repository. After saving, version control can be done easily from here.


Servos are labeled as defined below (They need to be relabeled on the hexapod
from the way they were, THE LABELS ON THE HEXAPOD MAY NOT FIT THESE YET.)

 A  FRONT  F
 B         E
 C   REAR  D


I'd like to implement the inverse kinematics into this arduino code rather than relying on outside generated arrays but I'm not sure how to go about this. Doing this would allow for more complex motions. 

Adding a gyroscope would then allow for adjusting to steep inclines.

Should the hexapod have a 'front'? Turning the front toward the direction of movement just results in more opportunities to catch on things. Maybe the hexapod should be able strafe along the ground instead.


One possibility is a tilt sensor attached to the chassis of the hexapod maybe paired with a sensor on the tip of each foot which can sense pressure or some other indicator that it is touching the ground, allowing many complex tasks like:

-Self-calibration: no more dealing with foot tips not making full contact,
evening the load between servos,

-More complex balancing: it would be able to tell when it is tipping and
which feet are the problem, as well as being able to feel if it has a
foothold (maybe),

-The ability to determine when it is stuck: It would be able to tell when a
foot is making contact when it shouldn't or vice versa. When it gets
especially stuck, it may also be able to stand on its back four legs
and feel out any obstacles close to the ground with its front two legs. It
could rely on an ultrasonic sensor for anything higher up.

-Detecting missing limbs; Not really useful for us, but it could adapt its
gait based on whether it has lost a limb as long as it can tell.

These sensors could be pressure sensors (maybe a spring and potentiometer,
not sure), buttons (probably too fragile), or even IR distance sensors.


An ultrasonic sensor facing downward may be useful for telling distance from
the ground.


Several gaits would be useful to have access to such as:

-Tripod: classic hexapod gait. Three legs swing forward while the other three support and move the body forward. Statically stable, reliable, baseline speed. Most generally useful. [Source](https://hexapodrobots.weebly.com/types-of-robot-gait.html)

-Quadruped: Two (probably) symmetric legs swing forward while the other four support and move the body forward. Very stable but of course slower than tripod. Likely would be useful to have for feeling out the terrain with the two front feet. [Source](https://hexapodrobots.weebly.com/types-of-robot-gait.html)

-One-by-one: Extremely slow but stable. One leg swings forward at a time as the body inches forward with the other five legs. Could be useful for very difficult terrain but is probably overkill. [Source](https://hexapodrobots.weebly.com/types-of-robot-gait.html)                                        ^

-One-by-one but better: This is ripple (and wave) gait. These gaits move multiple legs at a time, but each starts moving offset from the others and the speed can be changed to ensure a good balance of speed and stability. Ripple gait also has a significant cool factor and is very spidery. [Source](https://hackaday.io/project/21904-hexapod-modelling-path-planning-and-control/log/62326-3-fundamentals-of-hexapod-robot)

-All: Effectively belly-flopping. All six legs swing forward at once and then all six legs move the body forward. Maybe useful for ice or something. Probably not. Definitely funny anyways. If the servos are fast enough, this may be used to jump, though it definitely would not be fast enough to catch itself if it's jumping forward and would just slam.

-Bipod: 'Faster than nature.' Only two legs are on the ground at once. This is very fast, but is NOT statically stable. As long as the hexapod is on flat ground, it should be able to run using this gait relying on dynamic stability. [Source](https://youtu.be/QZt3eJzHLSU?si=h863vg1OPpXfI5gd) [Source](https://youtu.be/DKsyJYkdZ_o?si=HSgxqJErNcM0EqTi)


I've also been looking at this guys hexapod project on youtube. His stuff isn't perfectly applicable to our situation (mostly because his hexapod is not autonomous) but he's uploaded all his code and talks a bit about the process on his channel. I haven't taken the time needed to decipher enough to pull the necessary parts into this project, but maybe something in his code will save us a lot of time. [YouTube](https://www.youtube.com/@AecertRobotics) [GitHub](https://github.com/Ryan-Mirch/Aecerts_Hexapod_V1)


# Useful Links:

[GitHub Pages](https://pages.github.com/).

[Some hexapod gaits](https://hexapodrobots.weebly.com/types-of-robot-gait.html).

[Some fundamentals of hexapod gaits](https://hackaday.io/project/21904-hexapod-modelling-path-planning-and-control/log/62326-3-fundamentals-of-hexapod-robot).

["Six-Legged Robots Faster Than Nature-Inspired Gait"](https://youtu.be/QZt3eJzHLSU?si=h863vg1OPpXfI5gd).

[Visual and applicable gaits](https://youtu.be/DKsyJYkdZ_o?si=HSgxqJErNcM0EqTi).

[This guy does some hexapod stuff](https://www.youtube.com/@AecertRobotics).

[Non-autonomous hexapod stuff](https://github.com/Ryan-Mirch/Aecerts_Hexapod_V1).



