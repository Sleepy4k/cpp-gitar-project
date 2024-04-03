#include <iostream>

using std::cout;
using std::endl;
using std::string;

enum Type { Nature = 1, History = 2, Culture = 3 };

struct Destination {
  string name, description, location, work_hours;
  int person, price;
  Type type;
};

struct Node {
  Destination data;
  Node *next, *prev;
};

class Gitar {
private:
  Node *head, *tail, *newNode, *currentNode;

  bool isNodeEmpty() { return (head == nullptr) ? true : false; }

  int totalNodeData() {
    int total = 0;

    if (isNodeEmpty())
      return total;

    currentNode = head;

    do {
      total++;
      currentNode = currentNode->next;
    } while (currentNode != head);

    return total;
  }

public:
  Gitar() { head = tail = nullptr; }

  void test() { cout << "This is data from gitar class" << endl; }
};

int main() {
  Gitar gitar;

  gitar.test();

  return 0;
}