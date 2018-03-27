#include "stdafx.h"
#include "InputBitStream.h"


namespace MyLib
{

using namespace std;


InputBitStream::InputBitStream(const char * filePath)
	: numberOfPendingBits(0)
	, buffer(0)
	, inputFile(filePath, "rb")
{
	inputFile.seek(0, SEEK_END);

	lastByteNumber = inputFile.tell();

	inputFile.seek(0, SEEK_SET);
}

byte InputBitStream::read(byte num)
{
	byte b = 0;

	while (num > 0)
	{
		byte currentNum;

		if (numberOfPendingBits >= num)
		{
			currentNum = num;
		}
		else
		{
			currentNum = numberOfPendingBits;
		}

		b = (b << currentNum);
		b += (buffer >> 8 * sizeof buffer - currentNum);
		buffer = (buffer << currentNum);
		numberOfPendingBits -= currentNum;
		num -= currentNum;

		if (numberOfPendingBits == 0)
		{
			getWord();
			if (eof()) return b;
		}
	}

	return b;
}

void InputBitStream::getWord()
{
	buffer = inputFile.read();

	if (eof())
	{
		buffer = 0;
		return;
	}

	numberOfPendingBits = 8 * sizeof buffer;
}

}
