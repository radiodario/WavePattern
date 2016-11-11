#pragma once

#include "ofMain.h"
#include "ofxGpuParticles.h"
#include "ofxGui.h"
#include "ofxOsc.h"

#define _PROGRAMMABLE_RENDERER

class ofApp : public ofBaseApp{

  public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

  private:
    // set any update uniforms in this function
    void onParticlesUpdate(ofShader& shader);
    void handleOscMessages();
    bool isInCircle(int x, int y, int r) {
      x -= r;
      y -= r;
      float posR = sqrt(x*x + y*y);
      return posR < r;
    }
    ofxGpuParticles particles;
    ofEasyCam cam;

    bool drawGui;

    ofxPanel gui;
    ofParameter<float> emitter1freq;
    ofParameter<float> emitter2freq;
    ofParameter<float> emitter3freq;
    ofParameter<float> emitter1amp;
    ofParameter<float> emitter2amp;
    ofParameter<float> emitter3amp;
    ofParameter<float> damping;
    ofParameter<float> camTilt;
    ofParameter<float> camRoll;
    ofParameter<float> camPan;
    ofParameter<float> camDolly;
	ofParameter<float> amplitudeGain;
	ofParameter<float> frequencyGain;
    ofxOscReceiver receive;
};
