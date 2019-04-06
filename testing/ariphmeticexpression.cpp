#include <iterator>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <map>
#include <deque>

using namespace std;

struct member
{
    string number;
    char operation;
    bool priority;
};

string applyOperationWithPriority(const string &x, const vector<member> & expr)
{
    string res;
    deque<char> deq;
    if(expr.size() == 0) return x;
    deq.insert(deq.end(), x.begin(), x.end());
    bool current_priority = 1;
    for(const auto & operation : expr)
    {
        if(operation.priority > current_priority)
        {
            deq.push_front('(');
            deq.push_back(')');
        }
        current_priority = operation.priority;
        deq.push_back(' ');
        deq.push_back(operation.operation);
        deq.push_back(' ');
        deq.insert(deq.end(), operation.number.begin(), operation.number.end());
    }

    res.assign(deq.begin(), deq.end());
    return res;
}

//int main() {

//    string x;
//    cin>>x;
//    int N = 0;
//    cin>>N;
//    vector<member> expression(N);
//    for(auto &operation : expression)
//    {
//        cin>>operation.operation >> operation.number;
//        if(operation.operation == '+' || operation.operation == '-' )
//            operation.priority = 0;
//        else operation.priority = 1;
//    }
//    string result = applyOperationWithPriority(x,expression);
//    cout<<result<<endl;
//    return 0;
//}

//input
//8
//3
//* 3
//- 6
/// 1

//output
//(8 * 3 - 6) / 1

