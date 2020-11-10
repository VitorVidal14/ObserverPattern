#include "Headers.h"
#include "Observer.h"
#include "Observable.h"
#include "SaferObservable.h"
using namespace std;

class Person : public SaferObservable<Person>
{
    int age;
public:
    Person(int age) : age(age) {}

    int get_age() const
    {
        return age;
    }

    void set_age(int age)
    {
        if (this->age == age) return;
        this->age = age;
        notify(*this, "age");
    }
};

// observer & observable

struct ConsolePersonObserver : public Observer<Person> {
private:
    void field_changed(Person& source, const std::string& field_name) override
    {
        cout << "Person's " << field_name << " has changed to ";
        if (field_name == "age") cout << source.get_age();
        cout << '\n';
    }
};

int main(int ac, char* av[])
{
    Person person{ 10 };
    ConsolePersonObserver cpo;
    person.subscribe(cpo);

    person.set_age(11);
    person.set_age(12);

    person.unsubscribe(cpo);
    person.set_age(13);

    return 0;
}