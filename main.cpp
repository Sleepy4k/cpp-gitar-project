#include <string>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

enum Type { Nature = 1, History = 2, Culture = 3 } typeDestination;

struct Destination {
  string name, description, location, work_hours;
  int person, price;
  Type type;
};

struct Pagination {
  bool back, next;
};

template <typename S>
struct Node {
  S data;
  Node<S> *next, *prev;
};

template <typename S>
class List {
private:
  Node<S> *head, *tail, *newNode, *currentNode, *nodeHelper;

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

  template <typename T> void createNode(T data) {
    newNode = new Node<S>();
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

  void displayNode(Destination data) {
    cout << "Nama : " << data.name << " (" << data.location << ")" << endl;
    cout << "Deskripsi : " << data.description << endl;
  }

public:
  List() { head = tail = nullptr; }

  template <typename T> void insertHead(T data) {
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

  template <typename T> void insertTail(T data) {
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

  template <typename T> void insertMiddle(T data, int position) {
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

  template <typename T> void updateHead(T data) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    head->data = data;
  }

  template <typename T> void updateTail(T data) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return;
    }

    tail->data = data;
  }

  template <typename T> void updateMiddle(T data, int position) {
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

  template <typename T> T findNodeData(int position) {
    if (isNodeEmpty() || position > totalNodeData())
      return T {};

    currentNode = head;
    
    int index = 0;

    while (index < position - 1) {
      currentNode = currentNode->next;
      index++;
    }

    return currentNode->data;
  }

  Pagination showAllNodes(int index = 1, int pagination = 5) {
    if (isNodeEmpty()) {
      cout << "Belum ada data yang tersedia" << endl;
      return Pagination { false, false };
    }

    currentNode = head;

    // Prevent error (current data not updated)
    int totalData = totalNodeData();

    if (index > totalData) return Pagination { index > 5, index < totalData };

    cout << "=======================" << endl;

    do {
      if (index > pagination || index > totalData) break;

      cout << "ID : " << index << endl;
      displayNode(currentNode->data);
      cout << "=======================" << endl;

      // Update index before moving to the next node
      index++;

      // Move to the next node (circularly)
      currentNode = currentNode->next;
    } while (currentNode != nullptr);

    cout << endl;
  
    return Pagination { index > 5, index < totalData };
  }
};

class Gitar {
  private:
    List<Destination> destinationList;

    void show_destination() {
      int choice, index = 1, pagination = 5, page = 5;

      do {
        cout << "Menampilkan list dari " << index << " - " << page << " data" << endl;

        Pagination result = destinationList.showAllNodes(index, pagination);

        cout << "1. Lanjut ke laman berikut nya" << endl;
        cout << "2. Kembali ke laman sebelum nya" << endl;
        cout << "3. Keluar" << endl;
        cout << "===============================" << endl;
        cout << "Pilih tindakan anda : ";
        cin >> choice;

        switch (choice) {
        case 1:
          if (result.next) {
            page += pagination;
            index += pagination;
          }
          break;
        case 2:
          if (result.back) {
            page -= pagination;
            index -= pagination;
          }
          break;
        case 3:
          return;
        default:
          cout << "Pilihan tidak valid, silahkan coba lagi" << endl;
          break;
        }
      } while (true);
    }

    Destination form_destination() {
      int type;
      Destination data;

      cin.ignore();

      cout << "Masukan nama destinasi : ";
      getline(cin, data.name);

      cout << "Masukan deskripsi destinasi : ";
      getline(cin, data.description);

      cout << "Masukan lokasi destinasi : ";
      getline(cin, data.location);

      cout << "Masukan jam operasional : ";
      getline(cin, data.work_hours);

      cout << "Masukan jumlah orang per tiket : ";
      cin >> data.person;

      cout << "Masukan harga per tiket : ";
      cin >> data.price;

      cout << "Jenis destinasi" << endl;
      cout << "1. Alam" << endl;
      cout << "2. Sejarah" << endl;
      cout << "3. Budaya" << endl;
      cout << "==================" << endl;
      cout << "Masukan jenis destinasi : ";
      cin >> type;

      switch (type) {
      case 1:
        data.type = Nature;
        break;
      case 2:
        data.type = History;
        break;
      case 3:
        data.type = Culture;
        break;
      default:
        cout << "Pilihan tidak valid, jenis akan menjadi alam secara default" << endl;
        data.type = Nature;
        break;
      }

      return data;
    }
    
    void insert_destination() {
      int position;

      Destination data = form_destination();

      cout << "Data akan dimasukan ke?" << endl;
      cout << "1. Depan" << endl;
      cout << "2. Belakang" << endl;
      cout << "3. Tengah" << endl;
      cout << "=======================" << endl;
      cout << "Bagian : ";
      cin >> position;
      
      switch (position) {
      case 1:
        destinationList.insertHead(data);
        break;
      case 2:
        destinationList.insertTail(data);
        break;
      case 3:
        cout << "Masukan posisi data : ";
        cin >> position;

        destinationList.insertMiddle(data, position);
        break;
      default:
        cout << "Pilihan tidak valid, gagal menambahkan data" << endl;
        break;
      }
    }

    int find_destination() {
      int position = 0;

      cout << "Masukan id destinasi : ";
      cin >> position;

      Destination data = destinationList.findNodeData<Destination>(position);
    
      if (data.name.empty() || data.description.empty() || data.location.empty()) {
        cout << "Data tidak ditemukan" << endl;
        return -1;
      }

      cout << "===================" << endl;
      cout << "Nama : " << data.name << " (" << data.location << ")" << endl;
      cout << "Deskripsi : " << data.description << endl;
      cout << "Jam Operasional : " << data.work_hours << endl;
      
      if (data.price != 0)
        cout << "Harga Tiket : " << data.price << " / " << data.person << " orang" << endl;
      else
        cout << "Harga Tiket : Gratis" << endl;

      cout << "===================" << endl;
    
      return position;
    }

    void update_destination() {
      int status = find_destination();

      if (status == -1) return;

      Destination data = form_destination();

      if (status == 1) destinationList.updateHead(data);
      else destinationList.updateMiddle(data, status);

      cout << "Data berhasil diubah" << endl;
    }

    void delete_destination() {
      int status = find_destination();

      if (status == -1) return;

      char confirmation;

      cout << "Apakah kamu yakin mau menghapus? (y/N)" << endl;
      cin >> confirmation;

      if (tolower(confirmation) == 'y') {
        if (status == 1) destinationList.deleteHead();
        else destinationList.deleteMiddle(status);

        cout << "Data berhasil dihapus" << endl;
      } 
    }

  public:
    void destination_menu() {
      int choice, isRunning = 1;

      do {
        cout << "List of Destination Menu" << endl;
        cout << "1. Tampilkan Destinasi" << endl;
        cout << "2. Tambah Destinasi" << endl;
        cout << "3. Cari Destinasi" << endl;
        cout << "4. Ubah Destinasi" << endl;
        cout << "5. Hapus Destinasi" << endl;
        cout << "6. Kembali" << endl;
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
          find_destination();
          break;
        case 4:
          update_destination();
          break;
        case 5:
          delete_destination();
          break;
        case 6:
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

  gitar.destination_menu();

  return 0;
}