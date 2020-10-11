/*
목표 
 - 기본적인 윈도우 컨트롤 동작 이해
 - 키입력, 리사이즈 이벤트 등 이벤트를 처리하기 위한 동작 이해
 - 렌더링 로직 정의 및 확인하기
*/


//// Glad 
////  Opengl 필수 함수들을 포함하는 라이브러리
#include <glad/glad.h>
/// GUI 라이브러리
#include <GLFW/glfw3.h>

#include <iostream>

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
}

int main()
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
		glfwTerminate();
		return -1;
	}
	/// window의 컨텍스트를 현재 스레드의 주 컨텍스트로 지정하겠다고 GLFW에게 알려줍니다.
	glfwMakeContextCurrent(window);

	///GLAD 초기화(opengl 함수관련 내용)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	/// 왼쪽 하단(0,0) 오른쪽 상단이(800,600)
	glViewport(0, 0, 800, 600);
	// resize callback 이벤트 등록
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/// redering 루프
	/// 
	while (!glfwWindowShouldClose(window))
	{
		// 입력 체크
		processInput(window);
		
		// 렌더링 추가
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		///glClearColor로 설정한 값을 glClear 단계에서 clear한다.
		glClear(GL_COLOR_BUFFER_BIT);

		/// 키보드 마우스 이벤트 발생여부 체크
		glfwPollEvents();
		/// double 버퍼
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}