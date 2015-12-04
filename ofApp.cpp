#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofSetCircleResolution(100);

	Tweenzor::init();

	videoFilm.loadMovie("filmExport.mov"); // fra MCH
	videoAnim.loadMovie("anim.mov"); // fra Lucia

	// hvis aspekt er vigtigt
	filmOrigAspect = videoFilm.getWidth() / videoFilm.getHeight();
	animOrigAspect = videoAnim.getWidth() / videoAnim.getHeight();

	// sætter filmenes y-pos
	yFilm = 0 - ofGetWindowHeight() / 2;
	yAnim = ofGetWindowHeight() / 2;

	videoFilm.play();
	videoFilm.setLoopState(OF_LOOP_NONE);
	videoAnim.play();
	videoAnim.setLoopState(OF_LOOP_NONE);

	// filmene starter ud med at være på pause -- et still billede for brugeren.
	filmStill = 279;
	animStill = 200;
	videoFilm.setFrame(filmStill);
	videoAnim.setFrame(animStill);

	filmPlaying = false;
	animPlaying = false;
	screenHome = true;

	videoFilm.setPaused(!filmPlaying);
	videoAnim.setPaused(!animPlaying);

	// font stuff
	stdFont.loadFont("Menlo.ttc", 12);

	// home button
	homeX = ofGetWindowWidth() - 125;
	homeY = ofGetWindowHeight() - 125;
	homeRadius = 100;

	// play button
	playAlpha = 100.f;
}

//--------------------------------------------------------------
void ofApp::update() {
	videoFilm.update();
	videoAnim.update();
	Tweenzor::update(ofGetElapsedTimeMillis());

	if (videoFilm.getIsMovieDone() || videoAnim.getIsMovieDone()) {
		if (screenHome = true) {
			homePressed();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofBackgroundHex(0);
	
	ofSetColor(255);
	// filmen og animationen opdateres
	videoFilm.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * filmOrigAspect) / 2), yFilm, ofGetWindowHeight() * filmOrigAspect, ofGetWindowHeight());
	videoAnim.draw(0, yFilm + ofGetWindowHeight());

	// home button
	ofSetColor(255, 255, 255, ceil(homeAlpha));
	ofCircle(homeX, homeY, homeRadius);

	// play buttons
	ofSetColor(255, 255, 255, ceil(playAlpha));
	ofCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 4, 100);
	ofCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() - (ofGetWindowHeight() / 4), 100);
}

//==============================================================
void ofApp::filmStarted() {
	screenHome = false;
	Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yFilm, yFilm, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	yAnim = ofGetWindowHeight();
	videoFilm.setFrame(0);
	videoFilm.play();
	filmPlaying = true;

	videoAnim.stop();
	animPlaying = false;
}

void ofApp::animStarted() {
	screenHome = false;
	Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&yFilm, yFilm, 0.f - ofGetWindowHeight(), 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	videoAnim.setFrame(0);
	videoAnim.play();
	animPlaying = true;

	videoFilm.stop();
	filmPlaying = false;
}

void ofApp::homePressed() {
	screenHome = true;
	videoFilm.setFrame(filmStill);
	videoAnim.setFrame(animStill);

	videoFilm.stop();
	filmPlaying = false;

	videoAnim.stop();
	animPlaying = false;

	Tweenzor::add(&yFilm, yFilm, 0.f - ofGetWindowHeight() / 2, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&homeAlpha, homeAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
	Tweenzor::add(&playAlpha, playAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
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
	if (!filmPlaying && !animPlaying) {
		if (y < ofGetWindowHeight() / 2) {
			filmStarted();
		}
		else {
			animStarted();
		}
	}
	else if (filmPlaying || animPlaying) {
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