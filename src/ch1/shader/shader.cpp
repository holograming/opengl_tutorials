/*
Shader
 - 
*/

//// Glad 
////  Opengl �ʼ� �Լ����� �����ϴ� ���̺귯��
#include <glad/glad.h>
/// GUI ���̺귯��
#include <GLFW/glfw3.h>

#include <iostream>
#include "shaders.h"
#include "../../common/shader_s.h"

///window ������ ����ɶ����� update�ʿ�.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// Ű�Է�
void processInput(GLFWwindow* window);
GLuint shaderCompile(const GLenum type, const char* code);
GLFWwindow* const renderInit();


void renderLoopMain(GLFWwindow* const window);
/// <summary>
///  Practice list
/// </summary>
void renderLoopEX1(GLFWwindow* const window);
void renderLoopEX2(GLFWwindow* const window);
void renderLoopEX3(GLFWwindow* const window);

int main()
{
	auto window = renderInit();
	if(window)
	{
		renderLoopMain(window);
		//renderLoopEX1(window);
	}
	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resize Event callbak" << std::endl;
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		std::cout << "draw line line" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		std::cout << "draw fill mode" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

GLuint shaderCompile(const GLenum type, const char* code)
{
	unsigned int shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &code, NULL);
	glCompileShader(shader);

	int  success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return 0;
	}
	return shader;
}

GLFWwindow* const renderInit()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//window �ڵ�
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return nullptr;
	}
	/// window�� ���ؽ�Ʈ�� ���� �������� �� ���ؽ�Ʈ�� �����ϰڴٰ� GLFW���� �˷��ݴϴ�.
	glfwMakeContextCurrent(window);

	///GLAD �ʱ�ȭ(opengl �Լ����� ����)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	
	/// ���� �ϴ�(0,0) ������ �����(800,600)
	glViewport(0, 0, 800, 600);
	// resize callback �̺�Ʈ ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}



void renderLoopMain(GLFWwindow* const window)
{
	/*
	 Vertex shader�� ���ؼ� �̾߱��� �� ������ �Է� ������ vertex attribute��� �θ��ϴ�. 
	 �ϵ��� ���� ���ѵǾ� vertex attribute�� ������ �� �ִ� �ִ� ������ ������ �ֽ��ϴ�. 
	 OpenGL�� 4������ ��Ҹ� ���� vertex attribute�� �ּ� 16�������� �����ϰ� �ֽ��ϴ�. ������ ��� �ϵ����� �� ���� ����� �� �� �ֽ��ϴ�.
	 �׿� ���� ������ GL_MAX_VERTEX_ATTRIBS�� ���� �� �� �ֽ��ϴ�.
	*/
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	//-------------------------------------------------------------------------------------------------------------------
	/// shader ����
	
	const auto* vtk = "E:/opengl_tutorials/src/ch1/shader/glsl/vtx.glsl";
	const auto* frg = "E:/opengl_tutorials/src/ch1/shader/glsl/frg.glsl";

	Shader shader(vtk, frg);

	float vertices[] = {
		// ��ġ              // �÷�
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // ���� �ϴ�
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // ���� �ϴ�
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // �� 
	};
	
	unsigned int indices[] = {  // 0���� �����Ѵٴ� ���� ����ϼ���!
		0, 1, 2   // ù ��° �ﰢ��
	};

	// VBO �� ���ؽ� object���� �̸� ������ �ΰ� ����� �� �� �ֵ��� �����ش� ��ü
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/// ���� ���� draw�ƴ�, index drawing�ϱ� ���� ����
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// ��ġ attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); /// layout 0
	// �÷� attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); /// layout 1


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	while (!glfwWindowShouldClose(window))
	{
		// �Է� üũ
		processInput(window);

		// ������
		// colorbuffer ����
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/// Shader ��� ����
		shader.use();
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		/// �ﰢ�� ������
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		/// Ű���� ���콺 �̺�Ʈ �߻����� üũ
		glfwPollEvents();
		/// double ����
		glfwSwapBuffers(window);
	}
}


void renderLoopEX1(GLFWwindow* const window)
{

}

void renderLoopEX2(GLFWwindow* const window)
{

}

void renderLoopEX3(GLFWwindow* const window)
{

}
