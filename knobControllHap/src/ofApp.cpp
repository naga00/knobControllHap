#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofxXmlSettings settings;
    settings.loadFile("settings.xml");
    
    int appFPS = settings.getValue("group:appFPS", 60);
    isGUI = settings.getValue("group:isGUI", false);
    string srcURL = settings.getValue("group:file", "sample_hap.mov");
    int movieWidth = settings.getValue("group:width", 1024);
    int movieHeight = settings.getValue("group:height", 768);
    string loopState = settings.getValue("group:loopState", "NORMAL");
    startPosition = settings.getValue("group:startPosition", 0.0);
    initThrust = settings.getValue("group:initThrust", 0.1);
    friction = settings.getValue("group:friction", 0.97);
    isFullscreen = settings.getValue("group:isFullscreen", false);
    minSpeed = settings.getValue("group:minSpeed", 0.5);
    
    ofBackground(0, 0, 0);
    ofSetWindowTitle("Knob Controller Movie");
    ofSetFrameRate(appFPS);
    ofSetFullscreen(isFullscreen);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    ofSetVerticalSync(true);
    ofSetBackgroundAuto(true);
    ofSetWindowShape(movieWidth, movieHeight);
    
    player.load(srcURL);
    if(loopState == "NONE"){
        player.setLoopState(OF_LOOP_NONE);
    }else if(loopState == "NORMAL"){
        player.setLoopState(OF_LOOP_NORMAL);
    }else if(loopState == "PALINDROME"){
        player.setLoopState(OF_LOOP_PALINDROME);
    }
    player.play();
    player.setPosition(startPosition);
}

//--------------------------------------------------------------
void ofApp::update(){
    float accel = thrust;
    velocity += accel;
    velocity *= friction;
    speed = velocity;

    if(prevDirection == "right"){
        if(speed < minSpeed){
            speed = minSpeed;
        }
    }else if(prevDirection == "left"){
        if(speed > - minSpeed){
            speed = - minSpeed;
        }
    }
    
    player.setSpeed(speed);
    player.update();
    thrust = 0.0;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    if (player.isLoaded()){
        player.draw(0, 0);
    }
    
    if(isGUI){
        ofSetColor(30, 30, 30);
        ofDrawBitmapString(ofToString(ofGetFrameRate(), 0) + " FPS", 15, 20);
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    keyNum = key;
    if(keyNum == 358){
        thrust = initThrust;
        prevDirection = "right";
    }else if(keyNum == 356){
        thrust = -initThrust;
        prevDirection = "left";
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    keyNum = 0;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    float position = (float) x / (float) ofGetWindowWidth();
    cout << "Setting playhead to " << ofToString(position) << endl;
    player.setPosition(position);
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
    vector< string > fileList = dragInfo.files;
    player.load(fileList[0]);
}
