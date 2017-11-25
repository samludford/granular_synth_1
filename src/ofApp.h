#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include "maxiGrains.h"
#include <sys/time.h>

typedef hannWinFunctor grainPlayerWin;


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void audioOut(float * output, int bufferSize, int nChannels);
        void audioIn(float * input, int bufferSize, int nChannels);
    
    bool saving {false};
    
    
        double wave,sample,outputs[2];
        maxiSample samp;
        vector<maxiTimestretch<grainPlayerWin>*> stretches;
        maxiMix mymix;
        maxiTimestretch<grainPlayerWin> *ts;
        double speed, grainLength;
        int current;
        double pos;
    
        ofxMaxiFFT fft;
        ofxMaxiFFTOctaveAnalyzer oct;

    
        int		bufferSize; /* buffer size */
        int		sampleRate;
		
};
