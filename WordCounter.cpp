#pragma once
#include <WordCounter.hpp>

namespace wcounter {

	Dictionary& operator+=(Dictionary& dict, const Dictionary& other) {
		for (const auto& pair : other) {
			++dict[pair.first];
		}
		return dict;
	}

	Dictionary operator+(const Dictionary& lhs, const Dictionary& rhs) {
		Dictionary dict(lhs);
		dict += rhs;
		return dict;
	}

	bool IsSpecialChar(unsigned char c) noexcept {
		std::string special_chars = "~!@#$%^&*().:;/?<>,-+_={}[]| '`\"";
		return special_chars.find(c) != special_chars.npos;
	}

#ifdef _WIN32
	char delim = '\r';
#else
	char delim = '\n';
#endif

	std::string ReadTextFile(fs::path path) {
		if (!fs::exists(path)) {
			throw std::runtime_error("File does not exist");
		}
		std::ifstream stream(path, std::ios::app);
		if (!stream.is_open()) {
			throw std::runtime_error("File could not be opened");
		}
		std::string result;
		std::string line;
		while (std::getline(stream, line, delim)) {
			result += line;
		}
		return result;
	}

	void WriteStatsInFile(const Dictionary& dict, std::string file_name) {
		std::ofstream stream(file_name);
		if (!stream.is_open()) {
			throw std::runtime_error("File could not be opened");
		}
		for (auto it = dict.begin(); it != dict.end(); ++it) {
			stream << (*it).first << " : " << (*it).second << '\n';
		}
		stream.close();
	}

	std::vector<std::string> SplitIntoWords(std::string_view str) noexcept {
		std::vector<std::string> words;
		std::string word;

		for (auto&& c : str) {
			if (IsSpecialChar(c)) {
				if (!word.empty()) {
					words.push_back(word);
					word = "";
				}
				continue;
			}
			word += c;
		}
		return words;
	}

	void StringToLowerCase(std::string& str) noexcept {
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	}


	Dictionary CountWords(fs::path path) {
		Dictionary dict;
		std::string text(ReadTextFile(path));
		auto words = SplitIntoWords(text);
		std::for_each(words.begin(), words.end(), StringToLowerCase);
		for (auto&& word : words) {
			std::cout << word << '\n';
			++dict[word];
		}
		return dict;
	}

	Dictionary CountWords(std::span<fs::path> paths) {
		Dictionary dict;
		for (auto&& path : paths) {
			dict += CountWords(path);
		}
		return dict;
	}

	std::string GetMostFrequentWord(const Dictionary& dict) noexcept {
		auto pr = std::max_element(dict.begin(), dict.end(), [](
		const std::pair<std::string, std::size_t>& p1,
		const std::pair<std::string, std::size_t>& p2) {
				return p1.second < p2.second;
		});
		return pr->first;
	}

	std::string GetLessFrequentWord(const Dictionary& dict) noexcept {
		auto pr = std::min_element(dict.begin(), dict.end(), [](
			const std::pair<std::string, std::size_t>& p1,
			const std::pair<std::string, std::size_t>& p2) {
				return p1.second < p2.second;
		});
		return pr->first;
	}
}