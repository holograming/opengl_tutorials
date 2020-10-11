/*
Shader
 - 
*/

//// Glad 
////  Opengl 필수 함수들을 포함하는 라이브러리
#include <glad/glad.h>
/// GUI 라이브러리
#include <GLFW/glfw3.h>

#include <iostream>
#include "shaders.h"
#include "../../common/shader_s.h"

///window 사이즈 변경될때마다 update필요.
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
// 키입력
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

	//window 핸들
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		return nullptr;
	}
	/// window의 컨텍스트를 현재 스레드의 주 컨텍스트로 지정하겠다고 GLFW에게 알려줍니다.
	glfwMakeContextCurrent(window);

	///GLAD 초기화(opengl 함수관련 내용)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return nullptr;
	}
	
	/// 왼쪽 하단(0,0) 오른쪽 상단이(800,600)
	glViewport(0, 0, 800, 600);
	// resize callback 이벤트 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return window;
}



void renderLoopMain(GLFWwindow* const window)
{
	/*
	 Vertex shader에 대해서 이야기할 때 각각의 입력 변수는 vertex attribute라고 부릅니다. 
	 하드웨어에 의해 제한되어 vertex attribute를 선언할 수 있는 최대 갯수가 정해져 있습니다. 
	 OpenGL은 4가지의 요소를 가진 vertex attribute를 최소 16개까지는 보장하고 있습니다. 하지만 어떠한 하드웨어는 더 많이 허용할 수 도 있습니다.
	 그에 대한 정보는 GL_MAX_VERTEX_ATTRIBS를 통해 알 수 있습니다.
	*/
	int nrAttributes;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
	std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;

	//-------------------------------------------------------------------------------------------------------------------
	/// shader 빌드
	
	const auto* vtk = "E:/opengl_tutorials/src/ch1/shader/glsl/vtx.glsl";
	const auto* frg = "E:/opengl_tutorials/src/ch1/shader/glsl/frg.glsl";

	Shader shader(vtk, frg);

	float vertices[] = {
		// 위치              // 컬러
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // 우측 하단
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // 좌측 하단
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f    // 위 
	};
	
	unsigned int indices[] = {  // 0부터 시작한다는 것을 명심하세요!
		0, 1, 2   // 첫 번째 삼각형
	};

	// VBO 등 버텍스 object들을 미리 정의해 두고 사용해 줄 수 있도록 관리해는 객체
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/// 정점 모든걸 draw아닌, index drawing하기 위한 버퍼
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


	// 위치 attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0); /// layout 0
	// 컬러 attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1); /// layout 1


	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);


	while (!glfwWindowShouldClose(window))
	{
		// 입력 체크
		processInput(window);

		// 렌더링
		// colorbuffer 비우기
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/// Shader 사용 선언
		shader.use();
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		//glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
		
		/// 삼각형 렌더링
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		/// 키보드 마우스 이벤트 발생여부 체크
		glfwPollEvents();
		/// double 버퍼
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
