compile: gcc bmp.c canvas.c  

Very very simple raytracer draws a sphere on the screen with one light source.
The code really needs some serious cleaning and tidying.?.  
  
 Goal: Do the steps described here: https://github.com/ssloy/tinyraytracer/wiki/Part-1:-understandable-raytracing
 
idea:
 - need an add_sphere function. Adds a sphere to a global tree which sorts the spheres in POV closeness.
 - render_scene function which creates the bmp file.
 - add_pov function which adds the point of view of the scene.
 - add_sol function which adds a source of light to the scene.
  - multiple objects, spheres? need a tree that can point to any object that can be placed in the world
  - multiple sols? i think light intensities should add up, more thought on that later and that sols should be stored in a different tree.   
  - Integrate CMOCK and UNITY.

