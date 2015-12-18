#ifndef TONE_H
#define TONE_H
struct Tone
{
	int startTime;
	int frequency;
	short duration;

public:
	Tone(int _frequency, int _startTime, short _duration);
};

#endif