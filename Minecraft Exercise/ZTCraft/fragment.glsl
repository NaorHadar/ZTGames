#version 440 core

in vec4 color_fs;
out vec4 color;

void main(){
	color = color_fs;
}