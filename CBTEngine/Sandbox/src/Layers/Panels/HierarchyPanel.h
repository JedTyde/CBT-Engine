#pragma once

#include "Panels.h"

class HierarchyPanel : public Panels
{
public:
	HierarchyPanel();
	virtual ~HierarchyPanel();

	void Draw() override;
};