
#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
	
    ofAppGlutWindow window;
	ofSetupOpenGL(&window, 
		tinkerforgeAudioVisualzation::OUTPUT_WIDTH_DEFAULT,
		tinkerforgeAudioVisualzation::OUTPUT_HEIGHT_DEFAULT, 
	OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new tinkerforgeAudioVisualzation());

}
