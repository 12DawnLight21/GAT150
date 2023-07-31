#pragma once
#include "Model.h"

#include <string>
#include <map>
#include <memory>

namespace umbra
{
	class ModelManager
	{
	public:
		std::shared_ptr<Model> Get(const std::string& filename);

	private:
		std::map<std::string, std::shared_ptr<Model>> m_models; //takes a key and stores values; a dictionary in c#

	};

	extern ModelManager g_manager;
}