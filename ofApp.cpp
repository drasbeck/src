#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(100);

	Tweenzor::init();
	
	// filmene loades, husk at tage h�jde for om det er VideoPlayer eller HapPlayer
	one.loadMovie("1.mov");
	two.loadMovie("2.mov");
    one.setLoopState(OF_LOOP_NONE);
    two.setLoopState(OF_LOOP_NONE);

	// filmenes banner loades, husk at tage h�jde for filtype
	// banneret er sat til at have aspektet ofGetWindowsWidth * ofGetWindowHeight / 2
	bannerOne.loadImage("1.png");
	bannerTwo.loadImage("2.png");

	// hvis aspekt er vigtigt
	oneAspect = one.getWidth() / one.getHeight();
	twoAspect = two.getWidth() / two.getHeight();
	bannerOneAspect = bannerOne.getWidth() / bannerOne.getHeight();
	bannerTwoAspect = bannerTwo.getWidth() / bannerTwo.getHeight();

	// s�tter filmenes y-pos
	yOne = 0 - ofGetWindowHeight() / 2;

	// filmene som still billede for brugeren.
	oneStill = 280;
	twoStill = 265;
	one.setFrame(oneStill);
	two.setFrame(twoStill);
	one.play();
	two.play();
    one.stop();
    two.stop();
    
	// home button
	screenHome = true;
	homeBn.loadImage("homeBn.png");
	homeX = ofGetWindowWidth() - 125;
	homeY = ofGetWindowHeight() - 125;
	homeRadius = 100;

	// play button
	playAlpha = 200.f;
	playBn.loadImage("playBn.png");
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
	if (!one.isPlaying() && !two.isPlaying()) {
		bannerOne.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() / 2 * bannerOneAspect) / 2), yOne + ofGetWindowHeight() / 2, ofGetWindowHeight() / 2 * bannerOneAspect, yOne + ofGetWindowHeight());
		bannerTwo.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() / 2 * bannerTwoAspect) / 2), yOne + ofGetWindowHeight(), ofGetWindowHeight() / 2 * bannerOneAspect, yOne + ofGetWindowHeight());
	} else if (one.isPlaying() && !two.isPlaying()) {
		one.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * oneAspect) / 2), yOne, ofGetWindowHeight() * oneAspect, ofGetWindowHeight());
		bannerTwo.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() / 2 * bannerTwoAspect) / 2), yOne + ofGetWindowHeight(), ofGetWindowHeight() / 2 * bannerOneAspect, yOne + ofGetWindowHeight());
	} else if (!one.isPlaying() && two.isPlaying()) {
		bannerOne.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() / 2 * bannerOneAspect) / 2), yOne + ofGetWindowHeight() / 2, ofGetWindowHeight() / 2 * bannerOneAspect, yOne + ofGetWindowHeight());
		two.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * twoAspect) / 2), yOne + ofGetWindowHeight(), ofGetWindowHeight() * twoAspect, ofGetWindowHeight());
	}

	// home button
	ofSetColor(255, 255, 255, ceil(homeAlpha));
	//ofCircle(homeX, homeY, homeRadius);
	homeBn.draw(homeX - homeBn.getHeight() / 2, homeY - homeBn.getHeight() / 2);

	// play buttons
	ofSetColor(255, 255, 255, ceil(playAlpha));
	//ofCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 4, 100);
	//ofCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() - (ofGetWindowHeight() / 4), 100);
	playBn.draw(ofGetWindowWidth() / 2 - playBn.getWidth() / 2, ofGetWindowHeight() / 4 - playBn.getHeight() / 2);
	playBn.draw(ofGetWindowWidth() / 2 - playBn.getWidth() / 2, ofGetWindowHeight() - (ofGetWindowHeight() / 4) - playBn.getWidth() / 2);

	/*
	// debug
	ofSetColor(255);
	fpsStr = "frame rate: "+ofToString(ofGetFrameRate(), 2);
	ofDrawBitmapString(fpsStr, 5, 13);
	*/
}

//==============================================================
void ofApp::oneStarted() {
	screenHome = false;
    
    two.stop();
    
	Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yOne, yOne, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 200.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    
	one.setFrame(0);
    two.setFrame(twoStill);
	one.play();
}

void ofApp::twoStarted() {
	screenHome = false;
    
    one.stop();

    Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yOne, yOne, 0.f - ofGetWindowHeight(), 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 200.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    
    one.setFrame(oneStill);
	two.setFrame(0);
	two.play();
}

void ofApp::homePressed() {
	screenHome = true;
    
//    one.stop();
//    two.stop();
    
    Tweenzor::add(&yOne, yOne, 0.f - ofGetWindowHeight() / 2, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::addCompleteListener(Tweenzor::getTween(&yOne), this, &ofApp::onComplete);
    Tweenzor::add(&homeAlpha, homeAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&playAlpha, playAlpha, 200.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
}

void ofApp::onComplete(float* arg) {
	one.setFrame(oneStill);
//    one.play();
	one.stop();
	two.setFrame(twoStill);
//	two.play();
	two.stop();

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