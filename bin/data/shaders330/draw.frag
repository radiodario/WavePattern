#version 330

in vec2 Vertex_UV;
out vec4 fragColor;
uniform sampler2D uTexture;

void main()
{
  vec4 spriteTex = texture(uTexture, Vertex_UV.xy);
  //fragColor = vec4(1.0, .7, 1.0, 0.3);
  fragColor = spriteTex * vec4(1.0, .7, 1.0, 0.3);
  fragColor.a = 0.3;
}
