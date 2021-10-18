#pragma once
#include "IImage.h"

class CImage : public IImage
{
public:
	CImage(std::string path, int width, int height);
	std::string GetPath()const override;

	int GetWidth()const override;
	int GetHeight()const override;

	void Resize(int width, int height) override;
private:
	std::string m_filePath;
	int m_width = 0;
	int m_height = 0;
};