#pragma once

#ifndef INPUT_DATA_HELPER_HPP
#define INPUT_DATA_HELPER_HPP

#include <string>
#include <sstream>
#include <iostream>

/**
 * Deklarasi namespace InputData
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses input data dari user sehingga dapat
 * mencegah terjadinya error saat input data
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace InputData {
  /**
   * Method untuk mengambil input data dari user
   *
   * @param message pesan yang akan ditampilkan
   * 
   * @return string data yang diinputkan oleh user
   */
  static std::string getInput(const std::string &message, const std::string &fail) {
    // Menggunakan std::cout untuk menampilkan pesan
    using std::cout; // Import library cout
    // Menggunakan std::cin untuk mengambil input dari user
    using std::cin; // Import library cin
    // Menggunakan std::string untuk menyimpan data yang diinputkan
    using std::string; // Import library string

    // Melakukan perulangan hingga input tidak kosong
    while (true) {
      // Menampilkan pesan
      cout << message;

      // Inisialisasi variabel input untuk menyimpan data yang diinputkan
      string input;

      // Cek jika pada input sebelumnya terdapat data yang tersisa
      if (cin.peek() == '\n') {
        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');
      }

      // Mengambil input dari user
      cin >> input;

      // Cek jika user menginputkan data beserta spasi
      if (cin.peek() != '\n') {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      // Jika input tidak kosong maka kembalikan input
      if (!input.empty()) return input;

      // Menampilkan pesan error
      cout << fail << std::endl;
    }
  }

  /**
   * Method untuk mengambil input line data dari user
   *
   * @param message pesan yang akan ditampilkan
   * 
   * @return string data yang diinputkan oleh user
   */
  static std::string getInputLine(const std::string &message, const std::string &fail) {
    // Menggunakan std::cout untuk menampilkan pesan
    using std::cout; // Import library cout
    // Menggunakan std::cin untuk mengambil input dari user
    using std::cin; // Import library cin
    // Menggunakan std::string untuk menyimpan data yang diinputkan
    using std::string; // Import library string

    // Melakukan perulangan hingga input tidak kosong
    while (true) {
      // Menampilkan pesan
      cout << message;

      // Inisialisasi variabel input untuk menyimpan data yang diinputkan
      string input;

      // Cek jika pada input sebelumnya terdapat data yang tersisa
      if (cin.peek() == '\n') {
        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');
      }

      // Mengambil input dari user
      std::getline(cin, input);

      // Jika input tidak kosong maka kembalikan input
      if (!input.empty()) return input;

      // Menampilkan pesan error
      cout << fail << std::endl;
    }
  }

  /**
   * Method untuk mengambil input data integer dari user
   *
   * @param message pesan yang akan ditampilkan
   * 
   * @return int data yang diinputkan oleh user
   */
  static int getInputInt(const std::string &message, const std::string &fail) {
    // Menggunakan std::cout untuk menampilkan pesan
    using std::cout; // Import library cout
    // Menggunakan std::cin untuk mengambil input dari user
    using std::cin; // Import library cin
    // Menggunakan std::string untuk menyimpan data yang diinputkan
    using std::string; // Import library string
    // Menggunakan std::istringstream untuk mengkonversi string ke integer
    using std::istringstream; // Import library istringstream

    // Melakukan perulangan hingga input sesuai dengan tipe data integer
    while (true) {
      // Menampilkan pesan
      cout << message;

      // Inisialisasi variabel input untuk menyimpan data yang diinputkan
      string input;

      // Cek jika pada input sebelumnya terdapat data yang tersisa
      if (cin.peek() == '\n') {
        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');
      }

      // Mengambil input dari user
      cin >> input;

      // Cek jika user menginputkan data beserta spasi
      if (cin.peek() != '\n') {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      // Jika input kosong maka tambahkan pesan error
      if (input.empty()) {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      // Inisialisasi variabel ss untuk menyimpan data string
      istringstream ss(input);

      // Inisialisasi variabel result untuk menyimpan data yang sudah di konversi
      int result;

      // Mengkonversi string ke integer
      ss >> result;

      if (!ss.eof()) {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      // Mengembalikan nilai result
      return result;
    }
  }

  /**
   * Method untuk mengambil input data integer diantara min dan max
   *
   * @param message pesan yang akan ditampilkan
   * 
   * @return int data yang diinputkan oleh user
   */
  static int getInputIntRange(const std::string &message, const std::string &fail, int min, int max) {
    // Melakukan perulangan hingga input sesuai dengan range
    while (true) {
      // Mengambil input dari user
      int input = getInputInt(message, fail);

      // Jika input lebih dari min dan kurang dari max maka kembalikan input
      if (input >= min && input <= max) return input;

      // Menampilkan pesan error
      std::cout << fail << std::endl;
    }
  }

  /**
   * Method untuk mengambil input data char dari user
   *
   * @param message pesan yang akan ditampilkan
   * 
   * @return char data yang diinputkan oleh user
   */
  static char getInputChar(const std::string &message, const std::string &fail) {
    // Menggunakan std::cout untuk menampilkan pesan
    using std::cout; // Import library cout
    // Menggunakan std::cin untuk mengambil input dari user
    using std::cin; // Import library cin
    // Menggunakan std::string untuk menyimpan data yang diinputkan
    using std::string; // Import library string

    // Melakukan perulangan hingga input tidak kosong
    while (true) {
      // Menampilkan pesan
      cout << message;

      // Inisialisasi variabel input untuk menyimpan data yang diinputkan
      string input;

      // Cek jika pada input sebelumnya terdapat data yang tersisa
      if (cin.peek() == '\n') {
        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');
      }

      // Mengambil input dari user
      cin >> input;

      // Cek jika user menginputkan data beserta spasi
      if (cin.peek() != '\n') {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Membersihkan input buffer
        cin.clear();
        cin.ignore(10000, '\n');

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      // Jika input kosong maka lanjutkan ke perulangan berikutnya
      if (input.empty()) {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      if (input.length() > 1) {
        // Menampilkan pesan error
        cout << fail << std::endl;

        // Melanjutkan ke perulangan berikutnya
        continue;
      }

      // Mengembalikan nilai input
      return input[0];
    }
  }
}

#endif // INPUT_DATA_HELPER_HPP
