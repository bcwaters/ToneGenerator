#ifndef DATACHUNK_H
#define DATACHUNK_H
#include < array > 



struct DataChunk
{
	unsigned int dataId;
	unsigned int dataSize;

	//THIS NEEDS TO BE REFACTORED!
	//These data blocks vary in length depending on the format of the wave file.
	unsigned char* readDataBlocks;
	DataWrapper* data;

public:
	void setData(int size, int type);
	DataChunk();
	~DataChunk();
};

struct DataWrapper{
public:
	virtual DataWrapper* getData(int index);
};

template<class T>
struct DataBlocks:DataWrapper{
	T* data;

public:
	DataBlocks(int size){ data = new T[size]; };
	~DataBlocks(){ delete [] data; };
	getData(int index){ return data[index]; };
};

#endif