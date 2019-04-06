#include <iostream>
#include <string>
#include <vector>

using namespace std;

//stream optimization
//ios_base::sync_with_stdio(false);
//cin.tie(nullptr);

//template<typename T>
//struct ReadOnlyValue{
//    const T value;
//};

//template <typename T>
//ReadOnlyValue<T> MakeReadOnly(T x)
//{
//    return {x};
//}

//template <typename It>
//struct IteratorRange{
//    It first, last;
//    IteratorRange(It begin, It end): first(begin), last(end){}
//};

//#include <array>
//#include <string_view>
//int main()
//{

//    array<char,5> a = {'a','b','c','d','e'};
//    //string_view(a);
//    cout<<string_view(a.data())<<endl;
//    cout<<string_view(a.begin())<<endl;
//    //string_view(&a[0]);
//    cout<<string_view(a.data(),a.size())<<endl;
//    cout<<string_view(&a[0],a.size())<<endl;
//    cout<<string_view(a.begin(),a.size())<<endl;

////    ReadOnlyValue ro_int{4};
////    auto zi = MakeReadOnly('z');
////    ReadOnlyValue<int> ro_int2{5};
////    auto ro_dbl = MakeReadOnly<double>(5);
////    ReadOnlyValue<vector<int>> ro_vec{{4,6,11,23}};

////    vector<string> vs;
//    //IteratorRange vs_rng(vs.begin(), vs.end());
////    IteratorRange vs12(1,2);
////    vector<int> v;
////    IteratorRange<vector<int>::iterator> vi_rng{begin(v), end(v)};

////    vector<string> vs2;
////    auto vs_rng2(vs2.begin(), vs2.end());

////    IteratorRange<int> index_range(1,5);

//}
