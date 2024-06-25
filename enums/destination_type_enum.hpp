#pragma once

#ifndef DESTINATION_TYPE_SIZE_ENUM_HPP
#define DESTINATION_TYPE_SIZE_ENUM_HPP 3
#endif // DESTINATION_TYPE_SIZE_ENUM_HPP

#ifndef DESTINATION_TYPE_ENUM_HPP
#define DESTINATION_TYPE_ENUM_HPP

/**
 * Deklarasi Enum atau Enumeration Type
 *
 * Yaitu sebuah tipe data yang merepresentasikan
 * integral konstan, yang mana pada kasus ini,
 * kita membuat enum untuk menyimpan data type,
 * yang nanti nya kita gunakan untuk menyimpan
 * jenis jenis dari destinasi wisata
 */
enum DestinationType {
  Nature = 1,
  History = 2,
  Culture = 3
};

/**
 * Fungsi untuk mengubah data enum menjadi string
 *
 * @param type data enum yang akan diubah
 *
 * @return string data enum yang sudah diubah
 */
std::string destinationTypeToString(const DestinationType &type) {
  // Menggunakan switch case untuk mengecek
  // nilai dari type dan mengembalikan string
  switch (type) {
  // Jika type sama dengan Nature
  case Nature:
    // Mengembalikan string "Alam"
    return "Alam";
  // Jika type sama dengan History
  case History:
    // Mengembalikan string "Sejarah"
    return "Sejarah";
  // Jika type sama dengan Culture
  case Culture:
    // Mengembalikan string "Budaya"
    return "Budaya";
  // Jika tidak ada case yang sesuai
  default:
    // Mengembalikan string "Tidak diketahui"
    return "Tidak diketahui";
  }
}

/**
 * Fungsi untuk mengubah data integer menjadi string
 *
 * @param type data integer yang akan diubah
 *
 * @return string data integer yang sudah diubah
 */
std::string destinationTypeToString(const int &type) {
  // Menggunakan switch case untuk mengecek
  // nilai dari type dan mengembalikan string
  switch (type) {
  // Jika type sama dengan 1
  case 1:
    // Mengembalikan string "Alam"
    return "Alam";
  // Jika type sama dengan 2
  case 2:
    // Mengembalikan string "Sejarah"
    return "Sejarah";
  // Jika type sama dengan 3
  case 3:
    // Mengembalikan string "Budaya"
    return "Budaya";
  // Jika tidak ada case yang sesuai
  default:
    // Mengembalikan string "Tidak diketahui"
    return "Tidak diketahui";
  }
}

#endif // DESTINATION_TYPE_ENUM_HPP
