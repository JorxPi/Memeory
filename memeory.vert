#version 330 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTex;

out vec2 TexCoords;

uniform float scale = 1.0;
uniform mat4 model;
uniform mat4 proj;

uniform float t;

void main()
{
   float scaleFactor = 1.0 + sin(t) * 0.2;  // Scale factor with sinusoidal motion
   gl_Position = proj * model * vec4(aPos * scaleFactor, 0.0, 1.0);
   TexCoords = aTex;
}