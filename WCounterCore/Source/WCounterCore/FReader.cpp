#pragma once
#include "FReader.hpp"

namespace wcounter {
	void FReader::ReadFromPath(const std::filesystem::path& path) {
		std::ifstream file;
		try {
			if (fs::exists(path)) {
				file.open(path, std::ios::app);

				if (file.is_open()) {
					std::string line;
					while (std::getline(file, line, '\r')) {
						stream_ += line;
					}
				}
				else {
					throw std::ios_base::failure("Failed to open the file");
				}
			}
			else {
				throw std::ios_base::failure("Such file do not exist");
			}
		}
		catch (const std::ios_base::failure& exception) {
			std::cerr << "Exception caught: " << exception.what() << std::endl;
		}
		file.close();
	}
}