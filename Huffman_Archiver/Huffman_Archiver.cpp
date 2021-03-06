// Huffman_Archiver.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "HuffmanEncoder.h"
#include "HuffmanDecoder.h"

#include <iostream>
#include <string>


int main(int argc, char** argv)
{
	if (argc == 4)
	{
		if (std::string(argv[1]) == std::string("-c"))
		{
			MyLib::HuffmanEncoder huffmanEnc(argv[2]);
			huffmanEnc.encodeToFile(argv[3]);
			return 0;
		}
		else if (std::string(argv[1]) == std::string("-x"))
		{
			MyLib::HuffmanDecoder huffmanDec(argv[2]);
			huffmanDec.decodeToFile(argv[3]);
			return 0;
		}
	}

	std::cout << "Wrong parameters!" << std::endl;
	std::cout << "Parameters should be:" << std::endl;
	std::cout << "1) <action> = \'-c\' (compress) or \'-x\' (extract)" << std::endl;
	std::cout << "2) <input file name>" << std::endl;
	std::cout << "3) <output file name>" << std::endl;

	return 1;
}

