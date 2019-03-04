#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    ofSoundPlayer   mySound;

    //      int pt = 3;
    
private:
    ofArduino arduino;
    
    void setupArduino(const int& version);
    
    void digitalPinChanged(const int& pinNum);
    
    void analogPinChanged(const int& pinNum);
    
    ofPolyline line;
    
    ofColor color;
    
    int potX,potY = 0;
    float pixelX, pixelY = 0;
    
    int potX_1,potY_1 = 0;
    float pixelX_1, pixelY_1 = 0;
};

