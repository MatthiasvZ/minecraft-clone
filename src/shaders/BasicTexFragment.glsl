#version 460 core

in float v_Lighting;
in vec2 v_TexCoord;

out vec4 outColor;

uniform sampler2D tex;

void main()
{
    outColor = texture(tex, v_TexCoord) * vec4(v_Lighting, v_Lighting, v_Lighting, 1.0f);
}
