/*
Hello Triangle
 - 3D -> 2D로 변환하는 과정에 대한 이해
 - 주요 shader 이해
 - 그래픽 파이프 라인에 대한 이해
	* 3D-> 2D 변환하는 과정 + 색상을 입히는 과정

	Shader :
		- GPU에서 처리되는 그래픽스 동작
	* Vertex
		- 입력 3D point에 대한 좌표 변환(Model/Proj/ )
		- vertex 속성에 대한 처리
		- points 단위로 처리.
	* Geometry
		- primitive로 처리 하도록 함.
	* Fragment
		- 최종적으로 보여지그 위한 색상 처리
		- 광원/조명/그림자 등
*/


//// Glad 
////  Opengl 필수 함수들을 포함하는 라이브러리
#include <glad/glad.h>
/// GUI 라이브러리
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


///window 사이즈 변경될때마다 update필요.
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	std::cout << "Resize Event callbak" << std::endl;
	glViewport(0, 0, width, height);
}

// 키입력
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

void renderLoop(GLFWwindow* const window)
{
	/// redering 루프
	

	//-------------------------------------------------------------------------------------------------------------------
	/// shader 빌드
	const GLuint vertexShader = shaderCompile(GL_VERTEX_SHADER, vertexShaderSource);
	const GLuint fragmentShader = shaderCompile(GL_FRAGMENT_SHADER, fragmentShaderSource);
	
	/// Shader program
	/// Shader코드를 Shader program이랑 linking 해줘야 사용이 가능함.
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

	///After 링크 이후 shader 객체는 이미 shaderprogram에 넘어감. 필요없음.
	//glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	//-------------------------------------------------------------------------------------------------------------------
	/// shader 빌드
	const GLuint fragmentShader1 = shaderCompile(GL_FRAGMENT_SHADER, fragmentShaderSource1);

	/// Shader program
	/// Shader코드를 Shader program이랑 linking 해줘야 사용이 가능함.
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

	///After 링크 이후 shader 객체는 이미 shaderprogram에 넘어감. 필요없음.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader1);


	/// Shader 코드 링크 완료
	///GPU로 정점 데이터 및 shader 동작에 대한 정의 완료함.
	//-------------------------------------------------------------------------------------------------------------------

	//float vertices[] = {
	//	-0.5f, -0.5f, 0.0f,
	//	 0.5f, -0.5f, 0.0f,
	//	 0.0f,  0.5f, 0.0f
	//};

	//float vertices[] = {
	// 0.5f,  0.5f, 0.0f,  // 우측 상단
	// 0.5f, -0.5f, 0.0f,  // 우측 하단
	//-0.5f, -0.5f, 0.0f,  // 좌측 하단
	//-0.5f,  0.5f, 0.0f   // 좌측 상단
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
	unsigned int indices[] = {  // 0부터 시작한다는 것을 명심하세요!
		0, 1, 3,   // 첫 번째 삼각형
		1, 2, 3    // 두 번째 삼각형
	};

	// VBO 등 버텍스 object들을 미리 정의해 두고 사용해 줄 수 있도록 관리해는 객체
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	unsigned int VBO;
	//VBO에 대한 버퍼 고유 아이디 생성
	glGenBuffers(1, &VBO);
	//VBO GL_ARRAY_BUFFER 형태로 매핑
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	/// vertices를 GL_ARRAY_BUFFER 형태로 바인딩된 VBO 객체에 복사.
		//GL_STATIC_DRAW: 데이터가 거의 변하지 않습니다.
		//GL_DYNAMIC_DRAW: 데이터가 자주 변경됩니다.
		//GL_STREAM_DRAW : 데이터가 그려질때마다 변경됩니다.
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstTriangle), firstTriangle, GL_STATIC_DRAW);

	/// 정점 모든걸 draw아닌, index drawing하기 위한 버퍼
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	/// 정점 및 primitive를 처리하기 위한 속성 정의
	/// primitive : tri
	/// stride : 3 * flot
	/// 시작 pointer 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	///
	unsigned int VAO1;
	glGenVertexArrays(1, &VAO1);
	glBindVertexArray(VAO1);
	unsigned int VBO1;
	//VBO에 대한 버퍼 고유 아이디 생성
	glGenBuffers(1, &VBO1);
	//VBO GL_ARRAY_BUFFER 형태로 매핑
	glBindBuffer(GL_ARRAY_BUFFER, VBO1);
	/// vertices를 GL_ARRAY_BUFFER 형태로 바인딩된 VBO 객체에 복사.
		//GL_STATIC_DRAW: 데이터가 거의 변하지 않습니다.
		//GL_DYNAMIC_DRAW: 데이터가 자주 변경됩니다.
		//GL_STREAM_DRAW : 데이터가 그려질때마다 변경됩니다.
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondTriangle), secondTriangle, GL_STATIC_DRAW);

	/// 정점 모든걸 draw아닌, index drawing하기 위한 버퍼
	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	/// 정점 및 primitive를 처리하기 위한 속성 정의
	/// primitive : tri
	/// stride : 3 * flot
	/// 시작 pointer 0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);


	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	while (!glfwWindowShouldClose(window))
	{
		// 입력 체크
		processInput(window);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glUseProgram(shaderProgram1);
		glBindVertexArray(VAO1);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		/// 키보드 마우스 이벤트 발생여부 체크
		glfwPollEvents();
		/// double 버퍼
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