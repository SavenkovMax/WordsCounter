#include "WCounterCore/WordCounter.hpp"
#include <chrono>

int main() {
	wcounter::WordCounter wc;
	fs::path path("war-and-peace.txt");
	fs::path dist("mystats.txt");
	auto start = std::chrono::high_resolution_clock::now();
	wc.CountWords(path);
	wc.GetSortedStatByGreater(dist);
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
	std::cout << duration.count() << "sec" << '\n';
}