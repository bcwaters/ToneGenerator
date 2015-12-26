#ifndef FORMATCHUNK_H
#define FORMATCHUNK_H
struct FormatChunk
{
	static const short _STANDARD = 1;
	static const short _EIGHTBIT = 2;

	unsigned int fmtMark;				// format chunk marker with trailing null
	unsigned int fmtLength;			//16 for wave
	unsigned short fmtType;			//1 is PCM wavefile
	unsigned short numberOfChannels;
	unsigned int sampleRate;		// Commonvalue 44100 (Hertz)
	unsigned int byteRate;			//SampleRate * bitsPerSample * Channels/8
	unsigned short blockAlign;		//numChannels * bitsperSample/8
	unsigned short bitsPerSample;

public:
	FormatChunk();
	FormatChunk(short formatType);
	unsigned short getTestInfo();
	
};

#endif