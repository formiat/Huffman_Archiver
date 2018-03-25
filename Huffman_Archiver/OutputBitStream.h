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
	template<bool safe = false> void write(ushort word, byte num);

private:
	void flush();

private:
	std::FILE* outputFile;

	byte buffer;

	// Number of pending bits
	char numberOfPendingBits;
};

template<bool safe>
inline void OutputBitStream::write(ushort word, byte num)
{
	// If safe then clear not-needed bits
	if (safe)
	{
		word = (word << 8 * sizeof word - num);
		word = (word >> 8 * sizeof word - num);
	}

	if (num + numberOfPendingBits <= 8 * sizeof buffer)
	{
		buffer = (buffer << num);
		buffer += word;

		numberOfPendingBits += num;
	}
	else
	{
		byte currentNum;
		currentNum = 8 * sizeof buffer - numberOfPendingBits;

		byte delta;
		delta = num - currentNum;

		buffer = (buffer << currentNum);
		buffer += (word >> delta);
		
		numberOfPendingBits = 8 * sizeof buffer;

		flush();

		if (delta > 8 * sizeof buffer)
		{
			// Clear flushed bits
			word = (word << 8 * sizeof word - delta);
			word = (word >> 8 * sizeof word - delta);

			currentNum = 8 * sizeof buffer;
			delta = delta - currentNum;

			buffer += (word >> delta);
			numberOfPendingBits = 8 * sizeof buffer;
			flush();
		}

		// Clear flushed bits
		word = (word << 8 * sizeof word - delta);
		word = (word >> 8 * sizeof word - delta);

		buffer += word;

		numberOfPendingBits = delta;
	}

	if (numberOfPendingBits == 8 * sizeof buffer)
	{
		flush();
	}
}
