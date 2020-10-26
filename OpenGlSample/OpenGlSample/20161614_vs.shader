#version 330 core

// vertex 데이터 입력 값, 쉐이더의 실행때마다 값이 다릅니다.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

// 이 값은 한 매쉬동안은 상수적입니다.
uniform mat4 MVP;

void main() {

	// 정점의 출력 좌표, clip space에선 MVP * position
	gl_Position = MVP * vec4(vertexPosition_modelspace, 1);

	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}