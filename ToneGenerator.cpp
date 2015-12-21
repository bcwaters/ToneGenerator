#include "ToneGenerator.h"

void ToneGenerator::AddToneDataToWav(Wav* targetWav)
{
	targetWav->setDataBlock(generateToneData(targetWav->getByteRate()));
	targetWav->setDataSize(441000*2);
}

//This function is used to keep track of how long the wav file is going ot be 
//for encoding.  For now the 
void ToneGenerator::updateEncodingLength(Tone toneRecieved, unsigned int wavDataSize)
{
	//NumSamples * NumChannels * BitsPerSample/8
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
	short* newArr = new short[10000000]();
	short* waveCount = new short[1000000]();
	
	int amplitude = 5000;
	int bytesPerPeriod = 0;				//	byteRate/frequency finds how many bytes each period takes
	int periodRepeatValue = 0;			//	this indicates how many times to add the wav to the file duration * byteRate;
	int tonePosition = 0;				//	startTime*byteRate provides where the tone starts

	for (auto it = toneList.begin(); it != toneList.end(); ++it)
	{
		
		bytesPerPeriod = _byteRate / (it->frequency);
		bytesPerPeriod = bytesPerPeriod/2;				//This is to take into account the fact that there is 2 channels
		periodRepeatValue = (it->duration)*(bytesPerPeriod);
		periodRepeatValue = periodRepeatValue / 2;
		tonePosition = (it->startTime * _byteRate);
		

		//This entire thing can be encapsulated in a squareWave method.
		bool atTop = true;
		if (tonePosition<1000000)
		for (int j = tonePosition; j < tonePosition+periodRepeatValue; j=j+2)
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
	
	for (int i = 0; i < 1000000; i++)
	{
		if (waveCount[i]!=0)
		newArr[i] = newArr[i] / waveCount[i];
	}

	delete [] waveCount;
	return newArr;
}