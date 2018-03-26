#pragma once

#include "TypeAliases.h"
#include "InputBitStream.h"
#include <vector>


namespace MyLib
{

class Node
{
public:
	Node(byte b = 0) : left(nullptr), right(nullptr), b(b) {}
	Node(const Node& node) = delete;

	~Node() { delete left; delete right; }

	inline Node* getLeft() const { return left; }
	inline Node* getRight() const { return right; }
	inline byte getByte() const { return b; }

	inline void setLeft(Node* l) { left = l; }
	inline void setRight(Node* r) { right = r; }
	inline void setByte(byte b) { this->b = b; }

	Node& operator= (const Node& node) = delete;

private:
	Node* left;		// 0
	Node* right;	// 1
	byte b;
};

class HuffmanDecoder
{
public:
	HuffmanDecoder(const char* filePath);
	HuffmanDecoder(const HuffmanDecoder& huffmanDec) = delete;

	~HuffmanDecoder();

	void decodeToFile(const char* resultFilePath);

	HuffmanDecoder& operator= (const HuffmanDecoder& huffmanDec) = delete;

private:
	// Get pairs char-code from inputCodesString and fill with Tree them
	void parseCodesAndFillTree(InputBitStream& ibstream, byte& numOfBitsInLastByte);

private:
	std::string inputFilePath;

	Node* head;
};

}
