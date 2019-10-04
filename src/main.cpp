#include <thread>

#include "threading.h"

using namespace std;

int main()
{
  PCObject pc;

  thread producer(&PCObject::producer, &pc);
  thread consumer(&PCObject::consumer, &pc);
  consumer.join();
  producer.join();
  return 0;
}