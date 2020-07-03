#version 460 core

in vec3 position;
in float lighting;
in vec2 texCoord;

out float v_Lighting;
out vec2 v_TexCoord;

uniform mat4 u_MVP;

void main()
{
    v_Lighting = lighting;
    v_TexCoord = texCoord;

    gl_Position = u_MVP * vec4(position, 1.0);
}
