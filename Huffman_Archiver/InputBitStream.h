#pragma once

#include "TypeAliases.h"
#include "File.h"


namespace MyLib
{

class InputBitStream
{
public:
	InputBitStream(const char* filePath);

	// Returns highest bit of the byte from file
	bool get()
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

	// Returns num bits of the byte from file
	byte read(byte num);

	inline bool eof() const { return inputFile.eof(); }

	inline bool lastByte() const { return inputFile.tell() == lastByteNumber; }

	void clear() { inputFile.rewind(); }
	void seekg(long offset, int origin) { inputFile.seek(offset, origin); }

private:
	void getWord()
	{
		buffer = inputFile.read();

		if (eof())
		{
			buffer = 0;
			return;
		}

		numberOfPendingBits = 8 * sizeof buffer;
	}

private:
	File inputFile;

	long lastByteNumber;

	byte buffer;

	// Number of pending bits
	char numberOfPendingBits;
};

}
