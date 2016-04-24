#version 330 core

layout(location = 0) in vec3 vert;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 color;

//Xpos Ypos Zoom AspectRatio
uniform vec4 CAM;

uniform mat4 MVP;//No in use

out vec3 VERTCOLOR;
out vec2 UV;
void main()
{
	VERTCOLOR = color;
	//gl_Position = MVP * vec4(vert,1);

	
	gl_Position = vec4((vert.xz - CAM.xz) / (vert.y - CAM.y),0,1);
	gl_Position.x = 0-gl_Position.x * CAM.w;

	UV = vertexUV;
}