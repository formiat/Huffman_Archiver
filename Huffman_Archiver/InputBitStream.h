#pragma once

#include <cstdio>

using byte = unsigned char;
using ushort = unsigned short;


class InputBitStream
{
public:
	InputBitStream(const char* filePath);

	// Returns highest bit of the byte from file
	bool get();

	// Returns num bits of the byte from file
	byte read(byte num);

	inline bool eof() const { return std::feof(inputFile); }

	inline bool lastByte() const { return std::ftell(inputFile) == lastByteNumber; }

	void clear();
	void seekg(long offset, int origin);

	~InputBitStream();

private:
	void getWord();

private:
	std::FILE* inputFile;

	long lastByteNumber;

	byte buffer;

	// Number of pending bits
	char numberOfPendingBits;
};

