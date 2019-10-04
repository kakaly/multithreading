#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>

using namespace std;

class PCObject {
public:
  PCObject() : 
    m_counter(0),
    m_isIncremented(false)
    {
      cout << "PCObject called\n";
    }

    bool isIncremented() {
      return m_isIncremented;
    }
  
    void increment() {
      lock_guard<mutex> lock(m_mutex);
      cout << "Producer locked and counter incremented\n";
      m_counter++;
      m_isIncremented = true;
      cout << "Counter produced: " << m_counter << "\n\n";
      m_condVar.notify_one();
    }

    void print() {
      unique_lock<mutex> ulock(m_mutex);
      cout << "Consumer locked and counter consumed\n";
      m_condVar.wait(ulock, bind(&PCObject::isIncremented, this));
      m_isIncremented = false;
      cout << "Counter consumed: " << m_counter << "\n\n";
    }

    void producer() {
      while(true) {
        this_thread::sleep_for(chrono::seconds(2));
        increment();
      }
    }

    void consumer() {
      while(true) {
        this_thread::sleep_for(chrono::seconds(2));
        print();
      }
    }

private:
  int m_counter;
  bool m_isIncremented;
  condition_variable m_condVar;
  mutex m_mutex;
};
