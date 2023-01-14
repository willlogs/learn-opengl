#ifndef HIGINE_ENGINE
#define HIGINE_ENGINE

#include "common.h"
#include "shader/shader.cpp"
#include "shader/shaderProgram.cpp"
#include "texture.cpp"

using namespace std;

class engine
{
private:
	float vertices[32] = {
		// position							// colors								// uv
		0.5f,		0.5f,		0.0f,		1.0f,		0.0f,		0.0f,		0.0,		0.0,
		0.5f,		-0.5f,	0.0f,		0.0f,		1.0f,		0.0f,		1.0,		0.0,
    -0.5f, 	-0.5f, 	0.0f,		0.0f, 	0.0f,		1.0f,		1.0,		1.0,
    -0.5f,	0.5f,		0.0f,		1.0f,		0.0f,		1.0f,		0.0,		1.0
	};

	unsigned int indices[6] = {
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
	}; 

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	unsigned int ebo_id;

	texture test_texture;

	shader vertex_shader, fragment_shader;
	shaderProgram shader_program;

public:
	engine(/* args */);
	~engine();
	int runloop();

	bool isSetup = false;
	GLFWwindow *window;
};

void engine::framebuffer_size_callback(GLFWwindow* window, int width, int height){
	glViewport(0, 0, width, height);
}

engine::engine(/* args */)
{
	// need to initialize glfw
	glfwInit();
	// set hints for the next window that is gonna get created (setup the state of glfw)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// create a window
	window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	if(window == NULL){
		cout << "Failed to create window" << endl;
		glfwTerminate();
	}
	// set the current context to the window
	glfwMakeContextCurrent(window);

	// initialize glad
	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "failed to initialize GLAD" << endl;
	}

	// set viewport
	glViewport(0, 0, 800, 600);
	isSetup = true;

	unsigned int vbo_id;
	glGenBuffers(1, &vbo_id); // create buffer
	
	// vertex array object setup
	unsigned int vao_id;
	glGenVertexArrays(1, &vao_id);
	glBindVertexArray(vao_id);

	// element array object
	glGenBuffers(1, &ebo_id);

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

	// position
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*) 0
	);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void*) (3 * sizeof(float))
	);
	glEnableVertexAttribArray(1);

	// uv
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_FALSE,
		8 * sizeof(float),
		(void *) (5 * sizeof(float)) 
	);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// hookup resize callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// load texture
	test_texture = texture("/Users/willsamadi/dev/openGL/textures/wall.jpeg", GL_RGB);

	// create shaders
	vertex_shader = shader("/Users/willsamadi/dev/openGL/shaders/vertex.glsl", GL_VERTEX_SHADER);
	vertex_shader.compile();
	vertex_shader.check_compilation();

	fragment_shader = shader("/Users/willsamadi/dev/openGL/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
	fragment_shader.compile();
	fragment_shader.check_compilation();

	// create shader program
	shader_program = shaderProgram(&vertex_shader, &fragment_shader);
	glLinkProgram(shader_program.get_id());
	vertex_shader.delete_shader();
	fragment_shader.delete_shader();
}

int engine::runloop(){
	while(!glfwWindowShouldClose(window)){ // listen for close button pusing
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f );
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(shader_program.get_id());
		glBindTexture(GL_TEXTURE_2D, test_texture.get_id());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents(); // listen to events happening (keypress, ...)
	}

	glfwTerminate();
	return 0;
}

engine::~engine()
{

}


#endif