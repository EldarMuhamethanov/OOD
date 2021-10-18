#pragma once
#include <string>
#include <iostream>

class IImagesStorage
{
public:
	~IImagesStorage() = default;
	virtual std::string AddFile(std::string const& filePath) = 0;
	virtual void RemoveFile(std::string const& fileName) = 0;
};