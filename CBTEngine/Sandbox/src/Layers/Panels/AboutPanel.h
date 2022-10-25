#pragma once

#include "Panels.h"

class AboutPanel : public Panels
{
public:
	AboutPanel();
	virtual ~AboutPanel();

	void Draw() override;
};

