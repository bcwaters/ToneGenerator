#include "Wav.h"
#include "DataChunk.h"

Wav::Wav()
{
	//it turns out that windows media player does not even use the chunksize. The length of the 
	//audio file is determined by the dataChunk's size parameter.

	riffId = 0x46464952;			//52494646		//RIFF
	chunkSize = 1000036;//1000036;				//FILE SIZE total = all - (riffType + fileSize)   !8 bytes 
	riffFormat = 0x45564157;			//WAVE

	fmt = new FormatChunk(FormatChunk::_STANDARD);
	data = new DataChunk();
}
//MAIN RIFF CHUNK
unsigned int Wav::getRiffId()
{
	return riffId;
}
unsigned int Wav::getChunkSize()
{
	return chunkSize;
}
unsigned int Wav::getRiffFormat()
{
	return riffFormat;
}
//FMT CHUNK
unsigned int Wav::getFmt()
{
	return fmt->fmtMark;
}
unsigned int Wav::getFmtLength()
{
	return fmt->fmtLength;
}
unsigned short Wav::getFmtType()
{
	return fmt->fmtType;
}
unsigned short Wav::getNumberOfChannels()
{
	return fmt->numberOfChannels;
}
unsigned int Wav::getSampleRate()
{
	return fmt->sampleRate;
}
unsigned int Wav::getByteRate()
{
	return fmt->byteRate;
}
unsigned short Wav::getBlockAlign()
{
	return fmt->blockAlign;
}
unsigned short Wav::getBitsPerSample()
{
	return fmt->bitsPerSample;
}
//DATA CHUNK
unsigned int Wav::getDataId()
{
	return data->dataId;
}
unsigned int Wav::getDataSize()
{
	return data->dataSize;
}
short Wav::getDataBlock(int index)
{
	return data->dataBlocks[index];
}
void Wav::setDataSize(unsigned int newSize)
{
	data->dataSize = newSize;
}
void Wav::setDataBlock(short* newData)
{
	delete [] data->dataBlocks;
	data->dataBlocks = newData;
}
