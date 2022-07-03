/*
Observer Design Pattern

Intent: Lets you define a subscription mechanism to notify multiple objects
about any events that happen to the object they're observing.

Note that there's a lot of different terms with similar meaning associated
with this pattern. Just remember that the Subject is also called the
Publisher and the Observer is often called the Subscriber and vice versa.
Also the verbs "observe", "listen" or "track" usually mean the same thing.
*/

#include <iostream>
#include <list>
#include <string>

class IObserver
{
public:
  virtual ~IObserver() = default;
  virtual void Update(const std::string &message_from_subject) = 0;
};

class ISubject
{
public:
  virtual ~ISubject() = default;
  virtual void Attach(IObserver *observer) = 0;
  virtual void Detach(IObserver *observer) = 0;
  virtual void Notify() = 0;
};

// The Subject owns some important state and notifies observers when the state changes.
class Subject : public ISubject
{
public:
  virtual ~Subject()
  {
    std::cout << "Goodbye, I was the Subject." << std::endl;
  }

  // The subscription management methods.
  void Attach(IObserver *observer) override
  {
    list_observer_.push_back(observer);
  }
  void Detach(IObserver *observer) override
  {
    list_observer_.remove(observer);
  }
  void Notify() override
  {
    std::list<IObserver *>::iterator iterator = list_observer_.begin();

    HowManyObserver();

    while (iterator != list_observer_.end())
    {
      (*iterator)->Update(message_);
      ++iterator;
    }
  }

  void CreateMessage(const std::string &message = "Empty")
  {
    this->message_ = message;
    Notify();
  }

  void HowManyObserver() const
  {
    std::cout << "There are " << list_observer_.size() << " observers in the list.\n";
  }

  /*
  Usually, the subscription logic is only a fraction of what a Subject can
  really do. Subjects commonly hold some important business logic, that
  triggers a notification method whenever something important is about to
  happen (or after it).
  */
  void SomeBusinessLogic()
  {
    this->message_ = "change message message";
    Notify();
    std::cout << "I'm about to do some thing important" << std::endl;
    ;
  }

private:
  std::list<IObserver *> list_observer_;
  std::string message_;
};

class Observer : public IObserver
{
public:
  Observer(Subject &subject) : subject_(subject)
  {
    this->subject_.Attach(this);
    std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number_ << "\".\n";
    this->number_ = Observer::static_number_;
  }

  virtual ~Observer()
  {
    std::cout << "Goodbye, I was the Observer \"" << this->number_ << "\".\n";
  }

  void Update(const std::string &message_from_subject) override
  {
    message_from_subject_ = message_from_subject;
    PrintInfo();
  }

  void RemoveMeFromTheList()
  {
    subject_.Detach(this);
    std::cout << "Observer \"" << number_ << "\" removed from the list.\n";
  }

  void PrintInfo() const
  {
    std::cout << "Observer \"" << this->number_ << "\": a new message is available --> " << this->message_from_subject_ << "\n";
  }

private:
  std::string message_from_subject_;
  Subject &subject_;
  static int static_number_;
  int number_;
};

int Observer::static_number_ = 0;

void ClientCode()
{
  Subject *subject = new Subject;
  Observer *observer1 = new Observer(*subject);
  Observer *observer2 = new Observer(*subject);
  Observer *observer3 = new Observer(*subject);
  Observer *observer4;
  Observer *observer5;

  subject->CreateMessage("Hello World! :D");
  observer3->RemoveMeFromTheList();

  subject->CreateMessage("The weather is hot today! :p");
  observer4 = new Observer(*subject);

  observer2->RemoveMeFromTheList();
  observer5 = new Observer(*subject);

  subject->CreateMessage("My new car is great! ;)");
  observer5->RemoveMeFromTheList();

  observer4->RemoveMeFromTheList();
  observer1->RemoveMeFromTheList();

  delete observer5;
  delete observer4;
  delete observer3;
  delete observer2;
  delete observer1;
  delete subject;
}

int main()
{
  ClientCode();
  return 0;
}