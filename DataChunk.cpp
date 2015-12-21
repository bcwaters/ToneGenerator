#include "DataChunk.h"

DataChunk::DataChunk()
{
	dataId = 0x61746164;				//DATA
	dataSize = 0;					//This is the size of the DataBlock array

	//THIS NEEDS TO BE REFACTORED!
	//These data blocks vary in length depending on the format of the wave file.

	dataBlocks;

}

DataChunk::~DataChunk()
{
	delete [] dataBlocks;

}