#include "WavLoader.h"

Wav* WavLoader::loadWav(char* fileName)
{

	openFile(fileName);
	if (fileOpened)
	{
		loadRiffChunk();
		loadFmtChunk();
		loadDataChunk();
	}
	
	if (riff != nullptr && fmt != nullptr && data != nullptr)
	{
		return new Wav(riff, fmt, data);
	}
	else
	{
		return nullptr;
	}
}

void WavLoader::openFile(char* fileName)
{
	std::ifstream file(fileName, std::ios::in | std::ios::binary | std::ios::ate);
	if (file.is_open())
	{
		fileOpened = true;
		size = file.tellg();
		wavInMemory = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(wavInMemory, size);
		file.close();
		convertedHeaderData = reinterpret_cast<unsigned char*>(wavInMemory);
	}
}


//This function simply checks that the first chunk is formatted correctly and sets the riffchunk to a new one
//of the proper size.  If it is incorrect the riff is set to null
void WavLoader::loadRiffChunk() {
	
	if (convertedHeaderData[0] + convertedHeaderData[1] + convertedHeaderData[2] + convertedHeaderData[3] == 'R' + 'I' + 'F' + 'F')
	{
		unsigned int chunkSize = convertedHeaderData[4] + (convertedHeaderData[5] << 8) + (convertedHeaderData[6] << 16) + (convertedHeaderData[7] << 24);
		
		if (convertedHeaderData[8] + convertedHeaderData[9] + convertedHeaderData[10] + convertedHeaderData[11] == 'W' + 'A' + 'V' + 'E')
		{
			riff = new RiffChunk(chunkSize);
		}
		else
		{
			riff = nullptr;
		}
	}
	else
	{
		riff = nullptr;
	}
}

//This function loads all the information from the 2nd chunk in the Wave file into the fmt struct
void WavLoader::loadFmtChunk() {
	if (convertedHeaderData[12] + convertedHeaderData[13] + convertedHeaderData[14] + convertedHeaderData[15] == 'f' + 'm' + 't' + ' ')
	{
		fmt = new FormatChunk();
		fmt->fmtMark = 0x20746d66;
		fmt->fmtLength = convertedHeaderData[16] + (convertedHeaderData[17] << 8) + (convertedHeaderData[18] << 16) + (convertedHeaderData[19] << 24);
		fmt->fmtType = convertedHeaderData[20] + (convertedHeaderData[21] << 8);
		fmt->numberOfChannels = convertedHeaderData[22] + (convertedHeaderData[23] << 8);
		fmt->sampleRate = convertedHeaderData[24] + (convertedHeaderData[25] << 8) + (convertedHeaderData[26] << 16) + (convertedHeaderData[27] << 24);
		fmt->byteRate = convertedHeaderData[28] + (convertedHeaderData[29] << 8) + (convertedHeaderData[30] << 16) + (convertedHeaderData[31] << 24);
		fmt->blockAlign = convertedHeaderData[32] + (convertedHeaderData[33] << 8);
		fmt->bitsPerSample = convertedHeaderData[34] + (convertedHeaderData[35] << 8);
	}
	else
	{
		fmt = nullptr;
	}	
}
void WavLoader::loadDataChunk() {
	if (convertedHeaderData[36] + convertedHeaderData[37] + convertedHeaderData[38] + convertedHeaderData[39] == 'd' + 'a' + 't' + 'a')
	{
		data = new DataChunk();
		data->dataId = 0x61746164;
		data->dataSize = convertedHeaderData[40] + (convertedHeaderData[41] << 8) + (convertedHeaderData[42] << 16) + (convertedHeaderData[43] << 24);
		data->dataBlocks = new unsigned char[data->dataSize];
		for (int i = 0; i < data->dataSize; i++)
		{
			data->dataBlocks[i] = convertedHeaderData[44 + i];
		}

	}
}

unsigned int WavLoader::getTestInfo()
{
	return riff->chunkSize;
}

char* WavLoader::getBits()
{
	return wavInMemory;
}