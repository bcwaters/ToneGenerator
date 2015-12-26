#include "Wav.h"
#include "DataChunk.h"

Wav::Wav()
{
	//it turns out that windows media player does not even use the chunksize. The length of the 
	//audio file is determined by the dataChunk's size parameter.

	
	riff = new RiffChunk();
	fmt = new FormatChunk(FormatChunk::_STANDARD);
	data = new DataChunk();
}
Wav::Wav(RiffChunk* _riff, FormatChunk* _fmt, DataChunk* _data) {
	riff = _riff;
	fmt = _fmt;
	data = _data;
}
//MAIN RIFF CHUNK
unsigned int Wav::getRiffId()
{
	return riff->riffId;
}
unsigned int Wav::getChunkSize()
{
	return riff->chunkSize;
}
unsigned int Wav::getRiffFormat()
{
	return riff->riffFormat;
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

unsigned char Wav::getReadDataBlock(int index)
{
	return data->readDataBlocks[index];
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
