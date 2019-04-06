#ifndef A_H
#define A_H

#include <string>
using std::string;

//class Person {
//public:
//    void ChangeFirstName(int year, const string& first_name)
//    {
//        //cout<<"Add first_name to year:"<<year<<endl;;
//        if(names.empty())
//            names[year].name = first_name;
//        else
//        {
//            names[year].name = first_name;
//            int last = lastYear(year);
//            //cout << "Last year from "<<year<<" ="<<last << endl;
//            names[year].lastname = names[last].lastname;
//        }
//    }

//    void ChangeLastName(int year, const string& last_name)
//    {
//        //cout<<"Add last_name to year:"<<year<<endl;
//        if(names.empty())
//            names[year].lastname = last_name;
//        else
//        {
//            names[year].lastname = last_name;
//            int last = lastYear(year);
//            //cout << "Last year from "<<year<<" ="<<last << endl;
//            names[year].name = names[last].name;
//        }
//    }
//    void printNames()
//    {
//        cout<<"Print names ";
//        for(auto v : names)
//            cout<<v.first<<" ";
//        cout<<endl;
//    }

//    string GetFullName(int year) const
//    {
//        string res;
//        if(names.size()==0) return "Incognito";
//        if(year < names.begin()->first) return "Incognito";
//        if(!names.count(year))
//        {
//            int last = lastYear(year);
//            //cout << "Last year from "<<year<<" ="<<last << endl;
//            if(last == year) return "Incognito";

//            if(names.at(last).name.empty()) res=names.at(last).lastname + " with unknown first name";
//            else if(names.at(last).lastname.empty()) res=names.at(last).name +  " with unknown last name";
//            else res=names.at(last).name +" "+ names.at(last).lastname;
//        }
//        else
//        {
//            if(names.at(year).name.empty()) res=names.at(year).lastname + " with unknown first name";
//            else if(names.at(year).lastname.empty()) res=names.at(year).name +  " with unknown last name";
//            else res=names.at(year).name +" "+ names.at(year).lastname;
//        }
//        return res;
//    }

//private:
//    struct fullName
//    {
//        string name;
//        string lastname;
//    };
//    map<int,fullName> names;

//    int lastYear(int year) const
//    {
//        auto it = names.begin();
//        auto end = names.end();
//        int lastYear = it->first;
//        if(year <= lastYear)
//        {
//            //cout<<"year < lastYear";
//            return year;
//        }
//        while(it->first <= year && it!=end)
//        {
//            //cout<<"it.first = "<<it->first<<"<="<<year<<endl;
//            lastYear = it->first; it++;
//        }
//        return lastYear;
//    }
//};


#endif // A_H

