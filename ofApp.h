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
		unsigned int now;
		unsigned int lastDrawTime;
		unsigned int drawTimeDelta;
						
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);

		// tinkerforgeAudioVisuaization
		static const int OUTPUT_HEIGHT_DEFAULT = 200;
		static const int OUTPUT_WIDTH_DEFAULT = 400;
		static const int AUDIO_BUFFER_SIZE_DEFAULT = 256;
		static const int MAX_MAGNITUDE_VALUE = 28;

		const enum SYSTEM {MONO, STEREO};
		
		tinkerforgeAudioVisualzation();
		int deviceId;
		int audioBufferSize;
		int audioBufferSizeHalf;
		float spectrumBarWidth;
		int outputWidth;
		int outputHeight;
		float maxMagnitudeValue;
		SYSTEM system;
		
		unsigned int selectedDeviceId;
		int getAudioDeviceAmount();
		int getDeviceIdByConsole(int deviceAmount);

		void printConfig();
		void printAudioDevices();
		void initModel();
		void initGUI();
		void initAudio();
		void init();
		void recalculateDimensions(int width, int height);
		
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
		float* magnituesBefore;
		float* phases;
		float* magnitudesPeaks;
		const float MAGNITUDE_SMOOTHING_THRESHOLD = 0.025;
		float magnitudeSmoothingTreshold;
};

#endif	

