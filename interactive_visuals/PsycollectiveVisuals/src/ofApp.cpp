#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

	/**/
	video.load("backgroundVideo.mp4");
	
	/**/
	ofBackground(0);

	/**/
	//ofSetFrameRate(60);

	/**/
	ofSetBackgroundAuto(true);

	/**/
	psycollective.load("psycollective.png");
	
	/**/
	song.load("orianaRemix.mp3");

	/**/
	song.setLoop(true);
	video.setLoopState(OF_LOOP_NORMAL);

	/**/
	bands = 1;

	/**/
	fftSmooth = new float[1];

	/**/
	for (int i = 0; i < bands; i++)
	{
		fftSmooth[i] = 0;
	}
	
}

//--------------------------------------------------------------
void ofApp::update(){
	/**/
	video.update();


	/*Here we update the buffer receptor of the song spectrogram when using prerecorded audio*/
	ofSoundUpdate();

	/*Storing the prerecorded audio data in a pointer float variable*/
	float *value = ofSoundGetSpectrum(bands);

	/*for the number of frecuency bands returned from the ofSoundGetSpectrum() function....*/
	for (int i = 0; i < bands; i++)
	{
		fftSmooth[i] *= 0.80f;

		/*....we are getting each value and storing it in the fftSmooth array....*/
		/*....but first we smooth the value multiplying the value by 0.99f....*/
		if (fftSmooth[i] < value[i])
		{
			fftSmooth[i] = value[i];
			frecuency = fftSmooth[i];
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){

	/*for (int i = 0; i < bands; i++)
	{
		if ()
		{

		}
		frecuency = fftSmooth[i];
	}*/
	video.draw(0, 0);
	for (int i = 0; i < 1; i++)
	{
		float radius = ofNoise(fftSmooth[i]);
		float mappedRadius = ofMap(radius,0,1,0,300);
		psycollective.draw(ofGetWidth() / 2.7, ofGetHeight() / 3, mappedRadius, (psycollective.getWidth() / 2), (psycollective.getHeight() / 2));
	}
	
	ofLog() << "asdasdasd" << frecuency;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	switch (key)
	{
	case 'a':
		video.play();
		if (song.isPlaying()&&video.isPlaying())
		{
			video.setPaused(false);
			song.setPaused(false);
		}
		else
		{
			song.play();
		}
		break;

	case 'd':
		video.setPaused(true);
		song.setPaused(true);
		break;
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
