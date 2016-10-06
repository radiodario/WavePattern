#version 330

// ping pong inputs
uniform sampler2DRect particles0;
uniform sampler2DRect particles1;

uniform vec3 mouse;
uniform float radiusSquared;
uniform float elapsed;

in vec2 texCoordVarying;

layout(location = 0) out vec4 posOut;
layout(location = 1) out vec4 velOut;

void main()
{
    vec3 pos = texture(particles0, texCoordVarying.st).xyz;
    vec3 vel = texture(particles1, texCoordVarying.st).xyz;

    // mouse attraction
    vec3 direction = mouse - pos.xyz;
    float distSquared = dot(direction, direction);
    float magnitude = 500.0 * (1.0 - distSquared / radiusSquared);
    vec3 force = step(distSquared, radiusSquared) * magnitude * normalize(direction);

    // second attractor in (0.1, 0.9)
    vec3 attrPos = vec3(0.0, 0.0, 0.0);
    vec3 dir2 = attrPos - pos.xyz;
    float distSq = dot(dir2, dir2);
    float radius2sq = 2000. * 2000.;
    float mag = (sin(elapsed * 10)*500.0) * (1.0 - distSq / radius2sq);
    force += step(distSq, radius2sq) * mag * normalize(dir2);

    // gravity
    force += vec3(0.0, -0.5, 0.0);

    // accelerate
    vel += elapsed * force;

    // bounce off the sides
    vel.x *= step(abs(pos.x), 512.0) * 2.0 - 1.0;
    vel.y *= step(abs(pos.y), 384.0) * 2.0 - 1.0;

    // damping
    //vel *= 0.999995;

    // move
    pos += elapsed * vel;

    posOut = vec4(pos, 1.0);
    velOut = vec4(vel, 0.0);
}
