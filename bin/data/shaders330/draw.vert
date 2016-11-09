#version 330

uniform mat4 modelViewProjectionMatrix;
uniform sampler2DRect particles0;
uniform sampler2DRect particles1;
uniform sampler2DRect particles2;

in vec4  position;
in vec2  texcoord;

out vec2 texCoordVarying;
out vec2 vertPosition;

void main()
{
    texCoordVarying = texcoord;
    vec3 pos = texture(particles0, texCoordVarying).xyz;
    vec3 vel = texture(particles1, texCoordVarying).xyz;
    gl_Position = modelViewProjectionMatrix * vec4(texture(particles0, texCoordVarying).xyz, 1.0);
    vec3 force = texture(particles2, pos.xy).xyz;
    gl_PointSize = clamp((length(vel.xy) / 50.0), 1.0, 2.0);
    vertPosition = vel.xy;
}
