#include <stdio.h>
#include <iostream>
#include "Wav.h"
#include "WavWriter.h"
#include "ToneGenerator.h"

int main(int argc, const char* argv[])
{
	Wav * testWav = new Wav();
	WavWriter testWriter;
	ToneGenerator makerTone;
	
	int pause;
	printf("Hello enter a frequency to create:\n");
	FormatChunk *testChunk = new FormatChunk(1);
	//printf("%i", testChunk->getTestInfo());
	std::cin >> pause;

	makerTone.makeTone(pause, 0, 5);
	makerTone.AddToneDataToWav(testWav);
	testWriter.writeWav(testWav);

}


