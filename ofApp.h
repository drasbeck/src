#pragma once

#include "ofMain.h"
#include "ofTrueTypeFont.h"
#include "ofxGui.h"
#include "ofxTweenzor.h"


class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
   
    void exit();

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
	
    ofVideoPlayer videoFilm;
    ofVideoPlayer videoAnim;

    float xFilm, yFilm, xAnim, yAnim, homeX, playAlpha;
    int homeY, homeRadius;
    
    float filmOrigAspect, animOrigAspect;
    
    bool filmPlaying = false;
    bool animPlaying = false;
    
    ofxPanel gui;
    ofxButton playFilm, playAnim, homeButton;
    
    void filmStarted();
    void animStarted();
    void homePressed();

    ofTrueTypeFont stdFont;
};
