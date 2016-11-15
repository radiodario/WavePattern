#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
#ifdef _PROGRAMMABLE_RENDERER
  ofGLFWWindowSettings settings;
  settings.setGLVersion(4, 1);
  settings.width = 1920;
  settings.height = 1200;
  //settings.windowMode = OF_FULLSCREEN;

  ofCreateWindow(settings);
#else
  ofAppGlutWindow window;
  ofSetupOpenGL(&window, 1920,1080, OF_WINDOW);
#endif
  ofRunApp(new ofApp());
}
