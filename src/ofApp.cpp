/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    
    
    ofSetFrameRate(60);
    ofBackground(255);
    
    // audio setup
    sampleRate 	= 44100; /* Sampling Rate */
    bufferSize	= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    ofSetVerticalSync(true);
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    samp.load(ofToDataPath("loop_3.wav"));
    ts = new maxiTimestretch<grainPlayerWin>(&samp);
    stretches.push_back(ts);
    speed = 1;
    grainLength = 0.05;
    current=0;
    
    fft.setup(1024, 512, 256);
    oct.setup(44100, 1024, 10);
    
    ofSetSphereResolution(3);
    
    ofSoundStreamSetup(2,2,this, sampleRate, bufferSize, 4); /* this has to happen at the end of setup - it switches on the DAC */
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
    ofNoFill();
    for(int i=0; i < oct.nAverages; i++) {
        ofSetColor(0,0,0,oct.averages[oct.nAverages-i-1] / 20.0 * 255.0);
        ofPushMatrix();
        glTranslatef(ofGetWidth()/2,ofGetHeight()/2, 0);
        ofRotate(0.01 * ofGetFrameNum() * speed * i, 1, 0.1, 0);
        ofDrawSphere(0, 0, i * 5);
        ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels) {
    

    
    for (int i = 0; i < bufferSize; i++){
        
        wave = stretches[current]->play(speed, 0.1, 4, 0);
        
        if (fft.process(wave)) {
            oct.calculate(fft.magnitudes);
        }
        
        mymix.stereo(wave, outputs, 0.5);
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
    
    
}

//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    
    for(int i = 0; i < bufferSize; i++){
        
    }
    
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    if(key == ' ') {
        ofSaveScreen(ofToString(ofGetFrameNum()) + ".png");
    }
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    speed = ((double ) x / ofGetWidth() * 4.0) - 2.0;
    grainLength = ((double) y / ofGetHeight() * 0.1) + 0.001;
    pos = ((double) x / ofGetWidth() * 2.0);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    
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
