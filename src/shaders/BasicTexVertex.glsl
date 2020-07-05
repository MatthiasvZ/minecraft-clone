#version 460 core

in vec3 position;
in float lighting;
in float texCoordU;
in float texCoordV;

out float v_Lighting;
out vec2 v_TexCoords;

uniform mat4 u_MVP;

void main()
{
    v_Lighting = lighting;
    v_TexCoords = vec2(texCoordU, texCoordV);

    gl_Position = u_MVP * vec4(position, 1.0);
}
