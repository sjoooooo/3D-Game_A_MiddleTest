#version 330 core

// vertex ������ �Է� ��, ���̴��� ���ට���� ���� �ٸ��ϴ�.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// �� ���� �� �Ž������� ������Դϴ�.
uniform mat4 MVP;

void main() {

	// ������ ��� ��ǥ, clip space���� MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}