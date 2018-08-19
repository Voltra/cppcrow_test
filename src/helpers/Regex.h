#pragma once

#include <regex>
#include <string>

namespace app{
	namespace helpers{
		class Regex{
			public:
				using regex = std::regex;
				using cstring = const char*;
				using string = std::string;
				using matches_t = std::smatch;
			
			protected:
				regex re;
				
			public:
				Regex() = delete;
				Regex(const Regex&) = default;
				Regex(Regex&&) = default;
			
				Regex(const string& str) : re{str}{
				}
				
				Regex(const cstring& cstr) : re{cstr}{
				}
				
				Regex(const regex& re) : re{re}{
				}
				
				bool appliesTo(const string& str) const{
					return std::regex_search(str, this->re);
				}
				
				bool appliesTo(const cstring& cstr) const{
					return std::regex_search(cstr, this->re);
				}
				
				matches_t getMatchesFrom(const string& str) const{
					matches_t matches;
					std::regex_search(str, matches, this->re); //side effects on matches
					return matches;
				}
				
				matches_t getMatchesFrom(const cstring& cstr) const{
					return this->getMatchesFrom(std::string{cstr});
				}
				
		};
	}
}
