#pragma once

#include "ofMain.h"
#include "ofTrueTypeFont.h"
#include "ofxTweenzor.h"
#include "ofxHapPlayer.h"


class ofApp : public ofBaseApp {
    
public:
    void setup();
    void update();
    void draw();
    
    void exit();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    //ofxHapPlayer one;
    ofxHapPlayer two;
    
    ofVideoPlayer one;
    //ofVideoPlayer two;
    
    float xOne, yOne, xTwo, yTwo, homeAlpha, playAlpha;
    int homeX, homeY, homeRadius;
    
    float oneOrigAspect, twoOrigAspect;
    
    int oneStill, twoStill;
    
    bool onePlaying;
    bool twoPlaying;
    
    bool screenHome;
    
    void oneStarted();
    void twoStarted();
    void homePressed();
    
    ofTrueTypeFont stdFont;
    string fpsStr;
};
