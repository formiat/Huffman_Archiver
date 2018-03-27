#include "stdafx.h"
#include "HuffmanDecoder.h"
#include "File.h"


namespace MyLib
{

using namespace std;


HuffmanDecoder::HuffmanDecoder(const char * filePath)
	: inputFilePath(filePath)
	, head(new Node())
{
}

HuffmanDecoder::~HuffmanDecoder()
{
	delete head;
}

void HuffmanDecoder::decodeToFile(const char * resultFilePath)
{
	File outputFile(resultFilePath, "wb");
	InputBitStream ibstream(inputFilePath.c_str());
	byte numOfBitsInLastByte;

	parseCodesAndFillTree(ibstream, numOfBitsInLastByte);
	
	bool bitOfCode = ibstream.get();
	Node* current = head;
	while (!ibstream.eof())
	{
		if (!current->getLeft() && !current->getRight())
		{
			outputFile.write(current->getByte());
			current = head;
		}

		if (bitOfCode)					// If bit is '1' (true)
		{
			current = current->getRight();
		}
		else
		{
			current = current->getLeft();
		}

		if (ibstream.lastByte())
		{
			numOfBitsInLastByte--;
			if (numOfBitsInLastByte == 0)
			{
				break;
			}
		}

		bitOfCode = ibstream.get();
	}
}

void HuffmanDecoder::parseCodesAndFillTree(InputBitStream & ibstream, byte & numOfBitsInLastByte)
{
	while (!ibstream.eof())
	{
		byte b;
		b = ibstream.read(8 * sizeof(byte));

		byte codeLength;
		codeLength = ibstream.read(8 * sizeof(byte));

		if (codeLength == 0)
		{
			numOfBitsInLastByte = ibstream.read(8 * sizeof(byte));
			return;
		}

		Node* current = head;
		for (int i = 0; i < codeLength; i++)
		{
			bool bitOfCode;
			bitOfCode = ibstream.get();

			if (bitOfCode)					// If bit is '1' (true)
			{
				if (!current->getRight())
				{
					current->setRight(new Node());
				}
				current = current->getRight();
			}
			else
			{
				if (!current->getLeft())
				{
					current->setLeft(new Node());
				}
				current = current->getLeft();
			}
		}
		current->setByte(b);
	}
}

}
