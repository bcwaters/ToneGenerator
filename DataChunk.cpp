#include "DataChunk.h"
#include "GlobalCodes.cpp"

DataChunk::DataChunk()
{
	dataId = 0x61746164;				//DATA
	dataSize = 0;					//This is the size of the DataBlock array

	//THIS NEEDS TO BE REFACTORED!
	//These data blocks vary in length depending on the format of the wave file.

}

DataChunk::~DataChunk()
{
	delete data;
}

void DataChunk::setData(int size, int type)
{
	if (type == GlobalCodes::charCode)
	{
		data = new DataBlocks<unsigned char>(size);
	}
	else if (type == type == GlobalCodes::shortCode)
	{
		data = new DataBlocks<short>(size);
	}
	else
	{
		data = new DataBlocks<unsigned int>(size);
	}
}

