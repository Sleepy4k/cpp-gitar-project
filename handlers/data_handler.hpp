#pragma once

#ifndef DATA_HANDLER_HPP
#define DATA_HANDLER_HPP

#include <string>
#include <vector>
#include <sstream>

#include "../helpers/path.hpp"
#include "../helpers/file_storage.hpp"

/**
 * Deklarasi namespace DataHandler
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses CRUD data yang berhubungan dengan file
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace DataHandler {
  /**
   * @brief Membaca data dari file
   * 
   * @param filename string
   * 
   * @return std::vector<std::string>
   */
  std::vector<std::string> read(const std::string &filename) {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + filename);

    // Jika data kosong maka kembalikan data kosong
    if (fileData.empty()) return {};

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variabel data dan row untuk menyimpan data yang sudah di baca
    std::vector<std::string> data, row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Melakukan perulangan untuk membaca data per baris
    while (std::getline(ss, line, '\n')) {
      // Inisialisasi variabel word dan dummy untuk menyimpan data yang sudah di split
      std::string word, dummy;

      // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
      stringstream s(line);

      // Melakukan perulangan untuk membaca data per kata
      while (std::getline(s, word, ',')) {
        // Menyimpan data yang sudah di split ke dalam row
        row.push_back(word);
      }

      // Menghitung panjang dari row
      int length = row.size();

      // Melakukan perulangan untuk menggabungkan data yang sudah di split
      for (int i = 0; i < length; i++) {
        // Menyimpan data yang sudah di gabung ke dalam dummy
        (i == length - 1) ? dummy += row[i] : dummy += row[i] + " ";
      }

      // Menyimpan data yang sudah di gabung ke dalam data
      data.push_back(dummy);

      // Mengosongkan row
      row.clear();
    }

    // Mengembalikan data yang sudah di baca
    return data;
  }

  /**
   * @brief Menambahkan data ke dalam file
   * 
   * @param filename string
   * @param data string
   */
  void insert(const std::string &filename, const std::string &data) {
    // Menggunakan std::ofstream untuk menulis data ke dalam file
    using std::fstream; // Import library ofstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Mengecek apakah file sudah ada atau belum
    // Jika file sudah ada maka tambahkan data ke dalam file
    if (FileStorage::Exists(Path::getPath() + filename)) {
      // Membaca data dari file dengan menggunakan FileStorage::Read
      std::string fileData = FileStorage::Read(Path::getPath() + filename);

      // Cek apakah data kosong atau tidak
      // Jika data kosong maka tambahkan data ke dalam file
      if (fileData.empty()) {
        // Menulis data ke dalam file dengan menggunakan FileStorage::Write
        FileStorage::Write(Path::getPath() + filename, data);

        // Menghentikan proses
        return;
      }

      // Menambahkan data ke dalam file
      fileData += data;

      // Menulis data ke dalam file dengan menggunakan FileStorage::Write
      FileStorage::Write(Path::getPath() + filename, fileData);
    } else {
      // Membuat file baru jika file belum ada
      FileStorage::Create(Path::getPath() + filename);

      // Menulis data ke dalam file dengan menggunakan FileStorage::Write
      FileStorage::Write(Path::getPath() + filename, data);
    }
  }

  /**
   * @brief Mencari data di dalam file
   * 
   * @param filename string
   * @param data string
   * 
   * @return std::string
   */
  std::string find(const std::string &filename, const std::string &data) {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + filename);

    // Jika data kosong maka kembalikan data kosong
    if (fileData.empty()) return "";

    // Inisialisasi variabel line dan result untuk menyimpan data yang di baca
    std::string line, result;

    // Inisialisasi variabel row untuk menyimpan data yang sudah di split
    std::vector<std::string> row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Melakukan perulangan untuk membaca data per baris
    while (std::getline(ss, line, '\n')) {
      // Inisialisasi variabel word dan dummy untuk menyimpan data yang sudah di split
      std::string word, dummy;

      // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
      stringstream s(line);

      // Melakukan perulangan untuk membaca data per kata
      while (std::getline(s, word, ',')) {
        // Menyimpan data yang sudah di split ke dalam row
        row.push_back(word);
      }

      // Menghitung panjang dari row
      int length = row.size();

      // Melakukan perulangan untuk menggabungkan data yang sudah di split
      for (int i = 0; i < length; i++) {
        // Menyimpan data yang sudah di gabung ke dalam dummy
        (i == length - 1) ? dummy += row[i] : dummy += row[i] + " ";
      }

      // Membandingkan data yang sudah di gabung dengan data yang dicari
      // Jika data yang dicari ditemukan maka simpan data tersebut ke dalam result
      if (dummy.find(data) != std::string::npos) {
        // Menyimpan data yang sudah di temukan ke dalam result
        result = dummy;

        // Menghentikan perulangan
        break;
      }

      // Mengosongkan row
      row.clear();
    }

    // Mengembalikan data yang sudah di temukan
    return result;
  }

  /**
   * @brief Mengubah data yang sudah ada di dalam file
   * 
   * @param filename string
   * @param data string
   * @param newData string
   */
  void update(const std::string &filename, const std::string &data, const std::string &newData) {
    // Menggunakan std::ofstream untuk menulis data ke dalam file
    using std::fstream; // Import library ofstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Mengecek apakah file sudah ada atau belum
    // Jika file sudah ada maka tambahkan data ke dalam file
    if (FileStorage::Exists(Path::getPath() + filename)) {
      // Membaca data dari file dengan menggunakan FileStorage::Read
      std::string fileData = FileStorage::Read(Path::getPath() + filename);

      // Cek apakah data kosong atau tidak
      // Jika data kosong maka hentikan proses
      if (fileData.empty()) return;

      // Mencari posisi data yang akan diubah
      size_t pos = fileData.find(data);

      // Cek apakah data yang akan diubah ditemukan atau tidak
      // Jika data ditemukan maka ubah data tersebut
      if (pos != std::string::npos) {
        // Mengubah data yang sudah ada dengan data yang baru
        fileData.replace(pos, data.length(), newData);

        // Menulis data ke dalam file dengan menggunakan FileStorage::Write
        FileStorage::Write(Path::getPath() + filename, fileData);
      }
    }
  }

  /**
   * @brief Menghapus data yang sudah ada di dalam file
   * 
   * @param filename string
   * @param data string
   */
  void remove(const std::string &filename, const std::string &data) {
    // Menggunakan std::ofstream untuk menulis data ke dalam file
    using std::fstream; // Import library ofstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Mengecek apakah file sudah ada atau belum
    if (FileStorage::Exists(Path::getPath() + filename)) {
      // Membaca data dari file dengan menggunakan FileStorage::Read
      std::string fileData = FileStorage::Read(Path::getPath() + filename);

      // Cek apakah data kosong atau tidak
      // Jika data kosong maka hentikan proses
      if (fileData.empty()) return;

      // Mencari posisi data yang akan dihapus
      size_t pos = fileData.find(data);

      // Cek apakah data yang akan dihapus ditemukan atau tidak
      // Jika data ditemukan maka hapus data tersebut
      if (pos != std::string::npos) {
        // Menghapus data yang sudah ada
        fileData.erase(pos, data.length());

        // Menulis data ke dalam file dengan menggunakan FileStorage::Write
        FileStorage::Write(Path::getPath() + filename, fileData);
      }
    }
  }
}

#endif // DATA_HANDLER_HPP
