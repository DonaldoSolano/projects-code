#pragma once
#include "ofMain.h"
class particle
{
public:
	particle();
	void draw(float radius, ofColor color);
	void update();
	float posx, posy, stepx, stepy, radio;
	ofColor colorIn, colorOut;
};
