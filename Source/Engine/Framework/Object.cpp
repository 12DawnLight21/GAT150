#include "Object.h"

namespace umbra
{
	void Object::Read(const json_t& value)
	{
		READ_DATA(value, name);
	}
}