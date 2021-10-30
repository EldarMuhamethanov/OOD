#include "CInsertImage.h"

using namespace std;
namespace fs = std::filesystem;

CInsertImage::CInsertImage(IDocument& document, const std::string& path, int width, int height, const size_t position)
	: m_document(document)
	, m_path(path)
	, m_width(width)
	, m_height(height)
	, m_position(position)
{}

CInsertImage::~CInsertImage()
{
	fs::path path = m_newPath;
	string fileName = path.filename().string();
	m_document.GetImageStorage().RemoveFile(fileName);
}

void CInsertImage::DoExecute()
{
	std::shared_ptr<IImage> image = m_document.InsertImage(m_path, m_width, m_height, m_position);
	m_newPath = image->GetPath();
}

void CInsertImage::DoUnexecute()
{
	m_document.DeleteItem(m_position);
}