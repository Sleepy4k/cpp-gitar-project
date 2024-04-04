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

  void updateHead(Destination data) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    head->data = data;
  }

  void updateTail(Destination data) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    tail->data = data;
  }

  void updateMiddle(Destination data, int position) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    if (position < 1 || position > totalNodeData())
      cout << "Posisi data diluar jangkauan" << endl;
    else if (position == 1)
      cout << "Posisi bukan berada ditengah" << endl;
    else {
      currentNode = head;

      int index = 0;

      while (index < position - 1) {
        currentNode = currentNode->next;
        index++;
      }

      currentNode->data = data;
    }
  }

  void deleteHead() {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    currentNode = tail = head;

    if (currentNode->next == head) {
      head = tail = nullptr;
      delete currentNode;
      return;
    }

    while (tail->next != currentNode) {
      tail = tail->next;
    }

    head = head->next;
    head->prev = tail;
    tail->next = head;

    delete currentNode;
  }

  void deleteTail() {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    currentNode = tail = head;

    if (currentNode->next == head) {
      head = tail = nullptr;
      delete currentNode;
      return;
    }

    while (currentNode->next != head) {
      currentNode = currentNode->next;
    }

    tail = currentNode->prev;
    tail->next = head;
    head->prev = tail;

    delete currentNode;
  }

  void showAllNode() {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    currentNode = head;

    cout << "=======================" << endl;

    int index = 2;

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

  gitar.updateMiddle(Destination({"KAI", "ada", "ere", "sfds", 3, 50000, Culture}), 2);
  gitar.showAllNode();

  gitar.deleteTail();
  gitar.showAllNode();

  return 0;
}