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
  switch (transport) {
    case 1:
      return "Bus";
    case 2:
      return "Kereta Api";
    case 3:
      return "Pesawat Terbang";
    default:
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
  switch (transport) {
    case 1:
      return "Bus AC, TV, Pemamdu Wisata, Makanan dan Minuman, Toilet, dan Bagasi";
    case 2:
      return "Kereta Api Ekonomi, AC, TV, Makanan dan Minuman, Toilet, dan Bagasi";
    case 3:
      return "Pesawat Terbang Ekonomi, AC, TV, Makanan dan Minuman, Toilet, dan Bagasi";
    default:
      return "Tidak Diketahui";
  }
}

#endif // PACKAGE_TRANSPORT_ENUM_HPP
