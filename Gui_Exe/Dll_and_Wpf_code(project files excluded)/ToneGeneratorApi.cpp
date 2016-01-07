// This is the main DLL file.

#include "stdafx.h"
#include "ToneGeneratorApi.h"


ToneGeneratorApi::ToneGeneratorApiClass::ToneGeneratorApiClass()
{
	wavPtr = new Wav();
}

int ToneGeneratorApi::ToneGeneratorApiClass::getResult()
{
	return wavPtr->getByteRate();
}

void ToneGeneratorApi::ToneGeneratorApiClass::loadWav(char* fileName)
{
	WavLoader wavLoader;
	
	wavPtr = wavLoader.loadWav(fileName);
	
}

void ToneGeneratorApi::ToneGeneratorApiClass::encodeTones(int* tones, int count)
{
	ToneGenerator toneMaker;

	for (int i = 0; i/3 < count; i=i+3)
	{
		int tempFreq = tones[i];
		toneMaker.makeTone(tempFreq, tones[i+1], (short)tones[i+2]);
	}

	toneMaker.AddToneDataToWav(wavPtr);
}


void ToneGeneratorApi::ToneGeneratorApiClass::writeWav( char * fileName)
{
	WavWriter wavWriter;
	wavWriter.writeWav(wavPtr, fileName);
}