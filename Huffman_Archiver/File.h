#pragma once

#include "TypeAliases.h"
#include <cstdio>


namespace MyLib
{

class File
{
public:
	File(const char* fileName, const char* mode);
	File(const File& file) = delete;
	File(File&& file);

	~File();

	std::FILE* getHandle() { return handle; }

	byte read();
	void write(byte b);
	
	long tell() const;
	// Return true if success
	bool seek(long offset, int origin);
	void rewind();
	// Return true if EOF
	bool eof() const;

	// Return true if success
	bool close();

	File& operator=(const File& file) = delete;
	File& operator=(File&& file);

private:
	std::FILE* handle;

};

}
