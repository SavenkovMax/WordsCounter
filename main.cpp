#include <WordCounter.hpp>
#include <iostream>

int main() {
	auto d = wcounter::CountWords("../../tests/src/test.txt");
	wcounter::WriteStatsInFile(d, "stats.txt");
	std::cout << wcounter::GetMostFrequentWord(d) << '\n' << wcounter::GetLessFrequentWord(d) << '\n';
}