#include "CImage.h"

using namespace std;

CImage::CImage(string path, int width, int height)
	: m_filePath(path)
	, m_width(width)
	, m_height(height)
{}
std::string CImage::GetPath()const
{
	return m_filePath;
}
int CImage::GetWidth()const
{
	return m_width;
}
int CImage::GetHeight()const
{
	return m_height;
}
void CImage::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}