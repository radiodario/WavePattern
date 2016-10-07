#version 330

in vec2 vertPosition;
out vec4 fragColor;

void main()
{
  vec2 m = gl_FragCoord.xy - vertPosition.xy;

    fragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
