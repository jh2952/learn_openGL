#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>

// Forward Declerations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Source Code
const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
	"}\0";

// Set Vertices
float vertices[] =
{
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

int main()
{
	constexpr int monitorWidth = 800;
	constexpr int monitorHeight = 600;
	
	// Initialize GLFW. Configure GLFW using glfwWindowHint(target, hint);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a Window Object.
	GLFWwindow* window = glfwCreateWindow(monitorWidth, monitorHeight, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window\n";
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD\n";
		return -1;
	}

	// Create a Viewport
	glViewport(0, 0, monitorWidth, monitorHeight);

	// This function is used to set a callback function that will be
	// invoked whenever the size of the framebuffer (rendering area)
	// is changed.
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Create Vertex Shader
	unsigned int vertexShader; // Assign Memory for vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // Create vertex shader in that memory
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL); // replace the source code assigned to vertexShader with vertexShaderSource
	glCompileShader(vertexShader); // Dynamically Compile that Shader

	// Create Fragment Shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	unsigned int VBO; // Instantiate location to store vertex buffer object Id
	glGenBuffers(1, &VBO); // Generate VBO id and store it in VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO); // Bind VBO type to GL_ARRAY_BUFFER. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); // Set our vertices data into the the buffer bound to GL_ARRAY_BUFFER.
	
	// Create a Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0); // Specify how the vertex shader should interpret the vertex data
	glEnableVertexAttribArray(0); 

	// Create Shader Program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// Render Loop
	while (!glfwWindowShouldClose(window)) //i.e., while the user has *not* requested that 'window' be closed
	{
		processInput(window);
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // Set the clear Buffer Colour
		glClear(GL_COLOR_BUFFER_BIT);         // Clear the buffer
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window); // Swap front and back buffer frames
		glfwPollEvents();        // Process events and update window accordingly.
	}

	// End Program
	glfwTerminate();
	return 0;
}

// Window re-sizing callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// Handle user key input
void processInput(GLFWwindow* window)
{
	// If the Esc key in the window 'window' has been pressed
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
