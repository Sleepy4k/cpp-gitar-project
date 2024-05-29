#pragma once

#ifndef PATH_HELPER_HPP
#define PATH_HELPER_HPP

#include <string>

// Inisialisasi variabel basepath dengan nilai __FILE__
// __FILE__ adalah variabel yang menyimpan path dari file
// yang sedang di compile saat ini, contoh : /path/to/file.cpp
std::string basepath = __FILE__;

/**
 * Deklarasi namespace Path
 *
 * Namespace ini berfungsi untuk membantu dalam
 * proses pengambilan path dari file
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace Path {
  /**
   * @brief Mengembalikan nilai path dari variabel basepath
   * 
   * @return string
   */
  static std::string getPath() {
    // Mengembalikan nilai basepath
    return basepath;
  };

  /**
   * @brief Mengatur nilai path dari variabel basepath
   * 
   * @param path nama path yang akan di set ke basepath
   * 
   * @return void
   */
  static void setPath(std::string path) {
    // Mengambil posisi dari backslash atau slash terakhir
    // dan menghapus semua karakter setelahnya
    // Contoh : /path/to/file.cpp -> /path/to
    size_t lastBackslashPos = path.find_last_of("\\/");

    // Jika backslash atau slash ditemukan dan posisinya
    // berada di bagian tengah atau akhir dari path
    // maka hapus semua karakter setelahnya
    if (lastBackslashPos != std::string::npos) path = path.substr(0, lastBackslashPos);

    // Mengatur nilai basepath dengan nilai path
    basepath = path;
  };
}

#endif // PATH_HELPER_HPP
