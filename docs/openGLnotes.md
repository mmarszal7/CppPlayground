## OpenGL Concepts ([minimal setup](minimalExample.cpp)):

**OpenGL state machine** - OpenGL works as a state machine which means that you first **configure its state** and then **run it (draw)**<br>
**Front and Back buffers** - back buffer concept allow us to update image befor actually drawing it. If we would draw everything on front buffer we would see "drawing process" - from top-left to bottom-right corner<br>
**Binding** - in OpenGL binding means "selecting" element which you want to configure<br>
**Element id** - all OpenGL components (buffers, shaders, textures etc.) are configured by their ID in GPU memory<br>

---

**Vertex** (plural Vertices) - data structure with information like position, color, normal vectors etc. each of this information is called **attribure**<br>
**Vertex input** - sending data (vertices) from CPU to GPU (from C++ code to shaders):

- **Workflow** (see [minimalExample](minimalExample.cpp)) - to send data to GPU you need to:
  - define place in memory for you vertices - **Object Buffers (VOB)**
  - decribe how to read your data (attribures) from this place (attribure id, overall vertex size, attribure type, place in vertex where attribure starts) - **Attribure Pointers (VAP)**
  - create VAO - OpenGL specific thing for linking VOBs with VAPs - **Vertex Array Object (VAO)**
  - define how to make shape of your vertices - **Element Buffer Objects (EBO)**
- **VBO** - Vertex Buffer Object - name might be a little bit misleading but its just representation of some space in memory
- **VAP** - Vertex Attribure Pointer - describes how to read VBO - where are attribures and how to read them (how big are they, what type etc.)
    <p align="center" display="inline"> 
    <img width="500px" src="https://learnopengl.com/img/getting-started/vertex_attribute_pointer_interleaved_textures.png"/>
    </p>
- **VAO** - Vertex Array Object - used for configuring VBOs with their VAPs descriptions
- **EBO** - Element Buffer Object - (not actually part of this workflow) its job is to make bigger shapes from single vertices. Because GPU works on triangles it means that to make a bigger shape you need to define each triangle separetly. EBOs allow you to save VBO space by defining shapes by indexes (from Vertices in VBO) instead of defining whole shapes in VBOs:

  ```c++
  // For square we have:
  float vertices[] = {
  0.5f, 0.5f, 0.0f,     // top right
  0.5f, -0.5f, 0.0f,    // bottom right
  -0.5f, -0.5f, 0.0f,   // bottom left
  -0.5f, 0.5f, 0.0f     // top left
  };
  unsigned int indices[] = {
  0, 1, 3,              // first triangle
  1, 2, 3               // second triangle
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

**[Shaders](../src/OpenGL/Shader.h)** - programs running on GPU. Typical workflow for working with shaders:

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

## [Transformations](https://learnopengl.com/Getting-started/Coordinate-Systems):

In order to create the final scene we transform original vertices throught several **coordinate systems**:

- Local - move parts of object, rotate it, move it in certain direction
- World - move object in the world
- View - move world
- Clip - cut world according to fustum (orthographic or perspective)
- Screen space

<p align="center" display="inline"> 
<img width="500px" src="https://learnopengl.com/img/getting-started/coordinate_systems.png"/>
</p>

Process of converting vertices throught all those coordinate systems is called **MVP** (model-view-projection) = model position/angle + camera position/angle + field of view<br>

```cpp
// Model
glm::mat4 model = glm::mat4(1.0f);
model = glm::translate(model, glm::vec3(1.0f, 0.0f, 0.0f));
model = glm::rotate(model, glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
model = glm::scale(model, glm::vec3(0.2f));

// View - Camera
glm::vec3 cameraPosition = glm::vec3(3.0f, 2.0f, 0.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 yAxis = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 view = glm::lookAt(cameraPosition, cameraTarget, yAxis);

// Projection
float fov = 45.0f;
glm::mat4 projection = glm::perspective(glm::radians(fov), 800.0f / 600.0f, 0.1f, 100.0f);
```

In every of those transformations between **coordinate systems** we are using 3 main types of matrix operations:

<p align="center" display="inline"> 
<img width="500px" src="transformations.png"/>
</p>

---

## [Lighting](https://www.youtube.com/watch?v=7CdS8oOJtVA):

**Phong lightning model** - one of lighting models that consists 3 main parts: **ambient, diffuse and spectral** lighting. <br>In this model we assume that all light can be presented by sum of: "passive" light (ambient), light reflected in all directions (diffuse) and light reflected in your/watcher direction (specular).
<br>\*This model is not the best model but its relatively easy to implement, understand and it looks good which is enough for computer graphics("if it looks good, it's good") <br>

1. **Ambient** - simulates "passive" lighting, lighting when there is not clear light source (e.g. dark room at night) - mathematically presented as a constant value throughout a scene<br>

   <img height="30px" src="ambientFormula.png"/>
    
    ---

2. **Diffuse** - simulates reflection in all directions - mathematically presented as **cos** between the light source and the surface/vertex normal vector</br>

   <div style="float: left; width:100%">
   <div style="box-sizing: border-box; float: left; width: 50%; padding: 15px;">
   <img src="diffuse.png"/>
   </div>
   <span><b>Although</b> because calculating cosine is an expensive operation more often we calculate a dot procuct of unit vectors:</span>
   <div style="box-sizing: border-box; float: left; width: 50%; padding: 15px;">
   <img src="dotProduct.png"/>
   </div>
   <br>
   <span>And because this cosine cannot be lower than 0 (there is not light below surface) final formula looks like this:</span>
   <br>
   <div align="center" display="inline" style="box-sizing: border-box; float: left; width: 50%; padding: 5px;">
   <img height="40px" src="diffuseFormula.png"/>
   </div>
   </div>
   <span style="color: white;">.</span>

   ***

3. **Specular** - simulates reflection in a single/watcher direction (shiny look) - mathematically presented as a dot procuct between an angle of the light source reflection and the viewer

<p align="center" display="inline"> 
   <img width="800px" src="specularFormula.png"/>
</p>

---

4. **Summary**

    ```cpp
    // diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(light.position - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    
    // specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.  shininess);
    
    // Light * material
    vec3 ambient  = light.ambient  * material.ambient;
    vec3 diffuse  = light.diffuse  * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);
    
    vec3 result = ambient + diffuse + specular;
    ```
    
    To calculate "lighting" in general you need to calculate sum of     all relations between light sources and materials:
    
    <p align="center" display="inline"> 
    <img width="400px" src="finalFormula.png"/>
    </p>

---

## Resources:

- https://learnopengl.com/Introduction
- Lighting - https://www.youtube.com/watch?v=7CdS8oOJtVA
- Glad generator - https://glad.dav1d.de/#profile=core&language=c&specification=gl&loader=on&api=gl%3D4.6
