#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace fs = std::filesystem;

namespace wcounter {
	class FMapWriter {
	public:
		explicit FMapWriter() = default;
		~FMapWriter() = default;

		template <typename K, typename V>
		inline void Write(const std::filesystem::path& path, const std::unordered_map<K, V>& map) {
			WriteByPath(path, map);
		}

		template <typename K, typename V>
		inline void Write(const std::filesystem::path& path, const std::vector<std::pair<K, V>>& vec) {
			WriteVecByPath(path, vec);
		}

	private:
		template <typename K, typename V>
		void WriteByPath(const std::filesystem::path& path, const std::unordered_map<K, V>& map);

		template <typename K, typename V>
		inline void WriteVecByPath(const std::filesystem::path& path, const std::vector<std::pair<K, V>>& vec) {
			std::ofstream file;
			try {
				if (fs::exists(path)) {
					file.open(path, std::ios::app);

					if (!file.is_open()) {
						throw std::ios_base::failure("Failed to open the file");
					}
				}
				else {
					file.open(path);
				}
				for (const auto& el : vec) {
					file << el.first << " " << el.second << '\n';
				}
			}
			catch (const std::ios_base::failure& exception) {
				std::cerr << "Exception caught: " << exception.what() << std::endl;
			}
			file.close();
		}
	};
}
