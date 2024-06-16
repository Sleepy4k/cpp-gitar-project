#pragma once

#ifndef DESTINATION_CONTROLLER_HPP
#define DESTINATION_CONTROLLER_HPP

#include <iostream>

#include "user_controller.hpp"
#include "../helpers/path.hpp"
#include "../helpers/system.hpp"
#include "comment_controller.hpp"
#include "../enums/role_enum.hpp"
#include "../helpers/input_data.hpp"
#include "../handlers/stack_list.hpp"
#include "../helpers/file_storage.hpp"
#include "../models/destination_model.hpp"
#include "../structs/pagination_struct.hpp"
#include "../structs/destination_struct.hpp"

/**
 * Deklarasi class DestinationController
 *
 * Class list ini kita gunakan untuk menghandle
 * proses CRUD data destinasi wisata, dimana
 * nantinya kita akan menampilkan data destinasi
 * wisata, menambahkan data destinasi wisata,
 * mengubah data destinasi wisata, dan menghapus
 * data destinasi wisata
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
class DestinationController {
private:
  // Inisialisasi variabel userData untuk menyimpan data user
  // dari class UserController
  UserController userData;

  // Inisialisasi variabel commentController untuk menyimpan
  // data ulasan dari class CommentController
  CommentController commentController;

  // Inisialisasi variabel destinationList untuk menyimpan data destinasi
  // dari class LinkedList dengan tipe data DestinationStruct
  Stack<DestinationStruct> destinationList;

  /**
   * @brief Membuat form untuk mengisi data destinasi
   * 
   * @return DestinationStruct 
   */
  DestinationStruct form_destination() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Inisialisasi variabel type dan data untuk menyimpan data
    int type;

    // Inisialisasi variabel data untuk menyimpan data destinasi
    DestinationStruct data;

    // Meminta input dari user untuk mengisi nama destinasi
    data.name = InputData::getInputLine(
      "Masukan nama destinasi : ",
      "Nama destinasi tidak boleh kosong"
    );

    // Meminta input dari user untuk mengisi deskripsi destinasi
    data.description = InputData::getInputLine(
      "Masukan deskripsi destinasi : ",
      "Deskripsi destinasi tidak boleh kosong"
    );

    // Meminta input dari user untuk mengisi lokasi destinasi
    data.location = InputData::getInputLine(
      "Masukan lokasi destinasi : ",
      "Lokasi destinasi tidak boleh kosong"
    );

    // Meminta input dari user untuk mengisi jam operasional destinasi
    data.work_hours = InputData::getInputLine(
      "Masukan jam operasional : ",
      "Jam operasional tidak boleh kosong"
    );

    // Meminta input dari user untuk mengisi jumlah orang per tiket
    data.person = InputData::getInputIntRange(
      "Masukan jumlah orang per tiket : ",
      "Jumlah orang harus berupa angka! dan diantara 1 sampai 100!",
      1,
      100
    );

    // Meminta input dari user untuk mengisi harga per tiket
    data.price = InputData::getInputIntRange(
      "Masukan harga per tiket : ",
      "Harga harus berupa angka! dan diantara 1 sampai 1000000!",
      1,
      1000000
    );

    // Menaampilkan jenis destinasi
    cout << "Jenis destinasi" << endl;
    cout << "==================" << endl;
    cout << "1. Alam" << endl;
    cout << "2. Sejarah" << endl;
    cout << "3. Budaya" << endl;
    cout << "==================" << endl;

    // Meminta input dari user untuk mengisi jenis destinasi
    type = InputData::getInputIntRange(
      "Masukan jenis destinasi : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 3!",
      1,
      3
    );

    // Melakukan pengecekan jenis destinasi
    switch (type) {
    // Jika user memilih 1
    case 1:
      // Maka jenis destinasi akan menjadi alam
      data.type = Nature;

      // Menghentikan pengecekan
      break;
    // Jika user memilih 2
    case 2:
      // Maka jenis destinasi akan menjadi sejarah
      data.type = History;

      // Menghentikan pengecekan
      break;
    // Jika user memilih 3
    case 3:
      // Maka jenis destinasi akan menjadi budaya
      data.type = Culture;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3
    default:
      // Maka jenis destinasi akan menjadi alam secara default
      cout << "Pilihan tidak valid, jenis wisata akan menjadi alam secara default" << endl;

      // Menghentikan pengecekan
      data.type = Nature;

      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan data yang sudah di isi
    return data;
  }

  /**
   * @brief Fungsi untuk menambahkan data destinasi wisata
   * 
   * @return void
   */
  void insert_destination() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Deklarasi varaible position untuk menyimpan posisi data
    int position;

    // Memanggil method form_destination untuk membuat form
    // dan mengisi dari data destinasi yang akan di inputkan
    DestinationStruct data = form_destination();

    // Memanggil method findByName pada DestinationModel
    // untuk mencari data destinasi berdasarkan nama
    DestinationStruct isDuplicated = DestinationModel::findByName(data.name);

    // Cek apakah data yang di inputkan sudah ada atau belum
    // Jika sudah ada maka system akan mencetak pesan data sudah ada
    // dan menghentikan proses
    if (!isDuplicated.name.empty() || !isDuplicated.description.empty()) {
      // Mencetak pesan data sudah ada
      cout << "Data sudah ada" << endl;

      // Menghentikan proses
      return;
    }

    // Memanggil method insert pada destinationList
    // untuk menambahkan data destinasi pada linked list
    destinationList.push(data);

    // Memanggil method insert pada Destination
    // untuk menambahkan data destinasi pada file csv
    DestinationModel::insert(data);

    // Memanggil method pause pada SYS
    // untuk menjeda layar
    SYS::pause();
  }

  /**
   * @brief Menampilkan detail destinasi
   * 
   * @return void
   */
  void show_destination() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Cek apakah data destinasi kosong atau tidak
    // Jika kosong maka system akan mencetak pesan data masih kosong
    if (destinationList.empty()) {
      // Mencetak pesan data masih kosong
      cout << "Data masih kosong" << endl;

      // Memanggil method pause pada SYS
      // untuk menjeda layar
      SYS::pause();

      // Menghentikan proses
      return;
    }

    // Mencetak judul detail destinasi
    cout << "Detail Destinasi" << endl;

    // Mencetak garis untuk memisahkan antara judul
    cout << "===================" << endl;

    // Memanggil method showNodeData pada destination
    // untuk menampilkan data destinasi
    DestinationStruct data = destinationList.showNodeData(true);

    // Mencetak garis untuk memisahkan antara data
    cout << "===================" << endl;
    cout << "1. Buka Menu Komentar" << endl;
    cout << "2. Kembali" << endl;
    cout << "===================" << endl;

    // Deklarasi variabel choice
    int choice;

    // Meminta input dari user untuk memilih menu
    choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 2!",
      1, 2
    );

    // Jika user memilih menu 1
    // Maka system akan membuka menu komentar
    if (choice == 1) commentController.menu(userData, data.name);

    // Memanggil method pause pada SYS
    // untuk menjeda layar
    SYS::pause();
  }

  /**
   * @brief Menghapus data destinasi
   * 
   * @return void
   */
  void delete_destination() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Cek apakah data destinasi kosong atau tidak
    // Jika kosong maka system akan mencetak pesan data masih kosong
    if (destinationList.empty()) {
      // Mencetak pesan data masih kosong
      cout << "Data masih kosong" << endl;

      // Memanggil method pause pada SYS
      // untuk menjeda layar
      SYS::pause();

      // Menghentikan proses
      return;
    }

    // Mencetak data teratas dari stack
    DestinationStruct data = destinationList.peek();

    // Deklarasi variabel confirmation
    char confirmation;

    // Meminta konfirmasi dari user apakah yakin
    confirmation = InputData::getInputChar(
      "Apakah kamu yakin mau menghapus? (y/N) : ",
      "Pilihan harus berupa karakter! dan diantara y atau N!"
    );

    // Jika konfirmasi tidak y maka menghentikan proses
    if (tolower(confirmation) != 'y') return;

    // Menghapus data teratas dari stack
    destinationList.pop();

    // Memanggil method delete pada Destination untuk menghapus data
    cout << "Data " << data.name << " berhasil dihapus" << endl;

    DestinationModel::remove(data);

    // Memanggil method pause pada SYS
    // untuk menjeda layar
    SYS::pause();
  }

  /**
   * @brief Menampilkan menu destinasi
   * 
   * @param choice
   * @param index 
   * @param page 
   * @param pagination 
   * @param result 
   * 
   * @return bool 
   */
  bool adminMenu(int *choice, int *index, int *page, int *pagination, PaginationStruct result) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    cout << "Menu List Destinasi Wisata" << endl;
    cout << "===================" << endl;
    cout << "1. Detail Destinasi" << endl;
    cout << "2. Tambah Destinasi" << endl;
    cout << "3. Hapus Destinasi" << endl;
    cout << "4. Lanjut ke halaman berikutnya" << endl;
    cout << "5. Kembali ke halaman sebelumnya" << endl;
    cout << "6. Kembali" << endl;
    cout << "===================" << endl;

    *choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 7!",
      1,
      7
    );

    // Jika user memilih menu 7
    if (*choice == 7) return false;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar
    SYS::clear();

    // Melakukan pengecekan pilihan user
    switch (*choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method show_destination
      // untuk menampilkan detail destinasi
      show_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Memanggil method insert_destination
      // untuk menambahkan data destinasi
      insert_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 3
    case 3:
      // Memanggil method delete_destination
      // untuk menghapus data destinasi
      delete_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 4
    case 4:
      // Mengecek apakah data selanjutnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.next) break;

      // Jika tidak kosong maka system akan menambahkan index dan page
      *index += 1;
      *page += *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 5
    case 5:
      // Mengecek apakah data sebelumnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.back) break;

      // Jika tidak kosong maka system akan mengurangi index dan page
      *index -= 1;
      *page -= *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3, 4, 5
    default:
      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan nilai true
    return true;
  }

  /**
   * @brief Menampilkan menu destinasi
   * 
   * @param choice
   * @param index 
   * @param page 
   * @param pagination 
   * @param result 
   * 
   * @return bool 
   */
  bool userMenu(int *choice, int *index, int *page, int *pagination, PaginationStruct result) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    cout << "Menu List Destinasi Wisata" << endl;
    cout << "===================" << endl;
    cout << "1. Detail Destinasi" << endl;
    cout << "2. Lanjut ke halaman berikutnya" << endl;
    cout << "3. Kembali ke halaman sebelumnya" << endl;
    cout << "4. Kembali" << endl;
    cout << "===================" << endl;

    *choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 4!",
      1,
      4
    );

    // Jika user memilih menu 4
    if (*choice == 4) return false;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar
    SYS::clear();

    // Melakukan pengecekan pilihan user
    switch (*choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method show_destination
      // untuk menampilkan detail destinasi
      show_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Mengecek apakah data selanjutnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.next) break;

      // Jika tidak kosong maka system akan menambahkan index dan page
      *index += 1;
      *page += *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 3
    case 3:
      // Mengecek apakah data sebelumnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.back) break;

      // Jika tidak kosong maka system akan mengurangi index dan page
      *index -= 1;
      *page -= *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3
    default:
      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan nilai true
    return true;
  }

