#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(100);

	Tweenzor::init();

	one.loadMovie("1.mov");
	two.loadMovie("2.mov");

	// hvis aspekt er vigtigt
	oneOrigAspect = one.getWidth() / one.getHeight();
	twoOrigAspect = two.getWidth() / two.getHeight();

	// sætter filmenes y-pos
	yOne = 0 - ofGetWindowHeight() / 2;
	yTwo = ofGetWindowHeight() / 2;

	one.play();
	one.setLoopState(OF_LOOP_NONE);
	two.play();
	two.setLoopState(OF_LOOP_NONE);

	// filmene som still billede for brugeren.
	oneStill = 279;
	twoStill = 265;
	one.setFrame(oneStill);
	two.setFrame(twoStill);

	screenHome = true;

    one.stop();
    two.stop();
    
	// home button
	homeX = ofGetWindowWidth() - 125;
	homeY = ofGetWindowHeight() - 125;
	homeRadius = 100;

	// play button
	playAlpha = 100.f;
}

//--------------------------------------------------------------
void ofApp::update() {
	one.update();
	two.update();
	Tweenzor::update(ofGetElapsedTimeMillis());

	if (one.getIsMovieDone() || two.getIsMovieDone()) {
		if (!screenHome) {
			homePressed();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackground(0);
	
	// filmen og animationen opdateres
	ofSetColor(255);
	one.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * oneOrigAspect) / 2), yOne, ofGetWindowHeight() * oneOrigAspect, ofGetWindowHeight());
	two.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * twoOrigAspect) / 2), yOne + ofGetWindowHeight(), ofGetWindowHeight() * twoOrigAspect, ofGetWindowHeight());

	// home button
	ofSetColor(255, 255, 255, ceil(homeAlpha));
	ofCircle(homeX, homeY, homeRadius);

	// play buttons
	ofSetColor(255, 255, 255, ceil(playAlpha));
	ofCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 4, 100);
	ofCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() - (ofGetWindowHeight() / 4), 100);

	// debug
	ofSetColor(255);
	fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 5, 13);
}

//==============================================================
void ofApp::oneStarted() {
	screenHome = false;
    
    two.stop();
    
	Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yOne, yOne, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    
	yTwo = ofGetWindowHeight();
    
	one.setFrame(0);
    two.setFrame(twoStill);
	one.play();
}

void ofApp::twoStarted() {
	screenHome = false;
    
    one.stop();

    Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yOne, yOne, 0.f - ofGetWindowHeight(), 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    
    one.setFrame(oneStill);
	two.setFrame(0);
	two.play();
}

void ofApp::homePressed() {
	screenHome = true;
    
    one.stop();
    two.stop();
    
    Tweenzor::add(&yOne, yOne, 0.f - ofGetWindowHeight() / 2, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&yOne), this, &ofApp::onComplete);
    Tweenzor::add(&homeAlpha, homeAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&playAlpha, playAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
}

void ofApp::onComplete(float* arg) {
        two.setFrame(twoStill);
        one.setFrame(oneStill);
}

void ofApp::exit() {
	Tweenzor::destroy();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (!one.isPlaying() && !two.isPlaying()) {
		if (y < ofGetWindowHeight() / 2) {
			oneStarted();
		}
		else {
			twoStarted();
		}
	}
	else if (one.isPlaying() || two.isPlaying()) {
		if (x > homeX - homeRadius && x < homeX + homeRadius && y > homeY - homeRadius && y < homeY + homeRadius) {
			homePressed();
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}