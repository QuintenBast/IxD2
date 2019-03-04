#include "ofApp.h"

#define PIN_StickX 5
#define PIN_StickY 4

#define PIN_StickX_1 1
#define PIN_StickY_1 0


void ofApp::setup(){
    ofSetBackgroundAuto(false);
    ofBackground(0,0,0);
    ofAddListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    arduino.connect("/dev/cu.usbmodem14101");
    arduino.sendFirmwareVersionRequest();
    
    mySound.load("ping.flac");

}


void ofApp::update(){
    arduino.update();
    ofLog() << potX << " " << potY << endl;
    
    
    
    //    for (auto &vert : line.getVertices()){
    //        vert.x += ofRandom(-0.5,0.5);
    //        vert.y += ofRandom(-0.5,0.5);
    //    }
}


void ofApp::draw(){
    ofSetColor(color);
    line.draw();

    ofFill();
    ofSetColor(ofColor::red);
    ofDrawCircle(pixelX_1, pixelY_1, 10);
    
    ofSetColor(ofColor::blue);
    ofDrawCircle(pixelX, pixelY, 10);

}


void ofApp::setupArduino(const int& version) {
    ofRemoveListener(arduino.EInitialized, this, &ofApp::setupArduino);
    
    ofLog() << "Arduino firmware found: " << arduino.getFirmwareName()
    << " v" << arduino.getMajorFirmwareVersion() << "." << arduino.getMinorFirmwareVersion();
    
    arduino.sendAnalogPinReporting(PIN_StickX, ARD_ANALOG);
    arduino.sendAnalogPinReporting(PIN_StickY, ARD_ANALOG);
    
    arduino.sendAnalogPinReporting(PIN_StickX_1, ARD_ANALOG);
    arduino.sendAnalogPinReporting(PIN_StickY_1, ARD_ANALOG);
    
    ofAddListener(arduino.EAnalogPinChanged, this, &ofApp::analogPinChanged);
}


void ofApp::analogPinChanged(const int& pinNum) {
    if (pinNum==PIN_StickX) {
        potX = arduino.getAnalog(PIN_StickX);
    } else if (pinNum == PIN_StickY) {
        potY = arduino.getAnalog(PIN_StickY);
    }
    pixelX = ofMap(potX, 0,  1023, 0, ofGetWidth());
    pixelY = ofMap(potY, 0,  1023, 0, ofGetHeight());
 /*
        ofPoint pt;
        pt.set(pixelX ,pixelY);
        line.addVertex(pt);
  
  */
    
    
    if (pinNum==PIN_StickX_1) {
        potX_1 = arduino.getAnalog(PIN_StickX_1);
    } else if (pinNum == PIN_StickY_1) {
        potY_1 = arduino.getAnalog(PIN_StickY_1);
    }
    
    pixelX_1 = ofMap(potX_1, 0,  1023, 0, ofGetWidth());
    pixelY_1 = ofMap(potY_1, 0,  1023, 0, ofGetHeight());
    /*
     ofPoint pt;
     pt.set(pixelX ,pixelY);
     line.addVertex(pt);
     
     */
}


void ofApp::mousePressed(int x, int y, int button){
    line.clear();
}


void ofApp::keyPressed  (int key){
    if(key = 'p'){
    mySound.play();
    }
}

void ofApp::mouseDragged(int x, int y, int button){
    ofPoint pt;
    pt.set(x,y);
    line.addVertex(pt);
}
