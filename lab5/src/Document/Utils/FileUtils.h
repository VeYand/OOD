#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <fstream>
#include <stdexcept>
#include <filesystem>

class FileUtils
{
public:
	static void CopyFiles(const std::string &inputFilePath, const std::string &outputFilePath)
	{
		std::ifstream inputFile(inputFilePath);
		if (!inputFile.is_open())
		{
			throw std::runtime_error("Failed to open " + inputFilePath + " for reading.");
		}

		const std::filesystem::path outputDir = std::filesystem::path(outputFilePath).parent_path();
		if (!outputDir.empty() && !exists(outputDir))
		{
			create_directories(outputDir);
		}

		std::ofstream outputFile(outputFilePath);
		if (!outputFile.is_open())
		{
			throw std::runtime_error("Failed to open " + outputFilePath + " for writing.");
		}

		CopyStreams(inputFile, outputFile);

		if (!inputFile.eof())
		{
			throw std::runtime_error("Error reading input file.");
		}
	}

	static void DeleteFileIfExists(const std::string &filePath)
	{
		if (std::filesystem::exists(filePath))
		{
			std::filesystem::remove(filePath);
		}
	}

private:
	static void CopyStreams(std::istream &inputFile, std::ostream &outputFile)
	{
		char buffer[4096];
		while (inputFile)
		{
			inputFile.read(buffer, sizeof(buffer));
			outputFile.write(buffer, inputFile.gcount());

			if (!outputFile)
			{
				throw std::runtime_error("Failed to save data on disk.");
			}
		}
	}
};

#endif // FILEUTILS_H
