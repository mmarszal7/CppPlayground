#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <iostream>

#include "Shader.h"
#include "Camera.h"
#include "Texture.h"
#include "Renderer.h"
#include "Setup.cpp"

int main()
{
	Camera camera((glm::vec3(0.0f, 0.0f, 3.0f))); // camera must be initialized before window because its needed for user input

	GLFWwindow* window = setupGLFW(camera);

	Renderer renderer("resources/lighting.vert", "resources/lighting.frag");
	renderer.LoadCubeWithLighting();

	// Lamp
	Renderer lampRenderer("resources/lightSource.vert", "resources/lightSource.frag");
	lampRenderer.LoadCubeWithTexture();

	glm::vec3 lightPosition = glm::vec3(1.2f, 1.0f, 2.0f);
	glm::mat4 lightModel = glm::translate(glm::mat4(1.0f), lightPosition);
	lightModel = glm::scale(lightModel, glm::vec3(0.2f));

	while (!glfwWindowShouldClose(window))
	{
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Cube
		glm::mat4 model = glm::rotate(glm::mat4(1.0f), glm::radians(50.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		glm::mat4 view = camera.getViewMatrix();
		glm::mat4 projection = glm::perspective(glm::radians(camera.getFOV()), 800.0f / 600.0f, 0.1f, 100.0f);

		renderer.Draw(model, view, projection);

		// Lighting
		Shader shader = renderer.GetShader();
		shader.setVec3("lightPosition", lightPosition);
		shader.setVec3("viewPos", camera.getCameraPosition());
		shader.setVec3("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.setVec3("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
		shader.setVec3("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
		shader.setFloat("material.shininess", 32.0f);

		// Lamp
		lampRenderer.Draw(lightModel, view, projection);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}
