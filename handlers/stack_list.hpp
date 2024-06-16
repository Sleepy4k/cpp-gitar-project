#pragma once

#ifndef HANDLERS_STACK_LIST_HPP
#define HANDLERS_STACK_LIST_HPP

#include <iostream>

#include "../helpers/parse.hpp"
#include "../helpers/input_data.hpp"
#include "../structs/node_struct.hpp"
#include "../structs/pagination_struct.hpp"
#include "../structs/destination_struct.hpp"

/**
 * Deklarasi class Stack
 *
 * Class Stack ini kita gunakan untuk menghandle
 * single linked list yang kita buat
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
template <typename T>
class Stack {
private:
  NodeStruct<T> *top, *newNode, *currentNode;

  /**
   * @brief Mengecek apakah data dalam node masih kosong atau tidak
   *
   * @return boolean
   */
  bool isEmpty() {
    // Jika top bernilai nullptr maka akan mengembalikan nilai true
    // jika tidak akan mengembalikan nilai false
    return top == nullptr;
  }

  /**
   * @brief Menghitung total data yang ada pada node
   *
   * @return int
   */
  int totalNodeData() {
    // Insialisasi variable total dengan nilai 0
    int total = 0;

    if (isEmpty()) return total;

    // Menggunakan currentNode untuk mengecek data yang ada pada node
    currentNode = top;

    do {
      // Menambahkan satu nilai untuk variable total
      total++;

      // Mengganti nilai current menjadi node sebelumnya
      currentNode = currentNode->next;

      // jika nilai current node bukan nullptr lanjut looping
    } while (currentNode != nullptr);

    // Mengembalikan nilai total data yang ada pada node
    return total;
  }

  /**
   * @brief Mencari data pada node berdasarkan posisi
   *
   * @tparam C yaitu tipe data yang akan dicari
   * @param position yaitu posisi data yang akan dicari
   * 
   * @return C
   */
  template <typename C>
  C findNode(int position) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Jika data dalam node masih kosong
    if (isEmpty()) return C{};

    // Jika posisi lebih besar dari total data node
    // maka tampilkan pesan bahwa data tidak ditemukan
    if (position > totalNodeData()) {
      // Menampilkan pesan bahwa data tidak ditemukan
      cout << "Data tidak ditemukan" << endl;

      // Mengembalikan nilai struct T dengan nilai default
      return C{};
    }

    // Memberikan nilai top pada variable current node
    currentNode = top;

    // Inisialisasi variable index dengan nilai 0
    int index = 0;

    do {
      // Jika index sama dengan posisi
      // maka kembalikan data dari variable current node
      if (index == position) return currentNode->data;

      // Menambahkan satu nilai untuk variable index
      index++;

      // Mengganti nilai current menjadi node sebelumnya
      currentNode = currentNode->next;

      // jika nilai current node bukan nullptr lanjut looping
    } while (currentNode != nullptr);

    // Jika data tidak ditemukan maka tampilkan pesan
    cout << "Data tidak ditemukan" << endl;

    // Mengembalikan data dari variable current node
    return C{};
  }

  /**
   * @brief Menampilkan data dari struct DestinationStruct
   *
   * @param data yaitu data yang akan ditampilkan
   * @param isDetail yaitu menentukan apakah akan menampilkan detail atau tidak
   * @param _category yaitu kategori dari data yang akan ditampilkan
   *
   * @return void
   */
  void displayNode(DestinationStruct data, bool isDetail = false, int _category  = 1) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Jika data kosong maka akan mengembalikan nilai void
    if (data.name.empty() || data.description.empty() || data.location.empty())
      return;

    // Menampilkan data dari struct DestinationStruct
    cout << "Nama : " << data.name << " (" << destinationTypeToString(data.type) << ")" << endl;
    cout << "Lokasi : " << data.location << endl;
    cout << "Deskripsi : " << data.description << endl;

    // Jika nilai isDetail bernilai true maka akan menampilkan detail
    // jika tidak maka akan mengembalikan nilai void
    if (!isDetail) return;

    // Menampilkan detail dari data
    if (data.price != 0)
      cout << "Harga Tiket : Rp. " << Parse::intToCurrencyFormat(data.price) << " / " << data.person << " orang" << endl;
    else
      cout << "Harga Tiket : Gratis" << endl;

    cout << "Jumlah Pengunjung : " << Parse::intToDouble(data.pengunjung) << " orang" << endl;
    cout << "Jam Operasional : " << data.work_hours << endl;
  }

public:
  /**
   * @brief Constructor
   */
  Stack() {
    // Inisialisasi top dengan nullptr
    top = nullptr;
  }

  /**
   * @brief Mengecek apakah data dalam node masih kosong atau tidak
   *
   * @return boolean
   */
  bool empty() {
    return isEmpty();
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
   * @brief Menambahkan data ke dalam node
   * 
   * @param data data yang akan di masukkan ke dalam node
   * 
   * @return void
   */
  void push(T data) {
    // Membuat node baru
    newNode = new NodeStruct<T>;

    // Mengisi data ke dalam node baru
    newNode->data = data;

    // Mengisi pointer next dengan top
    newNode->next = top;

    // Mengisi pointer prev dengan nullptr
    newNode->prev = nullptr;

    // Mengganti top dengan node baru
    top = newNode;
  }

  /**
   * @brief Menghapus data dalam node teratas
   * 
   * @return void
   */
  void pop() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Jika data dalam node masih kosong
    if (isEmpty()) {
      // Maka akan menampilkan pesan error
      cout << "Stack is empty" << endl;
      return;
    }

    // Jika tidak maka akan menghapus node teratas
    currentNode = top;

    // Mengganti top dengan node selanjutnya
    top = top->next;

    // Menghapus node teratas
    delete currentNode;
  }

  /**
   * @brief Mencetak data dalam node teratas
   * 
   * @return void
   */
  T peek() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Jika data dalam node masih kosong
    if (isEmpty()) {
      // Maka akan menampilkan pesan error
      cout << "Stack is empty" << endl;

      // Menghentikan proses
      return T{};
    }

    // Menampilkan data dalam node teratas
    displayNode(top->data, true);

    // Mengembalikan data dalam node teratas
    return top->data;
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
    if (isEmpty()) {
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
    currentNode = top;

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

      // Mengganti nilai current menjadi node sebelumnya
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
   * @param isDetail untuk memberikan nilai detail data yang akan di tampilkan
   * 
   * @return T
   */
  T showNodeData(bool isDetail = false) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method isEmpty untuk mengecek
    // apakah node masih kosong atau tidak
    // Jika node kosong maka tampilkan pesan bahwa belum ada data
    if (isEmpty()) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Matikan method showNodeData
      return T{};
    }

    // Meminta inputan dari user untuk mencari data
    int position = InputData::getInputIntRange(
      "Masukan id : ",
      "ID harus berupa angka, dan diantara 1 sampai " + std::to_string(totalNodeData()) + "!",
      1, totalNodeData()
    );

    // Mencari data pada node dengan parameter position
    T foundData = findNode<T>(position - 1);

    // Menampilkan data yang ditemukan pada node
    displayNode(foundData, isDetail);

    // Mengembalikan nilai data yang ditemukan
    return foundData;
  }
};

#endif // HANDLERS_STACK_LIST_HPP
