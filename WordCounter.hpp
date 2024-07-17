#pragma once
#include <algorithm>
#include <fstream>
#include <string>
#include <initializer_list>
#include <unordered_map>
#include <string_view>
#include <filesystem>
#include <span>

namespace fs = std::filesystem;

namespace wcounter {

	using Dictionary = std::unordered_map<std::string, std::size_t>;

	bool IsSpecialChar(unsigned char c) noexcept;
	std::vector<std::string> SplitIntoWords(std::string_view str) noexcept;
	void StringToLowerCase(std::string& str) noexcept;

	std::string ReadTextFile(fs::path path);
	void WriteStatsInFile(const Dictionary& dict, std::string file_name);

	Dictionary CountWords(fs::path path);
	Dictionary CountWords(std::span<fs::path> paths);

	std::string GetMostFrequentWord(const Dictionary& dict) noexcept;
	std::string GetLessFrequentWord(const Dictionary& dict) noexcept;
}