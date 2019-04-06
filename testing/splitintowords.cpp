#include <iterator>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector<string> res;
    auto it = s.begin();
    auto nextSpace = it;
    while(true)
    {
        nextSpace = find(it, s.end(), ' ');
        res.push_back(string(it, nextSpace));
        if(nextSpace == s.end()) break;
        it = nextSpace + 1;
    }
    return res;
}

//int main() {
//  string s = "C Cpp Java Python";

//  vector<string> words = SplitIntoWords(s);
//  cout << words.size() << " ";
//  for (auto it = begin(words); it != end(words); ++it) {
//    if (it != begin(words)) {
//      cout << "/";
//    }
//    cout << *it;
//  }
//  cout << endl;

//  return 0;
//}
