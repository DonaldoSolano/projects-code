#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetWindowTitle("Video synth");
	ofSetWindowShape(1280, 720);
	ofSetFrameRate(60);
	ofBackground(ofColor::white);
	ofSetFullscreen(true);

	gui.setup("Parameters", "settings.xml");
	gui.add(countX.setup("countX", 50, 0, 200));
	gui.add(stepX.setup("stepX", 20, 0, 200));
	gui.add(twistX.setup("twistX", 5, -45, 45));

	gui.add(countY.setup("countY", 0, 0, 50));
	gui.add(stepY.setup("stepY", 20, 0, 200));
	gui.add(twistY.setup("twistY", 0, -30, 30));
	gui.add(pinchY.setup("pinchY", 0, 0, 1));

	globalGroup.setup("Global");
	globalGroup.add(automate.setup("automate", true));
	globalGroup.add(Scale.setup("Scale", 1, 0.0, 1));
	globalGroup.add(Rotate.setup("Rotate", 0, -180, 180));
	globalGroup.add(Background.setup("Background", 255, 0, 255));
	gui.add(&globalGroup);

	primGroup.setup("Primitive");
	primGroup.add(shiftY.setup("shiftY", 0.0, -1000.0, 1000.0));
	primGroup.add(rotate.setup("rotate", 0.0, -180.0, 180.0));
	primGroup.add(size.setup("size", ofVec2f(6, 6), ofVec2f(0, 0), ofVec2f(20, 20)));
	primGroup.add(color.setup("color", ofColor::black, ofColor(0, 0, 0, 0), ofColor::white));
	primGroup.add(filled.setup("filled", false));
	primGroup.add(type.setup("type", false));
	gui.add(&primGroup);

	mixerGroup.setup("Mixer");
	mixerGroup.setHeaderBackgroundColor(ofColor::darkRed);
	mixerGroup.setBorderColor(ofColor::darkRed);
	mixerGroup.add(imageAlpha.setup("image", 100, 0, 255));
	mixerGroup.add(videoAlpha.setup("video", 200, 0, 255));
	mixerGroup.add(cameraAlpha.setup("camera", 100, 0, 255));
	shader.load("kaleido");
	mixerGroup.add(kenabled.setup("kenabled", true));
	mixerGroup.add(ksectors.setup("ksectors", 10, 1, 100));
	mixerGroup.add(kangle.setup("kangle", 0, -180, 180));
	mixerGroup.add(kx.setup("kx", 0.5, 0, 1));
	mixerGroup.add(ky.setup("ky", 0.5, 0, 1));
	gui.minimizeAll();
	gui.add(&mixerGroup);

	gui.loadFromFile("settings.xml");

	ofLoadImage(image, "collage.jpg");

	video.loadMovie("flowing.mp4");
	video.play();

	showGui = true;

	sound.loadSound("nightcall.mp3");
	sound.setVolume(0.8);
	sound.setLoop(true);

	soundLevel = 0;
	ofSoundStreamSetup(0, 1, 44100, 128, 4);

	fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
}

//--------------------------------------------------------------
void ofApp::update() {
	ofSoundUpdate();
	video.update();
	if (camera.isInitialized()) camera.update();

	if (automate) {
		float *spectrum = ofSoundGetSpectrum(128);
		double level = 0;
		for (int i = 0; i < 128; i++) {
			level += spectrum[i] * spectrum[i];
		}
		level = sqrt(level / 128);
		level += soundLevel;
		float newRad = ofMap(level, 0, 1, 0.5, 1, true);
		Scale = Scale + 0.1 * (newRad - Scale);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	fbo.begin();
	draw2d();
	fbo.end();
	ofSetColor(255);
	if (kenabled) {
		shader.begin();
		shader.setUniform1i("ksectors", ksectors);
		shader.setUniform1f("kangleRad", ofDegToRad(kangle));
		shader.setUniform2f("kcenter", kx*ofGetWidth(), ky*ofGetHeight());
		shader.setUniform2f("screenCenter", 0.5*ofGetWidth(), 0.5*ofGetHeight());
	}
	fbo.draw(0, 0, ofGetWidth(), ofGetHeight());
	if (kenabled) shader.end();
	if (showGui) gui.draw();
}

//--------------------------------------------------------------
void ofApp::audioIn(float *input, int bufferSize,
	int nChannels) {
	double v = 0;
	for (int i = 0; i < bufferSize; i++) {
		v += input[i] * input[i];
	}
	v = sqrt(v / bufferSize);
	soundLevel = v;
}

//--------------------------------------------------------------
void ofApp::stripePattern() {
	ofSetColor(color);
	ofSetLineWidth(1);
	if (filled) ofFill(); else ofNoFill();
	for (int i = -countX; i <= countX; i++) {
		ofPushMatrix();
		ofTranslate(i * stepX, 0);
		ofRotate(i * twistX);
		ofTranslate(0, shiftY);
		ofRotate(rotate);
		ofScale(size->x, size->y);
		if (type) ofRect(-50, -50, 100, 100);
		else ofTriangle(0, 0, -50, 100, 50, 100);
		ofPopMatrix();
	}
	ofScale(6, 6);
	ofTriangle(0, 0, -50, 100, 50, 100);
}

//--------------------------------------------------------------
void ofApp::matrixPattern() {
	for (int y = -countY; y <= countY; y++) {
		ofPushMatrix();
		//---------------------
		if (countY > 0) {
			float scl = ofMap(y, -countY, countY, 1 - pinchY, 1);
			ofScale(scl, scl);
		}
		ofTranslate(0, y * stepY);
		ofRotate(y * twistY);
		stripePattern();
		//---------------------
		ofPopMatrix();
	}
}

//--------------------------------------------------------------
void ofApp::draw2d() {
	ofBackground(Background);
	ofDisableSmoothing();
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	ofSetColor(255, imageAlpha);
	image.draw(0, 0, ofGetWidth(), ofGetHeight());
	ofSetColor(255, videoAlpha);
	video.draw(0, 0, ofGetWidth(), ofGetHeight());
	if (camera.isInitialized()) {
		ofSetColor(255, cameraAlpha);
		camera.draw(0, 0, ofGetWidth(), ofGetHeight());
	}
	ofEnableSmoothing();
	ofEnableAlphaBlending();
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	float Scl = pow(Scale, 4.0f);
	ofScale(Scl, Scl);
	ofRotate(Rotate);
	matrixPattern();
	ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::exit() {
	gui.saveToFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'z') showGui = !showGui;

	if (key == 'c') {
		camera.setDeviceID(0);
		camera.setDesiredFrameRate(30);
		camera.initGrabber(1280, 720);
	}

	if (key == 'p') {
		if (!sound.getIsPlaying()) sound.play();
		else sound.stop();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
