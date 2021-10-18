#include "CImagesStorage.h"

namespace fs = std::filesystem;
using namespace std;

CImagesStorage::CImagesStorage(std::string const& path)
	: m_pathDirectory(path)
{
	fs::create_directories(path);
}

string CImagesStorage::AddFile(std::string const& filePath)
{
	fs::path path = filePath;

	string newFileName = GenerateUniqueFilename(path.filename().string());
	m_images.push_back(newFileName);

	fs::path newPath = m_pathDirectory;
	newPath /= newFileName;

	fs::copy_file(path.u8string(), newPath.u8string(), fs::copy_options::overwrite_existing);
	return newPath.string();
}

void CImagesStorage::RemoveFile(std::string const& fileName)
{
	fs::path imagePath = m_pathDirectory / fileName;
	fs::remove(imagePath.u8string());
}

string CImagesStorage::GenerateUniqueFilename(std::string const& originalFilename)
{
	fs::path fileName = originalFilename;
	fs::path fileExtension = fileName.extension();
	fs::path textFilename = fileName.stem();

	return textFilename.string() + '(' + to_string(m_images.size()) + ')' + fileExtension.string();
}