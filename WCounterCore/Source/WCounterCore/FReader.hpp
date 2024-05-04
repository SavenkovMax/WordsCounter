#pragma once
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <string_view>

namespace fs = std::filesystem;

namespace wcounter {
	class FReader {
	public:

		explicit FReader() = default;
		~FReader() = default;
		inline constexpr FReader(const FReader& other) noexcept : stream_(other.stream_) {}
		inline constexpr FReader(FReader&& other) noexcept : stream_(std::move(other.stream_)) {}
		inline constexpr FReader& operator=(const FReader& other) noexcept {
			if (this != &other) {
				stream_ = other.stream_;
			}
			return *this;
		}
		inline constexpr FReader& operator=(FReader&& other) noexcept {
			if (this != &other) {
				stream_ = std::move(other.stream_);
			}
			return *this;
		}

		inline void Read(const std::filesystem::path& filepath) {
			ReadFromPath(filepath);
		}

		inline constexpr void Clear() noexcept {
			stream_.clear();
		}

		inline constexpr std::string_view GetStream() const noexcept {
			return std::string_view(stream_);
		}

	private:
		std::string stream_;

		void ReadFromPath(const std::filesystem::path& path);
	};
}