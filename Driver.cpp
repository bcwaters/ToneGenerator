#include <stdio.h>
#include <iostream>
#include <string>
#include "Wav.h"
#include "WavWriter.h"
#include "WavLoader.h"
#include "ToneGenerator.h"

int main(int argc, const char* argv[])
{
	Wav * testWav = new Wav();

	WavWriter testWriter;
	ToneGenerator makerTone;
	WavLoader testLoad;
	

	printf("Welcome to the ToneGenerator app.  Soon this functionality will\nbe put behind a gui.  For now try out the console:\n\n");
	
	
	int pause = 0;
	
		printf("Enter 1 to load a wav\n");
		printf("Enter 2 to make tones\n");
		printf("Enter 3 to quit\n");
		
		while (pause != 1 && pause!=2 && pause!=3)
		{
			printf("enter a valid choice:\n");
			std::cin >> pause;
		}

		if (pause == 1)
		{
			std::string wavName;
			printf("please enter the name of the wav file \n for now it must be in the running directory and include .wav:");
			std:: cin >> wavName;
			testWav = testLoad.loadWav((char *)wavName.c_str());
			unsigned char * tempStor = reinterpret_cast<unsigned char*>(testLoad.getBits());

			for (int i = 0; i < testWav->getDataSize(); i++)
			{
				testWav->getDataBlockArray()[i] = testWav->getDataBlockArray()[i] * 2;
			}
		}
		else {
			testWav = new Wav();
			printf("Hello enter a frequency to create:\n");
			int freq = 0;
			std::cin >> freq;
			makerTone.makeTone(freq, 0, 10);
			makerTone.AddToneDataToWav(testWav);
		}

	

	std::string fileName;
	printf("Please Enter the name of the wav file to create\n");
	std::cin >> fileName;
	testWriter.writeWav(testWav,(char *) fileName.c_str());
	printf("Wav created\n");

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


