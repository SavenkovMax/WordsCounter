#pragma once
#include "WordCounter.hpp"

namespace wcounter {

	template <typename S = std::string>
	std::vector<S> SplitIntoWords(std::string_view str) {
		std::vector<S> results;
		std::string word;

		auto IsAlpha = [](unsigned char c) {
			return std::isalpha(c);
			};

		for (auto it = str.begin(); it != str.end(); ++it) {
			if (IsAlpha(*it)) {
				word += *it;
				if (std::distance(it, str.end()) == 1) {
					results.push_back(word);
				}
			}
			else {
				if (!word.empty()) {
					results.push_back(word);
				}
				word.clear();
			}
		}

		return results;
	}

	void MergeDict(std::unordered_map<std::string, size_t>& dist, const std::unordered_map<std::string, size_t>& source) {
		for (auto& el : source) {
			++dist[el.first];
		}
	}

	template <typename K, typename V, typename Compare>
	std::vector<std::pair<K, V>> SortUnorderedMap(const std::unordered_map<K, V>& map, Compare comp) {
		std::vector<std::pair<K, V>> vec(map.begin(), map.end());
		std::sort(vec.begin(), vec.end(), comp);
		return vec;
	}

	void WordCounter::CountWordsFromPath(const std::filesystem::path& path) {
		FReader input_reader;
		input_reader.Read(path);
		std::string_view str = input_reader.GetStream();
		std::vector<std::string> words = SplitIntoWords(str);

		for (size_t i = 0; i < words.size(); ++i) {
			ToLowerCase(words[i]);
			++words_map_[words[i]];
		}
	}

	void WordCounter::CountWords(const std::filesystem::path& path) {
		if (fs::is_directory(path)) {
			for (const auto& file : fs::directory_iterator(path)) {
				CountWordsFromPath(file.path());
			}
		}
		else {
			CountWordsFromPath(path);
		}
	}

	void WordCounter::GetSortedStatByLess(const std::filesystem::path& out) {
		FMapWriter writer;
		MapComparatorLess<std::string, size_t> comp;
		current_sorted_map_ = SortUnorderedMap(words_map_, comp);
		writer.Write(out, current_sorted_map_);
	}

	void WordCounter::GetSortedStatByGreater(const std::filesystem::path& out) {
		FMapWriter writer;
		MapComparatorGreater<std::string, size_t> comp;
		current_sorted_map_ = SortUnorderedMap(words_map_, comp);
		writer.Write(out, current_sorted_map_);
	}
}