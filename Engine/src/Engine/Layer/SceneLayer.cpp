#include <iostream>
#include "SceneLayer.h"
#include "Engine/Log/Log.h"
#include "glad/glad.h"
#include "Engine/LowAPI/Renderer/Buffer.h"
#include "Engine/LowAPI/Renderer/VertexArray.h"


namespace Engine
{
	void SceneLayer::OnAttach(Engine::WindowEvents& events)
	{
		float vertices[] = {
		  -0.5f, -0.5f, 0.0f,
		  0.5f, -0.5f, 0.0f,
		  0.5f, 0.5f, 0.0f,
		  0.5f, 0.5f, 0.0f,
		  -0.5f, 0.5f, 0.0f,
		  -0.5f, -0.5f, 0.0f,
		};

		unsigned int VBO;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);


		Ref<VertexBuffer> vb = VertexBuffer::Create(vertices, sizeof(vertices));
		vb->Bind();
		vb->SetLayout({{ ShaderDataType::Float3, "a_position" }});


		unsigned int VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);


		Ref<VertexArray> va = VertexArray::Create();
		va->Bind();
		va->SetVertexBuffer(vb);


		const char* vertexShaderSource = "#version 330 core\n"
										 "layout (location = 0) in vec3 aPos;\n"
										 "void main()\n"
										 "{\n"
										 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
										 "}\0";
		unsigned int vertexShader;
		vertexShader = glCreateShader(GL_VERTEX_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glCompileShader(vertexShader);

		int success;
		char infoLog[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		}


		//FRagment

		const char* fragmentShaderSource = "#version 330 core\n"
										   "out vec4 FragColor;\n"
										   "void main()\n"
										   "{\n"
										   "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
										   "} \0";

		unsigned int fragmentShader;
		fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
		glCompileShader(fragmentShader);

		unsigned int shaderProgram;
		shaderProgram = glCreateProgram();

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
			CORE_ASSERT_LOG(false, "Shader");
		}
		glUseProgram(shaderProgram);
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void SceneLayer::OnDetach(WindowEvents& events)
	{
	}

	void SceneLayer::OnUpdate()
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

}