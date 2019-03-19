# Google's cpplint command:
Pass arguments to be modified to functions not as pointers, but as
const reference.
```
cpplint --recursive --filter=-runtime/reference src
```

# Chapter 1: Output an image
I should take a look at the 
[stb_image.h](https://github.com/nothings/stb/blob/master/stb_image.h)
library to support multiple image formats **for free**.

Individual pixels should be "written" to the actual image file after
rendering is done. The details of how the rendered image is written to 
a file, should be encapsulated in a separate function/class.

During rendering, one should have access to an intermediate buffer, 
where pixel information will be stored. This way before outputting the 
final image filtering can also be applied.

I should take a look at ways, how multiple threads can access a such an
intermediate buffer.

# Chapter 2: The Vec3 class
Everything is put inside the Vec3 header file, because Peter Shirley
makes an extensive use of inline functions, and inline functions
could only be implemented inside the header file.

For an operator overload the order of parameters matter, e.g.

```C++
// Following two functions differ
Vec3 operator*(const Vec3 &v, float t)
Vec3 operator*(float t, const Vec3 &v)
```

# Chapter 3: Rays, a simple camera, and background
I had a small and annoying issue, with the *u/v* parameter for
traversing the image plane, namely instead of using division *i / # of
horizontal pixels*, I've did multiplication. Take me some time to find
out this mistake.
I made some extensive notes on how linear interpolation works inside
the `color()`.

# Chapter 4: Adding a sphere
I could practice the math on solving the equation for ray-sphere
intesection. It's really rewarding to solve the whole thing first
on paper and afterwards just to transfer it all into code. That's 
definitely the way I like to program.

Important take-off: **be really careful, when implementing math formula**!

$t0 \neq t1$
```
t0 = (-b - sqrt(discriminant)) / 2.f*a
t1 = (-b - sqrt(discriminant)) / (2.f*a)
```

# Chapter 5: Surface normals and multiple objects
I decided to implement the HitableList not quite as Peter Shirley, but made a
dynamic array of pointers, which was a nice exercise. Abstracting the Sphere
class and the implementation of the Hitable were not so challenging. There is
the thing inside Google's C++ style guide, that (input/output) parameters to
functions should be non-const pointers. See [this](https://stackoverflow.com/a/26441753/2935386).