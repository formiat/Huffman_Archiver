#include "stdafx.h"
#include "OutputBitStream.h"

using namespace std;


OutputBitStream::OutputBitStream(const char * filePath)
	: numberOfPendingBits(0)
	, buffer(0)
{
	fopen_s(&outputFile, filePath, "wb");
}

OutputBitStream::~OutputBitStream()
{
	if (numberOfPendingBits > 0)
	{
		buffer = (buffer << 8 * sizeof buffer - numberOfPendingBits);
		fwrite(&buffer, sizeof buffer, 1, outputFile);
	}
	fclose(outputFile);
}

void OutputBitStream::put(bool bit)
{
	buffer = buffer << 1;
	if (bit)
	{
		buffer += 1;
	}
	
	numberOfPendingBits++;

	if (numberOfPendingBits == 8 * sizeof buffer)
	{
		flush();
	}
}

void OutputBitStream::write(ushort word, byte num)
{
	while (num > 0)
	{
		// Clear not-needed bits
		word = (word << 8 * sizeof word - num);
		word = (word >> 8 * sizeof word - num);

		byte currentNum;

		if (num + numberOfPendingBits <= 8 * sizeof buffer)
		{
			currentNum = num;
		}
		else
		{
			currentNum = 8 * sizeof buffer - numberOfPendingBits;
		}

		num -= currentNum;
		buffer = (buffer << currentNum);
		buffer += (word >> num);
		numberOfPendingBits += currentNum;

		if (numberOfPendingBits == 8 * sizeof buffer)
		{
			flush();
		}
	}
}

void OutputBitStream::flush()
{
	fwrite(&buffer, sizeof buffer, 1, outputFile);
	buffer = 0;
	numberOfPendingBits = 0;
}
