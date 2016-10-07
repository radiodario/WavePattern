#version 330

uniform mat4 modelViewProjectionMatrix;
uniform sampler2DRect particles0;
uniform sampler2DRect particles1;

in vec4  position;
in vec2  texcoord;

out vec2 texCoordVarying;
out vec2 vertPosition;

void main()
{
    texCoordVarying = texcoord;
    gl_Position = modelViewProjectionMatrix * vec4(texture(particles0, texCoordVarying).xyz, 1.0);
    vertPosition = gl_Position.xy;
}
