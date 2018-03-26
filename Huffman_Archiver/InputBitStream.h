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
	bool get();

	// Returns num bits of the byte from file
	byte read(byte num);

	inline bool eof() const { return inputFile.eof(); }

	inline bool lastByte() const { return inputFile.tell() == lastByteNumber; }

	void clear();
	void seekg(long offset, int origin);

private:
	void getWord();

private:
	File inputFile;

	long lastByteNumber;

	byte buffer;

	// Number of pending bits
	char numberOfPendingBits;
};

}
