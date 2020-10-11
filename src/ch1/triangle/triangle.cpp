/*
Hello Triangle
 - 3D -> 2D�� ��ȯ�ϴ� ������ ���� ����
 - �ֿ� shader ����
 - �׷��� ������ ���ο� ���� ����
	* 3D-> 2D ��ȯ�ϴ� ���� + ������ ������ ����

	Shader :
		- GPU���� ó���Ǵ� �׷��Ƚ� ����
	* Vertex
		- �Է� 3D point�� ���� ��ǥ ��ȯ(Model/Proj/ )
		- vertex �Ӽ��� ���� ó��
		- points ������ ó��.
	* Geometry
		- primitive�� ó�� �ϵ��� ��.
	* Fragment
		- ���������� �������� ���� ���� ó��
		- ����/����/�׸��� ��
*/


//// Glad 
////  Opengl �ʼ� �Լ����� �����ϴ� ���̺귯��
#include <glad/glad.h>
/// GUI ���̺귯��
#include <GLFW/glfw3.h>

#include <iostream>


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n\0";

const char* fragmentShaderSource1 = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(1.0f, 0.f, 0.f, 1.0f);\n"
"}\n\0";


///window ������ ����ɶ����� update�ʿ�.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resize Event callbak" << std::endl;
	glViewport(0, 0, width, height);
}

// Ű�Է�
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

void renderLoop(GLFWwindow* const window)
{
	/// redering ����
	

	//-------------------------------------------------------------------------------------------------------------------
	/// shader ����
	const GLuint vertexShader = shaderCompile(GL_VERTEX_SHADER, vertexShaderSource);
	const GLuint fragmentShader = shaderCompile(GL_FRAGMENT_SHADER, fragmentShaderSource);
	
	/// Shader program
	/// Shader�ڵ带 Shader program�̶� linking ����� ����� ������.
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	char infoLog[512];
		
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "glShaderProgramingLnk Error : \n" << infoLog << std::endl;
		return;
	}

	///After ��ũ ���� shader ��ü�� �̹� shaderprogram�� �Ѿ. �ʿ����.
	//glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//-------------------------------------------------------------------------------------------------------------------
	/// shader ����
	const GLuint fragmentShader1 = shaderCompile(GL_FRAGMENT_SHADER, fragmentShaderSource1);

	/// Shader program
	/// Shader�ڵ带 Shader program�̶� linking ����� ����� ������.
	unsigned int shaderProgram1;
	shaderProgram1 = glCreateProgram();
	glAttachShader(shaderProgram1, vertexShader);
	glAttachShader(shaderProgram1, fragmentShader1);
	glLinkProgram(shaderProgram1);

	glGetProgramiv(shaderProgram1, GL_LINK_STATUS, &success);

	if (!success) {
		glGetProgramInfoLog(shaderProgram1, 512, NULL, infoLog);
		std::cout << "glShaderProgramingLnk Error : \n" << infoLog << std::endl;
		return;
	}

	///After ��ũ ���� shader ��ü�� �̹� shaderprogram�� �Ѿ. �ʿ����.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);


	/// Shader �ڵ� ��ũ �Ϸ�
	///GPU�� ���� ������ �� shader ���ۿ� ���� ���� �Ϸ���.
	//-------------------------------------------------------------------------------------------------------------------

	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//};

	//float vertices[] = {
	// 0.5f,  0.5f, 0.0f,  // ���� ���
	// 0.5f, -0.5f, 0.0f,  // ���� �ϴ�
	//-0.5f, -0.5f, 0.0f,  // ���� �ϴ�
	//-0.5f,  0.5f, 0.0f   // ���� ���
	//};

	float firstTriangle[] = {
		  -0.9f, -0.5f, 0.0f,  // left 
		  -0.0f, -0.5f, 0.0f,  // right
		  -0.45f, 0.5f, 0.0f,  // top 
	};
	float secondTriangle[] = {
		0.0f, -0.5f, 0.0f,  // left
		0.9f, -0.5f, 0.0f,  // right
		0.45f, 0.5f, 0.0f   // top 
	};
	unsigned int indices[] = {  // 0���� �����Ѵٴ� ���� ����ϼ���!
		0, 1, 3,   // ù ��° �ﰢ��
		1, 2, 3    // �� ��° �ﰢ��
	};

	// VBO �� ���ؽ� object���� �̸� ������ �ΰ� ����� �� �� �ֵ��� �����ش� ��ü
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	//VBO�� ���� ���� ���� ���̵� ����
	glGenBuffers(1, &VBO);
	//VBO GL_ARRAY_BUFFER ���·� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/// vertices�� GL_ARRAY_BUFFER ���·� ���ε��� VBO ��ü�� ����.
		//GL_STATIC_DRAW: �����Ͱ� ���� ������ �ʽ��ϴ�.
		//GL_DYNAMIC_DRAW: �����Ͱ� ���� ����˴ϴ�.
		//GL_STREAM_DRAW : �����Ͱ� �׷��������� ����˴ϴ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	/// ���� ���� draw�ƴ�, index drawing�ϱ� ���� ����
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	/// ���� �� primitive�� ó���ϱ� ���� �Ӽ� ����
	/// primitive : tri
	/// stride : 3 * flot
	/// ���� pointer 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	///
	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	unsigned int VBO1;
	//VBO�� ���� ���� ���� ���̵� ����
	glGenBuffers(1, &VBO1);
	//VBO GL_ARRAY_BUFFER ���·� ����
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	/// vertices�� GL_ARRAY_BUFFER ���·� ���ε��� VBO ��ü�� ����.
		//GL_STATIC_DRAW: �����Ͱ� ���� ������ �ʽ��ϴ�.
		//GL_DYNAMIC_DRAW: �����Ͱ� ���� ����˴ϴ�.
		//GL_STREAM_DRAW : �����Ͱ� �׷��������� ����˴ϴ�.
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	/// ���� ���� draw�ƴ�, index drawing�ϱ� ���� ����
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	/// ���� �� primitive�� ó���ϱ� ���� �Ӽ� ����
	/// primitive : tri
	/// stride : 3 * flot
	/// ���� pointer 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		// �Է� üũ
		processInput(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/// Ű���� ���콺 �̺�Ʈ �߻����� üũ
		glfwPollEvents();
		/// double ����
		glfwSwapBuffers(window);
	}
}

int main()
{
	auto window = renderInit();
	if(window)
	{
		renderLoop(window);
	}
	
	glfwTerminate();
	return 0;
}