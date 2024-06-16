#pragma once

#ifndef COMMENT_CONTROLLER_HPP
#define COMMENT_CONTROLLER_HPP

#include <iostream>

#include "user_controller.hpp"
#include "../helpers/path.hpp"
#include "../helpers/system.hpp"
#include "../helpers/input_data.hpp"
#include "../handlers/hash_table.hpp"
#include "../helpers/file_storage.hpp"
#include "../models/comment_model.hpp"
#include "../structs/comment_struct.hpp"
#include "../structs/pagination_struct.hpp"

/**
 * Deklarasi class CommentController
 *
 * Class list ini kita gunakan untuk melakukan
 * contructor untuk menghandle data ulasan
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
class CommentController {
private:
  // Inisialisasi variabel destinationName untuk menyimpan nama destinasi
  std::string destinationName;

  // Inisialisasi variabel userData untuk menyimpan data user
  // dari class UserController
  UserController userData;

  // Inisialisasi variabel hashTable untuk menyimpan data ulasan
  // dari class HashTable dengan tipe data CommentStruct
  HashTable<CommentStruct> commentList;

  /**
   * @brief Menampilkan semua ulasan
   * 
   * @return void
   */
  void showAllComment(int choice = 0, int index = 1, int page = 5, int pagination = 5) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Menampilkan data ulasan
    cout << "Ulasan Destinasi Wisata" << endl;
    cout << "===================" << endl;

    // Mencetak data dari pagination
    cout << "Menampilkan list dari " << page - pagination << " - " << page << " data" << endl;

    // Memanggil method showAll pada destination
    // untuk menampilkan semua data ulasan pada queue
    PaginationStruct result = commentList.showAll(index, pagination, false, destinationName);

    // Mencetak garis untuk memisahkan antara data
    cout << endl;

    cout << "===================" << endl;
    cout << "1. Lanjut ke halaman berikutnya" << endl;
    cout << "2. Kembali ke halaman sebelumnya" << endl;
    cout << "3. Kembali" << endl;
    cout << "===================" << endl;

    // Meminta input dari user
    choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 3!",
      1, 3
    );

    // Jika user memilih menu 3
    // maka akan keluar dari menu
    if (choice == 3) return;

    // Melakukan pengecekan pilihan user
    switch (choice) {
    // Jika user memilih menu 1
    case 1:
      // Mengecek apakah data selanjutnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.next) break;

      // Jika tidak kosong maka system akan menambahkan index dan page
      index += 1;
      page += pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Mengecek apakah data sebelumnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.back) break;

      // Jika tidak kosong maka system akan mengurangi index dan page
      index -= 1;
      page -= pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3
    default:
      // Menghentikan pengecekan
      break;
    }

    // Memanggil method showAllComment
    showAllComment(choice, index, page, pagination);
  }

  /**
   * @brief Menampilkan ulasan user
   * 
   * @return void
   */
  void showMyComment(int choice = 0, int index = 1, int page = 5, int pagination = 5) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Menampilkan data ulasan
    cout << "Ulasan Saya" << endl;
    cout << "===================" << endl;

    // Memanggil method showByUsername pada destination
    // untuk menampilkan data ulasan user
    commentList.showByUsername(destinationName, userData.getUsername());

    cout << "===================" << endl;
    cout << "1. Kembali" << endl;
    cout << "===================" << endl;

    // Meminta input dari user
    choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 3!",
      1, 1
    );

    // Jika user memilih menu 1
    // maka akan keluar dari menu
    if (choice == 1) return;
  }

  /**
   * @brief Menambahkan ulasan
   * 
   * @return void
   */
  void addComment() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Inisialisasi variabel comment untuk menyimpan data ulasan
    CommentStruct comment, isDuplicated = CommentModel::findByUsernameAndDestinationName(userData.getUsername(), destinationName);

    if (!isDuplicated.username.empty() && !isDuplicated.destination_name.empty()) {
      cout << "Anda sudah memberikan ulasan pada destinasi ini!" << endl;
      cout << "===================" << endl;
      cout << "Nama Destinasi : " << isDuplicated.destination_name << endl;
      cout << "Komentar : " << isDuplicated.comment << endl;

      switch (isDuplicated.rating) {
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

      cout << "===================" << endl;

      return;
    }

    // Meminta input dari user
    comment.destination_name = destinationName;
    comment.username = userData.getUsername();

    comment.comment = InputData::getInputLine(
      "Ulasan : ",
      "Ulasan tidak boleh kosong!"
    );

    comment.rating = InputData::getInputIntRange(
      "Rating : ",
      "Rating harus berupa angka! dan diantara 1 sampai 5!",
      1, 5
    );

    // Menambahkan data ulasan ke dalam queue list
    commentList.insert(comment);

    // Menambahkan data ulasan ke dalam file csv
    CommentModel::insert(comment);
  }

  /**
   * @brief Menghapus ulasan
   * 
   * @return void
   */
  void deleteComment() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Inisialisasi variabel comment untuk menyimpan data ulasan
    CommentStruct comment;

    // Meminta input dari user
    comment.destination_name = destinationName;
    comment.username = userData.getUsername();

    // Mencari data ulasan berdasarkan username dan nama destinasi
    CommentStruct isExist = CommentModel::findByUsernameAndDestinationName(comment.username, comment.destination_name);

    // Jika data ulasan tidak ditemukan
    if (isExist.username.empty() || isExist.destination_name.empty()) {
      // Menampilkan pesan error
      cout << "Ulasan tidak ditemukan!" << endl;

      // Memanggil method pause pada SYS
      // untuk menjeda layar terminal
      SYS::pause();

      // Menghentikan proses
      return;
    }

    // Menampilkan data ulasan
    cout << "Ulasan Destinasi Wisata" << endl;
    cout << "===================" << endl;
    cout << "Nama Destinasi : " << isExist.destination_name << endl;
    cout << "Komentar : " << isExist.comment << endl;

    // Melakukan pengecekan rating ulasan
    switch (isExist.rating) {
    // Jika rating 1
    case 1:
      // Menampilkan rating sangat buruk
      cout << "Rating : 1 (Sangat Buruk)" << endl;

      // Menghentikan pengecekan
      break;
    // Jika rating 2
    case 2:
      // Menampilkan rating buruk
      cout << "Rating : 2 (Buruk)" << endl;

      // Menghentikan pengecekan
      break;
    // Jika rating 3
    case 3:
      // Menampilkan rating cukup
      cout << "Rating : 3 (Cukup)" << endl;

      // Menghentikan pengecekan
      break;
    // Jika rating 4
    case 4:
      // Menampilkan rating baik
      cout << "Rating : 4 (Baik)" << endl;

      // Menghentikan pengecekan
      break;
    // Jika rating 5
    case 5:
      // Menampilkan rating sangat baik
      cout << "Rating : 5 (Sangat Baik)" << endl;

      // Menghentikan pengecekan
      break;
    }

    // Menampilkan garis untuk memisahkan antara data
    cout << "===================" << endl;

    // Meminta konfirmasi dari user
    char confirm = InputData::getInputChar(
      "Apakah anda yakin ingin menghapus ulasan ini? (y/n) : ",
      "Pilihan harus berupa y atau n!"
    );

    // Jika user memilih y maka akan menghapus data ulasan
    if (confirm == 'y') {
      // Menghapus data ulasan dari queue list
      commentList.remove(isExist);

      // Menghapus data ulasan dari file csv
      CommentModel::remove(isExist);
    }
  }

  /**
   * @brief Menampilkan semua ulasan
   * 
   * @return void
   */
  void showMainMenu() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Inisialisasi variabel choice untuk menyimpan pilihan user
    int choice;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Menampilkan menu utama
    cout << "Menu Ulasan Destinasi Wisata" << endl;
    cout << "===================" << endl;
    cout << "1. Lihat Ulasan" << endl;
    cout << "2. Lihat Ulasan Saya" << endl;
    cout << "3. Tambah Ulasan" << endl;
    cout << "4. Hapus Ulasan" << endl;
    cout << "5. Kembali" << endl;
    cout << "===================" << endl;

    // Meminta input dari user
    choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 4!",
      1, 5
    );

    // Jika user memilih menu 5
    // maka akan keluar dari menu
    if (choice == 5) return;

    // Melakukan pengecekan pilihan user
    switch (choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method showAllComment
      // untuk menampilkan semua data ulasan
      showAllComment();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Cek apakah user sudah login
      // Jika belum maka system akan menghentikan proses
      if (!userData.isAlreadyLogin()) {
        // Menampilkan pesan error
        cout << "Anda belum login!" << endl;

        // Menghentikan pengecekan
        break;
      }

      // Memanggil method showMyComment
      // untuk menampilkan data ulasan user
      showMyComment();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 3
    case 3:
      // Cek apakah user sudah login
      // Jika belum maka system akan menghentikan proses
      if (!userData.isAlreadyLogin()) {
        // Menampilkan pesan error
        cout << "Anda belum login!" << endl;

        // Menghentikan pengecekan
        break;
      }

      // Memanggil method addComment
      // untuk menambahkan data ulasan
      addComment();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 4
    case 4:
      // Cek apakah user sudah login
      // Jika belum maka system akan menghentikan proses
      if (!userData.isAlreadyLogin()) {
        // Menampilkan pesan error
        cout << "Anda belum login!" << endl;

        // Menghentikan pengecekan
        break;
      }

      // Memanggil method deleteComment
      // untuk menghapus data ulasan
      deleteComment();

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3, 4, 5
    default:
      // Menghentikan pengecekan
      break;
    }

    // Memanggil method pause pada SYS
    // untuk menjeda layar terminal
    SYS::pause();

    // Memanggil method showMainMenu
    showMainMenu();
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
    if (!FileStorage::Exists(Path::getPath() + COMMENT_DATA_PATH)) {
      // Membuat file destination_data.csv
      FileStorage::Create(Path::getPath() + COMMENT_DATA_PATH);

      // Menambahkan data destinasi secara default
      CommentModel::insert(CommentStruct{"Taman Nasional Bromo Tengger Semeru", "user", "View gunung nya bagus, cocok untuk orang yang suka dengan view gunung", 5});
      CommentModel::insert(CommentStruct{"Candi Borobudur", "user", "Komentar 2", 3});
    }

    // Mengcek apakah data ulasan kosong pada queue list
    // Jika kosong maka system akan menambahkan data ulasan
    if (commentList.empty()) {
      // Membaca data ulasan dari file csv
      std::vector<CommentStruct> comments = CommentModel::read();

      // Melakukan perulangan untuk menambahkan data ulasan ke dalam queue list
      // berdasarkan data yang sudah di baca
      for (CommentStruct comment : comments) {
        commentList.insert(comment);
      }
    }
  }

  /**
   * @brief Menampilkan menu ulasan
   * 
   * @param user UserController
   * @param destination string
   * 
   * @return void
   */
  void menu(UserController user, std::string destination) {
    // Mengisi data user dari class UserController
    userData = user;

    // Mengisi nama destinasi
    destinationName = destination;

    // Memanggil method showMainMenu
    showMainMenu();
  }
};

#endif // COMMENT_CONTROLLER_HPP
