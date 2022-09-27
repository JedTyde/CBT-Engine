#pragma once

#include "CBTpch.h"
#include "Layer.h"

#include <vector>

namespace CBT {

	Layer::Layer(const std::string& debugName)
		: m_DebugName(debugName)
	{
	}

	Layer::~Layer()
	{

	}

}

