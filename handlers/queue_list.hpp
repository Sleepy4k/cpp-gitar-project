#pragma once

#ifndef QUEUE_LIST_HPP
#define QUEUE_LIST_HPP

#include <iostream>

#include "../helpers/parse.hpp"
#include "../helpers/input_data.hpp"
#include "../structs/node_struct.hpp"
#include "../structs/reciept_struct.hpp"
#include "../structs/pagination_struct.hpp"

/**
 * Deklarasi class Queue
 *
 * Class Queue ini kita gunakan untuk menghandle
 * double circular linked list yang kita buat
 * agar berjalan sesuai dengan definisi nya
 * serta dapat menyimpan secara dinamik untuk
 * data komentar atau ulasan dari pengguna
 * menggunakan algorithm queue
 * (FIFO - First In First Out)
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
template <typename C>
class Queue {
private:
  // Inisialisasi variable bertipe data struct Node
  // dengan template dati typename class
  NodeStruct<C> *front, *back, *newNode, *currentNode, *nodeHelper;

  /**
   * @brief Mengecek apakah data dalam node masih kosong atau tidak
   *
   * @return boolean
   */
  bool isNodeEmpty() {
    // Jika front dan back memiliki nilai nullptr
    // maka kembalikan nilai true
    // Jika front dan back memiliki nilai selain nullptr
    // maka kembalikan nilai false
    return (front == nullptr && back == nullptr);
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

    // Memberikan nilai front pada variable current node
    currentNode = front;

    // Jika current node sama dengan back maka kembalikan nilai 1
    if (currentNode == back) return 1;

    // Melakukan perulangan hingga current node tidak sama dengan nullptr
    do {
      // Menambahkan satu nilai untuk variable total
      total++;

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan front lanjut looping
    } while (currentNode != nullptr);

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
   * @brief Memberikan nilai pada front dan back menjadi new node
   *
   * @return void
   */
  void insertFrontAndBack() {
    // Memberikan nilai front dan bacl menjadi newNode
    front = back = newNode;

    // Memberikan nilai next dan prev dari newNode menjadi front
    newNode->next = front;
  }

  /**
   * @brief Menampilkan data yang ada pada node
   *
   * @param data data yang akan di tampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   *
   * @return void
   */
  void displayNode(int id, RecieptStruct data, bool isDetail) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Melakukan pengecekan apakah data name dan phone kosong
    // jika iya maka kembalikan nilai void
    if (data.name.empty() || data.phone.empty()) return;

    cout << "ID             : " << id << endl;
    cout << "Nama           : " << data.name << endl;
    cout << "Telepon        : " << data.phone << endl;
    cout << "Paket          : " << data.package << endl;
    cout << "Tanggal        : " << data.date << endl;

    // Melakukan pengecekan apakah isDetail bernilai true
    // jika iya maka kita akan menampilkan data lebih detail
    if (!isDetail) return;

    cout << "Durasi         : " << data.duration << " hari" << endl;
    cout << "Harga          : Rp. " << Parse::intToCurrencyFormat(data.price) << endl;
    cout << "Jumlah         : " <<  data.people << " orang" << endl;
  }

