#version 330

uniform sampler2DRect particles0;
uniform sampler2DRect particles1;
uniform sampler2DRect particles2;
uniform mat4 modelViewProjectionMatrix;
in vec4  position;
in vec2  texcoord;

out vec2 texCoordFromVertex;
out vec2 vertPosition;

void main()
{
    texCoordFromVertex = texcoord;
    vec3 pos = texture(particles0, texcoord).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(pos, 1.0);
}
