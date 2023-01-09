#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "iostream"

using namespace std;

int main(){
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Test", NULL, NULL);
	if(window == NULL){
		cout << "Failed to create window" << endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		cout << "failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);

	while(!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}