#include <iostream>
#include <math.h>
#include "AudioFile.h"



using namespace std;

/*
#include "Talkthrough.h"

int i = 0;
const int  size = 12000;
int bufor[12000] = {0};


//--------------------------------------------------------------------------//
// Function:	Process_Data()												//
//																			//
// Description: This function is called from inside the SPORT0 ISR every 	//
//				time a complete audio frame has been received. The new 		//
//				input samples can be found in the variables iChannel0LeftIn,//
//				iChannel0RightIn, iChannel1LeftIn and iChannel1RightIn 		//
//				respectively. The processed	data should be stored in 		//
//				iChannel0LeftOut, iChannel0RightOut, iChannel1LeftOut,		//
//				iChannel1RightOut, iChannel2LeftOut and	iChannel2RightOut	//
//				respectively.												//
//--------------------------------------------------------------------------//
void Process_Data(void)
{

int sampleLeft=((iChannel0LeftIn<<8)>>3)>>8;
int sampleRight=((iChannel0RightIn<<8)>>3)>>8;
int sample = (sampleLeft+sampleRight)/2;


int toReturn = sample + bufor[i];
bufor[i] = sample;

i++;
if(i==size){
i=0;
}

//students code here


iChannel0LeftOut = toReturn;
iChannel0RightOut = toReturn;
}
*/

#define M_PI 3.14159265358979323846


int main() {
	AudioFile<double> audioFile;
	string filename = "banjo";
	audioFile.load(filename + ".wav");
	audioFile.printSummary();

	int sampleRate = audioFile.getSampleRate();
	int signalLength = audioFile.getNumSamplesPerChannel();
	double delay = 8.2;
	double frequency = 0.75;
	double coupling = 1;

	int channel = 0;
	int numSamples = audioFile.getNumSamplesPerChannel();

	int timeDelayMax = floor(0.001 * delay * sampleRate);
	double frequencyDelayChange = frequency / (double)sampleRate;
	double a = coupling;

	for (int i = timeDelayMax + 1; i < signalLength; i++) {

		double currentSample = audioFile.samples[channel][i];
		
		int delayTime = 1 + round(timeDelayMax / 2.0 * (1.0 - cos(2 * M_PI*frequencyDelayChange*i)));
		double newSampleValue = (1.0 / (1.0 + a)) * (currentSample + a * audioFile.samples[channel][i - delayTime]);
		audioFile.samples[channel][i] = newSampleValue;
	}


	audioFile.save(filename+"_result.wav");
	cout << "done" << endl;
	getchar();

	return 0;
}
