#pragma once

#include "TypeAliases.h"
#include <cstdio>
#include <utility>


namespace MyLib
{

using namespace std;


class File
{
public:
	File(const char* fileName, const char* mode) { fopen_s(&handle, fileName, mode); }
	File(const File& file) = delete;
	File(File&& file) { this->handle = file.handle; file.handle = nullptr; }

	~File() { close(); }

	std::FILE* getHandle() { return handle; }

	byte read() { byte b; fread(&b, sizeof b, 1, handle); return b; }
	void write(byte b) { fwrite(&b, sizeof b, 1, handle); }
	
	long tell() const { return ftell(handle); }
	// Return true if success
	bool seek(long offset, int origin) { return !fseek(handle, offset, origin); }
	void rewind() { std::rewind(handle); }
	// Return true if EOF
	bool eof() const { return feof(handle); }

	// Return true if success
	bool close() { return !fclose(handle); }

	File& operator=(const File& file) = delete;
	File& operator=(File&& file) { std::swap(this->handle, file.handle); return *this; }

private:
	std::FILE* handle;

};

}
