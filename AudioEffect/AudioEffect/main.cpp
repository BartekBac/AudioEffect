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
	audioFile.load("bedi.wav");
	audioFile.printSummary();

	int channel = 0;
	int numSamples = audioFile.getNumSamplesPerChannel();

	int size = 12000;

	const double  Tmax = 48000/2;
	const double Fdelay = 1 / 48000;
	const double pi = M_PI;
	double bufor[12000] = { 0 };

	/*for (int i = 0; i < size; i++) {
		bufor[i] = audioFile.samples[channel][i];
	}*/


	//for (int i = 0 , j = 0; i < numSamples; i++, j++)
	//{
	//	/*if (j == size) {
	//		j = 0;
	//	}*/
	//	double currentSample = audioFile.samples[channel][i];
	//	int index = i - Tmax*((double)1 + sin(2 * pi*i*Fdelay));


	//	if (index > 0 && index < numSamples) {
	//		audioFile.samples[channel][i] = currentSample + audioFile.samples[channel][index];
	//	}
	//	//bufor[j] = currentSample;
	//}
	//x/abs(x)*(1-e^((x^2)/abs(x))
	for (int i = 0; i < numSamples; i++) {
		
		double currentSample = audioFile.samples[channel][i];
	
		double value = currentSample / abs(currentSample)*(1 - exp((currentSample*currentSample) / abs(currentSample)));

		audioFile.samples[channel][i] = value;
	}

	audioFile.save("result.wav");
	cout << "done" << endl;
	getchar();

	return 0;
}
