#include "ToneGenerator.h"

void ToneGenerator::AddToneDataToWav(Wav* targetWav)
{
	unsigned char* toneArray = generateToneData(targetWav->getByteRate(), targetWav->getDataType());
	unsigned char* originalData = targetWav->getDataBlockArray();
	if (encodingLength > targetWav->getDataSize())
	{
		unsigned char * newData = new unsigned char[encodingLength]();
		for (int i = 0; i < targetWav->getDataSize(); i++)
		{
			newData[i] = originalData[i];
		}
		targetWav->setDataSize(encodingLength);
		targetWav->setDataBlockArray(newData);
		originalData = newData;
	}

	unsigned char byteOne;
	unsigned char byteTwo;

	for (int i = 0; i < targetWav->getDataSize(); i=i+2)
	{
		if (toneArray[i] + toneArray[i+1] != 0)
		{
			short combinedToneBytes = toneArray[i] + (toneArray[i + 1] << 8);
			short combinedDataBytes = originalData[i] + (originalData[i + 1] << 8);
			short bytesToWrite = (combinedToneBytes + combinedDataBytes);

			byteOne = bytesToWrite & 0x11;
			byteTwo = (bytesToWrite >> 8) & 0x11;
			
			originalData[i] = byteOne;
			originalData[i+1] = byteTwo;

		}
	}


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
unsigned char* ToneGenerator::generateToneData(unsigned int _byteRate, int dataType){

	for (auto it = toneList.begin(); it != toneList.end(); ++it)
	{
		Tone *tone = &*it;
		updateEncodingLength(tone, _byteRate);
	}

	unsigned char* newArr = new unsigned char[encodingLength]();
	unsigned char* waveCount = new unsigned char[encodingLength]();
	
	int amplitude = 5000;
	int bytesPerPeriod = 0;				//	byteRate/frequency finds how many bytes each period takes
	int periodRepeatValue = 0;			//	this indicates how many times to add the wav to the file duration * byteRate;
	int tonePosition = 0;				//	startTime*byteRate provides where the tone starts

	for (auto it = toneList.begin(); it != toneList.end(); ++it)
	{
		
		bytesPerPeriod = _byteRate / (it->frequency);
		bytesPerPeriod = bytesPerPeriod;				//This is to take into account the fact that there are 2 channels
		periodRepeatValue = (it->duration)*(_byteRate)/2;
		tonePosition = (it->startTime) * (_byteRate)/2;
		
		//This entire thing can be encapsulated in a squareWave method.
		addSquareWave(tonePosition,periodRepeatValue,amplitude,bytesPerPeriod,newArr,waveCount);

	}
	// end square wave method
	
	for (int i = 0; i < encodingLength; i++)
	{
		if (waveCount[i]!=0)
		newArr[i] = newArr[i] / waveCount[i];
	}

	//delete [] waveCount;
	return newArr;
}

void ToneGenerator::addSquareWave(int tonePosition, int periodRepeatValue, int amplitude, int bytesPerPeriod, unsigned char* newArr, unsigned char* waveCount)
{
	unsigned char byteOne;
	unsigned char byteTwo;
	bool atTop = true;
	if (tonePosition<encodingLength)
		for (int j = tonePosition; j < tonePosition + periodRepeatValue && j<encodingLength; j = j + 2)
		{
			byteOne = amplitude & 0xFF;
			byteTwo = (amplitude>>8) & 0xFF;
			if (atTop)
			{
				
				newArr[j] += byteOne;
				newArr[j + 1] += byteTwo;
				waveCount[j] = waveCount[j] + 1;
				waveCount[j + 1] = waveCount[j];
			}
			else
			{
				newArr[j] -= byteOne;
				newArr[j + 1] -= byteTwo;
				waveCount[j] = waveCount[j] + 1;
				waveCount[j + 1] = waveCount[j];
			}

			if (j % (bytesPerPeriod/2) == 0)
			{
				atTop = !atTop;
			}

			
		}
}