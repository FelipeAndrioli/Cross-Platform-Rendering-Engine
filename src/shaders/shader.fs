#version 400 core

in vec2 fragCoord;

out vec4 fragColor;

uniform in vec3 iResolution;
uniform in float iTime;

void main() {
    fragColor = vec4(cos(iTime), sin(iTime), 0., 1.);
}
