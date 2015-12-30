#ifndef DATACHUNK_H
#define DATACHUNK_H
#include < array > 


struct DataWrapper {
public:
	int type;
	virtual void* getData(int index) = 0;
	virtual int getDataType() = 0;
	virtual void setData(void * _data) {};

};

template<class T>
struct DataBlocks :DataWrapper {
	T* data;

public:
	DataBlocks(int size) { data = new T[size]; };
	~DataBlocks() { delete[] data; };
	void* getData(int index) { return (void*)(data[index]); };
	int getDataType() { return type; };
	void setData(void * _data)
	{
		data = static_cast<T*>(_data);
	}
	
};


struct DataChunk
{
	unsigned int dataId;
	unsigned int dataSize;

	//THIS NEEDS TO BE REFACTORED!
	//These data blocks vary in length depending on the format of the wave file.
	DataWrapper* data;

public:
	void setDataType(int type,int size);
	int getDataType();
	DataChunk();
	~DataChunk();
	void * getData(int index);
	void setDataArray(void * _data);

};

#endif