#pragma once

#ifndef FILE_STORAGE_HELPER_HPP
#define FILE_STORAGE_HELPER_HPP

#include <string>
#include <fstream>

/**
 * Deklarasi namespace FileStorage
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses CRUD file seperti membuat, membaca,
 * menulis, dan menghapus file
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace FileStorage {
  /**
   * Method untuk membuat file
   *
   * @param filename nama file yang akan dibaca
   */
  static void Create(const std::string &filename) {
    // Menggunakan std::ofstream untuk membuat file
    using std::ofstream; // Import library ofstream

    // Membuka file dengan nama filename
    ofstream file(filename);

    // Menutup file setelah selesai membuat
    file.close();
  }

  /**
   * Method untuk membaca file
   *
   * @param filename nama file yang akan dibaca
   * 
   * @return string data yang dibaca dari file
   */
  static std::string Read(const std::string &filename) {
    // Menggunakan std::ifstream untuk membaca file
    using std::ifstream; // Import library ifstream

    // Inisialisasi variable line dan data
    // line = untuk menyimpan data yang di baca
    // data = untuk menyimpan data yang sudah di baca
    std::string line, data = "";

    // Membuka file dengan nama filename
    ifstream file(filename);

    // Jika file tidak ditemukan maka kembalikan data kosong
    if (!file || !file.is_open()) {
      // Menutup file setelah selesai membaca
      file.close();

      // Mengembalikan data kosong
      return data;
    }

    // Looping hingga data yang di baca tidak kosong
    while (getline(file, line)) {
      data += line + "\n";
    }

    // Menutup file setelah selesai membaca
    file.close();

    // Mengembalikan data yang sudah di baca
    return data;
  }

  /**
   * Method untuk menulis file
   *
   * @param filename nama file yang akan ditulis
   * @param data data yang akan ditulis ke dalam file
   * 
   * @return bool status apakah data berhasil ditulis atau tidak
   */
  static bool Write(const std::string &filename, const std::string &data) {
    // Menggunakan std::ofstream untuk menulis file
    using std::ofstream; // Import library ofstream

    // Membuka file dengan nama filename
    ofstream file(filename);

    // Jika file tidak ditemukan maka kembalikan false
    if (!file || !file.is_open()) {
      // Menutup file setelah selesai menulis
      file.close();

      // Mengembalikan status false
      return false;
    }

    // Menulis data ke dalam file
    file << data;

    // Menutup file setelah selesai menulis
    file.close();

    // Mengembalikan status true
    return true;
  }

  /**
   * Method untuk menghapus file
   *
   * @param filename nama file yang akan dihapus
   * 
   * @return bool status apakah file berhasil dihapus atau tidak
   */
  static bool Delete(const std::string &filename) {
    // Menggunakan std::remove untuk menghapus file
    return std::remove(filename.c_str()) == 0;
  }

  /**
   * Method untuk mengecek apakah file ada atau tidak
   *
   * @param filename nama file yang akan dicek
   * 
   * @return bool status apakah file ada atau tidak
   */
  static bool Exists(const std::string &filename) {
    // Menggunakan std::ifstream untuk membaca file
    using std::ifstream; // Import library ifstream

    // Membuka file dengan nama filename
    ifstream file(filename);

    // Jika file tidak ditemukan maka kembalikan false
    if (!file || !file.is_open()) {
      // Menutup file setelah selesai membaca
      file.close();

      // Mengembalikan status false
      return false;
    }

    // Menutup file setelah selesai membaca
    file.close();

    // Mengembalikan nilai true
    return true;
  }
};

#endif // FILE_STORAGE_HELPER_HPP
