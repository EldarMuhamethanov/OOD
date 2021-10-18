#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../../Streams/Streams/CMemoryOutputStream.h"
#include "../../Streams/Streams/CMemoryInputStream.h"
#include "../../Streams/Streams/CFileOutputStream.h"
#include "../../Streams/Streams/CFileInputStream.h"
#include "../../Streams/Streams/CDecompressedInputStream.h"
#include "../../Streams/Streams/CCompressedOutputStream.h"
#include "../../Streams/Streams/CEncryptorOutputStream.h"
#include "../../Streams/Streams/CDecryptorInputStream.h"

using namespace std;

void WriteByteToFile(uint8_t byte, string const& fileName) {
    CFileOutputStream file(fileName);
    file.WriteByte(byte);
}

void WriteBlockToFile(const void* srcData, streamsize size, string const& fileName) {
    CFileOutputStream file(fileName);
    file.WriteBlock(srcData, size);
}


SCENARIO("Write 1 byte to memory")
{
    std::vector<uint8_t> data;
    CMemoryOutputStream memoryOutput(data);
    uint8_t symb = 1;
    memoryOutput.WriteByte(symb);
    REQUIRE(data[0] == symb);
}

SCENARIO("Write 10 bytes to memory at once ")
{
    std::vector<uint8_t> data;
    CMemoryOutputStream memoryOutput(data);
    const char* dataOutput = new char[10];
    dataOutput = "mememememe";
    memoryOutput.WriteBlock(dataOutput, 10);
    REQUIRE(data[0] == dataOutput[0]);
    REQUIRE(data[1] == dataOutput[1]);
    REQUIRE(data[2] == dataOutput[2]);
    REQUIRE(data[3] == dataOutput[3]);
    REQUIRE(data[4] == dataOutput[4]);
    REQUIRE(data[5] == dataOutput[5]);
    REQUIRE(data[9] == dataOutput[9]);
}

SCENARIO("Read 1 byte from memory")
{
    std::vector<uint8_t> data;
    uint8_t symbol = 1;
    data.push_back(symbol);
    CMemoryInputStream memoryInput(data);
    const char* dataOutput = new char[10];

    uint8_t readed = memoryInput.ReadByte();
    REQUIRE(readed == symbol);
}

SCENARIO("Read 10 bytes from memory")
{
    std::vector<uint8_t> data;
    uint8_t symbol1 = 1;
    uint8_t symbol2 = 2;
    for (int i = 0; i < 5; i++)
    {
        data.push_back(symbol1);
        data.push_back(symbol2);
    }
    CMemoryInputStream memoryInput(data);
    char* dataOutput = new char[10];
    memoryInput.ReadBlock(dataOutput, 10);
    REQUIRE(data[0] == dataOutput[0]);
    REQUIRE(data[1] == dataOutput[1]);
    REQUIRE(data[2] == dataOutput[2]);
    REQUIRE(data[3] == dataOutput[3]);
    REQUIRE(data[4] == dataOutput[4]);
    REQUIRE(data[9] == dataOutput[9]);
}

SCENARIO("Write  1 byte to file")
{
    uint8_t symb = 'm';
    std::string fileName = "output.txt";
    WriteByteToFile(symb, fileName);
    ifstream outputFile(fileName, ios::binary);
    std::vector<uint8_t> data;
    char readSymbol;
    outputFile.read(&readSymbol, 1);
    REQUIRE(readSymbol == symb);
}

SCENARIO("Write block of symbols to file")
{
    const char* testString = new char[10];
    testString = "checkstring";
    std::string fileName = "output.txt";
    WriteBlockToFile(testString, 10, fileName);
    ifstream inputFile(fileName, ios::binary);
    std::vector<uint8_t> data;
    char* resultString = new char[10];
    for (int i = 0; i < 10; i++)
        inputFile >> resultString[i];
    REQUIRE(resultString[0] == testString[0]);
    REQUIRE(resultString[1] == testString[1]);
    REQUIRE(resultString[2] == testString[2]);
    REQUIRE(resultString[3] == testString[3]);
    REQUIRE(resultString[4] == testString[4]);
    REQUIRE(resultString[5] == testString[5]);
    REQUIRE(resultString[9] == testString[9]);
}

