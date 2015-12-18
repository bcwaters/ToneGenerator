#ifndef DATACHUNK_H
#define DATACHUNK_H
#include < array > 

struct DataChunk
{
	unsigned int dataId;
	unsigned int dataSize;

	//THIS NEEDS TO BE REFACTORED!
	//These data blocks vary in length depending on the format of the wave file.
	short* dataBlocks;

public:
	DataChunk();
	~DataChunk();
};

#endif