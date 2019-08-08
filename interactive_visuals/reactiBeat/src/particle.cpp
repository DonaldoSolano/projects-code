#include "particle.h"



particle::particle()
{
	posx = ofRandom(ofGetWidth());
	posy = ofRandom(ofGetHeight());
	radio = ofRandom(10, 40);
	stepx = ofRandom(-1.5, 1.5);
	stepy = ofRandom(-1.5, 1.5);
	colorIn = ofColor(ofRandom(255), ofRandom(255), ofRandom(255), 100);
	colorOut = ofColor(ofRandom(255), ofRandom(255), ofRandom(255));
}
void particle::draw(float radius, ofColor color)
{
	ofPushMatrix();
	ofTranslate(posx,posy);
	ofRotateZ(posx);
	ofFill();
	ofSetColor(color);
	ofDrawCircle(0, 0, radius);
	ofNoFill();
	ofSetColor(colorOut);
	ofDrawCircle(0, 0, 5);
	ofPopMatrix();
}
void particle::update()
{
	posx += stepx;
	posy += stepy;

	if (posx > ofGetWidth() || posx < 0)
	{
		stepx *= -1;
	}

	if (posy > ofGetHeight() || posy < 0)
	{
		stepy *= -1;
	}
}


