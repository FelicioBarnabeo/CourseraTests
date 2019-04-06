#include "test_runner.h"

#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;

//Token — шаблонный тип, про который известно лишь то, что он имеет константный метод IsEndSentencePunctuation,
//возвращающий true, если токен является знаком пунктуации, заканчивающим предложение, и false в противном случае.
//Объекты этого типа запрещено копировать. При наличии копирования этих объектов вы получите ошибку компиляции.

//Предложением считается последовательность токенов, заканчивающаяся подряд идущими токенами, являющимися знаками пунктуации конца предложения.
//Иными словами, любое предложение должно состоять из двух частей:

//1)токены, для которых IsEndSentencePunctuation возвращает false
//  (такие токены обязаны присутствовать в предложении за исключением, возможно, первого предложения);
//2)токены, для которых IsEndSentencePunctuation возвращает true
//  (такие токены обязаны присутствовать в предложении за исключением, возможно, последнего предложения).

//Ограничения
//Максимальное количество токенов — 10^6. Время выполнения одного вызова функции ограничено 1 секундой.

template <typename Token>
using Sentence = vector<Token>;

//Решение авторов 0.35
template <typename TokenForwardIt>
TokenForwardIt FindSentenceEnd(TokenForwardIt tokens_begin, TokenForwardIt tokens_end) {
  const TokenForwardIt before_sentence_end =
      adjacent_find(tokens_begin, tokens_end,
                    [](const auto& left_token, const auto& right_token) {
                      return left_token.IsEndSentencePunctuation()
                          && !right_token.IsEndSentencePunctuation();
                    });
  return before_sentence_end == tokens_end
      ? tokens_end
      : next(before_sentence_end);
}

// Класс Token имеет метод bool IsEndSentencePunctuation() const
template <typename Token>
vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens) {
  vector<Sentence<Token>> sentences;
  auto tokens_begin = begin(tokens);
  const auto tokens_end = end(tokens);
  while (tokens_begin != tokens_end) {
    const auto sentence_end = FindSentenceEnd(tokens_begin, tokens_end);
    Sentence<Token> sentence;
    for (; tokens_begin != sentence_end; ++tokens_begin) {
      sentence.push_back(move(*tokens_begin));
    }
    sentences.push_back(move(sentence));
    //Цикл добавления можно сократить через move итераторы
//    sentences.push_back(Sentence<Token>(make_move_iterator(tokens_begin), make_move_iterator(sentence_end)));
//    tokens_begin = sentence_end;
  }
  return sentences;
}

//Проходит тест , 0.40 -time
//нельзя копировать объекты типа Token
//template <typename Token>
//vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
//{
//    vector<Sentence<Token>> senteces;
//    auto beg = tokens.begin();
//    auto end = tokens.end();
////    auto lastPunctuation = find_if(begin(tokens), end(tokens), [](const Token& token){return token.IsEndSentencePunctuation();});
////    while(lastPunctuation!=end(tokens) && lastPunctuation->IsEndSentencePunctuation()){lastPunctuation++;}
////    senteces.push_back(move(vector<Token>(tokens.begin(),lastPunctuation)));
//    while(beg != end){
//        auto sentence_end = find_if(beg, end, [](const Token& token){return token.IsEndSentencePunctuation();});
//        while(sentence_end != end && sentence_end->IsEndSentencePunctuation())
//        {
//            ++sentence_end ;
//        }
//        Sentence<Token> sentence;
//        for(; beg!=sentence_end; beg++){
//            sentence.push_back(move(*beg));
//        }
//        senteces.push_back(move(sentence));
//    }
//    return move(senteces);
//}

//Проходит тест , 0.47 -time
//нельзя копировать объекты типа Token
//template <typename Token>
//vector<Sentence<Token>> SplitIntoSentences(vector<Token> tokens)
//{
//    auto it = tokens.begin();
//    vector<Sentence<Token>> sentences;

//    Sentence<Token> sentence;
//    while(it != end(tokens)){
//        while(it!=tokens.end() && !it->IsEndSentencePunctuation())
//        {
//            sentence.push_back(move(*it)) ;
//            ++it;
//        }
//        while(it!=tokens.end() && it->IsEndSentencePunctuation()){
//               sentence.push_back(move(*it)) ;
//               ++it;
//        }
//        sentences.push_back(move(sentence));
//        sentence.clear();
//    }
//    return move(sentences);
//}

struct TestToken {
    string data;
    bool is_end_sentence_punctuation = false;

    bool IsEndSentencePunctuation() const {
        return is_end_sentence_punctuation;
    }
    bool operator==(const TestToken& other) const {
        return data == other.data && is_end_sentence_punctuation == other.is_end_sentence_punctuation;
    }
};

ostream& operator<<(ostream& stream, const TestToken& token) {
    return stream << token.data;
}


//// Тест содержит копирования объектов класса TestToken
//// Для проверки отстутствия копирования в функции SplitIntoSentences
//// необходимо написать отдельный тест
void TestSplitting() {
    ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!"}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!"}}
    })
    );

    ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}}
    })
    );

    ASSERT_EQUAL(
    SplitIntoSentences(vector<TestToken>({{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}, {"Without"}, {"copies"}, {".", true}})),
    vector<Sentence<TestToken>>({
        {{"Split"}, {"into"}, {"sentences"}, {"!", true}, {"!", true}},
        {{"Without"}, {"copies"}, {".", true}},
    })
    );
}


//int main() {
//    TestRunner tr;
//    RUN_TEST(tr, TestSplitting);
//    return 0;
//}
