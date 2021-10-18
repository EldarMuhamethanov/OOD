#pragma once
#include <filesystem>
#include <iostream>
#include <string>
#include <map>
#include "IImageStorage.h"

class CImagesStorage: public IImagesStorage
{
public:
	CImagesStorage(std::string const& path);

	std::string AddFile(std::string const& filePath) override;
	void RemoveFile(std::string const& fileName) override;
private:
	std::string GenerateUniqueFilename(std::string const& originalFilename);

	std::filesystem::path m_pathDirectory;
	std::vector<std::string> m_images;
};

