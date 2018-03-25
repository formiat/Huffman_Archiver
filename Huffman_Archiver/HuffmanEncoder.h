#pragma once

#include "OutputBitStream.h"
#include <cstdio>
#include <vector>
#include <stack>

using byte = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using ulong = unsigned long long;


class Node_w
{
public:
	// For last level
	Node_w(uint w, byte b) : left(nullptr), right(nullptr), w(w), b(b) {}
	// For all levels, except last
	Node_w(Node_w* left, Node_w* right, uint w) : left(left), right(right), w(w) {}
	Node_w(const Node_w& node) = delete;

	~Node_w() { delete left; delete right; }

	inline Node_w* getLeft() const { return left; }
	inline Node_w* getRight() const { return right; }
	inline uint getWeight() const { return w; }
	inline byte getByte() const { return b; }

	Node_w& operator= (const Node_w& node) = delete;

private:
	Node_w* left;		// Edge. Weight == 0
	Node_w* right;		// Edge. Weight == 1
	uint w;				// Weight (count of occurrences)
	byte b;				// byte
};

struct CmpNode_wPtr_LessOrEqual
{
	bool operator() (const Node_w* node1, const Node_w* node2) { return node1->getWeight() <= node2->getWeight(); }
};

struct TraverseDump
{
	TraverseDump(Node_w* node, ushort code, byte codeLength) : node(node), code(code), codeLength(codeLength) {}

	Node_w* node;
	ushort code;
	byte codeLength;
};

class HuffmanEncoder
{
public:
	HuffmanEncoder(const char* filePath);
	HuffmanEncoder(const HuffmanEncoder& huffmanEnc) = delete;

	~HuffmanEncoder();

	void encodeToFile(const char* outputFilePath);

	HuffmanEncoder& operator= (const HuffmanEncoder& huffmanEnc) = delete;

private:
	// Count weight for every symbol. Returns inputFileStream to zero position.
	void countWeights(std::vector<uint>& weights);

	// Traverse tree and set codes
	void traverseAndSetCodes(std::stack<TraverseDump>& traverseStack);

	void encode();

private:
	std::FILE* inputFile;

	ulong outputCodeLength;

	// Vector of codes of bytes
	std::vector<std::pair<ushort, byte>> codes;
};

