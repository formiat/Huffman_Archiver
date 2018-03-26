#include "stdafx.h"
#include "File.h"
#include <utility>


namespace MyLib
{

using namespace std;


File::File(const char * fileName, const char * mode)
{
	fopen_s(&handle, fileName, mode);
}

File::File(File && file)
{
	this->handle = file.handle;
	file.handle = nullptr;
}

File::~File()
{
	close();
}

byte File::read()
{
	byte b;
	fread(&b, sizeof b, 1, handle);
	return b;
}

void File::write(byte b)
{
	fwrite(&b, sizeof b, 1, handle);
}

long File::tell() const
{
	return ftell(handle);
}

bool File::seek(long offset, int origin)
{
	return !fseek(handle, offset, origin);
}

void File::rewind()
{
	std::rewind(handle);
}

bool File::eof() const
{
	return feof(handle);
}

bool File::close()
{
	return !fclose(handle);
}

File & File::operator=(File && file)
{
	std::swap(this->handle, file.handle);
	return *this;
}

}
