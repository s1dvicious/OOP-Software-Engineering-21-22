/*
It’s pretty easy to implement a sloppy Singleton.
You just need to hide the constructor and implement a static creation method.

The same class behaves incorrectly in a multithreaded environment.
Multiple threads can call the creation method simultaneously and get several instances of Singleton class.
*/

/*
 * The Singleton class defines the `GetInstance` method that serves as an
 * alternative to constructor and lets clients access the same instance of this
 * class over and over.
 */

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

class Singleton
{
protected:
    /*
    The Singleton's constructor should always be private/protected
    to prevent directconstruction calls with the `new` operator.
    */
    Singleton(const std::string &value) : value_(value) {}

    static Singleton *singleton_;

    std::string value_;

public:
    // Singletons should not be cloneable.
    Singleton(Singleton &other) = delete;

    // Singletons should not be assignable.
    void operator=(const Singleton &) = delete;

    /*
    This is the static method that controls the access to the singleton instance.
    On the first run, it creates a singleton object and places it into the static field.
    On subsequent runs, it returns the client existing object stored in the static field.
    */
    static Singleton *GetInstance(const std::string &value);

    // Finally, any singleton should define some business logic, which can be executed on its instance.
    void SomeBusinessLogic()
    {
        // ...
    }

    const std::string &value() const
    {
        return value_;
    }
};

Singleton *Singleton::singleton_ = nullptr;
;

// Static methods should be defined outside the class.
Singleton *Singleton::GetInstance(const std::string &value)
{
    /*
    This is a safer way to create an instance. instance = new Singleton is
    dangeruous in case two instance threads wants to access at the same time
    */
    if (singleton_ == nullptr)
        singleton_ = new Singleton(value);

    return singleton_;
}

void ThreadFoo()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << std::endl;
}

void ThreadBar()
{
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton *singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << std::endl;
}

int main()
{
    std::cout << "If you see the same value, then singleton was reused (yay!\n"
              << "If you see different values, then 2 singletons were created (booo!!)\n\n"
              << "RESULT:\n";
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}