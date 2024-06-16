#pragma once

#ifndef SYSTEM_HELPER_HPP
#define SYSTEM_HELPER_HPP

#include <string>

/**
 * Deklarasi namespace SYS
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses sistem seperti membersihkan layar, menjeda layar, dll
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace SYS {
  /**
   * @brief Membersihkan layar
   * 
   * @return void
   */
  static const void clear() {
    // Jika sistem operasi adalah windows
    #ifdef _WIN32
      // Menggunakan perintah sistem cls untuk membersihkan layar
      system("cls");
    // Jika sistem operasi adalah unix
    #else
      // Menggunakan perintah sistem clear untuk membersihkan layar
      system("clear");
    #endif
  }

  /**
   * @brief Menjeda layar
   * 
   * @return void
   */
  static const void pause() {
    // Jika sistem operasi adalah windows
    #ifdef _WIN32
      // Menggunakan perintah sistem pause untuk menjeda layar
      system("pause");
    // Jika sistem operasi adalah unix
    #else
      // Menggunakan perintah sistem read untuk menjeda layar
      system("read -p 'Press [Enter] key to continue...'");
    #endif
  }
}

#endif // SYSTEM_HELPER_HPP
