#version 330

#define SPEED_OF_SOUND 50
#define TWO_PI 6.28318530718

// ping pong inputs
uniform sampler2DRect particles0;
uniform sampler2DRect particles1;
uniform sampler2DRect particles2;

uniform vec2 resolution;
uniform vec3 mouse;
uniform float radiusSquared;
uniform float elapsed;
uniform float time;
uniform float emitter1freq;
uniform float emitter2freq;
uniform float emitter3freq;
uniform float emitter1amp;
uniform float emitter2amp;
uniform float emitter3amp;
uniform float damping;

in vec2 texCoordVarying;

layout(location = 0) out vec4 posOut;
layout(location = 1) out vec4 velOut;
layout(location = 2) out vec4 forceOut;

vec3 bowlSound(vec3 partPos, vec3 attrPos, float radius, float freq, float amp) {
  vec3 force = vec3(0.);
  vec3 direction = partPos.xyz - attrPos;
  float dist = distance(attrPos, partPos);
  //float mag = (sin((time-timeBack) / freq) * amp) * (1.0 - distSq / radiusSq);
  float f = 10000 / freq;
  float t = int(time);// % int(freq);
  float mag = sin(time) * sin((dist)*TWO_PI/f) * amp;
  force += mag * normalize(direction);
  return force;
}

float rand(float n){return fract(sin(n) * 43758.5453123);}

// update the force grid;
vec3 updateForce() {
  vec2 forcePos = texCoordVarying.st;


  vec3 force = vec3(0.);//texture(particles2, forcePos).xyz;
  force += bowlSound(
      vec3(forcePos, -1. + rand(elapsed)),
      vec3(500, 600., 0.),
      100.0,
      emitter1freq,// * sin(time*0.001) + 200.0,
      emitter1amp
      );

  force += bowlSound(
      vec3(forcePos, -1. + rand(elapsed)),
      vec3(250., 400., 0.),
      100.,
      emitter2freq,// * sin(time*0.0001) + 200.0,
      emitter2amp
      );

  force += bowlSound(
      vec3(forcePos, -1. + rand(elapsed)),
      vec3(750., 400., 0.),
      100.,
      emitter3freq,//220.0 * sin(time*0.001) + 200.0,
      emitter3amp
      );

//  force = vec3(
//      rand(time * dist) * 500,
//      rand(time * dist) * 500,
//      0.);

  return force;
}

vec3 getForceForParticle(vec3 pos) {
  vec2 forceIndex = vec2(
      1000 * (pos.x + resolution.x * 0.5)/resolution.x,// * 0.5 + 0.5; // texture coordinates basically
      1000 * (pos.y + resolution.x * 0.5)/resolution.x
    );
  return texture(particles2, forceIndex).xyz;
}

void main()
{

    vec3 pos = texture(particles0, texCoordVarying.st).xyz;
    vec3 vel = texture(particles1, texCoordVarying.st).xyz;
    vec3 force = getForceForParticle(pos);
    //vec3 force = vec3(0.);

    // accelerate
    vel += elapsed * force;

    // bounce off the sides
    vel.x *= step(abs(pos.x), resolution.x/2) * 2.0 - 1.0;
    vel.y *= step(abs(pos.y), resolution.y/2) * 2.0 - 1.0;

    // damping
    vel *= 1 - damping;

    // move
    pos += elapsed * vel;

    posOut = vec4(pos, 1.0);
    velOut = vec4(vel, 0.0);
    forceOut = vec4(updateForce(), 0.0); //vec4(updateForce(force.xy, fidx), 0.0);
}
