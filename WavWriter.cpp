#include "WavWriter.h"
#include "Wav.h"



void WavWriter::writeWav(Wav * wavToWrite, char * fileName)
{
	
	testFile.open(fileName, std::ios::binary);
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
	
	
		for (int i = 0; i < wavToWrite->getDataSize(); i=i+2)
		{
			if (i % 4 <4)
			{
				writeUnsignedChar(wavToWrite->getDataBlock(i));
				writeUnsignedChar(wavToWrite->getDataBlock(i+1));
			}
			else
			{
				writeUnsignedChar(0);
				writeUnsignedChar(0);
			}
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

void WavWriter::writeUnsignedChar(unsigned char  input)
{
	testFile.write(reinterpret_cast<const char *>(&input), sizeof(unsigned char));
}
