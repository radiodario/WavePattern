#version 330

layout(points) in;
layout(triangle_strip, max_vertices = 10) out;

in vec2 texCoordFromVertex[];

uniform mat4 projectionMatrix;
uniform float imgWidth, imgHeight;
uniform float size;
out vec2 Vertex_UV;

void main()
{
  vec4 p1, p2, p3, p4;
  vec2 t1, t2, t3, t4;


  vec4 pos_in = gl_in[0].gl_Position;

  p1 = pos_in + vec4(-size, -size, 0.0, 0.0) * projectionMatrix;
  p2 = pos_in + vec4(size, -size, 0.0, 0.0) * projectionMatrix;
  p3 = pos_in + vec4(-size, size, 0.0, 0.0) * projectionMatrix;
  p4 = pos_in + vec4(size, size, 0.0, 0.0) * projectionMatrix;

  t1 = vec2(0, 0);
  t2 = vec2(imgWidth, 0);
  t3 = vec2(imgWidth, imgHeight);
  t4 = vec2(0, imgHeight);

  gl_Position = p1;
  Vertex_UV = vec2(0.0, 0.0);
  EmitVertex();

  gl_Position = p2;
  Vertex_UV = vec2(0.0, 1.0);
  EmitVertex();

  gl_Position = p3;
  Vertex_UV = vec2(1.0, 0.0);
  EmitVertex();

  gl_Position = p4;
  Vertex_UV = vec2(1.0, 1.0);
  EmitVertex();

}
