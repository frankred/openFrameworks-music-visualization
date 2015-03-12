#include "ofApp.h"
#include "stdio.h"

//--------------------------------------------------------------
tinkerforgeAudioVisualzation::tinkerforgeAudioVisualzation(int deviceId, int outputWidth, int outputHeight, int spectrumBarAmount, SYSTEM system){
	this->deviceId = deviceId;
	this->outputWidth = outputWidth;
	this->outputHeight = outputHeight;
	this->system = system;
}

tinkerforgeAudioVisualzation::tinkerforgeAudioVisualzation(){	 
	printAudioDevices();
	this->deviceId = getDeviceIdByConsole(getAudioDeviceAmount());
	this->outputWidth = OUTPUT_WIDTH_DEFAULT;
	this->outputHeight = OUTPUT_HEIGHT_DEFAULT;
	this->system = STEREO;
	this->audioBufferSize = AUDIO_BUFFER_SIZE_DEFAULT;
	
	this->window = new float[this->audioBufferSize];
	this->magnitudes = new float[this->audioBufferSize];
	this->phases = new float[this->audioBufferSize];
	
}

void tinkerforgeAudioVisualzation::setup(){
	init();
	myFft = new fft(this->audioBufferSize);
}

void tinkerforgeAudioVisualzation::init(){
	this->recalculateDimensions();
	this->initModel();
	this->initGUI();
	this->initAudio();
}

void tinkerforgeAudioVisualzation::initGUI(){
	ofBackground(211,211,211);
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

//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::draw(){
	myFft->powerSpectrum(0, this->stereo_left, window, magnitudes, phases);

	cout << magnitudes[64] << "\n";

	ofSetHexColor(0x000000);
	for (int i = 0; i < this->audioBufferSize; i++){
		ofRect(i*this->audioBufferSize, this->outputHeightCenter, this->audioBufferSize,this->stereo_left[i] * this->outputHeightCenter);
	}





	/* draw the right:
	ofSetHexColor(0x545454);
	ofRect(600,100,256,200);

	ofSetHexColor(0xFFFFFF);
	for (int i = 0; i < 256; i++){
		ofLine(600+i, 200, 600+i, 200+this->stereo_left[i] * 100.0f);
	}
	*/
}


static float adder = 0;
//--------------------------------------------------------------
void tinkerforgeAudioVisualzation::audioReceived(float * input, int bufferSize, int nChannels){	
	// samples are "interleaved"
	// for (int i = 0; i < bufferSize; i++){
	//	left[i] = input[i*2];
	//	right[i] = input[i*2+1];
	// }
	// bufferCounter++;
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
	this->outputWidth = w;
	this->outputHeight = h;
	this->recalculateDimensions();
}

void tinkerforgeAudioVisualzation::recalculateDimensions(){

}


