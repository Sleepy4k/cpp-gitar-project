#include <iostream>

using std::cin;
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

class List {
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
  List() { head = tail = nullptr; }

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

  void deleteMiddle(int position) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    currentNode = head;

    int index = 0;

    while (index < position - 1) {
      currentNode = currentNode->next;
      index++;
    }

    nodeHelper = currentNode->prev;
    nodeHelper->next = currentNode->next;
    nodeHelper = currentNode->next;
    nodeHelper->prev = currentNode->prev;

    delete currentNode;
  }

  void clearAllNode() {
    if (!isNodeEmpty()) {
      currentNode = head->next;

      while (currentNode != head) {
        nodeHelper = currentNode->next;
        delete currentNode;
        currentNode = nodeHelper;
      }

      delete head;
      
      head = tail = nullptr;
    }

    cout << "Semua data berhasil di hapus" << endl;
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

class Gitar {
  private:
    List destinationList;

    void show_destination() {}
    
    void insert_destination() {}

    void update_destination() {}

    void delete_destination() {}

  public:
    void destination_menu() {
      int choice, isRunning = 1;

      do {
        cout << "List of Destination Menu" << endl;
        cout << "1. Tampilkan Destinasi" << endl;
        cout << "2. Tambah Destinasi" << endl;
        cout << "3. Ubah Destinasi" << endl;
        cout << "4. Hapus Destinasi" << endl;
        cout << "5. Kembali" << endl;
        cout << "===================" << endl;
        cout << "Pilih menu : ";
        cin >> choice;

        switch (choice) {
        case 1:
          show_destination();
          break;
        case 2:
          insert_destination();
          break;
        case 3:
          update_destination();
          break;
        case 4:
          delete_destination();
          break;
        case 5:
          isRunning = 0;
          break;
        default:
          cout << "Pilihan tidak valid" << endl;
          break;
        }
      } while (isRunning == 1);
    }
};

int main() {
  Gitar gitar;

  return 0;
}