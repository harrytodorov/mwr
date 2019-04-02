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

# Chapter 6: Antialiasing
The implementation of antialiasing, that P. Shirley propeses in this chapter
was not really challenging to implement. The only thing, that took me some time
was to decide how to abstract the random number genrator, and not use drand48()
always, cause it's a bit annoying to have to always do some math tricks to
make it such, that it can suit your needs. But I'm pretty happy of the way I did
it, cause I've used it over and over for the following chapters, without
having to think twice about ranges.
There are also different antialiasing techniques, which are worth revisiting.
Plus, one topic, which is probalby as important, as the way one chooses to have
its random points, namely which filter to use to produce the final pixel value.
There seems to be quite nice article about it, which seems to be worth the time
reading. [This](http://www.reedbeta.com/blog/antialiasing-to-splat-or-not/) one!

# Chapter 7: Diffuse materials
This chapter took me a bit of time to figure it out. Because of the way it was
laid down. I surely got a bit confused, but it also helped me, to find out
2 cool places online: [place 1](http://viclw17.github.io/) and [place 2](https://karthikkaranth.me/blog/generating-random-points-in-a-sphere/).
Here are my handwritten notes on the topic:
![difuse material, handwritten notes](diffuse_materials.jpg)

The chapter also mentioned two important concepts: gamma correction and
shadow bias (also called shadow acne).

# Chapter 8: Metal
The implementation of different materials forced the author to think about
of implementing materials as an _abstract_ class.
Which for the first time made me realize, in C++ an instance of an abstract
class should always be on the heap, should be a pointer! How can otherwise the
compiler would know how much space the instance would take. So that was
important take away from this chapter.
Peter Shirley do not really goes in the physics of explaining how a metal
scatters the light, just uses some tricks to make it look viable.
A nice thing, I could do was to practice a bit my linear algebra and derive
the normal vector.
One thing to notice here is that for the computation of the reflection vector
$r$, $n$ could also point "downwards" and the computation of $r$ would still
be valid. As well as the vector $i$ is not forced to be normalized. But one
has to keep in mind, that $|r| = |i|$. $n$ on the other hand should be
normalized.

__Input__:
* $i$: incident light ray
* $n$: normal at the hit point

__Output__:
* $r$: reflectcion of $i$

Let $ b = n \cdot i $, the projection of $i$ onto $n$. Then $r$ can be computed
easily:
$$ r = i - 2*b*n$$

![difuse material, handwritten notes](reflection_vector.jpg)

# Chapter 9: Dialectics
Pfff... This chapter was the toughest for me... I haven't count the number
of times, where I should correct my code, and it still does not produce
correct images of a dialectic. So here I want to go once more step by step
through the whole procedure, and look at the different components in details
and with examples.
