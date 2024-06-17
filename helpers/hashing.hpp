#pragma once

#ifndef HASH_SALT_HELPER_HPP
#define HASH_SALT_HELPER_HPP
  static const char salt[10] = "?^&*%$#@!";
#endif // HASH_SALT_HELPER_HPP

#ifndef HASH_HELPER_HPP
#define HASH_HELPER_HPP

/**
 * Deklarasi namespace Hashing
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses enkripsi dan dekripsi password
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace Hashing {
  /**
   * @brief Encrypt the password
   * 
   * @param password string
   * 
   * @return string 
   */
  static std::string encrypt(std::string password) {
    // Menggunakan std::to_string untuk mengkonversi
    // tipe data numerik ke dalam string
    using std::to_string; // Import library to_string

    // Deklarasi variabel hash dengan nilai awal 0
    int hash = 0;

    // Melakukan iterasi sebanyak karakter pada password
    for (unsigned int i = 0; i < password.length(); i++) {
      /**
       * Untuk logic dari hash ini, kita menggunakan
       * operasi bitwise XOR dan shift left dan right
       * untuk menghasilkan nilai hash yang unik
       * 
       * Note :
       * 1. XOR (^) : Operasi bitwise XOR akan menghasilkan
       *   nilai 1 jika kedua bit yang dibandingkan berbeda
       *  dan 0 jika sama
       * 
       * 2. Shift Left (<<) : Operasi shift left akan
       *  menggeser bit ke kiri sebanyak n kali
       *  misalnya 0001 << 1 akan menghasilkan 0010
       * 
       * 3. Shift Right (>>) : Operasi shift right akan
       * menggeser bit ke kanan sebanyak n kali
       * misalnya 0010 >> 1 akan menghasilkan 0001
       * 
       * 4. ASCII : Setiap karakter pada password akan
       * diubah menjadi nilai ASCII nya, misalnya
       * karakter 'a' akan diubah menjadi 97
       * 
       * 5. Hash : Hash adalah nilai yang dihasilkan
       * dari operasi bitwise XOR dan shift left dan right
       * yang akan digunakan sebagai nilai enkripsi
       * password
       * 
       * Baca lebih lanjut di website lms pada
       * mata kuliah pengantar sistem digital
       */
      hash ^= (hash << 5) + (hash >> 2) + password[i];
    }

    // Ubah nilai hash ke dalam string
    password = to_string(hash);

    // Deklarasi variabel salted_hash dengan nilai awal string kosong
    std::string salted_hash = "";

    // Melakukan iterasi sebanyak karakter pada password,
    // untuk logic dari salted_hash ini, kita menggunakan
    // salt yang sudah didefinisikan sebelumnya yaitu
    // pada variabel array salt
    for (char c : password) {
      // Dari setiap karakter pada password, kita akan
      // mengubah nilai ASCII nya menjadi karakter
      // yang sesuai dengan index pada array salt
      // misalnya karakter '1' akan diubah menjadi '?'
      // karena value berbentuk char, kita bisa langsung
      // mengubahnya menjadi int dengan cara mengurangi
      // nilai ASCII dari karakter '0'
      salted_hash += salt[c - '0'];
    }

    // Mengembalikan nilai salted_hash
    return salted_hash;
  }

  /**
   * @brief Verify the password
   * 
   * @param password string 
   * @param hash stirng
   * 
   * @return true 
   * @return false 
   */
  static bool verify(const std::string password, const std::string hash) {
    /**
     * Untuk logic dari verify ini, kita akan
     * membandingkan nilai hash yang dihasilkan
     * dari password yang diinputkan dengan hash
     * 
     * Jika kedua nilai hash sama, maka password
     * yang diinputkan benar
     * 
     * Jika tidak, maka password yang diinputkan salah
     */
    return hash == encrypt(password);
  }
};

#endif // HASH_HELPER_HPP