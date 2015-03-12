#ifndef _TEST_APP
#define _TEST_APP


#include "ofMain.h"
#include "ofxSoundStream.h"
#include "fft.h"

class tinkerforgeAudioVisualzation : public ofBaseApp{
	
	public:
		
		// openFrameworks
		void setup();
		void update(){};
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		// tinkerforgeAudioVisuaization
		static const int OUTPUT_HEIGHT_DEFAULT = 100;
		static const int OUTPUT_WIDTH_DEFAULT = 300;
		static const int AUDIO_BUFFER_SIZE_DEFAULT = 256;
		const enum SYSTEM {MONO, STEREO};
		
		tinkerforgeAudioVisualzation();
		tinkerforgeAudioVisualzation(int deviceId, int outputWidth, int outputHeight, int spectrumBarAmount, SYSTEM system);
		int deviceId;
		int audioBufferSize;
		int outputWidth;
		int outputHeight;
		int outputHeightCenter;
		SYSTEM system;
		
		unsigned int selectedDeviceId;
		int getAudioDeviceAmount();
		int getDeviceIdByConsole(int deviceAmount);
		void printAudioDevices();
		void initModel();
		void initGUI();
		void initAudio();
		void init();
		void recalculateDimensions();
		
		void audioReceived 	(float * input, int bufferSize, int nChannels);
		void audioInputListener (ofxAudioEventArgs &args);
	
		ofxSoundStream stream;
	
		float* mono;
		float* stereo_left;
		float* stereo_right;

		// fft
		fft* myFft;
		float* window;
		float* magnitudes;
		float* phases;
};

#endif	

