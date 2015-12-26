#include <stdio.h>
#include <iostream>
#include "Wav.h"
#include "WavWriter.h"
#include "WavLoader.h"
#include "ToneGenerator.h"

int main(int argc, const char* argv[])
{
	Wav * testWav = new Wav();

	WavWriter testWriter;
	ToneGenerator makerTone;
	

	
	int pause;
	WavLoader testLoad;
	testWav = testLoad.loadWav("WilhelmScream.wav");
	unsigned char * tempStor = reinterpret_cast<unsigned char*>(testLoad.getBits());
	
	for (int i = 0; i < 20; i++)
	{
		printf("%x ", tempStor[i]);
	}
	
	printf("\n%u", testLoad.getTestInfo());
	testWriter.writeWav(testWav, 0);

	/*printf("Hello enter a frequency to create:\n");
	FormatChunk *testChunk = new FormatChunk(1);
	//printf("%i", testChunk->getTestInfo());
	std::cin >> pause;
	printf("\n byteRate: %i\n", testWav->getByteRate());

	for (int i = 0; i < 2; i++)
	{
		printf("ToneAdded:  %i\n", pause-(i*30));
		makerTone.makeTone(pause - (i*30), i, 1);
		if (pause>200 && i % 3 == 0)
		{
			makerTone.makeTone(pause , i, 2);
		}
	}

	makerTone.AddToneDataToWav(testWav);
	testWriter.writeWav(testWav);

	*/


	std::cin >> pause;
}