public:
  /**
   * @brief Inisialisasi data destinasi
   * 
   * @return void
   */
  void init() {
    // Mengecek apakah file destination_data.csv tidak ada
    // Jika tidak ada maka system akan membuat file destination_data.csv
    // dan menambahkan data destinasi secara default
    if (!FileStorage::Exists(Path::getPath() + DESTINATION_DATA_PATH)) {
      // Membuat file destination_data.csv
      FileStorage::Create(Path::getPath() + DESTINATION_DATA_PATH);

      // Menambahkan data destinasi secara default
      DestinationModel::insert(DestinationStruct{"Taman Nasional Bromo Tengger Semeru", "Taman Nasional Bromo Tengger Semeru adalah sebuah kawasan konservasi alam di Jawa Timur", "Probolinggo Jawa Timur", "24 Jam", 1, 50000, Nature});
      DestinationModel::insert(DestinationStruct{"Candi Borobudur", "Candi Borobudur adalah sebuah candi Buddha yang terletak di Magelang Jawa Tengah", "Magelang Jawa Tengah", "06.00 - 17.00", 1, 50000, History});
    }

    // Mengecek apakah data destinasi kosong pada stack
    // Jika kosong maka system akan membaca data dari file csv
    if (destinationList.empty()) {
      // Membaca data dari file csv
      std::vector<DestinationStruct> data = DestinationModel::read();

      // Melakukan perulangan untuk menambahkan data ke dalam stack
      // berdasarkan data yang sudah di baca dari file csv
      for (int i = 0; i < data.size(); i++) {
        // Menambahkan data ke dalam stack
        destinationList.push(data[i]);
      }
    }
  }

  /**
   * @brief Menampilkan menu destinasi
   * 
   * @param user 
   * @param comment
   * 
   * @return void
   */
  void menu(UserController user, CommentController comment) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mengisi data user dari class UserController
    userData = user;

    // Mengisi data comment dari class CommentController
    commentController = comment;

    // Deklarasi variabel isRunning, choice, index, page, pagination
    bool isRunning = true;
    int choice, index = 1, page = 5, pagination = 5;

    do {
      // Memanggil method clear pada SYS
      // untuk membersihkan layar
      SYS::clear();

      // Mencetak data dari pagination
      cout << "Menampilkan list dari " << page - pagination << " - " << page << " data" << endl;

      // Memanggil method showAllNodes pada destination
      // untuk menampilkan semua data destinasi pada linked list
      PaginationStruct result = destinationList.showAllNodes(index, pagination, false);

      // Mencetak garis untuk memisahkan antara data
      cout << endl;

      // Melakukan pengecekan apakah user adalah admin atau tidak
      // Jika user adalah admin maka system akan menampilkan menu admin
      // Jika user bukan admin maka system akan menampilkan menu user
      if (userData.isUserAdmin()) isRunning = adminMenu(&choice, &index, &page, &pagination, result);
      else isRunning = userMenu(&choice, &index, &page, &pagination, result);
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }
};

#endif // DESTINATION_CONTROLLER_HPP
