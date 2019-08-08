#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup(){
	ofSetLogLevel(OF_LOG_VERBOSE);
	//--------------------------
	gui.setup("Configuration");
	globalGroup.setup("Color");
	globalGroup.add(numParticles.setup("Number of particles",0,0,100));
	globalGroup.add(particleResolution.setup("Particle resolution", 0, 3, 100));
	globalGroup.add(soundIsLiveToggle.setup("Live audio", false));
	globalGroup.add(trackPlayingToggle.setup("Recorded track", false));
	globalGroup.add(backgroundColor.setup("Background color", ofColor::white, ofColor(0, 0, 0, 0), ofColor::white));
	globalGroup.add(lineColor.setup("Line color", ofColor::black, ofColor(0, 0, 0, 0), ofColor::white));
	globalGroup.add(particleColor.setup("Particle color", ofColor::black, ofColor(0, 0, 0, 0), ofColor::white));
	gui.add(&globalGroup);
	//--------------------------
	particleResolution.addListener(this, &ofApp::circleResolutionChanged);
	//--------------------------
	ofSetFrameRate(60);
	//--------------------------
	song.load("nightcall.mp3");
	ofBackground(20);
	song.setLoop(true);
	song.setVolume(1);
	ofSetBackgroundAuto(true);
	sizeVector = ofRandom(9);
	fftSmooth = new float[8192];

	for (int i = 0; i < 8192; i++)
	{
		fftSmooth[i]=0;
	}

	bands = 512;

	decayRate = 0.05;
	minimumThreshold = 0.1;
	threshold = minimumThreshold;

	// 0 output channels, 
	// 2 input channels
	// 44100 samples per second
	// 256 samples per buffer
	// 4 num buffers (latency)

	soundStream.getDeviceList();

	//if you want to set a different device id 
	/*soundStream.setDeviceID(channelNum);*/ //bear in mind the device id corresponds to all audio devices, including  input-only and output-only devices.

	int bufferSize = 128;

	bufferCounter = 0;
	drawCounter = 0;
	smoothedVol = 0.0;
	scaledVol = 0.0;

	//Initialize the soundLevel variable and start to capture the sound.
	soundStream.setup(this, 0, 1, 44100, bufferSize, 4);
	soundLevel = 0; 

	
	liveButton = false;
	trackButton = false;

	//.............
	gui.loadFromFile("settings.xml");

	showGui = true;

	ofSetFullscreen(true);

}

//--------------------------------------------------------------
void ofApp::update(){
	//-----------------------------------------
	if (fabs(particulas.size()-numParticles)!=0)
	{
		particulas.resize(numParticles);
	}
	//----------------------------------
	ofSoundUpdate();
	//----------------------------------
	for (int i = 0; i < particulas.size(); i++)
	{
		particulas[i].update();
	}
	if (particulas.size() > numParticles)
	{
		particulas.pop_back();
	}
	float *value = ofSoundGetSpectrum(bands);
	for (int i = 0; i < bands; i++)
	{
		fftSmooth[i] *= 0.99f;
		
		if (fftSmooth[i]<value[i])
		{
			fftSmooth[i] = value[i];
		}
	}
	//---------------------------------------------
	switch (trackPlayingToggle)
	{
	case true:
		if (trackButton == false)
		{
			if (song.isPlaying())
			{
				song.setPaused(false);
			}
			else
			{
				song.play();
			}
			soundStream.stop();
			soundIsLiveToggle = false;
			trackButton = true;
		}
		break;

	case false:
		trackButton = false;
		song.setPaused(true);
		break;
	}

	switch (soundIsLiveToggle)
	{
	case true:
		if (liveButton == false)
		{
			trackPlayingToggle = false;
			song.setPaused(true);
			song.setPosition(0);
			soundStream.start();
			liveButton = true;
		}
		break;

	case false:
		liveButton = false;
		soundStream.stop();
		break;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	ofTranslate(0,0,0);

	//-------------------------------
	if (trackPlayingToggle == true || soundIsLiveToggle == true)
	{
		float a = sin(ofGetElapsedTimef()*M_TWO_PI*0.5); 
		a = ofMap(a, -1, 1, 0, 1);
		ofBackgroundGradient(backgroundColor,255*a);
	}
	else
	{
	//Intentionally left blank.	
	}
	
	for (int i = 0; i < particulas.size(); i++)
	{
		minFrecuency = MIN(fftSmooth[0], fftSmooth[i]);
		if (soundIsLiveToggle == false)
		{
			double u = 30.0*minFrecuency;
			particleRadius = -(fftSmooth[i]*u);
		}
		else
		{
			particleRadius = -(soundLevel * 100.0f);
		}

		particulas[i].draw(particleRadius, particleColor);
	}
	for (int j = 0; j < particulas.size(); j++)
	{
		for (int k = j + 1; k < particulas.size(); k++)
		{
			if (particulas.size() >= 1 && (trackPlayingToggle == true || soundIsLiveToggle == true))
			{
				if (ofDist(particulas[j].posx, particulas[j].posy, particulas[k].posx, particulas[k].posy) < 100)
				{
					ofPushMatrix();
					ofPushStyle();
					ofSetLineWidth(3);
					ofSetColor(lineColor);
					noiseLine.begin();
					noiseLine.addVertex(particulas[j].posx, particulas[j].posy);
					noiseLine.addVertex(particulas[k].posx, particulas[k].posy);
					ofVec2f v1(particulas[j].posx, particulas[j].posy);
					ofVec2f v2(particulas[k].posx, particulas[k].posy);
					ofVec3f mid = v1.getMiddle(v2);
					mid += ofRandom(-5, 5);
					noiseLine.addVertex(mid);
					noiseLine.close();
					noiseLine.draw();
					noiseLine.clear();
					ofPopStyle();
					ofPopMatrix();
				}
			}
		}
	}
	if (showGui) gui.draw();
}

//--------------------------------------------------------------
int ofApp::getMin(float arr[], int n)
{
	arr = new float[n];
	float res = arr[0];
	for (int i = 1; i < n; i++)
		res = MIN(res, arr[i]);
	return res;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'z') showGui = !showGui;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int & circleResolution){
	ofSetCircleResolution(circleResolution); 
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels) {
	double v = 0;
	for (int i = 0; i < bufferSize; i++) {
		v += input[i] * input[i];
	}
	v = sqrt(v / bufferSize);
	soundLevel = v;
	//ofLog(OF_LOG_NOTICE, "the soundLevel is %f", soundLevel);
}
//--------------------------------------------------------------
void ofApp::exit() {
	gui.saveToFile("settings.xml");
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
