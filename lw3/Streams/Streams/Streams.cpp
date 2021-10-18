#include <iostream>
#include <algorithm>
#include <fstream>
#include "CFileInputStream.h"
#include "CMemoryInputStream.h"
#include "CMemoryOutputStream.h"
#include "CFileOutputStream.h"
#include "CCompressedOutputStream.h"
#include "CDecompressedInputStream.h"
#include "CEncryptorOutputStream.h"
#include "CDecryptorInputStream.h"
#include "Encryptor.h"
#include <random>

using namespace std;

const string ENCRYPT = "--encrypt";
const string DECRYPT = "--decrypt";
const string COMPRESS = "--compress";
const string DECOMPRESS = "--decompress";

enum class ActionType{
	Compress,
	Decompress,
	Encrypt,
	Decrypt,
};

struct Action {
	ActionType type;
	int value;
};

struct Args
{
	string inputFilename;
	string outputFilename;
	vector<Action> actions;
};

ActionType getActionTypeByString(string const& str)
{
	if (str == ENCRYPT)
		return ActionType::Encrypt;
	if (str == DECRYPT)
		return ActionType::Decrypt;
	if (str == COMPRESS)
		return ActionType::Compress;
	if (str == DECOMPRESS)
		return ActionType::Decompress;
	throw exception("unknown action string");
}

Args ParseArgs(int argc, char* argv[]) {
	Args args;
	args.inputFilename = argv[argc - 2];
	args.outputFilename = argv[argc - 1];

	int argIndex = 1;
	while (argIndex < argc - 2) {
		string arg = argv[argIndex];
		Action action;
		action.type = getActionTypeByString(arg);
		switch (action.type)
		{
		case ActionType::Compress:
			action.value = 0;
			argIndex++;
			break;
		case ActionType::Decompress:
			action.value = 0;
			argIndex++;
			break;
		case ActionType::Encrypt:
			action.value = atoi(argv[argIndex + 1]);
			argIndex += 2;
			break;
		case ActionType::Decrypt:
			action.value = atoi(argv[argIndex + 1]);
			argIndex += 2;
			break;
		default:
			break;
		}
		args.actions.push_back(action);
	}
	return args;
}

void DecorateStreams(unique_ptr<IInputDataStream>& input, unique_ptr<IOutputDataStream>& output, vector<Action> actions)
{
	for_each(actions.begin(), actions.end(), [&output](Action& action) {
		switch (action.type)
		{
		case ActionType::Compress:
			output = make_unique<CCompressedOutputStream>(move(output));
			break;
		case ActionType::Encrypt:
			output = make_unique<CEncryptorOutputStream>(move(output), make_unique<Encryptor>(action.value));
			break;
		default:
			break;
		}
	});
	for_each(actions.rbegin(), actions.rend(), [&input](Action& action) {
		switch (action.type)
		{
		case ActionType::Decompress:
			input = make_unique<CDecompressedInputStream>(move(input));
			break;
		case ActionType::Decrypt:
			input = make_unique<CDecryptorInputStream>(move(input), make_unique<Encryptor>(action.value));
			break;
		default:
			break;
		}
	});
}

int main(int argc, char* argv[])
{
	Args args = ParseArgs(argc, argv);

	unique_ptr<IInputDataStream> input = make_unique<CFileInputStream>(args.inputFilename);
	unique_ptr<IOutputDataStream> output = make_unique<CFileOutputStream>(args.outputFilename);
	vector<Action> actions = args.actions;
	DecorateStreams(input, output, actions);

	auto byte = input->ReadByte();
	while (!input->IsEOF())
	{
		output->WriteByte(byte);
		byte = input->ReadByte();
	}

	return 0;
}
