#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#include "InputStream/CFileInputStream.h"
#include "InputStream/Decorator/CDecompressInputStream.h"
#include "InputStream/Decorator/CDecryptInputStream.h"
#include "OutputStream/CFileOutputStream.h"
#include "OutputStream/Decorator/CCompressOutputStream.h"
#include "OutputStream/Decorator/CEncryptOutputStream.h"

template<typename Decorator, typename... Args>
auto MakeDecorator(const Args &... args)
{
	return [=]<typename T>(T &&b) {
		return std::make_unique<Decorator>(std::forward<T>(b), args...);
	};
}

template<typename Component, typename Decorator>
auto operator<<(Component &&component, const Decorator &decorate)
{
	return decorate(std::forward<Component>(component));
}


void ShowUsage(const std::string& name)
{
	std::cout << "Usage: " << name << " [options] <input-file> <output-file>\n"
			<< "Options:\n"
			<< "--encrypt <key>    : Adds an encryption step using the given key\n"
			<< "--decrypt <key>    : Adds a decryption step using the given key\n"
			<< "--compress         : Adds compression step\n"
			<< "--decompress       : Adds decompression step\n";
}

int main(const int argc, char *argv[])
{
	if (argc < 3)
	{
		ShowUsage(argv[0]);
		return 1;
	}

	std::vector<std::function<std::unique_ptr<IInputDataStream>(std::unique_ptr<IInputDataStream>)> > inputDecorators;
	std::vector<std::function<std::unique_ptr<IOutputDataStream>(std::unique_ptr<IOutputDataStream>)> >
			outputDecorators;

	const char *inputFile = nullptr;
	const char *outputFile = nullptr;

	for (int i = 1; i < argc; ++i)
	{
		if (strcmp(argv[i], "--encrypt") == 0 && i + 1 < argc)
		{
			int key = std::stoi(argv[++i]);
			outputDecorators.emplace_back(MakeDecorator<CEncryptOutputStream>(key));
		}
		else if (strcmp(argv[i], "--decrypt") == 0 && i + 1 < argc)
		{
			int key = std::stoi(argv[++i]);
			inputDecorators.emplace_back(MakeDecorator<CDecryptInputStream>(key));
		}
		else if (strcmp(argv[i], "--compress") == 0)
		{
			outputDecorators.emplace_back(MakeDecorator<CCompressOutputStream>());
		}
		else if (strcmp(argv[i], "--decompress") == 0)
		{
			inputDecorators.emplace_back(MakeDecorator<CDecompressInputStream>());
		}
		else if (!inputFile)
		{
			inputFile = argv[i];
		}
		else if (!outputFile)
		{
			outputFile = argv[i];
		}
		else
		{
			ShowUsage(argv[0]);
			return 1;
		}
	}

	if (!inputFile || !outputFile)
	{
		ShowUsage(argv[0]);
		return 1;
	}

	std::unique_ptr<IInputDataStream> inputStream = std::make_unique<CFileInputStream>(inputFile);
	std::unique_ptr<IOutputDataStream> outputStream = std::make_unique<CFileOutputStream>(outputFile);


	for (const auto &decorator: inputDecorators)
	{
		inputStream = std::move(inputStream) << decorator;
	}

	for (const auto &decorator: outputDecorators)
	{
		outputStream = std::move(outputStream) << decorator;
	}

	char buffer[2];
	while (!inputStream->IsEOF())
	{
		const auto bytesRead = inputStream->ReadBlock(buffer, sizeof(buffer));
		outputStream->WriteBlock(buffer, bytesRead);

		if (!inputStream->IsEOF())
		{
			const auto ch = inputStream->ReadByte();
			outputStream->WriteByte(ch);
		}
	}

	// while (!inputStream->IsEOF())
	// {
	// 	const auto ch = inputStream->ReadByte();
	// 	outputStream->WriteByte(ch);
	// }

	// char buffer[2];
	// while (!inputStream->IsEOF())
	// {
	// 	const auto bytesRead = inputStream->ReadBlock(buffer, sizeof(buffer));
	// 	outputStream->WriteBlock(buffer, bytesRead);
	// }

	return 0;
}
