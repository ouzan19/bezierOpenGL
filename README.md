<html>
<body>
<h1> Interactive Bezier Surface with OpenGL   </h1>

<p> C++ project which renders the given bezier surface and provides interactive editing. <br>

<p> The input specifications are provided in <a href="problem definition.pdf"> problem definition </a>  <br>



<h2> Transformation Mode:  </h2>
<p>This mode allows the program to perform some transformations on the surface object. Func-
tionalities of this mode are given as follows:<br>

<ul style="list-style-type:disc">
<li> Translate: The program allows user to translate the surface object along x, y, and z axes. ’q’
and ’w’ buttons translate the object in -x and +x directions, respectively. ’a’ and ’s’ buttons
translate the object in -y and +y directions, respectively. ’z’ and ’x’ buttons translate the object
in -z and +z directions, respectively. </li>
<li>Rotate: The program allows user to translate the surface object along +y direction. ’r’ button
rotates the surface object in counter clockwise along +y direction and ’t’ button rotates the
surface object in clockwise along +y direction. The surface object rotates around the position
which is the average point of all the sampling points. </li>
</ul>

<h2> Surface Editing Mode:  </h2>

<ul style="list-style-type:disc">
<li>This mode allows the program to change the shape of the surface object by altering the coordi
nates of the control points. When this mode is activated, the control points are also drawn in
the scene with the surface object. </li>
<li>First this mode is activated, the selected control point is the point in (0, 0)th location in the
input file. The selected point is highlighted by assigning a different color than the other control
points so that the control point which is currently selected is distinguished from the other control
points easily.</li>
<li>The arrow keys change selected control points. In other words, the user is able to change currently
selected point by using arrow keys. Control points are given in the input file as M-by-N array.
This mode uses the array locations specified in the input file as control point coordinates. Arrow
keys are used for increment/decrement control point coordinates in order to change selected
control point.</li>
<li>If the selected control point has (i, j) control point coordinates then right and left arrow keys
increment and decrement i value of the selected control point coordinate (row index), respectively.
Similarly, up and down arrow keys increment and decrement j value of the selected control point
coordinate (column index).</li>
<li>Selected control point is translated with the buttons used for object translation in Transforma-
tion Mode. That means, ’q’ and ’w’ buttons translate the selected control point in -x and +x
directions, respectively. ’a’ and ’s’ buttons translate the selected control point in -y and +y
directions, respectively. ’z’ and ’x’ buttons translate the selected control point in -z and +z
directions, respectively. Please note that after modifying the selected control point coordinates,
you should update the surface object with respect to the modification.</li>
<li>Number of sample points is changed by via keyboard input. ’i’ botton decreases row sampling
by dividing its value by two and ’o’ button increases row sampling by multiplying its value by
two (SampleR value from the input file). Similarly, ’k’ botton decreases column sampling by
dividing its value by two and ’l’ button increases column sampling by multiplying its value by
two (SampleC value from the input file).</li>
<li>Please note that mouse event handling is active in both Transformation and Surface Editing
Mode.</li>

</ul>

</html>
</body>