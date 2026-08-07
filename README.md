*This project was created as part of the 42 curriculum by mmaquine and gabrgarc.*

# miniRT

## Description

miniRT is a small ray tracer written in C.

The program reads a scene from a `.rt` file. It then renders the scene in a
MiniLibX window. The scene uses simple geometric objects, a camera, ambient
light, and point light.

The mandatory version supports:

- Ambient light.
- One camera.
- One point light.
- Spheres.
- Planes.
- Cylinders.
- Ambient and diffuse lighting.
- Hard shadows.
- Correct handling of object intersections, including inside intersections.
- Clean window close with `ESC` or the window close button.

The bonus version adds:

- Several point lights.
- Colored lights.
- Specular light.
- Reflection.
- Checker pattern materials.
- Cone objects.
- Multi-threaded rendering.
- BVH acceleration for fast rendering

## Instructions

### Requirements

This project uses MiniLibX on Linux. You need the X11 development libraries.

On Debian or Ubuntu, install:

```sh
sudo apt install build-essential libx11-dev libxext-dev libbsd-dev zlib1g-dev
```

### Build

Build the mandatory program:

```sh
make
```

Build the bonus program:

```sh
make bonus
```

Remove object files:

```sh
make clean
```

Remove object files and binaries:

```sh
make fclean
```

Rebuild:

```sh
make re
```

### Run

Run the mandatory program with one scene file:

```sh
./miniRT scenes/mandatory/mandatory.rt
```

Run the bonus program with one bonus scene file:

```sh
./miniRT_bonus scenes/bonus/bonus.rt
```

The program accepts only one argument. The argument must be a scene file with
the `.rt` extension.

## Scene File

A scene file uses one element per line. Empty lines are allowed. Fields can use
one or more spaces.

Elements with uppercase identifiers are unique. A valid mandatory scene must
have one ambient light, one camera, and one light.

### Mandatory Elements

Ambient light:

```text
A <ratio> <R,G,B>
```

Camera:

```text
C <x,y,z> <x,y,z orientation> <fov>
```

Light:

```text
L <x,y,z> <brightness> <R,G,B>
```

Sphere:

```text
sp <x,y,z center> <diameter> <R,G,B>
```

Plane:

```text
pl <x,y,z point> <x,y,z normal> <R,G,B>
```

Cylinder:

```text
cy <x,y,z center> <x,y,z axis> <diameter> <height> <R,G,B>
```

### Bonus Scene Rules

Use `make bonus` to build the bonus binary. Then run `miniRT_bonus` with a
bonus `.rt` scene:

```sh
make bonus
./miniRT_bonus scenes/bonus/bonus.rt
```

The bonus parser uses the same mandatory scene rules, with these additions:

- You can define more than one `L` element.
- Light color is used in the render.
- Objects can receive material options after the base color.
- The cone object uses the `co` identifier.

Cone:

```text
co <x,y,z vertex> <x,y,z axis> <angle> <height> <R,G,B> [material options]
```

Cone rules:

- The axis vector must be normalized.
- The angle must be greater than `1.0` and less than `89.0`.
- The height must be positive.

Material options:

```text
c <R,G,B> <scale>
check
r <ratio>
```

Material rules:

- `c` enables a checker pattern with a second color and a scale.
- `check` enables a checker pattern with white as the second color and `1.0` as
  the scale.
- `r` enables reflection.
- The reflection ratio must be in the range `[0.0, 1.0]`.
- The checker scale must be positive.
- Material options are available for `sp`, `pl`, `cy`, and `co`.
- You can combine material options on the same object.

### Value Rules

- Ratios and brightness values must be in the range `[0.0, 1.0]`.
- RGB values must be in the range `[0, 255]`.
- Normal and orientation vectors must use values in the range `[-1.0, 1.0]`.
- The camera FOV must be in the range `[0, 180]`.
- Diameter and height values must be positive.

If the scene has an invalid configuration, the program exits and prints
`Error` followed by a specific error message.

## Examples

Minimal mandatory scene:

```text
A 0.2 255,255,255
C -50,0,20 0,0,1 70
L -40,0,30 0.7 255,255,255
pl 0,0,0 0,1.0,0 255,0,225
sp 0,0,20 20 255,0,0
cy 50.0,0.0,20.6 0,0,1.0 14.2 21.42 10,0,255
```

Bonus material options can be added after an object color:

```text
sp 0,0,20 20 255,0,0 c 255,255,255 1.0 r 0.4
pl 0,-2,0 0,1,0 200,200,200 check
co 4,-2,7 0,1,0 30 4 200,100,50 r 0.2
```

## Project Layout

- `srcs/`: mandatory source files.
- `includes/`: mandatory header files.
- `srcs_bonus/`: bonus source files.
- `include_bonus/`: bonus header files.
- `libft/`: local Libft implementation.
- `minilibx-linux/`: MiniLibX source.
- `scenes/mandatory/`: valid mandatory scenes.
- `scenes/bonus/`: bonus scenes.
- `scenes/error/`: invalid scenes for parser tests.

## Resources

- [Ray Tracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html): a practical introduction to ray tracing.
- [Scratchapixel](https://www.scratchapixel.com/): lessons about ray tracing, geometry, lighting, and rendering.
- [The Ray Tracer Challenge](http://raytracerchallenge.com/): a test-driven book by Jamis Buck.
- STEINBRUCH, Alfredo; WINTERLE, Paulo. **Geometria Analítica**. 2. ed.
  São Paulo: Makron Books, 1987.
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx): reference for the 42 graphics library.

AI was used to help draft and review this README. It was used for technical
writing and subject requirement checks. It was
not used as the only source of truth for the project behavior. The README was
checked against the local source files, scene files, Makefile, and
subject.
