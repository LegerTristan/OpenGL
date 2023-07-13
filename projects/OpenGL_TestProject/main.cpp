#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void FrameBufferSizeCallback(GLFWwindow* window, int width, int height);
void ProcessInput(GLFWwindow* window);

// Settings
const unsigned int SCREEN_WIDTH = 800,
				   SCREEN_HEIGHT = 600;

int main()
{
	// GLFW : initialization and configuration
	// ----------------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW : window creation
	// -----------------------
	GLFWwindow* _window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "OpenGL_TestProject", NULL, NULL);
	if (_window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, FrameBufferSizeCallback);
	glfwSetWindowTitle(_window, "Fuck this shit !");

	// GLAD : Load all OpenGL function pointers
	// -----------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glfwSetWindowAspectRatio(_window, 16, 9);

	// Render loop
	// ------------
	while (!glfwWindowShouldClose(_window))
	{
		// Handle window inputs
		// ---------------------
		ProcessInput(_window);

		// GLFW : Swap buffers an poll ID events (keys pressed/released, mouse moved etc.)
		// --------------------------------------------------------------------------------
		glfwSwapBuffers(_window);
		glfwPollEvents();

		// Specify the color of the background
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);

		// Clean the back buffer and assign the new color to it.
		glClear(GL_COLOR_BUFFER_BIT);
	}

	// GLFW : Terminate, clearing all previously allocated GLFW resources.
	// --------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

// Process all inputs : query GLFW whether relevant keys are pressed/released this frame 
// and react accordingly
// --------------------------------------------------------------------------------------
void ProcessInput(GLFWwindow* _window)
{
	if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(_window, true);
}

// GLFW : Whenever the window size changed (by OS or user resize) this callback function executes
// -----------------------------------------------------------------------------------------------
void FrameBufferSizeCallback(GLFWwindow* _window, int _width, int _height)
{
	// Make sure the viewport matches the new window dimensions;
	// Note that width and height will be significantly larger than specified on retina displays.
	glViewport(0, 0, _width, _height);
}