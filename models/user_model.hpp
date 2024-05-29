#pragma once

// Path file data user
#ifndef USER_DATA_PATH
#define USER_DATA_PATH "/data/user_data.csv"
#endif

#ifndef USER_MODEL_HPP
#define USER_MODEL_HPP

#include <string>

#include "../helpers/path.hpp"
#include "../enums/role_enum.hpp"
#include "../structs/user_struct.hpp"
#include "../handlers/data_handler.hpp"

/**
 * Deklarasi namespace UserModel
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses CRUD data user
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace UserModel {
  /**
   * @brief Membaca data user dari file
   * 
   * @return std::vector<UserStruct> 
   */
  std::vector<UserStruct> read() {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + USER_DATA_PATH);

    // Jika data kosong maka kembalikan data kosong
    if (fileData.empty()) return {};

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<UserStruct> data;

    // Inisialisasi variabel row untuk menyimpan data yang sudah di baca
    std::vector<std::string> row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Melakukan perulangan untuk membaca data per baris
    while (std::getline(ss, line, '\n')) {
      // Inisialisasi variabel word  untuk menyimpan data yang sudah di split
      std::string word;

      // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
      stringstream s(line);

      // Melakukan perulangan untuk membaca data per kata
      while (std::getline(s, word, ',')) {
        // Menyimpan data yang sudah di split ke dalam row
        row.push_back(word);
      }

      // Inisialisasi struct UserStruct
      UserStruct user;

      // Mengisi data struct DestinationStruct dengan data dari file
      user.username = row[0];
      user.password = row[1];
      user.role = static_cast<Role>(std::stoi(row[2]));

      // Menyimpan data struct UserStruct ke dalam data
      data.push_back(user);

      // Mengosongkan row
      row.clear();
    }

    // Mengembalikan data yang sudah di baca
    return data;
  }

  /**
   * @brief Menambahkan data user ke dalam file
   * 
   * @param data UserStruct
   * 
   * @return void
   */
  void insert(const UserStruct &data) {
    // Menyimpan data ke dalam file dengan menggunakan DataHandler::insert
    DataHandler::insert(USER_DATA_PATH, data.username + "," + data.password + "," + std::to_string(data.role));
  }
}

#endif // USER_MODEL_HPP
