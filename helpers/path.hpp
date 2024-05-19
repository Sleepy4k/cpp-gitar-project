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
  const std::string getPath() {
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
  const void setPath(std::string path) {
    // Find the last backslash or slash
    // and remove the filename from the path (if any)
    // such as: /path/to/file.exe -> /path/to
    size_t lastBackslashPos = path.find_last_of("\\/");
    if (lastBackslashPos != std::string::npos) path = path.substr(0, lastBackslashPos);

    basepath = path;
  };
}

#endif // PATH_HELPER_HPP
