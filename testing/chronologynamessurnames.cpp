#include <iterator>
#include <vector>
#include <iostream>
#include <set>
#include <algorithm>
#include <string>
#include <map>

using namespace std;

string findNameByYear(const map<int,string> &names, int year)
{
    string name;
    auto it = names.upper_bound(year);
    if(it!=names.begin()) name = prev(it)->second;
    return name;
}

class Person {
public:
    void ChangeFirstName(int year, const string& first_name) {
        namesPerYears[year] = first_name;
    }
    void ChangeLastName(int year, const string& last_name) {
        surnamesPerYears[year] = last_name;
    }
    string GetFullName(int year) {
        string first_name = findNameByYear(namesPerYears, year);
        string last_name = findNameByYear(surnamesPerYears, year);

        if(first_name.empty() && last_name.empty()) return "Incognito";
        else if(first_name.empty()) return last_name+" "+"with unknown first name";
        else if(last_name.empty()) return first_name+" "+"with unknown last name";
        else return first_name+" "+last_name;
    }
    private:
    map<int, string> namesPerYears;
    map<int, string> surnamesPerYears;
};

//int main() {
//    Person person;

//    person.ChangeFirstName(1965, "Polina");
//    person.ChangeLastName(1967, "Sergeeva");
//    for (int year : {1900, 1965, 1990}) {
//    cout << person.GetFullName(year) << endl;
//    }

//    person.ChangeFirstName(1970, "Appolinaria");
//    for (int year : {1969, 1970}) {
//    cout << person.GetFullName(year) << endl;
//    }

//    person.ChangeLastName(1968, "Volkova");
//    for (int year : {1969, 1970}) {
//    cout << person.GetFullName(year) << endl;
//    }

//    return 0;
//}
