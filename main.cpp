#include <iostream>

using std::cout;
using std::endl;
using std::string;

enum Type { Nature = 1, History = 2, Culture = 3 } typeDestination;

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
  Node *head, *tail, *newNode, *currentNode, *nodeHelper;

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

  void createNode(Destination data) {
    newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;
    newNode->prev = nullptr;
  }

  void insertHeadAndTail() {
    head = newNode;
    tail = head;
    newNode->next = head;
    newNode->prev = head;
  }

public:
  Gitar() { head = tail = nullptr; }

  void test() { cout << "This is data from gitar class" << endl; }

  void insertHead(Destination data) {
    createNode(data);

    if (isNodeEmpty()) {
      insertHeadAndTail();
      return;
    }

    while (tail->next != head) {
      tail = tail->next;
    }

    head->prev = newNode;
    tail->next = newNode;
    newNode->next = head;
    newNode->prev = tail;
    head = newNode;
  }

  void insertTail(Destination data) {
    createNode(data);

    if (isNodeEmpty()) {
      insertHeadAndTail();
      return;
    }

    while (tail->next != head) {
      tail = tail->next;
    }

    head->prev = newNode;
    tail->next = newNode;
    newNode->next = head;
    newNode->prev = tail;
    tail = newNode;
  }

  void insertMiddle(Destination data, int position) {
    createNode(data);

    if (isNodeEmpty()) {
      insertHeadAndTail();
      return;
    }

    int index = 0;

    currentNode = head;

    while (index < position - 1) {
      currentNode = currentNode->next;
      index++;
    }

    nodeHelper = currentNode->prev;
    nodeHelper->next = newNode;

    newNode->next = currentNode;
    newNode->prev = nodeHelper;

    currentNode->prev = newNode;
  }

  void showAllNode() {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    currentNode = head;

    cout << "=======================" << endl;

    do {
      cout << "Nama : " << currentNode->data.name << endl;
      cout << "Deskripsi : " << currentNode->data.description << endl;
      cout << "=======================" << endl;

      currentNode = currentNode->next;
    } while (currentNode != head);

    cout << endl;
  }
};

int main() {
  Gitar gitar;

  gitar.test();

  gitar.insertHead(
      Destination{"baturaden", "fsfs", "dfss", "dsfs", 3, 2500, Nature});
  gitar.showAllNode();

  gitar.insertTail(
      Destination{"Musium", "dfdsf", "dfs", "adad", 1, 5000, History});
  gitar.showAllNode();

  gitar.insertMiddle(
      Destination{"Stasiun", "fds", "dada", "ewrw", 1, 25000, Culture}, 2);
  gitar.showAllNode();

  return 0;
}