SCENARIO("Read 1 byte from file")
{
    std::string fileName = "input.txt";
    ofstream inputFile(fileName, ios::binary);
    uint8_t symbol = 'a';
    inputFile << symbol;
    inputFile.close();
    CFileInputStream memoryInput(fileName);
    REQUIRE(memoryInput.ReadByte() == symbol);
}

SCENARIO("Read 10 bytes from file")
{
    std::string fileName = "input.txt";
    ofstream inputFile(fileName, ios::binary);
    const char* data = new char[10];
    data = "checkstring";
    for (int i = 0; i < 10; i++)
    {
        inputFile << data[i];
    }
    inputFile.close();
    CFileInputStream memoryInput(fileName);
    uint8_t* dataOutput = new uint8_t[10];
    memoryInput.ReadBlock(dataOutput, 10);
    REQUIRE(data[0] == dataOutput[0]);
    REQUIRE(data[1] == dataOutput[1]);
    REQUIRE(data[2] == dataOutput[2]);
    REQUIRE(data[3] == dataOutput[3]);
    REQUIRE(data[4] == dataOutput[4]);
    REQUIRE(data[9] == dataOutput[9]);
}


void CompressMemory(unique_ptr<CMemoryInputStream> input, vector<uint8_t>& v)
{
    unique_ptr<CMemoryOutputStream> outputStream = make_unique<CMemoryOutputStream>(v);
    CCompressedOutputStream compressed(move(outputStream));


    auto byte = input->ReadByte();
    while (!input->IsEOF())
    {
        compressed.WriteByte(byte);
        byte = input->ReadByte();
    }
}

void DecompressMemory(shared_ptr<CMemoryOutputStream> finalstream, vector<uint8_t>& v)
{
    unique_ptr<CMemoryInputStream> inputStream = make_unique<CMemoryInputStream>(v);
    CDecompressedInputStream decompressed(move(inputStream));

    auto byte = decompressed.ReadByte();
    while (!decompressed.IsEOF())
    {
        finalstream->WriteByte(byte);
        byte = decompressed.ReadByte();
    }
}


SCENARIO("compressed memory when decompressed")
{
    string startValue = "112234";
    vector<uint8_t> data(startValue.begin(), startValue.end());
    unique_ptr<CMemoryInputStream> input = make_unique<CMemoryInputStream>(data);

    vector<uint8_t> compressed;
    CompressMemory(move(input), compressed);

    vector<uint8_t> decompressed;
    unique_ptr<CMemoryOutputStream> finalstream = make_unique<CMemoryOutputStream>(decompressed);
    DecompressMemory(move(finalstream), compressed);

    REQUIRE(decompressed == data);
}


void EncryptMemory(unique_ptr<CMemoryInputStream> input, vector<uint8_t>& v, int key)
{
    unique_ptr<CMemoryOutputStream> outputStream = make_unique<CMemoryOutputStream>(v);
    CEncryptorOutputStream encprypt(move(outputStream), make_unique<Encryptor>(key));


    auto byte = input->ReadByte();
    while (!input->IsEOF())
    {
        encprypt.WriteByte(byte);
        byte = input->ReadByte();
    }
}

void DecryptMemory(shared_ptr<CMemoryOutputStream> finalstream, vector<uint8_t>& v, int key)
{
    unique_ptr<CMemoryInputStream> inputStream = make_unique<CMemoryInputStream>(v);
    CDecryptorInputStream decryptor(move(inputStream), make_unique<Encryptor>(key));

    auto byte = decryptor.ReadByte();
    while (!decryptor.IsEOF())
    {
        finalstream->WriteByte(byte);
        byte = decryptor.ReadByte();
    }
}


SCENARIO("encrypt memory when decrypt")
{
    string startValue = "112234";
    vector<uint8_t> data(startValue.begin(), startValue.end());
    unique_ptr<CMemoryInputStream> input = make_unique<CMemoryInputStream>(data);

    vector<uint8_t> compressed;
    EncryptMemory(move(input), compressed, 5);

    vector<uint8_t> encrypted;
    unique_ptr<CMemoryOutputStream> finalstream = make_unique<CMemoryOutputStream>(encrypted);
    DecryptMemory(move(finalstream), compressed, 5);

    REQUIRE(encrypted == data);
}