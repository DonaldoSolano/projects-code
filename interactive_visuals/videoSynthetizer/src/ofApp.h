#pragma once

#include "ofMain.h"
#include "ofxGui.h"
//#include ""
class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void stripePattern();
	void matrixPattern();
	void draw2d();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	void audioIn(float *input, int bufferSize, int nChannels);
	void exit();

	float soundLevel;

	ofxPanel gui;
	ofxIntSlider countX;
	ofxFloatSlider stepX;
	ofxFloatSlider twistX;

	ofxIntSlider countY;
	ofxFloatSlider stepY, twistY, pinchY;

	ofxGuiGroup globalGroup;
	ofxFloatSlider Scale;
	ofxFloatSlider Rotate;
	ofxFloatSlider Background;

	ofxGuiGroup primGroup;
	ofxFloatSlider shiftY, rotate;
	ofxVec2Slider size;
	ofxColorSlider color;
	ofxToggle filled, type;

	ofxGuiGroup mixerGroup;
	ofxFloatSlider imageAlpha, videoAlpha, cameraAlpha;

	bool showGui;

	ofTexture image;

	ofVideoPlayer video;

	ofVideoGrabber camera;

	ofFbo fbo;

	ofSoundPlayer sound;

	ofShader shader;
	ofxToggle kenabled;
	ofxIntSlider ksectors;
	ofxFloatSlider kangle, kx, ky;

	ofxToggle automate;
};
