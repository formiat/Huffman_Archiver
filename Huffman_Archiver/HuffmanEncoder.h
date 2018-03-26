#pragma once

#include "TypeAliases.h"
#include "OutputBitStream.h"
#include "File.h"
#include <vector>
#include <stack>


namespace MyLib
{

class WNode
{
public:
	// For last level
	WNode(uint w, byte b) : left(nullptr), right(nullptr), w(w), b(b) {}
	// For all levels, except last
	WNode(WNode* left, WNode* right, uint w) : left(left), right(right), w(w) {}
	WNode(const WNode& node) = delete;

	~WNode() { delete left; delete right; }

	inline WNode* getLeft() const { return left; }
	inline WNode* getRight() const { return right; }
	inline uint getWeight() const { return w; }
	inline byte getByte() const { return b; }

	WNode& operator= (const WNode& node) = delete;

private:
	WNode* left;		// Edge. Weight == 0
	WNode* right;		// Edge. Weight == 1
	uint w;				// Weight (count of occurrences)
	byte b;				// byte
};

struct CmpWNodePtr_LessOrEqual
{
	bool operator() (const WNode* node1, const WNode* node2) { return node1->getWeight() <= node2->getWeight(); }
};

struct TraverseDump
{
	TraverseDump(WNode* node, ushort code, byte codeLength) : node(node), code(code), codeLength(codeLength) {}

	WNode* node;
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

	void createTreeAndSetHead(std::vector<uint>& weights);

	// Traverse tree and set codes
	void traverseAndSetCodes(std::stack<TraverseDump>& traverseStack);

	void encode();

private:
	File inputFile;

	ulong outputCodeLength;

	// Vector of codes of bytes
	std::vector<std::pair<ushort, byte>> codes;

	WNode* head;
};

}
