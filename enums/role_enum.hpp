#pragma once

#ifndef ROLE_ENUM_HPP
#define ROLE_ENUM_HPP

/**
 * Deklarasi Enum atau Enumeration Role
 *
 * Yaitu sebuah tipe data yang merepresentasikan
 * integral konstan, yang mana pada kasus ini,
 * kita membuat enum untuk menyimpan data role,
 * yang nantinya kita gunakan untuk autentikasi
 */
enum Role {
  Guest = 1,
  Admin = 2
};

/**
 * Fungsi untuk mengubah data enum menjadi string
 *
 * @param role data enum yang akan diubah
 *
 * @return string data enum yang sudah diubah
 */
std::string roleToString(const Role &role) {
  // Menggunakan switch case untuk mengecek
  // nilai dari role dan mengembalikan string
  switch (role) {
  // Jika role sama dengan Guest
  case Guest:
    // Mengembalikan string "Guest"
    return "Guest";
  // Jika role sama dengan Admin
  case Admin:
    // Mengembalikan string "Admin"
    return "Admin";
  // Jika tidak ada case yang sesuai
  default:
    // Mengembalikan string "Tidak diketahui"
    return "Tidak diketahui";
  }
}

/**
 * Fungsi untuk mengubah data integer menjadi string
 *
 * @param role data integer yang akan diubah
 *
 * @return string data integer yang sudah diubah
 */
std::string roleToString(const int &role) {
  // Menggunakan switch case untuk mengecek
  // nilai dari role dan mengembalikan string
  switch (role) {
  // Jika role sama dengan Guest
  case Guest:
    // Mengembalikan string "Guest"
    return "Guest";
  // Jika role sama dengan Admin
  case Admin:
    // Mengembalikan string "Admin"
    return "Admin";
  // Jika tidak ada case yang sesuai
  default:
    // Mengembalikan string "Tidak diketahui"
    return "Tidak diketahui";
  }
}

#endif // ROLE_ENUM_HPP
