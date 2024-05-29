#pragma once

#ifndef TOTAL_TRANSPORT_ENUM
#define TOTAL_TRANSPORT_ENUM 3
#endif

#ifndef PACKAGE_TRANSPORT_ENUM_HPP
#define PACKAGE_TRANSPORT_ENUM_HPP

#include <string>

/**
 * Enum PackageTransport
 * 
 * Enum ini digunakan untuk membuat enumerasi
 * dari jenis transportasi yang tersedia
 * untuk paket wisata
 */
enum PackageTransport {
  BUS = 1,
  TRAIN = 2,
  AIRPLANE = 3
};

/**
 * @brief Mengambil nama fasilitas transportasi
 * 
 * @param transport
 * 
 * @return string
 */
std::string getFacilityName(int transport) {
  // Menggunakan switch case untuk mengecek
  // nilai dari transport dan mengembalikan string
  switch (transport) {
  // Jika transport sama dengan 1
  case 1:
    // Mengembalikan string "Bus"
    return "Bus";
  // Jika transport sama dengan 2
  case 2:
    // Mengembalikan string "Kereta Api"
    return "Kereta Api";
  // Jika transport sama dengan 3
  case 3:
    // Mengembalikan string "Pesawat Terbang"
    return "Pesawat Terbang";
  // Jika tidak ada case yang sesuai
  default:
    // Mengembalikan string "Tidak Diketahui"
    return "Tidak Diketahui";
  }
}

/**
 * @brief Mengambil daftar fasilitas transportasi
 * 
 * @param transport
 * 
 * @return string
 */
std::string getListOfFacility(int transport) {
  // Menggunakan switch case untuk mengecek
  // nilai dari transport dan mengembalikan string
  switch (transport) {
  // Jika transport sama dengan 1
  case 1:
    // Mengembalikan string "Bus AC, TV, Pemamdu Wisata, Makanan dan Minuman, Toilet, dan Bagasi"
    return "Bus AC, TV, Pemamdu Wisata, Makanan dan Minuman, Toilet, dan Bagasi";
  // Jika transport sama dengan 2
  case 2:
    // Mengembalikan string "Kereta Api Ekonomi, AC, TV, Makanan dan Minuman, Toilet, dan Bagasi"
    return "Kereta Api Ekonomi, AC, TV, Makanan dan Minuman, Toilet, dan Bagasi";
  // Jika transport sama dengan 3
  case 3:
    // Mengembalikan string "Pesawat Terbang Ekonomi, AC, TV, Makanan dan Minuman, Toilet, dan Bagasi"
    return "Pesawat Terbang Ekonomi, AC, TV, Makanan dan Minuman, Toilet, dan Bagasi";
  // Jika tidak ada case yang sesuai
  default:
    // Mengembalikan string "Tidak Diketahui"
    return "Tidak Diketahui";
  }
}

#endif // PACKAGE_TRANSPORT_ENUM_HPP
