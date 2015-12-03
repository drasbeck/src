#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    
    Tweenzor::init();
    
    videoFilm.load("film.mov"); // fra MCH
    videoAnim.load("anim.mov"); // fra Lucia
    
    // hvis aspekt er vigtigt
    filmOrigAspect = videoFilm.getWidth()/videoFilm.getHeight();
    animOrigAspect = videoAnim.getWidth()/videoAnim.getHeight();
    
    // sætter filmenes y-pos
    yFilm = 0 - ofGetWindowHeight() / 2;
    yAnim = ofGetWindowHeight() / 2;
    
    videoFilm.play();
    videoAnim.play();
    
    // filmene starter ud med at være på pause -- et still billede for brugeren.
    videoFilm.setPaused(!filmPlaying);
    videoAnim.setPaused(!animPlaying);
    
    // gui-stuff
    playFilm.addListener(this, &ofApp::filmStarted);
    playAnim.addListener(this, &ofApp::animStarted);
    homeButton.addListener(this, &ofApp::homePressed);
    
    gui.setup();
    
    gui.add(playFilm.setup("play Film"));
    gui.add(playAnim.setup("play Animation"));
    gui.add(homeButton.setup("stop"));
    
    ofSetCircleResolution(100);
    
    // font stuff
    stdFont.load("Menlo.ttc", 12);
    
    // home button
    homeX = -101.f;
    homeY = ofGetWindowHeight() - 125;
    homeRadius = 100;
    
    // play button
    playAlpha = 100.f;
}

//--------------------------------------------------------------
void ofApp::update(){
    videoFilm.update();
    videoAnim.update();
    Tweenzor::update(ofGetElapsedTimeMillis());
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackgroundHex(0);
    ofSetColor(255);
    
    // filmen i fullscreen
    videoFilm.draw((ofGetWindowWidth() / 2) - ((ofGetWindowHeight() * filmOrigAspect) / 2), yFilm, ofGetWindowHeight() * filmOrigAspect, ofGetWindowHeight());
    
    // animationen i fullscreen
    videoAnim.draw(0, yFilm + ofGetWindowHeight());

    // home button
    ofSetColor(255, 255, 255, 100);
    ofDrawCircle(homeX, homeY, homeRadius);

    // play buttons
    ofSetColor(255, 255, 255, ceil(playAlpha));
    ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() / 4, 100);
    ofDrawCircle(ofGetWindowWidth() / 2, ofGetWindowHeight() - (ofGetWindowHeight() / 4), 100);

    //gui.draw();
}

//==============================================================
void ofApp::filmStarted() {
    Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&yFilm, yFilm, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&homeX, homeX, 125.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    yAnim = ofGetWindowHeight();
    videoFilm.play();
    filmPlaying = true;
    
    videoAnim.stop();
    animPlaying = false;
}

void ofApp::animStarted() {
    Tweenzor::add(&playAlpha, playAlpha, 0.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&yFilm, yFilm, 0.f - ofGetWindowHeight(), 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&homeX, homeX, 125.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    videoAnim.play();
    animPlaying = true;
    
    videoFilm.stop();
    filmPlaying = false;
}

void ofApp::homePressed() {
    videoFilm.stop();
    filmPlaying = false;

    videoAnim.stop();
    animPlaying = false;

    Tweenzor::add(&yFilm, yFilm, 0.f - ofGetWindowHeight() / 2, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&homeX, homeX, -101.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
    Tweenzor::add(&playAlpha, playAlpha, 100.f, 0.f, 0.5f, EASE_IN_OUT_QUINT);
}

void ofApp::exit(){
    Tweenzor::destroy();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (!filmPlaying && !animPlaying) {
        if (y < ofGetWindowHeight() / 2) {
            filmStarted();
        } else {
            animStarted();
        }
    } else if (filmPlaying || animPlaying) {
        if (x > homeX - homeRadius && x < homeX + homeRadius && y > homeY - homeRadius && y < homeY + homeRadius) {
            homePressed();
        }
    }
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

}
