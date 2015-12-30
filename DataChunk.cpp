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

void DataChunk::setDataType(int size, int type)
{
	if (type == GlobalCodes::charCode)
	{
		
		data = new DataBlocks<unsigned char>(size);
		data->type = type;
	}
	else if (type == type == GlobalCodes::shortCode)
	{
		data = new DataBlocks<short>(size);
		data->type = type;
	}
	else
	{
		data = new DataBlocks<unsigned int>(size);
		data->type = type;
	}
}

void * DataChunk::getData(int index)
{
	return data->getData(index);
}

int DataChunk::getDataType()
{
	return data->getDataType();
}

void DataChunk::setDataArray(void * _data)
{
	data->setData(_data);
}