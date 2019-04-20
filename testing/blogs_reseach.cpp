#include "test_runner.h"
#include "profile.h"
#include<algorithm>
#include <map>
#include <string>
#include<set>
#include<string>
#include<sstream>
#include<functional>
#include<future>
#include<thread>
#include<iterator>
using namespace std;

template<typename It>
class Range {
public:
	Range(It begin, It end) : begin_(begin), end_(end) {}
	It begin() const { return begin_; }
	It end() const { return end_; }
	size_t size() const { return distance(begin_, end_); }

private:
	It begin_;
	It end_;
};

template <typename Iterator>
class Paginator {
private:
	vector<Range<Iterator>> pages;

public:
	Paginator(Iterator begin, Iterator end, size_t page_size) {
		for (size_t left = distance(begin, end); left > 0; ) {
			size_t current_page_size = min(page_size, left);
			Iterator current_page_end = next(begin, current_page_size);
			pages.push_back({ begin, current_page_end });

			left -= current_page_size;
			begin = current_page_end;
		}
	}

	auto begin() const {
		return pages.begin();
	}

	auto end() const {
		return pages.end();
	}

	size_t size() const {
		return pages.size();
	}
};

template <typename C>
auto Paginate(C& c, size_t page_size) {
	return Paginator(begin(c), end(c), page_size);
}

struct Stats {
	map<string, int> word_frequences;

	void operator += (const Stats& other) {
		for (const auto& freq : other.word_frequences) {
			this->word_frequences[freq.first] += freq.second;
		}
	}
};
ostream& operator<<(ostream& out, const Stats& stats) {
	return out << stats.word_frequences;
}
using VectorRange = vector<string>::iterator;
Stats ExploreKeyWordRange(const set<string>& key_words, const Range< VectorRange>& range) {
	Stats stats;
	for (const auto& words : range) {
			if (key_words.find(words) != key_words.end()) {
				++stats.word_frequences[words];
		}
	}
	return stats;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
	vector<string> vect;
	istream_iterator<string> begininput(input);
	istream_iterator<string> endinput;
	copy(begininput, endinput, back_inserter(vect));
	//string line;
	//while (input >> line) {
	//	vect.push_back(line);
	//}
	const size_t concurrence(thread::hardware_concurrency() == 0 ?
		4 : thread::hardware_concurrency());
	const size_t page_size = static_cast<size_t>(vect.size() / concurrence + 1);
	vector<future<Stats>> future_word;
	Stats stats;
	for (auto& range : Paginate(vect, page_size)) {
		future_word.push_back(async(ExploreKeyWordRange, ref(key_words), move(range)));
	}
	for (auto&f : future_word) {
		stats += f.get();
	}
	return stats;
}

void TestBasic() {
	const set<string> key_words = { "yangle", "rocks", "sucks", "all" };

	stringstream ss;
	ss << "this new yangle service really rocks\n";
	ss << "It sucks when yangle isn't available\n";
	ss << "10 reasons why yangle is the best IT company\n";
	ss << "yangle rocks others suck\n";
	ss << "Goondex really sucks, but yangle rocks. Use yangle\n";

	const auto stats = ExploreKeyWords(key_words, ss);
	const map<string, int> expected = {
	  {"yangle", 6},
	  {"rocks", 2},
	  {"sucks", 1}
	};
	ASSERT_EQUAL(stats.word_frequences, expected);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestBasic);
}