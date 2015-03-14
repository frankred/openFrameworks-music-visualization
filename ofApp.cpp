#include "ofApp.h"
#include "stdio.h"

//--------------------------------------------------------------
tinkerforgeAudioVisualzation::tinkerforgeAudioVisualzation(){	 
	// Defaults
	this->system = STEREO;
	this->audioBufferSize = AUDIO_BUFFER_SIZE_DEFAULT;
	this->audioBufferSizeHalf = this->audioBufferSize / 2;
	this->maxMagnitudeValue = MAX_MAGNITUDE_VALUE;
	this->recalculateDimensions(OUTPUT_WIDTH_DEFAULT, OUTPUT_HEIGHT_DEFAULT);

	// Select device
	printAudioDevices();
	this->deviceId = getDeviceIdByConsole(getAudioDeviceAmount());

	this->window = new float[this->audioBufferSize];
	this->magnitudes = new float[this->audioBufferSize];
	this->phases = new float[this->audioBufferSize];

	this->printConfig();
}

void tinkerforgeAudioVisualzation::recalculateDimensions(int width, int height){
	this->outputWidth = width;
	this->outputHeight = height;
	this->spectrumBarWidth = this->outputWidth / this->audioBufferSize;
}

void tinkerforgeAudioVisualzation::printConfig(){
	cout << "buffer size: " << this->audioBufferSize << "\n";
	cout << "buffer size half: " << this->audioBufferSizeHalf  << "\n";
	cout << "max magnitude value: " << this->maxMagnitudeValue << "\n";
	cout << "ui output with: " << this-> outputWidth << "\n"; 
	cout << "ui output height: " << this-> outputHeight << "\n"; 
	cout << "bar width: " << this->spectrumBarWidth << "\n";
}

void tinkerforgeAudioVisualzation::setup(){
	init();
	myFft = new fft(this->audioBufferSize);
}

void tinkerforgeAudioVisualzation::init(){
	this->initModel();
	this->initGUI();
	this->initAudio();
}

void tinkerforgeAudioVisualzation::initGUI(){
    ofSetFrameRate(60.0f);
	ofBackground(28,211,211);
}

void tinkerforgeAudioVisualzation::initModel(){
	if(this->system == MONO){
		this->mono = new float[this->audioBufferSize];
		return;
	}

	if(this->system == STEREO){
		this->stereo_left = new float[this->audioBufferSize];
		this->stereo_right = new float[this->audioBufferSize];
	}
}

void tinkerforgeAudioVisualzation::initAudio(){
	stream.setDeviceId(deviceId);
	stream.setup(0, 2, this, 44100, this->audioBufferSize, 2);
	ofAddListener(stream.audioReceivedEvent, this, &tinkerforgeAudioVisualzation::audioInputListener);
}

//--------------------------------------------------------------

void tinkerforgeAudioVisualzation::draw(){

	// Create window function for fft to avoid strange fft behaviour
	myFft->genWindow(1, this->audioBufferSize, this->window);

	// Calculate power spectrum with fft
	myFft->powerSpectrum(this->stereo_left, window, magnitudes, phases);

	float oneMagnitudeInPixel = this->outputHeight / this->maxMagnitudeValue;
	float oneBarInPixelIncludingDistance = this->outputWidth / audioBufferSizeHalf;
	
	float preferedDistanceBetweenBars = 1;
	
	float distance;
	float barWidth;

	// If there is no place for a distance
	if(oneBarInPixelIncludingDistance - preferedDistanceBetweenBars <= 0){
		distance = 0;
		barWidth = this->outputWidth / audioBufferSizeHalf;
	} else {
		distance = preferedDistanceBetweenBars;
		barWidth = (this->outputWidth / audioBufferSizeHalf) - preferedDistanceBetweenBars;
	}
	
	// Draw audio visualization
	for (int i = 0; i < this->audioBufferSizeHalf; i++){
		ofRect((i * barWidth) + (i * distance) + 2, this->outputHeight - 2, barWidth, -this->magnitudes[i] * oneMagnitudeInPixel);
	}
}


static float adder = 0;
//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::audioReceived(float * input, int bufferSize, int nChannels){	

}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::audioInputListener(ofxAudioEventArgs &ofxAudioEvent){	
	for (int i = 0; i < ofxAudioEvent.bufferSize; i++){
		this->stereo_left[i] = ofxAudioEvent.buffer[i*2];
		this->stereo_right[i] = ofxAudioEvent.buffer[i*2+1];
	}
}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::keyPressed  (int key){ 
	
}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::keyReleased(int key){ 
	
}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::windowResized(int w, int h){
	cout << "window resized\n";
	this->recalculateDimensions(w, h);
}

int tinkerforgeAudioVisualzation::getDeviceIdByConsole(int deviceAmount){
	int deviceId = -1;
	std::cout << "Select the device you want to listen to (" << 0 << " - " << deviceAmount << "):\n"; 
	std::cin >> deviceId;
	return deviceId;
}

int tinkerforgeAudioVisualzation::getAudioDeviceAmount(){
	RtAudio *rtAudio = 0;
	try { 
		rtAudio = new RtAudio();
	} catch (RtError &error) {
		error.printMessage();
	}
	int audioDevicesAmount = rtAudio->getDeviceCount();
	delete rtAudio;
	return audioDevicesAmount;
}


void tinkerforgeAudioVisualzation::printAudioDevices(){
	RtAudio *rtAudio = 0;
	try {
		rtAudio = new RtAudio();
	} catch (RtError &error) {
		error.printMessage();
	}
	
	int devicesAmount = rtAudio->getDeviceCount();
	
	std::cout << "Devices: \n";
	RtAudio::DeviceInfo info;
	for (int i=0; i<devicesAmount; i++) {
		try {
			info = rtAudio->getDeviceInfo(i);
		} catch (RtError &error) {
			error.printMessage();
			break;
		}
		std::cout << i << ": " << info.name << "\n";
	}

	delete rtAudio;
}



