#pragma once
#include <memory>
#include <vector>
#include "CShape.h"

class CPictureDraft
{

public:
	typedef std::vector<std::unique_ptr<IShape>> Storage;
	CPictureDraft();

	bool IsEmpty()const;

	void AddShape(std::unique_ptr<IShape>&& shape);
	size_t GetShapeCount() const;
	std::unique_ptr<IShape>& GetShape(size_t index);

	CPictureDraft(CPictureDraft&&) = default;
	CPictureDraft& operator=(CPictureDraft&&) = default;

	CPictureDraft(const CPictureDraft&) = delete;
	CPictureDraft& operator=(const CPictureDraft&) = delete;
private:
	Storage m_shapes;
};
