#pragma once
#include "Panels.h"


class InspectorPanel : public Panels
{
public:
	InspectorPanel();
	~InspectorPanel();

	void Draw() override;

private:
	//void ShowObjectHierarchy(GameObject* obj);
	bool addComp = false;
};