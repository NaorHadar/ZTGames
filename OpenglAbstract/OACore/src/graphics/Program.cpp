#include "ngengine.h"
#include "Program.h"

namespace ngengine {
	namespace graphics {

		void Program::addShader(Shader shader) 
		{
			GLuint shaderID;
			std::string shaderCode;
			std::ifstream shaderFile;

			shaderFile.exceptions(std::ifstream::badbit);

			try
			{
				shaderFile.open(shader.fileLocation);
				std::stringstream shaderStream;
				shaderStream << shaderFile.rdbuf();

				shaderFile.close();

				shaderCode = shaderStream.str();
			}
			catch (std::ifstream::failure e)
			{
				char msg[50];
				sprintf_s(msg, "ERROR:SHADER::FILE_NOT_SUCCESFULLY_READ\n");
				std::cout << msg << std::endl;
			}

			const GLchar* shaderSource = shaderCode.c_str();

			shaderID = glCreateShader(shader.shaderType);
			glShaderSource(shaderID, 1, &shaderSource, nullptr);
			glCompileShader(shaderID);

			GLint success;
			GLchar infoLog[512];

			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
				sprintf_s(infoLog, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s", infoLog);
				std::cout << infoLog << std::endl;
			};

			glAttachShader(program, shaderID);
			glLinkProgram(program);

			glGetProgramiv(program, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(program, 512, NULL, infoLog);
				sprintf_s(infoLog, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s", infoLog);
				std::cout << infoLog << std::endl;
			}

			glDetachShader(program, shaderID);
			glDeleteShader(shaderID);
		}

		void Program::addShaders(std::initializer_list<Shader> shaderList)
		{
			for (Shader shader : shaderList) {
				addShader(shader);
			}
		}
	}
}