#pragma once

#include "utils\Size.h"
#include "Dependencies\GLEW\include\GL\glew.h"
#include "Dependencies\GLFW\include\GLFW\glfw3.h"

namespace ngengine {
	namespace app {
		class Window {
		public:
			Window(const std::string&, utils::Size2D);
			~Window();
			
		public:
			void createWindow();
			void makeContext();
			inline bool shouldClose() const { return glfwWindowShouldClose(windowHandler) != 0; };
			void updateWindow();
			void showWindow();
			utils::Size2D getSize();

		public:
			inline std::string getTitle() const { return windowTitle; }
			inline utils::Size2D getSize() const { return windowSize; }
			void setTitle(const std::string&);

		private:
			static void _onResizeCallback(GLFWwindow*, int, int);

		private:
			std::string windowTitle;
			utils::Size2D windowSize;
			GLFWwindow* windowHandler;
		};
	}
}