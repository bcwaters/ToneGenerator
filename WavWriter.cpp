#include "WavWriter.h"
#include "Wav.h"



void WavWriter::writeWav(Wav * wavToWrite)
{
	
	testFile.open("test.wav", std::ios::binary);
	writeInt(wavToWrite->getRiffId());
	writeInt(wavToWrite->getChunkSize());
	writeInt(wavToWrite->getRiffFormat());
	writeInt(wavToWrite->getFmt());
	writeInt(wavToWrite->getFmtLength());
	writeShort(wavToWrite->getFmtType());
	writeShort(wavToWrite->getNumberOfChannels());
	writeInt(wavToWrite->getSampleRate());
	writeInt(wavToWrite->getByteRate());
	writeShort(wavToWrite->getBlockAlign());
	writeShort(wavToWrite->getBitsPerSample());
	writeInt(wavToWrite->getDataId());
	writeInt(wavToWrite->getDataSize());
	
	for (int i = 0; i < 1000000; i++)
	{
		writeShort(wavToWrite->getDataBlock(i));
	}
	

	testFile.close();

}

void WavWriter::writeInt(unsigned int  input)
{	
	testFile.write(reinterpret_cast<const char *>(&input), sizeof(unsigned int));
}

void WavWriter::writeShort(short  input)
{
	testFile.write(reinterpret_cast<const char *>(&input), sizeof(short));
}
