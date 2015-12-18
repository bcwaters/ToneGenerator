#include "DataChunk.h"

DataChunk::DataChunk()
{
	dataId = 0x61746164;				//DATA
	dataSize = 1000000;					//This is the size of the DataBlock array

	//THIS NEEDS TO BE REFACTORED!
	//These data blocks vary in length depending on the format of the wave file.
	dataBlocks = new short[1000000];

	int baseline = -16000;
	int rightLine = -16000;
	for (int i = 0; i < 1000000; i++)
	{


		if (i % 2 == 0)
		{
			baseline = baseline + 380 * 2;
			dataBlocks[i] = baseline;
		}
		else
		{
			rightLine = rightLine + (1280);
			dataBlocks[i] = rightLine;
		}


		if (i % 22050 == 0)
		{
			baseline = -16000;
		}
	}
}

DataChunk::~DataChunk()
{
	delete [] dataBlocks;

}