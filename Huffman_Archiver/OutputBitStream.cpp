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

void OutputBitStream::flush()
{
	fwrite(&buffer, sizeof buffer, 1, outputFile);
	buffer = 0;
	numberOfPendingBits = 0;
}
