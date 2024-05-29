#pragma once

// Path file data destinasi wisata
#ifndef COMMENT_DATA_PATH
#define COMMENT_DATA_PATH "/data/comment_data.csv"
#endif

#ifndef COMMENT_MODEL_HPP
#define COMMENT_MODEL_HPP

#include <string>

#include "../helpers/path.hpp"
#include "../handlers/data_handler.hpp"
#include "../structs/comment_struct.hpp"

/**
 * Deklarasi namespace CommentModel
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses CRUD data ulasan dari destinasi wisata
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace CommentModel {
  /**
   * @brief Membaca data ulasan dari file
   * 
   * @return std::vector<CommentStruct> 
   */
  std::vector<CommentStruct> read() {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + COMMENT_DATA_PATH);

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<CommentStruct> data;

    // Inisialisasi variabel row untuk menyimpan data yang sudah di baca
    std::vector<std::string> row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Melakukan perulangan untuk membaca data per baris
    while (std::getline(ss, line, '\n')) {
      // Inisialisasi variabel word untuk menyimpan data yang sudah di split
      std::string word;

      // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
      stringstream s(line);

      // Melakukan perulangan untuk membaca data per kata
      while (std::getline(s, word, ',')) {
        // Menyimpan data yang sudah di split ke dalam row
        row.push_back(word);
      }

      CommentStruct comment;

      comment.destination_name = row[0];
      comment.username = row[1];
      comment.comment = row[2];
      comment.rating = std::stoi(row[3]);

      // Menyimpan data struct CommentStruct ke dalam data
      data.push_back(comment);

      // Mengosongkan row
      row.clear();
    }

    // Mengembalikan data yang sudah di baca
    return data;
  }

  /**
   * @brief Membaca data ulasan dari file berdasarkan username
   * 
   * @return std::vector<CommentStruct> 
   */
  std::vector<CommentStruct> readByUsername(const std::string &username) {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<CommentStruct> result, data = read();

    // Melakukan perulangan untuk membaca data per baris
    for (int i = 0; i < data.size(); i++) {
      // Cek apakah usernama yang dicari sama dengan nama pada data
      // Jika tidak sama maka lanjut ke data selanjutnya
      if (data[i].username != username) continue;

      // Menyimpan data yang sudah di temukan ke dalam variabel result
      result.push_back(data[i]);
    }

    // Mengembalikan data yang sudah di baca
    return result;
  }

  /**
   * @brief Menambahkan data ulasan ke dalam file
   * 
   * @param data CommentStruct
   */
  void insert(const CommentStruct &data) {
    std::string dataString = data.destination_name + "," + data.username + "," + data.comment + "," + std::to_string(data.rating);

    // Menyimpan data ke dalam file dengan menggunakan DataHandler::insert
    DataHandler::insert(COMMENT_DATA_PATH, dataString);
  }

  /**
   * @brief Mencari data ulasan berdasarkan usernama
   * 
   * @param username string
   * @param destinationName string
   * 
   * @return CommentStruct 
   */
  CommentStruct findByUsernameAndDestinationName(const std::string &username, const std::string &destinationName) {
    // Membaca data dari file dengan menggunakan CommentModel::readByUsername
    const std::vector<CommentStruct> data = readByUsername(username);

    // Inisialisasi struct CommentStruct
    CommentStruct destination;

    // Melakukan perulangan untuk mencari data berdasarkan nama
    for (int i = 0; i < data.size(); i++) {
      // Cek apakah usernama yang dicari sama dengan nama pada data
      // Jika tidak sama maka lanjut ke data selanjutnya
      if (data[i].destination_name != destinationName) continue;

      // Jika sama maka simpan data tersebut ke dalam variabel destination
      destination = data[i];

      // Menghentikan perulangan
      break;
    }

    // Mengembalikan data yang sudah di temukan
    return destination;
  }

  /**
   * @brief Mengubah data yang sudah ada di dalam file
   * 
   * @param filename string
   * @param data string
   * @param newData string
   * 
   * @return void
   */
  void update(const CommentStruct &data, const CommentStruct &newData) {
    // Merangkap data baru ke dalam string
    std::string newDataString = newData.destination_name + "," + newData.username + "," + newData.comment + "," + std::to_string(newData.rating);

    // Merangkap data lama ke dalam string
    std::string dataString = data.destination_name + "," + data.username + "," + data.comment + "," + std::to_string(data.rating);

    // Mengubah data yang sudah ada di dalam file dengan menggunakan DataHandler::update
    DataHandler::update(COMMENT_DATA_PATH, dataString, newDataString);
  }

  /**
   * @brief Menghapus data yang sudah ada di dalam file
   * 
   * @param data string
   * 
   * @return void
   */
  void remove(const CommentStruct &data) {
    // Merangkap data ke dalam string
    std::string dataString = data.destination_name + "," + data.username + "," + data.comment + "," + std::to_string(data.rating);

    // Menghapus data yang sudah ada di dalam file dengan menggunakan DataHandler::remove
    DataHandler::remove(COMMENT_DATA_PATH, dataString);
  }
}

#endif // COMMENT_MODEL_HPP
