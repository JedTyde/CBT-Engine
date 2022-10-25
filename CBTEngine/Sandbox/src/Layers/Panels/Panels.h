#pragma once

#include <string>

class Panels
{
public:
	Panels(const char* name);
	virtual ~Panels();

	void SetActive(bool enabled);
	void SwitchActive();
	bool IsActive() const;
	virtual void Draw() = 0;
	virtual void Update() {}
	const char* GetName() const { return name; }

public:
	bool active = true;
protected:
	const char* name;
};