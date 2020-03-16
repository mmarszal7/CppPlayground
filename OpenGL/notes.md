## OpenGL Concepts:

**OpenGL state machine** - OpenGL works as a state machine which means that you first **configure its state** and then **run it (draw)**<br>
**Front and Back buffers** - back buffer concept allow us to update image befor actually drawing it. If we would draw everything on front buffer we would see "drawing process" - from top-left to bottom-right corner<br>
**Binding** - in OpenGL binding means "selecting" element which you want to configure<br>
**Element id** - all OpenGL components (buffers, shaders, textures etc.) are configured by their ID in GPU memory<br>

---

<p align="center" display="inline" style="font-size:21px">
<a src="/minimalExample.cpp">Here</a> is a code for a minimal OpenGL setup
</p>

**Vertex** (plural Vertices) - data structure with information like position, color, normal vectors etc. each of this information is called **attribure**<br>
**Vertex input** - sending data (vertices) from CPU to GPU (from C++ code to shaders):

- **Workflow** (see [minimalExample](minimalExample.cpp)) - to send data to GPU you need to:
  - define place in memory for you vertices - **Object Buffers (VOB)**
  - decribe how to read your data (attribures) from this place (attribure id, overall vertex size, attribure type, place in vertex where attribure starts) - **Attribure Pointers (VAP)**
  - create VAO - OpenGL specific thing for linking VOBs with VAPs - **Vertex Array Object (VAO)**
  - define how to make shape of your vertices - **Element Buffer Objects (EBO)**
- **VBO** - Vertex Buffer Object - name might be a little bit misleading but its just representation of some space in memory
- **VAP** - Vertex Attribure Pointer - describes how to read VBO - where are attribures and how to read them (how big are they, what type etc.)
- **VAO** - Vertex Array Object - used for configuring VBOs with their VAPs descriptions
- **EBO** - Element Buffer Object - (not actually part of this workflow) its job is to make bigger shapes from single vertices. Because GPU works on triangles it means that to make a bigger shape you need to define each triangle separetly. EBOs allow you to save VBO space by defining shapes by indexes (from Vertices in VBO) instead of defining whole shapes in VBOs:

  ```c++
  // For square we have:
  float vertices[] = {
  0.5f, 0.5f, 0.0f, // top right
  0.5f, -0.5f, 0.0f, // bottom right
  -0.5f, -0.5f, 0.0f, // bottom left
  -0.5f, 0.5f, 0.0f // top left
  };
  unsigned int indices[] = {
  0, 1, 3, // first triangle
  1, 2, 3 // second triangle
  };

  // Instead of
  float vertices[] = {
   0.5f,  0.5f, 0.0f,  // first triangle
   0.5f, -0.5f, 0.0f,  //
  -0.5f, -0.5f, 0.0f,  //

  -0.5f,  0.5f, 0.0f,  // second triangle
  -0.5f, -0.5f, 0.0f,  // duplicated 3rd vertex
   0.5f,  0.5f, 0.0f   // duplicated 1st vertex
  };
  ```

  - it has even bigger impact when your vertex is bigger that only xyz

---

**Shaders** - programs running on GPU. Typical workflow for working with shaders:

- write shader
- create shader object and compile it
- create shader program
- attach all shaders to this program
- link program
- delete shaders

**Vertex shader** - _(runs for every vertex in VBO)_ - based on vertex properties (e.g. position) + external conditions (e.g. camera position) calculates vertex position on a screen<br>
**Fragment shader** - _(runs for every pixel)_ - based on material properties (e.g. basic color) + external conditions (e.g. lightning) calculates color of each pixel
<br>\* because it runs for every pixel sometimes its cheaper to make some calculations inside vertex shader which for big triangle runs 3 instead of e.g. 50k times<br>
**Attribute** - each vertex shader input<br>
**Uniform** - each fragment shader input<br>

---

## Resources:

https://learnopengl.com/Introduction
https://glad.dav1d.de/#profile=core&language=c&specification=gl&loader=on&api=gl%3D4.6
