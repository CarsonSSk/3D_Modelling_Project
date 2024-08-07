#version 330 core
layout(location = 0) in vec3 aPos;
uniform mat4 transform;
uniform float aspectRatio;

void main() {
    vec3 scaledPos = aPos;
    scaledPos.y /= aspectRatio;
    gl_Position = transform * vec4(scaledPos, 1.0);
}
