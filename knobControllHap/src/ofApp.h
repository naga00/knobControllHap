#pragma once

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxHapPlayer.h"

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
    
    ofxHapPlayer player;
    int keyNum;
    bool isGUI;
    bool isFullscreen;
    
    float startPosition = 0.0;
    float initThrust = 0.0;
    float friction = 0.0;
    float thrust = 0.0;
    float velocity = 0.0;
    float speed = 0.0;
    
    string prevDirection = "right";
    float minSpeed = 0.0;
};

