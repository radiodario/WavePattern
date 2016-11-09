#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
  ofBackground(0);
  ofSetFrameRate(60);

  receive.setup(5001);
  gui.setup();
  gui.add(emitter1freq.set("emitter1freq", 111.0, 1.0, 600));
  gui.add(emitter2freq.set("emitter2freq", 111.0, 1.0, 600));
  gui.add(emitter3freq.set("emitter3freq", 111.0, 1.0, 600));
  gui.add(emitter1amp.set("emitter1amp", 10.0, 1.0, 1000));
  gui.add(emitter2amp.set("emitter2amp", 10.0, 1.0, 1000));
  gui.add(emitter3amp.set("emitter3amp", 10.0, 1.0, 1000));
  gui.add(camTilt.set("camTilt", 0, -1, 1));
  gui.add(camRoll.set("camRoll", 0, -1, 1));
  gui.add(camPan.set("camPan", 0, -1, 1));
  gui.add(camDolly.set("camDolly", 0, -1, 1));
  gui.add(damping.set("damping", 0.0081, 0, 1));
  // 1,000,000 particles
  unsigned w = 1100;
  unsigned h = 1100;

  drawGui = false;
  particles.init(w, h, OF_PRIMITIVE_POINTS, false, 3);

  particles.loadShaders("shaders330/update", "shaders330/draw");

  // initial positions
  // use new to allocate 4,000,000 floats on the heap rather than
  // the stack
  float wWidth = ofGetWidth() * 1.f;
  float wHeight = ofGetHeight() * 1.f;

  float* particlePosns = new float[w * h * 4];
  for (unsigned y = 0; y < h; ++y)
  {
    for (unsigned x = 0; x < w; ++x)
    {
      unsigned idx = y * w + x;
      particlePosns[idx * 4] = wWidth * x / (float)w - (wWidth/2); // particle x
      particlePosns[idx * 4 + 1] = wHeight * y / (float)h - (wHeight/2); // particle y
      particlePosns[idx * 4 + 2] = 0.f; // particle z
      particlePosns[idx * 4 + 3] = 0.f; // dummy
    }
  }
  particles.loadDataTexture(ofxGpuParticles::POSITION, particlePosns);
  delete[] particlePosns;

  // initial velocities
  particles.zeroDataTexture(ofxGpuParticles::VELOCITY);

  // initial forces
  // cols and rows to calculate how many forces;

  particles.zeroDataTexture(ofxGpuParticles::FORCE);

  // listen for update event to set additonal update uniforms
  ofAddListener(particles.updateEvent, this, &ofApp::onParticlesUpdate);
}

//--------------------------------------------------------------
void ofApp::update()
{
  ofSetWindowTitle(ofToString(ofGetFrameRate(), 2));
  handleOscMessages();
  particles.update();
}

// set any update uniforms in this function
void ofApp::onParticlesUpdate(ofShader& shader)
{
  ofVec3f mouse(ofGetMouseX() - .5f * ofGetWidth(), .5f * ofGetHeight() - ofGetMouseY() , 0.f);
  shader.setUniform3fv("mouse", mouse.getPtr());
  shader.setUniform1f("elapsed", ofGetLastFrameTime());
  shader.setUniform1f("time", ofGetElapsedTimeMillis());
  shader.setUniform1f("radiusSquared", 200.f * 200.f);
  shader.setUniform1f("emitter1freq", emitter1freq);
  shader.setUniform1f("emitter2freq", emitter2freq);
  shader.setUniform1f("emitter3freq", emitter3freq);
  shader.setUniform1f("emitter1amp", emitter1amp);
  shader.setUniform1f("emitter2amp", emitter2amp);
  shader.setUniform1f("emitter3amp", emitter3amp);
  shader.setUniform1f("damping", damping);
  float w = ofGetWidth() * 1.f;
  float h = ofGetHeight() * 1.f;
  ofVec2f resolution(w, h);
  shader.setUniform2fv("resolution", resolution.getPtr());

}

//--------------------------------------------------------------
void ofApp::draw()
{
  cam.begin();
  cam.dolly(camDolly);
  cam.tilt(camTilt);
  cam.pan(camPan);
  cam.roll(camRoll);
  ofEnableBlendMode(OF_BLENDMODE_ADD);
  particles.draw();
  ofDisableBlendMode();
  cam.end();
  if (drawGui) {
    gui.draw();
  }
}

//--------------------------------------------------------------
void ofApp::handleOscMessages() {
  while (receive.hasWaitingMessages()) {
    ofxOscMessage m;
    receive.getNextMessage(&m);
    string msgAddress = m.getAddress();

    //ofLog(OF_LOG_NOTICE, msgAddress + " " + ofToString(m.getArgAsFloat(0)));
    if (msgAddress == "/attack1") {
    }
    if (msgAddress == "/attack2") {
    }
    if (msgAddress == "/attack3") {
    }
    if (msgAddress == "/frequency1") {
      emitter1freq = m.getArgAsFloat(0);
    }
    if (msgAddress == "/frequency2") {
      emitter2freq = m.getArgAsFloat(0);
    }
    if (msgAddress == "/frequency3") {
      emitter3freq = m.getArgAsFloat(0);
    }
    if (msgAddress == "/amplitude1") {
      emitter1amp = m.getArgAsFloat(0) * 1000;
    }
    if (msgAddress == "/amplitude2") {
      emitter2amp = m.getArgAsFloat(0) * 1000;
    }
    if (msgAddress == "/amplitude3") {
      emitter3amp = m.getArgAsFloat(0) * 1000;
    }
  }

}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
  if (key == 'h') {
    drawGui = !drawGui;
  }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
