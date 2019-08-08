#pragma once
#include "particle.h"
#include "ofMain.h"
#include "ofxGui.h"

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
		int getMin(float arr[], int n);
		void exit();

		/*Audio object for  frencuency spectrum extraction.*/
 		ofSoundPlayer song;
		
		/*Dinamic particle array*/
		vector<particle> particulas;

		/*(sizeVector)Variable to limit the number of particles created. (bands)Variable as parameter that stores the number of bands given when using the function ofGetSpectrum(int bands)*/
		int sizeVector, bands;

		/*(fftSmooth)Variable to store the result of the ofGetSpectrum function*/
		float *fftSmooth;

		/*(threshold)Variable for establishing a  maximum limit for onset detection*/
		float threshold;

		/*(minimumThreshold)Variable for establishing a minimum limit for onset detection*/
		float minimumThreshold;

		/*(decayRate)Variable for estabilize the signal when processing it*/
		float decayRate;

		/*(void audioIn)Function for live audio processing*/
		void audioIn(float * input, int bufferSize, int nChannels);

		void circleResolutionChanged(int & circleResolution);

		/*()*/
		float soundLevel;

		/*()*/
		float minFrecuency;

		/*()*/
		int 	bufferCounter;
		int 	drawCounter;

		/*()*/
		float smoothedVol;
		float scaledVol;

		
		/*(soundStream)Variable to receive the input audio signal for further processing*/
		ofSoundStream soundStream;

		/*(noiseLine)Variable to create the line segments between close particles using the circle's centroid*/
		ofPolyline noiseLine;

		/*()*/
		ofxPanel gui;
		ofxGuiGroup globalGroup;
		ofxColorSlider backgroundColor, lineColor, particleColor;
		ofxIntSlider numParticles, particleResolution;

		/*()*/
		float particleRadius;

		/*()*/
		ofxToggle trackPlayingToggle, soundIsLiveToggle;

		/*()*/
		bool liveButton, trackButton, showGui;
};
