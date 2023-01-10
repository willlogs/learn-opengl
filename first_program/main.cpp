#include "iostream"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace std;

const char *vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
  "FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\0";

int main(){
	// need to initialize glfw
	glfwInit();
	// set hints for the next window that is gonna get created (setup the state of glfw)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// create a window
	GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	if(window == NULL){
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return -1;
	}
	// set the current context to the window
	glfwMakeContextCurrent(window);

	// initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "failed to initialize GLAD" << endl;
		return -1;
	}

	// set viewport
	glViewport(0, 0, 800, 600);

	// setup triangle
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	unsigned int vbo_id;
	glGenBuffers(1, &vbo_id); // create buffer
	
	// vertex array object setup
	unsigned int vao_id;
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	glBindBuffer(
		GL_ARRAY_BUFFER,
		vbo_id
	); // bind buffer to context (only a single buffer can be bound to each type)
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(vertices),
		vertices,
		GL_STATIC_DRAW
	); // fill in the buffer (this will fill vbo as that's what's bound to array_buffer)

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		(void*) 0
	);
	glEnableVertexAttribArray(0);

	// create shaders
	unsigned int vertexShader, fragmentShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER); // create empty vertex shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER); // create empty fragment shader
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(vertexShader);
	glCompileShader(fragmentShader);

	// check compile status
	int  success;
	char infoLog[512];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
    glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if(!success)
	{
    glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// create shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// main loop of the program
	while(!glfwWindowShouldClose(window)){ // listen for close button pusing
		glUseProgram(shaderProgram);
		glBindVertexArray(vao_id);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents(); // listen to events happening (keypress, ...)
	}

	// release resources
	glfwTerminate();
	return 0;
}