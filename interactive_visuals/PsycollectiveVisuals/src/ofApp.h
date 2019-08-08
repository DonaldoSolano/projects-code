#pragma once

#include "ofMain.h"

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
		
		ofImage psycollective;

		/*(bands)Variable as parameter that stores the number of bands given when using the function ofGetSpectrum(int bands)*/
		int bands;

		/*(fftSmooth)Variable to store the result of the ofGetSpectrum function*/
		float *fftSmooth;

		/*Audio object for  frencuency spectrum extraction.*/
		ofSoundPlayer song;

		/**/
		float frecuency;

		/**/
		ofVideoPlayer video;
};
