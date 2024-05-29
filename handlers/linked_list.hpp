#pragma once

#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>
#include <iostream>

#include "../helpers/parse.hpp"
#include "../helpers/input_data.hpp"
#include "../structs/node_struct.hpp"
#include "../structs/user_struct.hpp"
#include "../structs/package_struct.hpp"
#include "../structs/pagination_struct.hpp"
#include "../structs/destination_struct.hpp"
#include "../enums/package_transport_enum.hpp"

using std::cout;
using std::endl;
using std::string;

/**
 * Deklarasi class List
 *
 * Class list ini kita gunakan untuk menghandle
 * double circular linked list yang kita buat
 * agar berjalan sesuai dengan definisi nya
 * serta dapat menyimpan secara dinamik untuk
 * semua struct yang sudah kita buat seperti
 * destination dan user menggunakan algorithm
 * stack (LIFO - Last In First Out)
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
template <typename C>
class List {
private:
  // Inisialisasi variable bertipe data struct Node dengan
  // template dari typename class
  NodeStruct<C> *head, *tail, *newNode, *currentNode, *nodeHelper;

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

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Kembalikan nilai total
    return total;
  }

  /**
   * @brief Membuat node baru pada variable new node
   *
   * @tparam T Jenis data yang akan di masukan pada node
   * @param data untuk memberikan nilai pada field data
   *
   * @return void
   */
  template <typename T>
  void createNode(T data) {
    // Membuat node baru dengan template typename class
    newNode = new NodeStruct<C>();

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
   * @tparam T Jenis data yang akan di kembalikan
   * @param position untuk mencari posisi node
   *
   * @return T
   */
  template <typename T>
  T findNode(int position) {
    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable index dengan nilai 0
    int index = 0;

    // Jika posisi lebih besar dari total data node
    // maka tampilkan pesan bahwa data tidak ditemukan
    if (position > totalNodeData()) {
      cout << "Data tidak ditemukan" << endl;
      return T{};
    }

    // Melakukan loop hingga index sama dengan position - 1
    while (index < position - 1) {
      // Menambahkan satu nilai untuk variable index
      index++;

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;
    }

    // Mengembalikan data dari variable current node
    return currentNode->data;
  }

  /**
   * @brief Mencari node dengan parameter struct DestinationStruct
   *
   * @param data untuk mencari data yang sama dalam node
   *
   * @return DestinationStruct
   */
  DestinationStruct findNode(DestinationStruct data) {
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
    // Jika tidak maka kembalikan struct DestinationStruct dengan data kosong
    return (isFound) ? currentNode->data : DestinationStruct{};
  }

  /**
   * @brief Mencari node dengan parameter struct UserStruct
   *
   * @param data untuk mencari data yang sama dalam node
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
        isFound = true;
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
   * @brief Menampilkan data dari struct DestinationStruct
   *
   * @param data yaitu data yang akan ditampilkan
   *
   * @return void
   */
  void displayNode(DestinationStruct data, bool isDetail = false, int _category = 1) {
    if (data.name.empty() || data.description.empty() || data.location.empty())
      return;

    cout << "Nama : " << data.name << " (" << destinationTypeToString(data.type) << ")" << endl;
    cout << "Lokasi : " << data.location << endl;
    cout << "Deskripsi : " << data.description << endl;

    if (!isDetail) return;

    if (data.price != 0)
      cout << "Harga Tiket : Rp. " << Parse::intToCurrencyFormat(data.price) << " / " << data.person << " orang" << endl;
    else
      cout << "Harga Tiket : Gratis" << endl;

    cout << "Jumlah Pengunjung : " << Parse::intToDouble(data.pengunjung) << " orang" << endl;
    cout << "Jam Operasional : " << data.work_hours << endl;
  }

  /**
   * @brief Menampilkan data dari struct UserStruct
   *
   * @param data yaitu data yang akan ditampilkan
   *
   * @return void
   */
  void displayNode(UserStruct data, bool isDetail = false, int _category = 1) {
    if (data.username.empty()) return;

    cout << "Username : " << data.username << " (" << data.role << ")" << endl;

    if (!isDetail || data.password.empty()) return;

    cout << "Password : " << data.password << endl;
  }

  void displayNode(PackageStruct data, bool isDetail = false, int category = 1) {
    if (data.name.empty() || data.description.empty()) return;

    cout << "Nama : " << data.name << " (" << destinationTypeToString(data.type) << ")" << endl;
    cout << data.description << endl;
    cout << "Harga : Rp. " << Parse::intToCurrencyFormat(data.price) << " / " << data.people << " orang" << endl;

    if (!isDetail) return;

    cout << "Jenis Transportasi : " << getFacilityName(data.transport) << endl;
    cout << "Fasilitas : " << data.facility << endl;
    cout << "Durasi : " << data.duration << " hari" << endl;
  }

  DestinationStruct updateNode(DestinationStruct data, DestinationStruct newData) {
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
    // Jika tidak maka kembalikan struct DestinationStruct dengan data kosong
    if (isFound) {
      currentNode->data = newData;
      return currentNode->data;
    }

    return DestinationStruct{};
  }

  UserStruct updateNode(UserStruct data, UserStruct newData) {
    // Memberikan nilai head pada variable current node
    currentNode = head;

    // Inisialisasi variable isFound dengan nilai false
    bool isFound = false;

    do {
      // Jika data username sama dengan data username dari current node
      // maka ubah nilai isFound menjadi true dan matikan loop
      if (currentNode->data.username == data.username) {
        isFound = true;
        break;
      }

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (currentNode != head);

    // Jika isFound bernilai true maka kembalikan data dari current node
    // Jika tidak maka kembalikan struct UserStruct dengan data kosong
    if (isFound) {
      currentNode->data = newData;
      return currentNode->data;
    }

    return UserStruct{};
  }

  void removingNodeByData(DestinationStruct data) {
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
    // Jika tidak maka kembalikan struct DestinationStruct dengan data kosong
    if (isFound) {
      nodeHelper = currentNode->prev;
      nodeHelper->next = currentNode->next;

      nodeHelper = currentNode->next;
      nodeHelper->prev = currentNode->prev;

      delete currentNode;
    } else {
      cout << "Data tidak ditemukan" << endl;
      return;
    }
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
   * @tparam T Jenis data yang akan di masukan pada node
   * @param data nilai yang akan di masukan pada node dengan tipe data T
   */
  template <typename T>
  void push(T data) {
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
   * @brief Mencari data pada node dengan parameter
   *       data yang akan di cari
   * 
   * @tparam T Jenis data yang akan di masukan pada node
   * @param data nilai yang akan di masukan pada node dengan tipe data T
   */
  template <typename T>
  T findNodeData(int type, T data = T{}) {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka kembalikan nilai data kosong
    if (isNodeEmpty()) return T{};

    // Inisialisasi variable position dengan nilai 0
    int position;

    // Melakukan pengecekan tipe data yang akan di cari
    switch (type) {
    // Jika tipe data adalah 1
    case 1:
      // Meminta inputan dari user untuk mencari data
      position = InputData::getInputIntRange(
        "Masukan id : ",
        "ID harus berupa angka",
        1, totalNodeData()
      );

      // Mencari data pada node dengan parameter position
      data = findNode<T>(position);

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
   * @tparam T Jenis data yang akan di update pada node
   * @param data nilai yang akan dicari pada node
   * @param newData nilai yang akan di update pada node
   */
  template <typename T>
  T update(T data, T newData) {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method update
      return T{};
    }

    // Memanggil method updateNode untuk mengupdate data
    // pada node dengan parameter data dan newData
    return updateNode(data, newData);
  }

  /**
   * @brief Menghapus data pada tail node
   * 
   * @return void
   */
  void pop() {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method update
      return;
    }

    // Jika data yang ditemukan adalah head
    if (head == tail) {
      // Menghapus data pada head dan tail
      delete head;

      // Memberikan nilai nullptr pada head dan tail
      head = tail = nullptr;

      // Matikan method remove
      return;
    }

    // Memberikan nilai tail menjadi node sebelum tail
    tail = tail->prev;

    // Menghapus data pada node setelah tail
    delete tail->next;

    // Memberikan nilai next dari tail menjadi head
    tail->next = head;

    // Memberikan nilai prev dari head menjadi tail
    head->prev = tail;
  }

  /**
   * @brief Menghapus data pada node dengan parameter
   *        data yang akan di hapus
   * 
   * @tparam T Jenis data yang akan di hapus pada node
   * @param data nilai yang akan di hapus pada node
   */
  template <typename T>
  void removeByData(T data) {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method update
      return;
    }

    // Memanggil method removingNodeByData untuk menghapus data
    // pada node dengan parameter data yang akan di hapus
    removingNodeByData(data);
  }

  /**
   * @brief Menghapus semua data yang ada pada node
   *
   * @return void
   */
  void clear() {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node tidak kosong maka hapus semua data
    if (!isNodeEmpty()) {
      // Memberikan nilai currentNode menjadi head
      currentNode = head->next;

      // Melakukan looping hingga currentNode sama dengan head
      while (currentNode != head) {
        // Memberikan nilai nodeHelper menjadi node selanjutnya
        nodeHelper = currentNode->next;

        // Menghapus data pada currentNode
        delete currentNode;

        // Memberikan nilai currentNode menjadi nodeHelper
        currentNode = nodeHelper;
      }

      // Menghapus data pada head ketika currentNode sama dengan head
      delete head;

      // Memberikan nilai nullptr pada head dan tail
      head = tail = nullptr;
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

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan head lanjut looping
    } while (index <= offset);

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
   * @param id menggunakan id untuk mencari data pada node
   */
  template <typename T>
  T showNodeData(bool isDetail = false) {
    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isNodeEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method showNodeData
      return T{};
    }

    // Mencari data yang akan di tampilkan pada node
    // dengan parameter data yang akan dicari
    T foundData = findNodeData<T>(1);

    // Menampilkan data yang ditemukan pada node
    displayNode(foundData, isDetail);

    // Mengembalikan nilai data yang ditemukan
    return foundData;
  }
};

#endif // LINKED_LIST_HPP
