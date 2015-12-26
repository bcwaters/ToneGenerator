#include "RiffChunk.h"

RiffChunk::RiffChunk()
{
	riffId = 0x46464952;			//52494646		//RIFF
	chunkSize = 1000036;//1000036;				//FILE SIZE total = all - (riffType + fileSize)   !8 bytes 
	riffFormat = 0x45564157;			//WAVE
}

RiffChunk::RiffChunk(unsigned int dataSize)
{
	riffId = 0x46464952;			//52494646		//RIFF
	chunkSize = dataSize;//1000036;				//FILE SIZE total = all - (riffType + fileSize)   !8 bytes 
	riffFormat = 0x45564157;			//WAVE
}