#include "Panels.h"

Panels::Panels(const char* name) : name(name)
{}

Panels::~Panels()
{}

void Panels::SetActive(bool enabled)
{
	active = enabled;
}

void Panels::SwitchActive()
{
	active = !active;
}

bool Panels::IsActive() const
{ 
	return active;
}
