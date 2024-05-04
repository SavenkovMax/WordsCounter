#pragma once
#include <algorithm>
#include <string>
#include <initializer_list>
#include <unordered_map>
#include <string_view>

#include "FReader.hpp"
#include "FMapWriter.hpp"

namespace wcounter {
	template <typename K, typename V>
	struct MapComparatorLess {
		inline bool operator()(const std::pair<K, V>& lhs, const std::pair<K, V>& rhs) {
			return lhs.second < rhs.second;
		}
	};

	template <typename K, typename V>
	struct MapComparatorGreater {
		inline bool operator()(const std::pair<K, V>& lhs, const std::pair<K, V>& rhs) {
			return lhs.second > rhs.second;
		}
	};

	inline void ToLowerCase(std::string& str) {
		std::transform(str.begin(), str.end(), str.begin(), ::tolower);
	}

	template <typename S>
	[[nodiscard]] std::vector<S> SplitIntoWords(std::string_view str);

	void MergeDict(std::unordered_map<std::string, size_t>& dist, const std::unordered_map<std::string, size_t>& source);

	template <typename K, typename V, typename Compare>
	[[nodiscard]] std::vector<std::pair<K, V>> SortUnorderedMap(const std::unordered_map<K, V>& map, Compare comp);

	class WordCounter {
	public:
		explicit WordCounter() = default;
		~WordCounter() = default;

		void CountWords(const std::filesystem::path& in);

		inline void GetStat(const std::filesystem::path& out) {
			FMapWriter writer;
			writer.Write(out, words_map_);
		}

		void GetSortedStatByLess(const std::filesystem::path& out);

		void GetSortedStatByGreater(const std::filesystem::path& out);

		inline void ClearMap() noexcept {
			words_map_.clear();
		}

		inline void ClearSortedArr() noexcept {
			current_sorted_map_.clear();
		}

		inline size_t WordFrequency(const std::string& word) noexcept {
			if (words_map_.find(word) == words_map_.end()) {
				return 0ULL;
			}
			return words_map_.at(word);
		}

	private:
		std::unordered_map<std::string, size_t> words_map_;
		std::vector<std::pair<std::string, size_t>> current_sorted_map_;

		void CountWordsFromPath(const std::filesystem::path& path);
	};
}