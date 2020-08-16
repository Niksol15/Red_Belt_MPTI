#include <algorithm>
#include <map>
#include <vector>
#include <string>
#include <sstream>
#include <future>
#include <iterator>
#include <set>
#include <thread>
#include <cmath>

using namespace std;

struct Stats {
    map<string, int> word_frequences;

    void operator += (const Stats& other) {
        for (auto& [word, frequency] : other.word_frequences) {
            word_frequences[word] += frequency;
        }
    }
};

vector<string> Split(const string& line) {
    istringstream line_splitter(line);
    return {istream_iterator<string>(line_splitter), istream_iterator<string>()};
}

Stats ExploreLine(const set<string>& key_words, const string& line) {
    Stats result;
    for (const string& word : Split(line)) {
        if (key_words.count(word) > 0) {
            result.word_frequences[word]++;
        }
    }
    return result;
}

Stats ExploreBatch(const set<string>& key_words, vector<string> lines) {
    Stats result;
    for (const string& line : lines) {
        result += ExploreLine(key_words, line);
    }
    return result;
}

Stats ExploreKeyWords(const set<string>& key_words, istream& input) {
    const size_t SIZE = 1000;
    vector<string> words;
    words.reserve(SIZE);
    vector<future<Stats>> futures;
    for (string line; getline(input, line); ) {
        words.push_back(move(line));
        if (words.size() == SIZE) {
            futures.push_back(
                    async(ExploreBatch, ref(key_words), move(words))
            );
            words.reserve(SIZE);
        }
    }

    Stats result;

    if (!words.empty()) {
        result += ExploreBatch(key_words, move(words));
    }

    for (auto& f : futures) {
        result += f.get();
    }

    return result;
}
