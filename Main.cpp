#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

//Testing upload

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

int main()
{
	//Initialize GLFW
	glfwInit();
	

	//Tell GLFW what we are using
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Form vertices for our triangle
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f // Upper corner
	};

	//Form Window
	GLFWwindow* window = glfwCreateWindow(800, 800, "OPENGL basics", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW Window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//Add window to context
	glfwMakeContextCurrent(window);

	//Load Glad so it configured OpenGL
	gladLoadGL();

	//Specify the viewport of OpenGl in the window
	glViewport(0, 0, 800, 800);

	//Make our vertex shader and form machine code
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//make the fragment shader and form machine code
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//form overall shader program to be applied by attaching our shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	//wrap it up by linking our shaders
	glLinkProgram(shaderProgram);

	//remove unnecessary shader objects
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	//Create reference containers for the Vertex Array Object (VAO) and Vertex Buffer Object (VBO)
	GLuint VAO, VBO;
	
	//Generate each with 1 object
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	//Make the VAO the current object by binding it
	glBindVertexArray(VAO);

	//Bind the VBO by specifying that it is a GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//Introduce the vertices into the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//configure the vertex attribute so that OpenGl knows how to read the VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//Enable our attribute so that OpenGL knows how to use it
	glEnableVertexAttribArray(0);

	//Bind the VBO and VAO to 0 so that we dont accidentally modify them
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Background color specification
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

	//clean buffer and assign new color to it
	glClear(GL_COLOR_BUFFER_BIT);

	//swap the buffers of front and back graphics
	glfwSwapBuffers(window);

	//Main while loop
	while (!glfwWindowShouldClose(window))
	{
		//Speficy color
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		//Clean buffer
		glClear(GL_COLOR_BUFFER_BIT);
		//Tell OPENGl what shaders we want to use
		glUseProgram(shaderProgram);
		//Bind the VAO so OpenGL knows to use it
		glBindVertexArray(VAO);
		//Draw the triangles via GL primitive
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//swap the front and back buffer
		glfwSwapBuffers(window);
		//Take care of all GLFW events
		glfwPollEvents();
	}

	//delete objects
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	//Clean up window and glfw process
	glfwDestroyWindow(window);
	glfwTerminate();

	//great success
	return 0;
}