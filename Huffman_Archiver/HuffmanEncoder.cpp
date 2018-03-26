#include "stdafx.h"
#include "HuffmanEncoder.h"
#include <set>
#include <utility>


namespace MyLib
{

using namespace std;


HuffmanEncoder::HuffmanEncoder(const char * filePath)
	: codes(numeric_limits<byte>::max() + 1, pair<ushort, byte>(0, 0))
	, outputCodeLength(0)
	, inputFile(filePath, "rb")
{
}

void HuffmanEncoder::encodeToFile(const char * outputFilePath)
{
	encode();

	OutputBitStream obstream(outputFilePath);

	// Output char-code table
	for (uint i = 0; i < codes.size(); i++)
	{
		// If codeLength > 0
		if (codes[i].second > 0)
		{
			// Write byte
			obstream.write(i, 8 * sizeof(byte));
			// Write codeLength
			obstream.write(codes[i].second, 8 * sizeof(byte));
			// Write code of byte
			obstream.write(codes[i].first, codes[i].second);
		}
	}

	// Output terminal zero ushort
	obstream.write((ushort)0, 8 * sizeof(ushort));

	// Output number of bits in last byte
	obstream.write((byte)(outputCodeLength % (8 * sizeof(byte))), 8 * sizeof(byte));

	// Write all code
	while (!inputFile.eof())
	{
		byte b;
		b = inputFile.read();
		obstream.write(codes[b].first, codes[b].second);
	}
}

void HuffmanEncoder::encode()
{
	// Vector of weight of bytes
	vector<uint> weights(numeric_limits<byte>::max() + 1, 0);
	countWeights(weights);

	set<WNode*, CmpWNodePtr_LessOrEqual> tree;

	// Copy elements from vector of weights to set of WNodes
	for (uint i = 0; i < weights.size(); i++)
	{
		if (weights[i] > 0)
		{
			tree.insert(new WNode(weights[i], i));
		}
	}

	while (tree.size() > 1)
	{
		// Take first minimal element (tree is sorted set)
		WNode* left = *tree.begin();
		tree.erase(tree.begin());

		// Take second minimal element (tree is sorted set)
		WNode* right = *tree.begin();
		tree.erase(tree.begin());

		// Insert parent for two minimal elements
		tree.insert(new WNode(left, right, left->getWeight() + right->getWeight()));
	}

	stack<TraverseDump> traverseStack;
	traverseStack.emplace(*tree.begin(), 0, 0);

	traverseAndSetCodes(traverseStack);
	delete *tree.begin();
}

void HuffmanEncoder::countWeights(vector<uint> & weights)
{
	while (!inputFile.eof())
	{
		byte b;
		b = inputFile.read();
		weights[b]++;
	}
	inputFile.rewind();
}

void HuffmanEncoder::traverseAndSetCodes(stack<TraverseDump> & traverseStack)
{
	while (traverseStack.size() > 0)
	{
		TraverseDump traverseDump = traverseStack.top();
		traverseStack.pop();

		if (!traverseDump.node->getLeft() || !traverseDump.node->getRight())				// Write code when we reach end
		{
			codes[traverseDump.node->getByte()].first = traverseDump.code;
			codes[traverseDump.node->getByte()].second = traverseDump.codeLength;
			outputCodeLength += (traverseDump.node->getWeight() + 1) * traverseDump.codeLength;
		}
		else
		{
			traverseStack.emplace(traverseDump.node->getLeft(), (traverseDump.code << 1), traverseDump.codeLength + 1);
			traverseStack.emplace(traverseDump.node->getRight(), (traverseDump.code << 1) + 1, traverseDump.codeLength + 1);
		}
	}
}

}
