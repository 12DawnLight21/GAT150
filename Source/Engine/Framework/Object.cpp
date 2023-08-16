#include "Object.h"

namespace umbra
{
	bool Object::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, name)

		return true;
	}
}