#include "stdafx.h"
#include "InputBitStream.h"

using namespace std;


InputBitStream::InputBitStream(const char * filePath)
	: numberOfPendingBits(0)
	, buffer(0)
{
	fopen_s(&inputFile, filePath, "rb");

	fseek(inputFile, 0, SEEK_END);

	lastByteNumber = ftell(inputFile);

	fseek(inputFile, 0, SEEK_SET);
}

bool InputBitStream::get()
{
	if (numberOfPendingBits == 0)
	{
		getWord();
		if (eof()) return 0;
	}

	bool tempBuffer = (bool)(0x80 & buffer);
	
	buffer = buffer << 1;

	numberOfPendingBits--;

	return tempBuffer;
}

byte InputBitStream::read(byte num)
{
	byte b;

	if (numberOfPendingBits >= num)
	{
		b = (buffer >> 8 * sizeof buffer - num);
		buffer = buffer << num;
		numberOfPendingBits -= num;
	}
	else
	{
		byte delta;
		delta = num - numberOfPendingBits;

		b = (buffer >> 8 * sizeof buffer - numberOfPendingBits);
		buffer = buffer << numberOfPendingBits;
		numberOfPendingBits = 0;

		getWord();
		if (eof()) return b;

		b = (b << delta);
		
		b += (buffer >> 8 * sizeof buffer - delta);
		buffer = buffer << delta;
		numberOfPendingBits -= delta;
	}
	
	if (numberOfPendingBits == 0)
	{
		getWord();
	}

	return b;
}

void InputBitStream::clear()
{
	rewind(inputFile);
}

void InputBitStream::seekg(long offset, int origin)
{
	fseek(inputFile, offset, origin);
}

InputBitStream::~InputBitStream()
{
	fclose(inputFile);
}

void InputBitStream::getWord()
{
	fread(&buffer, sizeof buffer, 1, inputFile);
	
	if (eof())
	{
		buffer = 0;
		return;
	}

	numberOfPendingBits = 8 * sizeof buffer;
}

