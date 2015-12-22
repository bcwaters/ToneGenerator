#include "FormatChunk.h"

FormatChunk::FormatChunk(short formatType)
{
	//this is the default format I have chosen
	if (formatType == 1)
	{
		fmtMark = 0x20746d66;			//666d7020// format chunk marker with trailing null
		fmtLength = 0x0000010;			//16 for wave
		fmtType = 1;					//1 is PCM wavefile
		numberOfChannels = 0x0002;
		sampleRate = 22050;				// Commonvalue 44100 (Hertz)
		blockAlign = 0x0004;			//numChannels * bitsperSample/8
		bitsPerSample = 0x0010;			//16 bits per sample (8 for left 8 for right)
		byteRate = (sampleRate*bitsPerSample*numberOfChannels) / 8;			//SampleRate * bitsPerSample * Channels/8
	}


}

unsigned short FormatChunk::getTestInfo()
{
	return blockAlign;
}