#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human
{
public:
    Human(const string &name, const string &prof) :
        Name(name), Profession(prof){}
    virtual ~Human(){}
    virtual void Walk(const string & dest) const = 0;
    void printWalk(const string & dest) const
    {
        cout << Profession <<": " << Name << " walks to: " << dest << endl;
    }
    const string Name;
    const string Profession;
};

class Student : public Human
{
public:

    Student(const string& name, const string& favouriteSong) :
        Human(name, "Student")
      , FavouriteSong(favouriteSong){}

    void Learn() const{
        cout << "Student: " << Name << " learns" << endl;
    }

    void SingSong() const{
        cout << "Student: " << Name << " sings a song: " << FavouriteSong << endl;
    }

    void Walk(const string &destination) const override
    {
        printWalk(destination);
        SingSong();
    }

private:
    string FavouriteSong;
};

class Teacher : public Human
{
public:
    Teacher(const string& name, const string& subject) :
        Human(name, "Teacher"), Subject(subject){}
    void Teach() const
    {
        cout<< "Teacher: "<< Name << " teaches: "<<Subject <<endl;
    }
    void Walk(const string &destination) const override {
        printWalk(destination);
    }
private:
    string Subject;
};

class Policeman : public Human
{
public:
    Policeman(const string& name) : Human(name, "Policeman"){}

    void Check(const Human & h) const
    {
        cout << "Policeman: " << this->Name << " checks " << h.Profession << ". "
           << h.Profession << "'s name is: " << h.Name<<endl;
    }
    void Walk(const string &destination) const override {
        printWalk(destination);
    }
};

void VisitPlaces(const Human &h, const vector<string>& places) {
    for (const auto &p : places) {
        h.Walk(p);
    }
}


//int main() {
//    Teacher t("Jim", "Math");
//    Student s("Ann", "We will rock you");
//    Policeman p("Bob");

//    VisitPlaces(t, {"Moscow", "London"});
//    p.Check(s);
//    VisitPlaces(s, {"Moscow", "London"});
//    return 0;
//}
