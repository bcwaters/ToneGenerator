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
	printf("\n byteRate: %i\n", testWav->getByteRate());

	//makerTone.makeTone(pause, 0, 1);
	//makerTone.makeTone(pause, 0, 1);
	
	for (int i = 0; i < 20; i++)
	{
		printf("ToneAdded:  %i\n", pause-(i*30));
		makerTone.makeTone(pause - (i*30), i, 1);
		if (pause>200 && i % 3 == 0)
		{
			makerTone.makeTone(pause , i, 2);
		}
	}

	/*makerTone.makeTone(pause, 3, 30);
	makerTone.makeTone(pause, 9, 3);
	makerTone.makeTone(pause, 14, 3);
	makerTone.makeTone(pause - 100, 7, 9);
	makerTone.makeTone(pause - 100, 16, 3);
	*/
	//makerTone.makeTone(200, 0, 7);

	makerTone.AddToneDataToWav(testWav);
	testWriter.writeWav(testWav);
	std::cin >> pause;
}