public:
  /**
   * @brief Constructor dari class List yang akan
   *       memberikan nilai nullptr pada front dan back
   *      ketika class List di inisialisasi
   * 
   * @return void
   */
  Queue() {
    // Memberikan nilai nullptr pada front dan back
    // dengan alur front = back, yang mana nilai dari
    // back diinisialisasi dengan nilai nullptr
    // sehingga front dan bacl memiliki nilai yang sama
    front = back = nullptr;
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

  C get(int index) {
    // Inisialisasi variable data dengan nilai default
    C data = C{};

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka kembalikan nilai data
    if (isNodeEmpty()) return data;

    // Inisialisasi variable index dengan nilai 0
    int i = 0;

    // Memberikan nilai front pada variable current node
    currentNode = front;

    // Melakukan perulangan hingga index lebih kecil dari total data
    do {
      // Jika index sama dengan nilai yang di cari
      if (i == index) {
        // Memberikan nilai data pada field data dari currentNode
        // ke dalam variable data
        data = currentNode->data;

        // Menghentikan perulangan
        break;
      }

      i++;

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan front lanjut looping
    } while (currentNode != front);

    // Mengembalikan nilai data
    return data;
  }

  /**
   * @brief Menambahkan data ke dalam node
   *
   * @tparam T jenis data yang akan dimasukkan ke dalam node
   * @param data data yang akan dimasukkan ke dalam node
   * 
   * @return void
   */
  template <typename T>
  void enqueue(T data) {
    // Memanggil method createNode untuk membuat node baru
    // dengan parameter data yang akan di masukan
    // sehingga newNode akan memiliki nilai data yang sama
    createNode(data);

    // Memanggil method isNodeEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka memanggil method insertFrontAndBack
    if (isNodeEmpty()) {
      // Memanggil method InsertFrontAndBack untuk memberikan
      // nilai pada front dan back menjadi newNode
      insertFrontAndBack();

      // Matikan method enqueue
      return;
    }

    // Memberikan nilai back pada field next dari newNode
    back->next = newNode;

    // Memberikan nilai front pada field prev dari newNode
    back = newNode;
  }

  /**
   * @brief Menghapus data dari node
   *
   * @return void
   */
  void dequeue() {
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
      return;
    }

    // Memberikan nilai front pada variable nodeHelper
    currentNode = front;

    // Memberikan nilai front pada field next dari front
    front = front->next;

    // Menghapus currentNode
    delete currentNode;
  }

  /**
   * @brief Menampilkan semua data yang ada pada node
   *
   * @param page untuk memberikan nilai halaman yang akan di tampilkan
   * @param perpage untuk memberikan nilai data per halaman yang akan di tampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   * @param username untuk memberikan nilai username yang akan di cari
   * @param isAdmin untuk memberikan nilai status admin yang akan di cari
   *
   * @return PaginationStruct
   */
  PaginationStruct showAll(int page, int perpage, bool isDetail, std::string username, bool isAdmin) {
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

    // Insialisasi variable found dengan nilai 0
    int found = 0;

    // Memberikan nilai front pada variable current node
    currentNode = front;

    // Menampilkan separator untuk memisahkan data
    cout << "====================" << endl;

    // Melakukan perulangan pada setiap data, hingga semua
    // data yang memiliki nama destinasi yang sama sudah habis
    do {
      // Jika index lebih besar atau sama dengan start
      // dan index lebih kecil dari total data
      // serta index lebih kecil dari offset
      // serta data yang ditemukan sama dengan username
      // maka tampilkan data yang ada pada node
      if (index < total && found < offset) {
        // Jika found lebih besar atau sama dengan start
        // maka tampilkan data yang ditemukan pada node
        if (found >= start) {
          // Menampilkan data yang ditemukan pada node
          displayNode(found + 1, currentNode->data, isDetail);

          // Menampilkan separator untuk memisahkan data
          cout << "====================" << endl;
        }

        // Menambahkan satu nilai untuk variable found
        found++;
      }

      // Menambahkan satu nilai untuk variable index
      index++;

      // Mengganti nilai current menjadi node selanjutnya
      currentNode = currentNode->next;

      // jika nilai current node bukan front lanjut looping
    } while (index < total);

    // Jika offset lebih kecil dari total data
    // maka ubah nilai isNext menjadi true
    if (offset < total) isNext = true;

    // Jika page lebih besar dari 1
    // maka ubah nilai isBack menjadi true
    if (page > 1) isBack = true;

    // Mengembalikan nilai struct PaginationStruct
    return PaginationStruct{isBack, isNext};
  }
};

#endif // QUEUE_LIST_HPP
