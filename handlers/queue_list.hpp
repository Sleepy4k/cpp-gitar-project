#pragma once

#ifndef QUEUE_LIST_HPP
#define QUEUE_LIST_HPP

#include <string>
#include <iostream>

#include "../helpers/parse.hpp"
#include "../helpers/input_data.hpp"
#include "../structs/node_struct.hpp"
#include "../structs/comment_struct.hpp"
#include "../structs/pagination_struct.hpp"
#include "../structs/destination_struct.hpp"

using std::cout;
using std::endl;
using std::string;

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
   * @brief Menampilkan data yang ada pada node
   *
   * @param data data yang akan di tampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   *
   * @return void
   */
  void displayNode(CommentStruct data, bool isDetail) {
    if (data.username.empty() || data.comment.empty()) return;

    cout << "Nama Destinasi : " << data.destination_name << endl;
    cout << "Nama Pengguna : " << data.username << endl;
    cout << "Komentar : " << data.comment << endl;

    if (!isDetail) return;

    if (data.rating < 1 || data.rating > 5) return;

    switch (data.rating) {
    case 1:
      cout << "Rating : 1 (Sangat Buruk)" << endl;
      break;
    case 2:
      cout << "Rating : 2 (Buruk)" << endl;
      break;
    case 3:
      cout << "Rating : 3 (Cukup)" << endl;
      break;
    case 4:
      cout << "Rating : 4 (Baik)" << endl;
      break;
    case 5:
      cout << "Rating : 5 (Sangat Baik)" << endl;
      break;
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
  Queue() {
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
    // Jika node kosong maka memanggil method insertHeadAndTail
    if (isNodeEmpty()) {
      // Memanggil method insertHeadAndTail untuk memberikan
      // nilai pada head dan tail menjadi newNode
      insertHeadAndTail();

      // Matikan method insertHead
      return;
    }

    // Memberikan nilai next dari tail menjadi newNode
    tail->next = newNode;

    // Memberikan nilai prev dari newNode menjadi tail
    newNode->prev = tail;

    // Memberikan nilai next dari newNode menjadi head
    newNode->next = head;

    // Memberikan nilai prev dari head menjadi newNode
    head->prev = newNode;

    // Memberikan nilai head menjadi newNode
    head = newNode;
  }

  /**
   * @brief Menghapus data dari node
   *
   * @return void
   */
  void dequeue() {
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
      delete head;

      // Memberikan nilai nullptr pada head dan tail
      head = tail = nullptr;

      // Matikan method update
      return;
    }

    // Memberikan nilai nodeHelper pada head
    nodeHelper = head;

    // Memberikan nilai head pada node selanjutnya
    head = head->next;

    // Memberikan nilai prev dari head menjadi nullptr
    head->prev = tail;

    // Memberikan nilai next dari tail menjadi head
    tail->next = head;

    // Menghapus nodeHelper
    delete nodeHelper;
  }

  /**
   * @brief Menghapus data dari node
   *
   * @param destinationName untuk memberikan nilai nama destinasi yang akan di hapus
   * @param username untuk memberikan nilai username yang akan di hapus
   *
   * @return void
   */
  void dequeue(const string &destinationName, const string &username) {
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
      // Jika data yang ditemukan adalah data yang dicari
      if (head->data.username == username && head->data.destination_name == destinationName) {
        delete head;

        // Memberikan nilai nullptr pada head dan tail
        head = tail = nullptr;

        // Matikan method update
        return;
      }
    }

    // Memberikan nilai nodeHelper pada head
    nodeHelper = head;

    // Melakukan looping hingga nodeHelper sama dengan tail
    do {
      // Jika data yang ditemukan adalah data yang dicari
      if (nodeHelper->data.username != username
      && nodeHelper->data.destination_name != destinationName) {
        // Mengganti nilai nodeHelper menjadi node selanjutnya
        nodeHelper = nodeHelper->next;

        // Jika nodeHelper bukan head lanjut looping
        continue;
      }

      // Jika data yang ditemukan adalah head
      if (nodeHelper == head) {
        // Memberikan nilai head pada node selanjutnya
        head = head->next;

        // Memberikan nilai prev dari head menjadi tail
        head->prev = tail;

        // Memberikan nilai next dari tail menjadi head
        tail->next = head;

        // Menghapus nodeHelper
        delete nodeHelper;

        // Matikan method update
        return;
      }

      // Jika data yang ditemukan adalah tail
      if (nodeHelper == tail) {
        // Memberikan nilai tail pada node sebelumnya
        tail = tail->prev;

        // Memberikan nilai next dari tail menjadi head
        tail->next = head;

        // Memberikan nilai prev dari head menjadi tail
        head->prev = tail;

        // Menghapus nodeHelper
        delete nodeHelper;

        // Matikan method update
        return;
      }

      // Memberikan nilai next dari node sebelumnya
      nodeHelper->prev->next = nodeHelper->next;

      // Memberikan nilai prev dari node selanjutnya
      nodeHelper->next->prev = nodeHelper->prev;

      // Menghapus nodeHelper
      delete nodeHelper;

      // Matikan method update
      return;

      // Jika nodeHelper bukan head lanjut looping
    } while (nodeHelper != head);
  }

  /**
   * @brief Menampilkan semua data yang ada pada node
   *
   * @param destinationName untuk memberikan nilai nama destinasi yang akan di cari
   * @param page untuk memberikan nilai halaman yang akan di tampilkan
   * @param perpage untuk memberikan nilai data per halaman yang akan di tampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   *
   * @return PaginationStruct
   */
  PaginationStruct showAll(const string &destinationName, int page, int perpage, bool isDetail = false) {
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
      if (index >= start && index < total && index < offset
      && currentNode->data.destination_name == destinationName) {
        // Menampilkan id data yang ada pada node
        cout << "ID : " << index + 1 << endl;

        // Menampilkan data yang ditemukan pada node
        displayNode(currentNode->data, isDetail);

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
   * @brief Menampilkan semua data yang ada pada node
   *        berdasarkan username yang di cari
   * 
   * @param destinationName untuk memberikan nilai nama destinasi yang akan di cari
   * @param username untuk memberikan nilai username yang akan di cari
   * @param page untuk memberikan nilai halaman yang akan di tampilkan
   * @param perpage untuk memberikan nilai data per halaman yang akan di tampilkan
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   *
   * @return PaginationStruct
   */
  PaginationStruct showAllByUsername(const string &destinationName, const string &username, int page, int perpage, bool isDetail = false) {
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
      if (index >= start && index < total && index < offset
      && currentNode->data.username == username
      && currentNode->data.destination_name == destinationName) {
        // Menampilkan id data yang ada pada node
        cout << "ID : " << index + 1 << endl;

        // Menampilkan data yang ditemukan pada node
        displayNode(currentNode->data, isDetail);

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
};

#endif // QUEUE_LIST_HPP
