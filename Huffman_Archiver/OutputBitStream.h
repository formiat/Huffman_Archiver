#pragma once

#include <cstdio>

using byte = unsigned char;
using ushort = unsigned short;


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
	std::FILE* outputFile;

	byte buffer;

	// Number of pending bits
	char numberOfPendingBits;
};

