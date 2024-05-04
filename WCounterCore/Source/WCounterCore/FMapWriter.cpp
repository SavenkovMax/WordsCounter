#pragma once
#include "FMapWriter.hpp"

namespace wcounter {

	template <typename K, typename V>
	void FMapWriter::WriteByPath(const std::filesystem::path& path, const std::unordered_map<K, V>& map) {
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
			for (const auto& el : map) {
				file << el.first << " " << el.second << '\n';
			}
		}
		catch (const std::ios_base::failure& exception) {
			std::cerr << "Exception caught: " << exception.what() << std::endl;
		}
		file.close();
	}
}
