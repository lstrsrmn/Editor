#version 120

varying vec2 texCoord0;
varying vec3 normal0;

uniform sampler2D diffuse;
uniform vec3 directionalLightDirection;
uniform vec4 ambient;
uniform vec4 colour;

void main() {
    gl_FragColor = texture2D(diffuse, texCoord0) * colour
    * clamp(dot(-directionalLightDirection, normal0), 0.0, 1.0) + ambient;
}