#version 330 core

out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2DMS screenTexture;

const float offset = 1.0 / 300.0;

void main()
{

    vec2 offsets[9] = vec2[](
    vec2(-offset,  offset), // top-left
    vec2( 0.0f,    offset), // top-center
    vec2( offset,  offset), // top-right
    vec2(-offset,  0.0f),   // center-left
    vec2( 0.0f,    0.0f),   // center-center
    vec2( offset,  0.0f),   // center-right
    vec2(-offset, -offset), // bottom-left
    vec2( 0.0f,   -offset), // bottom-center
    vec2( offset, -offset)  // bottom-right
    );

    float kernel[9] = float[](
    0, 0, 0,
    0, 1, 0,
    0, 0, 0
    );

    vec3 sampleTex[9];
    for(int i = 0; i < 9; i++)
    {
        vec3 s1 = vec3(texelFetch(screenTexture, ivec2((TexCoords + offsets[i]).x * 1200, (TexCoords + offsets[i]).y * 800), 0));
        vec3 s2 = vec3(texelFetch(screenTexture, ivec2((TexCoords + offsets[i]).x * 1200, (TexCoords + offsets[i]).y * 800), 1));
        vec3 s3 = vec3(texelFetch(screenTexture, ivec2((TexCoords + offsets[i]).x * 1200, (TexCoords + offsets[i]).y * 800), 2));
        vec3 s4 = vec3(texelFetch(screenTexture, ivec2((TexCoords + offsets[i]).x * 1200, (TexCoords + offsets[i]).y * 800), 3));
        sampleTex[i] = (s1+s2+s3+s4) / 4;
    }
    vec3 col = vec3(0.0);
    for(int i = 0; i < 9; i++)
    col += sampleTex[i] * kernel[i];

    FragColor = vec4(col, 0);
}