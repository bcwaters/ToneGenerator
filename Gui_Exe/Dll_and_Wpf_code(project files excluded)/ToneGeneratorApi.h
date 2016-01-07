// ToneGeneratorApi.h
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\Wav.h"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\Wav.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\DataChunk.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\FormatChunk.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\RiffChunk.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\WavLoader.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\WavWriter.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\ToneGenerator.cpp"
#include "C:\Users\Ryan\Desktop\GitHubRepos\ToneGenerator\Tone.cpp"


#pragma once

using namespace System;

namespace ToneGeneratorApi {

	public ref class ToneGeneratorApiClass
	{

		
	public:
		ToneGeneratorApiClass();
		int getResult();
		void loadWav(char* fileName);
		void writeWav( char * fileName);
		void encodeTones(int* tones, int count);
		
		int result;
		// TODO: Add your methods for this class here.

	private:
		Wav* wavPtr;
		
	};
}
