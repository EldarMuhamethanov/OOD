#include "CPictureDraft.h"
#include <stdexcept>


using namespace std;

CPictureDraft::CPictureDraft()
{}

bool CPictureDraft::IsEmpty() const
{
	return m_shapes.empty();
}

size_t CPictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

unique_ptr<IShape>& CPictureDraft::GetShape(size_t index)
{
	if (index < GetShapeCount())
	{
		return m_shapes.at(index);
	}
	throw out_of_range("index is out of range");
}
 
void CPictureDraft::AddShape(std::unique_ptr<IShape>&& shape)
{
	m_shapes.push_back(move(shape));
}


