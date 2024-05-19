#pragma once

#ifndef PARSE_HELPER_HPP
#define PARSE_HELPER_HPP

#include <string>

/**
 * Deklarasi namespace Parse
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses parsing data
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace Parse {
  /**
   * @brief Mengkonversi nilai integer menjadi string dengan format mata uang
   * 
   * @param value nilai integer yang akan di konversi
   * 
   * @return string
   */
  std::string intToCurrencyFormat(int value) {
    // Mengkonversi nilai integer menjadi string
    std::string str = std::to_string(value);

    // Menginisialisasi variabel result dengan nilai kosong
    std::string result = "";

    // Menginisialisasi variabel counter dengan nilai 0
    int counter = 0;

    // Melakukan perulangan dari belakang ke depan
    for (int i = str.length() - 1; i >= 0; i--) {
      // Jika counter sudah mencapai 3
      if (counter == 3) {
        // Menambahkan karakter titik ke dalam result
        result = "." + result;

        // Mengembalikan counter ke nilai 0
        counter = 0;
      }

      counter++;
      result = str[i] + result;
    }

    // Mengembalikan nilai result
    return result;
  }

  /**
   * @brief Mengkonversi nilai integer menjadi double
   * 
   * @param value nilai integer yang akan di konversi
   * 
   * @return double
   */
  double intToDouble(int value) {
    // Mengkonversi nilai integer menjadi double
    double converted = static_cast<double>(value);

    // Membagi nilai double dengan 1000
    converted /= 1000.0;

    // Mengembalikan nilai double
    return converted;
  }
}

#endif // PARSE_HELPER_HPP
