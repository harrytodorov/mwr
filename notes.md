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

