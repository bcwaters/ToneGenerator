#ifndef RIFFCHUNK_H
#define RIFFCHUNK_H

struct RiffChunk
{
	unsigned int riffId;			//"RIFF"
	unsigned int chunkSize;			//fileLength - 8
	unsigned int riffFormat;		//"WAVE"

public:
	RiffChunk();
	RiffChunk(unsigned int dataSize);
};

#endif