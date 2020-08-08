#include <vector>

using namespace std;

template <typename Token>
using Sentence = vector<Token>;

template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
    vector<Sentence<Token>> res(1);
    for(size_t i = 0; i < tokens.size(); ++i){
        res.back().push_back(move(tokens[i]));
        if(tokens[i].IsEndSentencePunctuation()){
            ++i;
            while(i < tokens.size() && tokens[i].IsEndSentencePunctuation()){
                res.back().push_back(move(tokens[i]));
                ++i;
            }
            if (i < tokens.size()){
                res.push_back(Sentence<Token>());
                res.back().push_back(move(tokens[i]));
            }
        }
    }
    return res;
}
