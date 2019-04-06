#include <string>
#include <vector>
#include <iostream>

using namespace std;

//#define HE HI
//#define LLO _THERE
//#define HELLO "HI THERE"
//#define CAT(a,b) a##b
//#define XCAT(a,b) CAT(a,b)
//#define CALL(fn) fn(HE,LLO)
//CAT(HE,LLO); // "HI THERE", because concatenation occurs before normal expansion
//XCAT(HE,LLO); // HI_THERE, because the tokens originating from parameters ("HE" and "LLO") are expanded first
//CALL(CAT); // "HI THERE", because parameters are expanded first
//#define LINE __LINE__

#define CAT(l) id##l
#define XCAT(a) CAT(a)
#define UNIQ_ID XCAT(__LINE__)

//int main() {
//  int UNIQ_ID = 0;
//  string UNIQ_ID = "hello";
//  vector<string> UNIQ_ID = {"hello", "world"};
//  vector<int> UNIQ_ID = {1, 2, 3, 4};

//}
