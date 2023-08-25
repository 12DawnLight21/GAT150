#pragma once
#include "radpidjson/include/rapidjson/document.h"
#include "Math/Vector2.h"
#include "Math/Color.h"
#include "Math/Rect.h"

#include <string>

#define READ_DATA(value, data) umbra::Json::Read(value, #data, data);
#define READ_DATA_REQUIRED(value, data) umbra::Json::Read(value, #data, data, true);

#define READ_NAME_DATA(value, name, data) umbra::Json::Read(value, name, data)
#define READ_NAME_DATA_REQUIRED(value, name, data) umbra::Json::Read(value, name, data, true)

#define HAS_DATA(value, data) value.HasMember(#data)
#define GET_DATA(value, data) value[#data]

namespace umbra
{
	class Json
	{
	public:
		static bool Load(const std::string& filename, rapidjson::Document& document);
		static bool Read(const rapidjson::Value& value, const std::string& name, int& data, bool required = false);

		static bool Read(const rapidjson::Value& value, const std::string& name, float& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, bool& data, bool required = false);
		static bool Read(const rapidjson::Value& value, const std::string& name, std::string& data, bool required = false);

		static bool Read(const rapidjson::Value& value, const std::string& name, Vector2& data, bool required = false);

		static bool Read(const rapidjson::Value& value, const std::string& name, Color& data, bool required = false); //michael needs this
		static bool Read(const rapidjson::Value& value, const std::string& name, Rect& data, bool required = false); //michael needs this
	};

	using json_t = rapidjson::Value;
}