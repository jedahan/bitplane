#pragma once

#include "ofMain.h"
#include "ofGraphics.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
        ofVideoGrabber grabber;
        ofImage grabberAsGray;
        ofImage bitPlane;
        int duckheight, bitposition, significantdigit;
        int bits;
        int number;

        bool sectionSignificant(int section);
};
