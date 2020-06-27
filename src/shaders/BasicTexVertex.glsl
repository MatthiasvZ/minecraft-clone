#version 460 core

in vec3 position;
in vec2 texCoord;

out vec2 v_TexCoord;

uniform mat4 u_MVP;
uniform float u_Time;

void main()
{
    v_TexCoord = texCoord;

    //gl_Position = u_MVP * vec4(position * 0.25 * (sin(u_Time) + 4.0f), 1.0);
    gl_Position = u_MVP * vec4(position, 1.0);
}
