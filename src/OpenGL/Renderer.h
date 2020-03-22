#ifndef RENDERER_H
#define RENDERER_H

#include <glad\glad.h>
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"

#include <vector>
#include "Model.h"
using namespace std;

class Renderer
{
public:
	Renderer(const char* vertexPath, const char* fragmentPath) :
		shader(vertexPath, fragmentPath), mesh(), gameModel() {	}

	void LoadCubeWithTexture()
	{
		float vertices[] = {
			// positions          // colors           // texture coords
			 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left 

			 0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 0.0f, // top right
			 0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 1.0f, // bottom right
			-0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f, // bottom left
			-0.5f,  0.5f, 0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f  // top left 
		};

		unsigned int indices[] = {
			0, 1, 3, 1, 2, 3, // bottom
			4, 5, 6, 6, 7, 4, // top
			0, 1, 5, 5, 4, 0, // right
			2, 3, 6, 6, 7, 3, // left
			0, 3, 7, 7, 4, 0, // back
			1, 2, 6, 6, 1, 5  // front
		};

		vector<Vertex> meshVertices;
		for (size_t i = 0; i < sizeof(vertices) / sizeof(float) / 8; i++)
			meshVertices.emplace_back(glm::vec3(vertices[8 * i + 0], vertices[8 * i + 1], vertices[8 * i + 2]), glm::vec3(vertices[8 * i + 3], vertices[8 * i + 4], vertices[8 * i + 5]), glm::vec2(vertices[8 * i + 6], vertices[8 * i + 7]), glm::vec3(), glm::vec3());

		vector<unsigned int> meshIndices(indices, indices + sizeof indices / sizeof indices[0]);

		TextureLoader textureLoader("resources/container.jpg");
		vector<Texture> textures = { Texture(textureLoader.ID, "texture_normal", "resources/container.jpg") };

		Mesh newMesh(meshVertices, meshIndices, textures);
		mesh = newMesh;
	}

	void LoadCubeWithLighting()
	{
		float vertices[] = {
			// positions          // normals           // texture coords
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
			 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,

			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,

			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,

			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,

			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
			 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
			-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
			-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
		};

		// Batch rendering
		vector<Vertex> vec;
		int const objects = 1.0f;
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		for (int ii = 0; ii < objects; ii++)
		{
			for (int j = 0; j < objects; j++)
			{
				for (int k = 0; k < objects; k++)
				{
					for (size_t i = 0; i < sizeof(vertices) / sizeof(float) / 8; i++)
						if (y == 0 || y == objects - 1 || z == 0 || z == objects - 1 || x == 0 || x == objects - 1)
							vec.emplace_back(glm::vec3(vertices[8 * i + 0] + x, vertices[8 * i + 1] + y, vertices[8 * i + 2] + z), glm::vec3(vertices[8 * i + 3], vertices[8 * i + 4], vertices[8 * i + 5]), glm::vec2(vertices[8 * i + 6], vertices[8 * i + 7]), glm::vec3(), glm::vec3());
					x++;
				}
				x = 0;
				y++;
			}
			y = 0;
			z++;
		}

		vector<unsigned int> ind;

		vector<Texture> textures;
		TextureLoader textureLoader("resources/container.jpg");
		textures.emplace_back(textureLoader.ID, "texture_normal", "resources/container.jpg");

		Mesh newMesh(vec, ind, textures);
		mesh = newMesh;
	}

	void LoadModel()
	{
		drawFromModel = true;

		Model model("resources/nanosuit/nanosuit.obj");
		gameModel = model;
	}

	void Draw(glm::mat4 model, glm::mat4 view, glm::mat4 projection)
	{
		if (drawFromModel != NULL)
			gameModel.Draw(shader);
		else
			mesh.Draw(shader);

		shader.use(model, view, projection);
	}

	Shader GetShader() { return shader; }

private:
	Shader shader;
	Mesh mesh;
	Model gameModel;
	bool drawFromModel = false;
};
#endif