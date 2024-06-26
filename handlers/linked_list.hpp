#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <iostream>

#include "../helpers/parse.hpp"
#include "../helpers/input_data.hpp"
#include "../structs/node_struct.hpp"
#include "../structs/user_struct.hpp"
#include "../structs/package_struct.hpp"
#include "../structs/pagination_struct.hpp"
#include "../enums/package_transport_enum.hpp"

/**
 * Deklarasi class List
 *
 * Class list ini kita gunakan untuk menghandle
 * double circular linked list yang kita buat
 * agar berjalan sesuai dengan definisi nya
 * serta dapat menyimpan secara dinamik untuk
 * semua struct yang sudah kita buat seperti
 * data user
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
template <typename T>
class List {
private:
  // Inisialisasi variable bertipe data struct Node dengan
  // template dari typename class
  NodeStruct<T> *head, *tail, *newNode, *currentNode, *nodeHelper;

  /**
   * @brief Mengecek apakah data dalam node masih kosong atau tidak
   *
   * @return boolean
   */
  bool isNodeEmpty() {
    // Jika head bernilai nullptr maka kembalikan nilai true,
    // Jika head tidak bernilai nullptr maka kembalikan nilai false
    return head == nullptr;
  }

  /**
   * @brief Menghitung jumlah data yang ada pada node
   *
   * @return integer
   */
  int totalNodeData() {
    // Inisialisasi variable total dengan nilai 0
    int total = 0;

    // Cek apakah node kosong, jika iya maka kembalikan nilai 0
    if (isNodeEmpty()) return total;

    // Memberikan nilai head pada variable current node
    currentNode = head;

    do {
      // Menambahkan satu nilai untuk variable total
      total++;

      // Mengganti nilai current menjadi node sebelumnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Kembalikan nilai total
    return total;
  }

  /**
   * @brief Membuat node baru pada variable new node
   *
   * @param data untuk memberikan nilai pada field data
   *
   * @return void
   */
  void createNode(T data) {
    // Membuat node baru dengan template typename class
    newNode = new NodeStruct<T>();

    // Memberikan nilai data pada field data dari newNode
    newNode->data = data;

    // Memberikan nilai nullptr pada field next dan prev dari newNode
    newNode->next = newNode->prev = nullptr;
  }

  /**
   * @brief Memberikan nilai pada head dan tail menjadi new node
   *
   * @return void
   */
  void insertHeadAndTail() {
    // Memberikan nilai head dan tail menjadi newNode
    head = tail = newNode;

    // Memberikan nilai next dan prev dari newNode menjadi head
    newNode->next = newNode->prev = head;
  }

  /**
   * @brief Mencari node dengan paratemer posisi
   *
   * @tparam C yaitu tipa data yang akan di cari
   * @param position untuk mencari posisi node
   *
   * @return C
   */
  template <typename C>
  C findNode(int position) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isNodeEmpty untuk mengecek
    if (isNodeEmpty()) return C{};

    // Jika posisi lebih besar dari total data node
    // maka tampilkan pesan bahwa data tidak ditemukan
    if (position > totalNodeData()) {
      // Menampilkan pesan bahwa data tidak ditemukan
      cout << "Data tidak ditemukan" << endl;

      // Mengembalikan nilai data kosong
      return T{};
    }

    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable index dengan nilai 0
    int index = 0;

    do {
      // Jika index sama dengan position - 1
      // maka matikan looping
      if (index == position - 1) return currentNode->data;

      // Menambahkan satu nilai untuk variable index
      index++;

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Jika data tidak ditemukan maka tampilkan pesan
    cout << "Data tidak ditemukan" << endl;

    // Mengembalikan data dari variable current node
    return C{};
  }

  /**
   * @brief Mencari node dengan parameter struct UserStruct
   *
   * @param user untuk mencari data yang sama dalam node
   *
   * @return UserStruct
   */
  UserStruct findNode(UserStruct user) {
    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable isFound dengan nilai false
    bool isFound = false;

    do {
      // Jika data username sama dengan data usernama dari current node
      // maka ubah nilai isFound menjadi true dan matikan loop
      if (currentNode->data.username == user.username) {
        // Mengubah nilai isFound menjadi true
        isFound = true;

        // Matikan looping
        break;
      }

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Jika isFound bernilai true maka kembalikan data dari current node
    // Jika tidak maka kembalikan struct UserStruct dengan data kosong
    return (isFound) ? currentNode->data : UserStruct{};
  }

  /**
   * @brief Mencari node dengan parameter struct PackageStruct
   *
   * @param data untuk mencari data yang sama dalam node
   *
   * @return PackageStruct
   */
  PackageStruct findNode(PackageStruct data) {
    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable isFound dengan nilai false
    bool isFound = false;

    do {
      // Jika data name sama dengan data nama dari current node
      // maka ubah nilai isFound menjadi true dan matikan loop
      if (currentNode->data.name == data.name) {
        isFound = true;
        break;
      }

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Jika isFound bernilai true maka kembalikan data dari current node
    // Jika tidak maka kembalikan struct PackageStruct dengan data kosong
    return (isFound) ? currentNode->data : PackageStruct{};
  }

  /**
   * @brief Menampilkan data dari struct UserStruct
   *
   * @param data yaitu data yang akan ditampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   * @param _category untuk memberikan nilai kategori data yang akan di tampilkan
   *
   * @return void
   */
  void displayNode(UserStruct data, bool isDetail = false, int _category = 1) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Jiak data username kosong maka mengembalikan nilai void
    if (data.username.empty()) return;

    // Menampilkan data yang ada pada node
    cout << "Username : " << data.username << " (" << data.role << ")" << endl;

    // Jika isDetail bernilai false maka kembalikan nilai void
    if (!isDetail || data.password.empty()) return;

    // Menampilkan data password yang ada pada node
    cout << "Password : " << data.password << endl;
  }

  /**
   * @brief Menampilkan data dari struct PackageStruct
   *
   * @param data yaitu data yang akan ditampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   * @param category untuk memberikan nilai kategori data yang akan di tampilkan
   *
   * @return void
   */
  void displayNode(PackageStruct data, bool isDetail = false, int category = 1) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Jika data name kosong maka mengembalikan nilai void
    if (data.name.empty() || data.description.empty()) return;

    // Menampilkan data yang ada pada node
    cout << "Nama  : " << data.name << " (" << destinationTypeToString(data.type) << ")" << endl;
    cout << data.description << endl;
    cout << "Harga : Rp. " << Parse::intToCurrencyFormat(data.price) << " / " << data.people << " orang" << endl;

    // Jika isDetail bernilai false maka kembalikan nilai void
    if (!isDetail) return;

    // Menampilkan detail data yang ada pada node
    cout << "Jenis Transportasi : " << getFacilityName(data.transport) << endl;
    cout << "Fasilitas : " << data.facility << endl;
    cout << "Durasi : " << data.duration << " hari" << endl;
  }

  /**
   * @brief Mengupdate data pada node dengan parameter data dan newData
   *
   * @param data untuk mencari data yang akan di update
   * @param newData untuk memberikan nilai data yang baru
   *
   * @return UserStruct
   */
  UserStruct updateNode(UserStruct data, UserStruct newData) {
    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable isFound dengan nilai false
    bool isFound = false;

    do {
      // Jika data username sama dengan data username dari current node
      // maka ubah nilai isFound menjadi true dan matikan loop
      if (currentNode->data.username == data.username) {
        // Mengubah nilai isFound menjadi true
        isFound = true;

        // Matikan looping
        break;
      }

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Jika isFound bernilai true maka kembalikan data dari current node
    // Jika tidak maka kembalikan struct UserStruct dengan data kosong
    if (isFound) {
      // Mengupdate data pada node dengan parameter data dan newData
      currentNode->data = newData;

      // Mengembalikan nilai data dari current node
      return currentNode->data;
    }

    // Jika data tidak ditemukan maka kembalikan nilai data kosong
    return UserStruct{};
  }

public:
  /**
   * @brief Constructor dari class List yang akan
   *       memberikan nilai nullptr pada head dan tail
   *      ketika class List di inisialisasi
   * 
   * @return void
   */
  List() {
    // Memberikan nilai nullptr pada head dan tail
    // dengan alur head = tail, yang mana nilai dari
    // tail diinisialisasi dengan nilai nullptr
    // sehingga head dan tail memiliki nilai yang sama
    head = tail = nullptr;
  }

  /**
   * @brief Destructor dari class List yang akan
   *       menghapus semua data yang ada pada node
   *       ketika class List di hancurkan
   * 
   * @return void
   */
  ~List() {
    // Menghapus semua memory yang ada pada node
    // mengubah nilai menjadi nullptr
    newNode = currentNode = nodeHelper = nullptr;
  }

  /**
   * @brief Menghitung jumlah data yang ada pada node
   * 
   * @return integer
   */
  int size() {
    // Memanggil method totalNodeData untuk menghitung
    // jumlah data yang ada pada node dan mengembalikan nilai
    // dari total data yang ada pada node
    return totalNodeData();
  }

  /**
   * @brief Mengecek apakah node masih kosong atau tidak
   *
   * @return boolean
   */
  bool isEmpty() {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka kembalikan nilai true
    // Jika node tidak kosong maka kembalikan nilai false
    return isNodeEmpty();
  }

  /**
   * @brief Menambahkan data pada head node dengan
   *       parameter data yang akan di masukan
   * 
   * @param data nilai yang akan di masukan pada node dengan tipe data T
   * 
   * @return void
   */
  void insertHead(T data) {
    // Memanggil method createNode untuk membuat node baru
    // dengan parameter data yang akan di masukan
    // sehingga newNode akan memiliki nilai data yang sama
    createNode(data);

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka memanggil method insertHeadAndTail
    if (isNodeEmpty()) {
      // Memanggil method insertHeadAndTail untuk memberikan
      // nilai pada head dan tail menjadi newNode
      insertHeadAndTail();

      // Matikan method insertHead
      return;
    }

    // Memberikan nilai prev dari head menjadi newNode
    head->prev = newNode;

    // Memberikan nilai next dari newNode menjadi head
    newNode->next = head;

    // Memberikan nilai next dari tail menjadi newNode
    tail->next = newNode;

    // Memberikan nilai prev dari newNode menjadi tail
    newNode->prev = tail;

    // Memberikan nilai head menjadi newNode
    head = newNode;
  }

  /**
   * @brief Menambahkan data pada tail node dengan
   *       parameter data yang akan di masukan
   * 
   * @param data nilai yang akan di masukan pada node dengan tipe data T
   * 
   * @return void
   */
  void insertTail(T data) {
    // Memanggil method createNode untuk membuat node baru
    // dengan parameter data yang akan di masukan
    // sehingga newNode akan memiliki nilai data yang sama
    createNode(data);

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka memanggil method insertHeadAndTail
    if (isNodeEmpty()) {
      // Memanggil method insertHeadAndTail untuk memberikan
      // nilai pada head dan tail menjadi newNode
      insertHeadAndTail();

      // Matikan method insertHead
      return;
    }

    // Memberikan nilai prev dari head menjadi newNode
    head->prev = newNode;

    // Memberikan nilai next dari tail menjadi newNode
    tail->next = newNode;

    // Memberikan nilai next dari newNode menjadi head
    newNode->next = head;

    // Memberikan nilai prev dari newNode menjadi tail
    newNode->prev = tail;

    // Memberikan nilai tail menjadi newNode
    tail = newNode;
  }

  /**
   * @brief Menambahkan data pada node dengan
   *       parameter data yang akan di masukan
   * 
   * @param position posisi node yang akan di masukan
   * @param data nilai yang akan di masukan pada node dengan tipe data T
   * 
   * @return void
   */
  void insertAt(int position, T data) {
    // Jika posisi sama dengan 1 maka masukan data pada head
    if (position == 1) {
      // Memanggil method insertHead untuk memasukan data pada head
      insertHead(data);

      // Matikan method insertAt
      return;
    }

    // Jika posisi sama dengan total data node
    // maka masukan data pada tail
    if (position == totalNodeData()) {
      // Memanggil method insertTail untuk memasukan data pada tail
      insertTail(data);

      // Matikan method insertAt
      return;
    }

    // Memanggil method createNode untuk membuat node baru
    // dengan parameter data yang akan di masukan
    // sehingga newNode akan memiliki nilai data yang sama
    createNode(data);

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka memanggil method insertHeadAndTail
    if (isNodeEmpty()) {
      // Memanggil method insertHeadAndTail untuk memberikan
      // nilai pada head dan tail menjadi newNode
      insertHeadAndTail();

      // Matikan method insertHead
      return;
    }

    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable index dengan nilai 0
    int index = 0;

    do {
      // Jika index sama dengan position - 1
      // maka masukan data pada node
      if (index == position - 1) {
        // Memberikan nilai next dari newNode menjadi current node
        newNode->next = currentNode;

        // Memberikan nilai prev dari newNode menjadi current node sebelumnya
        newNode->prev = currentNode->prev;

        // Memberikan nilai next dari current node sebelumnya menjadi newNode
        currentNode->prev->next = newNode;

        // Memberikan nilai prev dari current node menjadi newNode
        currentNode->prev = newNode;

        // Matikan looping
        break;
      }

      // Menambahkan satu nilai untuk variable index
      index++;

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);
  }

  /**
   * @brief Mencari data pada node dengan parameter
   *       data yang akan di cari
   * 
   * @tparam C Jenis data yang akan di masukan pada node
   * @param data nilai yang akan di masukan pada node dengan tipe data T
   */
  template <typename C>
  C findNodeData(int type, C data = C{}) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka kembalikan nilai data kosong
    if (isNodeEmpty()) return C{};

    // Inisialisasi variable position dengan nilai 0
    int position;

    // Melakukan pengecekan tipe data yang akan di cari
    switch (type) {
    // Jika tipe data adalah 1
    case 1:
      // Meminta inputan dari user untuk mencari data
      position = InputData::getInputIntRange(
        "Masukan id : ",
        "ID harus berupa angka, dan lebih dari 0 serta kurang dari " + std::to_string(totalNodeData() + 1) + "!",
        1, totalNodeData()
      );

      // Mencari data pada node dengan parameter position
      data = findNode<C>(position);

      // Matikan pengecekan tipe data
      break;
    // Jika tipe data adalah 2
    case 2:
      // Mencari data pada node dengan parameter data
      data = findNode(data);

      // Matikan pengecekan tipe data
      break;
    // Jika tipe data tidak valid
    default:
      // Menampilkan pesan bahwa tipe data tidak valid
      cout << "Tipe data tidak valid" << endl;

      // Matikan pengecekan tipe data
      break;
    }

    // Mengembalikan nilai data yang ditemukan
    return data;
  }

  /**
   * @brief Mengupdate data pada node dengan parameter
   *        data yang akan di update dan newData yang
   *       akan di masukan pada node
   * 
   * @tparam C Jenis data yang akan di update pada node
   * @param data nilai yang akan dicari pada node
   * @param newData nilai yang akan di update pada node
   */
  template <typename C>
  C update(C data, C newData) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method update
      return C{};
    }

    // Memanggil method updateNode untuk mengupdate data
    // pada node dengan parameter data dan newData
    return updateNode(data, newData);
  }

  /**
   * @brief Menghapus data pada node
   *
   * @return void
   */
  void removeHead() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method removeHead
      return;
    }

    // Memanggil method totalNodeData untuk menghitung
    // jumlah data yang ada pada node
    int total = totalNodeData();

    // Jika total data sama dengan 1
    // maka hapus data pada head
    if (total == 1) {
      // Menghapus data pada head
      delete head;

      // Memberikan nilai nullptr pada head dan tail
      head = tail = nullptr;

      // Matikan method removeHead
      return;
    }

    // Memberikan nilai nodeHelper pada head
    nodeHelper = head;

    // Memberikan nilai head pada nodeHelper
    head = head->next;

    // Memberikan nilai next dari tail menjadi head
    tail->next = head;

    // Memberikan nilai prev dari head menjadi tail
    head->prev = tail;

    // Menghapus data pada nodeHelper
    delete nodeHelper;
  }

  /**
   * @brief Menghapus semua data yang ada pada node
   *
   * @return void
   */
  void clear() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node tidak kosong maka hapus semua data
    if (!isNodeEmpty()) {
      // Inisialisasi variable total dengan nilai totalNodeData
      int total = totalNodeData();

      // Melakukan looping hingga total data lebih besar dari 0
      for (int i = 0; i < total; i++) {
        // Memanggil method removeHead untuk menghapus data pada node
        removeHead();
      }
    }

    // Menampilkan pesan bahwa semua data berhasil di hapus
    cout << "Semua data berhasil di hapus" << endl;
  }

  /**
   * @brief Menampilkan semua data yang ada pada node
   *
   * @param page untuk memberikan nilai halaman yang akan di tampilkan
   * @param perpage untuk memberikan nilai data per halaman yang akan di tampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   *
   * @return PaginationStruct
   */
  PaginationStruct showAllNodes(int page, int perpage, bool isDetail = false, int category = 1) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Insialisasi variable isBack dengan nilai false
    bool isBack = false;

    // Insialisasi variable isNext dengan nilai false
    bool isNext = false;

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Mengembalikan nilai struct PaginationStruct dengan nilai default
      return PaginationStruct{isBack, isNext};
    }

    // Inisialisasi variable total dengan nilai 0
    int total = totalNodeData();

    // Inisialisasi variable offset
    // dengan nilai page dikurangi 1 dikali perpage
    int offset = page * perpage;

    // Inisialisasi variable start
    // dengan nilai offset dikurangi perpage
    int start = offset - perpage;

    // Insialisasi variable index dengan nilai 0
    int index = 0;

    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Menampilkan separator untuk memisahkan data
    cout << "====================" << endl;

    // Melakukan looping hingga index sama dengan offset
    do {
      // Jika index sama atau lebih besar dari start
      // dan index lebih kecil dari total data
      // serta index lebih kecil dari offset
      // maka tampilkan data yang ada pada node
      if (index >= start && index < total && index < offset) {
        // Menampilkan id data yang ada pada node
        cout << "ID : " << index + 1 << endl;

        // Menampilkan data yang ditemukan pada node
        displayNode(currentNode->data, isDetail, category);

        // Menampilkan separator untuk memisahkan data
        cout << "====================" << endl;
      }

      // Menambahkan satu nilai untuk variable index
      index++;

      // Mengganti nilai current menjadi node setelahnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (index < offset);

    // Jika offset lebih kecil dari total data
    // maka ubah nilai isNext menjadi true
    if (offset < total) isNext = true;

    // Jika page lebih besar dari 1
    // maka ubah nilai isBack menjadi true
    if (page > 1) isBack = true;

    // Mengembalikan nilai struct PaginationStruct
    return PaginationStruct{isBack, isNext};
  }

  /**
   * @brief Menampilkan data yang ada pada node
   *        dengan parameter data yang akan di tampilkan
   * 
   * @tparam C Jenis data yang akan di tampilkan pada node
   * @param id menggunakan id untuk mencari data pada node
   * 
   * @return C
   */
  template <typename C>
  C showNodeData(bool isDetail = false) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method showNodeData
      return C{};
    }

    // Mencari data yang akan di tampilkan pada node
    // dengan parameter data yang akan dicari
    C foundData = findNodeData<T>(1);

    // Menampilkan data yang ditemukan pada node
    displayNode(foundData, isDetail);

    // Mengembalikan nilai data yang ditemukan
    return foundData;
  }
};

#endif // LINKED_LIST_HPP
