/*
��ǥ 
 - �⺻���� ������ ��Ʈ�� ���� ����
 - Ű�Է�, �������� �̺�Ʈ �� �̺�Ʈ�� ó���ϱ� ���� ���� ����
 - ������ ���� ���� �� Ȯ���ϱ�
*/


//// Glad 
////  Opengl �ʼ� �Լ����� �����ϴ� ���̺귯��
#include <glad/glad.h>
/// GUI ���̺귯��
#include <GLFW/glfw3.h>

#include <iostream>

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
}

int main()
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
		glfwTerminate();
		return -1;
	}
	/// window�� ���ؽ�Ʈ�� ���� �������� �� ���ؽ�Ʈ�� �����ϰڴٰ� GLFW���� �˷��ݴϴ�.
	glfwMakeContextCurrent(window);

	///GLAD �ʱ�ȭ(opengl �Լ����� ����)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}


	/// ���� �ϴ�(0,0) ������ �����(800,600)
	glViewport(0, 0, 800, 600);
	// resize callback �̺�Ʈ ���
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/// redering ����
	/// 
	while (!glfwWindowShouldClose(window))
	{
		// �Է� üũ
		processInput(window);
		
		// ������ �߰�
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		///glClearColor�� ������ ���� glClear �ܰ迡�� clear�Ѵ�.
		glClear(GL_COLOR_BUFFER_BIT);

		/// Ű���� ���콺 �̺�Ʈ �߻����� üũ
		glfwPollEvents();
		/// double ����
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}