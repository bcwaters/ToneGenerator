#include "WavWriter.h"
#include "Wav.h"
#include "GlobalCodes.cpp"



void WavWriter::writeWav(Wav * wavToWrite, int tempCode)
{
	
	testFile.open("testRead.wav", std::ios::binary);
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
	writeData( wavToWrite);
		
	testFile.close();
}

void WavWriter::writeData(Wav* _wavToWrite)
{
	if (_wavToWrite->getDataType() == GlobalCodes::charCode)
	{
		writeUnsignedCharData(_wavToWrite);
	}
	else
	{
		writeShortData(_wavToWrite);
	}
	
}

void WavWriter::writeInt(unsigned int input)
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

void WavWriter::writeShortData(Wav* _wavToWrite)
{
	//testFile.write(reinterpret_cast<const char *>(&input), sizeof(short));
	for (int i = 0; i < _wavToWrite->getDataSize(); i = i+2)
	{
		short temp = reinterpret_cast<short>(_wavToWrite->getDataBlock(i));
		writeShort(temp);
		temp = reinterpret_cast<short>(_wavToWrite->getDataBlock(i+1));
		writeShort(temp);
	}
}

void WavWriter::writeUnsignedCharData(Wav* _wavToWrite)
{
	unsigned char temp;

	for (int i = 0; i < _wavToWrite->getDataSize(); i++)
	{
		temp =  reinterpret_cast<unsigned char>(_wavToWrite->getDataBlock(i));
		writeUnsignedChar(temp);
	}
}
