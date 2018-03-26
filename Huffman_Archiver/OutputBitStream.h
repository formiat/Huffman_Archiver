#pragma once

#include "TypeAliases.h"
#include "File.h"


namespace MyLib
{

class OutputBitStream
{
public:
	OutputBitStream(const char* filePath);

	~OutputBitStream();

	// Puts bit to file
	void put(bool bit);

	// Puts num bits of word to file
	void write(ushort word, byte num);

private:
	void flush();

private:
	File outputFile;

	byte buffer;

	// Number of pending bits
	char numberOfPendingBits;
};

}
