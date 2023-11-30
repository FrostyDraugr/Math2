Hi, this is my math assignment.

Most of the work for this assigment was put into making my own Math Library, JMath which tbh I found to be the most entertaining part of this.

To see all of the assigments working together, simply download the project and open the: BaseMap level found in Content.

The level itself is just an endlessly looping simulation of balls falling down on obstacles.

In the scene 

Assignment 1:
The one I worked the least on, currently it only does a quick check during the collision to see if the collision happend on top of the obstacles.
If that's the case it adds an upward momentum to the falling ball in addition to its new velocity.
Code in BallActor.cpp with comment

Assignment 2:
The obstacles endlessly lerp between two target scale values.
The exact scale values and lerp curve can be set on each obstacle in the scene.
The curves themselves are defined in JMath
Code in Cube.cpp (I know it's not a cube but still)

Assigment 3/4:
Combined the entry since Assignment 4 can't be done without Assigment 3.
Each BallActor checks all the obstacles in the level and get their current radius.
It does an intersection check and then calculates a new Velocity vector if they're
intersecting.
The code only works with Sphere Colliders.
Code in BallActor.cpp

Assignment 5:
When a Ball Actor get's to a certain Z value (Could be an intersection check with a killfield but I hardcoded it) it get's reset.
The new reset positon is altered with a PerlinNoise3D value, the actors death coordinates being the input for the noise.
Code in BallActor.cpp
I also did a quick PerlinNoise curve and BallActor color change depending on noise.
It doesn't work well but it works just as intended.
