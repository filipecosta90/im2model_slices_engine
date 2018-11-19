#include <cppkafka/cppkafka.h>
#include <cstdlib>
#include <iostream>

using namespace std;
using namespace cppkafka;

int main() {
  // Create the config
  const char* val = std::getenv("BROKER_LIST");
  std::string broker_list = (val == NULL) ? std::string("127.0.0.1:9092") : std::string(val);
  std::cout << "using broker_list " << broker_list << std::endl;
  Configuration config = {
    { "metadata.broker.list", broker_list }
  };

  // Create the producer
  Producer producer(config);

  // Produce a message!
  string message = "hey there!";
  producer.produce(MessageBuilder("test").partition(0).payload(message));
  producer.flush();
}
