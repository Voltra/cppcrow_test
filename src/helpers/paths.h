#pragma once

#include <string>

namespace app{
	namespace helpers{
		inline std::string fromPublic(const std::string& str){ return "public" + str; }
		inline std::string fromStatic(const std::string& str){ return fromPublic("/assets/" + str); }
	}
}
