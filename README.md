# miniRT
The goal of this program is to generate images using the Raytracing protocol. 
Those computer-generated images will each represent a scene, as seen from a specific angle and position, defined by simple geometric objects, and each with its own lighting system.


## Arguments
A scene in format `*.rt`

## Allowed functions

- open, close, read, write, printf, malloc, free, perror, strerror, exit
- All functions of the math library (`-lm man man 3 math`)
- All functions of the MinilibX

## Notes to make develop easier

### Program explaination

1. Parse data and error handling
2. Initialize camera
3. Raycast. Throw a ray from every pixel of the screen to our parsed scene or world. 
We transform the X,Y window coordinates to our world coordinates, and we create a ray 
from the camera position pointing to the infinite in the camera direction.

> Rays are an abstraction with 2 vectors, that represent an origin point and a
direction. A direction is a normalized vector, a vector that has a lenght of 1.
They also have a struct for color, that has 3 integers, one for each color channel.

4. Hit the world. We iterate over the object list and check if our ray collides with 
any object, creating a t_hit object.

> Hits are another abstraction with 2 vectors, a float t, an object pointer and a
color. The vectors are the point in which the ray collided with our object, and
the normal of the surface it hit. The most important thing here is the t value, that
represents the depth of the hit object, has any point in a line can be represented
like **P = origin + t * direction**. It also stores a reference to the object that it
hit, being NULL if it didn't hit anything.

5. Calculate shading. If the ray we traced from the camera to the world hit something,
we have to trace another ray from the hit point to the point of light, if we hit
another object, there is shade at that point.

