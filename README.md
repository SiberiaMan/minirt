# Mini Ray-Tracing
![alt text](https://github.com/SiberiaMan/Images/blob/master/minirt/Screenshot%20from%202021-08-27%2012-41-08.png)
###### Warning! Works only on Mac OS!
## Desription
A simple ray-tracing school 21 project. Supports following features:  
-Shadows  
-Ambient light   
-Rotation and moving of camera in parse-file  

Geometric shapes supported by the program:  
-Sphere  
-Square  
-Triangle  
-Cylinder  
-Plane  

## How to use
Run `make` in a directory, you will get an executable `minirt` file. So you can choose a scene in the following way:  
```
./minirt /path/to/scene/filename.rt
```
To get a screenshot of the selected scene:  
```
./minirt /path/to/scene/filename.rt --save
```
or press `W` while viewing a scene  
> Some scenes with a correct syntax are located in the directory
## Syntax of .rt file
+ Resolution:
  + `R` `1920` `1080`
  + Identifier: `R`
  + Screen width
  + Screen height
</br></br>
+ Ambient lightning:
  + `A` `0.2` `255,255,255`
  + Identifier: `A`
  + Ambient lighting ratio in range [0.0,1.0].
  + RGB colors in range [0-255].
</br></br>
+ Camera:
  + `c` `-50,0,20` `0,0,1` `70`
  + Identifier: `c`
  + x,y,z coordinates of the view point.
  + View direction vector.
  + FOV : Horizontal field of view in degrees in range [0,180].
</br></br>
+ Light:
  + `l` `-45,50,0` `0.6` `10,0,255`
   + Identifier: `l`
   + x,y,z coordinates of the light point.
   + The light brightness ratio in range [0.0,1.0].
   + RGB colors in range [0-255].
</br></br>
+ Sphere:
  + `sp` `0,0,20.6` `12.6` `10,0,255` `0.4`
  + Identifier: `sp`
  + x,y,z coordinates of the sphere center.
  + The sphere diameter.
  + RGB colors in range [0-255].
</br></br>
+ Plane:
  + `pl` `0,0,-10` `0,0.5,0` `0,0,225` `0.4`
  + Identifier: `pl`
  + x,y,z coordinates.
  + 3d normalized orientation vector. In range [-1,1] for each x,y,z axis.
  + RGB colors in range [0-255].
</br></br>
+ Square:
  + `sq` `0,0,20.6` `1,0,0` `12.6` `255,0,255` `0.4`
  + Identifier: `sq`
  + x,y,z coordinates of the square center.
  + 3d normalized orientation vector. In range [-1,1] for each x,y,z axis.
  + Side size.
  + RGB colors in range [0-255].
</br></br>
+ Cylinder:
  + `cy` `50,0,20.6` `0,0,1` `10,0,255` `14.2` `21.42` `0.4`
  + Identifier: `cy`
  + x,y,z coordinates of the cylinder center.
  + 3d normalized orientation vector. In range [-1,1] for each x,y,z axis.
  + The cylinder diameter.
  + The cylinder height.
  + RGB colors in range [0-255].
</br></br>
+ Triangle:
  + `tr` `10,20,10` `10,10,20` `20,10,10` `0,0,255` `0.4`
  + Identifier: `tr`
  + x,y,z coordinates of the first point.
  + x,y,z coordinates of the second point.
  + x,y,z coordinates of the third point.
  + RGB colors in range [0-255].
## Example  
Top picture  
```
l 0,0,-7 0.4 0,0,0  
l 0,0,3 0.8 0,0,0  
l 0,0,9 0.7 0,0,0  
l 0,10,0 0,4 0,0,0  
l 0,10,0 0.5 0,0,0  

A 0.3 255,0,0  
  
R 500 500  
  
c 8,0,8 0,1,0 90  
c 0,0,8 1,1,0 90  
c 0,0,-7 -1,-1,0 120  
  
pl 0,0,-8 0,0,1 48,0,59  
pl 0,-3,0  0,1,0 12,189,231  
pl 0,0,10 0,0,1 90,69,90  
  
sq 0,0,0 0,0,1 8 45,98,198  
cy 0,0,0 1,1,0 0,0,100 2 10  
cy 0,0,0 -1,1,0 100,0,0 2 10  
cy 0,0,0 0,0,1 0,100,0 2 10  
  
cy 4,0,0 0,1,0 0,255,0 0.9 20  
cy -4,0,0 0,1,0 0,255,0 0.9 20  
  
sp 0.4,0,4 0.6 255,255,255  
sp -1,0,5 0.4 255,255,255  
sp 0.4,0,6 0.3 255,255,255  
sp 0.4,0,7 0.3 255,255,255  
sp -0.4,1,6 0.3 255,255,255  
sp 0.5,0.7,6 0.3 0,255,255  
  
tr  -3,4,0 0,8,0 3,4,0 120,230,120  
```
