#include "ToneGenerator.h"

void ToneGenerator::AddToneDataToWav(Wav* targetWav)
{
	targetWav->setDataBlock(generateToneData(targetWav->getByteRate()));
	targetWav->setDataSize(encodingLength/2 + targetWav->getByteRate());
}

//This function is used to keep track of how long the wav file is going ot be 
//for encoding.  For now the 
void ToneGenerator::updateEncodingLength(Tone* toneRecieved, unsigned int _byteRate)
{
	int toneLength = ((toneRecieved->startTime) * (_byteRate )) + ((toneRecieved->duration) * _byteRate );
		if (toneLength > encodingLength)
			encodingLength = toneLength;
}

void ToneGenerator::makeTone(int frequency, int startTime, short duration)
{
	Tone *newTone = new Tone(frequency, startTime, duration);
	toneList.push_front (*newTone);
	++listSize;
}

void ToneGenerator::clearToneGenerator()
{
	listSize = 0;
	toneList.clear();
}


//This function converts each Tone in the tone list to bytes which can be read in a wav File
//All tones are added together and then the amplitude is scaled back down
short* ToneGenerator::generateToneData(unsigned int _byteRate){

	for (auto it = toneList.begin(); it != toneList.end(); ++it)
	{
		Tone *tone = &*it;
		updateEncodingLength(tone, _byteRate);
	}

	short* newArr = new short[encodingLength+_byteRate]();
	short* waveCount = new short[encodingLength + _byteRate]();
	
	int amplitude = 5000;
	int bytesPerPeriod = 0;				//	byteRate/frequency finds how many bytes each period takes
	int periodRepeatValue = 0;			//	this indicates how many times to add the wav to the file duration * byteRate;
	int tonePosition = 0;				//	startTime*byteRate provides where the tone starts

	for (auto it = toneList.begin(); it != toneList.end(); ++it)
	{
		
		bytesPerPeriod = _byteRate / (it->frequency);
		bytesPerPeriod = bytesPerPeriod/2;				//This is to take into account the fact that there are 2 channels
		periodRepeatValue = (it->duration)*(_byteRate)/2;
		tonePosition = (it->startTime) * (_byteRate)/2;
		
		//This entire thing can be encapsulated in a squareWave method.
		bool atTop = true;
		if (tonePosition<encodingLength)
		for (int j = tonePosition; j < tonePosition+periodRepeatValue  && j<encodingLength; j=j+2)
		{			
			if (atTop)
			{
				newArr[j] += amplitude;
				newArr[j + 1] += amplitude;
				waveCount[j] = waveCount[j]+1;
				waveCount[j + 1] = waveCount[j];
			}
			else
			{
				newArr[j] += -amplitude;
				newArr[j + 1] += -amplitude;
				waveCount[j] = waveCount[j] + 1;
				waveCount[j + 1] = waveCount[j];
			}

			if (j % (bytesPerPeriod/2) == 0)
			{
				atTop = !atTop;
			}
		}

	}
	// end square wave method
	
	for (int i = 0; i < encodingLength; i++)
	{
		if (waveCount[i]!=0)
		newArr[i] = newArr[i] / waveCount[i];
	}

	delete [] waveCount;
	return newArr;
}