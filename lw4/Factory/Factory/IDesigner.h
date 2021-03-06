#include "CPictureDraft.h"

class IDesigner {
public:
	virtual ~IDesigner() = default;
	virtual CPictureDraft CreateDraft(std::istream& inputData) = 0;
};