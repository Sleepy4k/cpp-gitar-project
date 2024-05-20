#pragma once

#ifndef PACKAGE_STRUCT_HPP
#define PACKAGE_STRUCT_HPP

#include <string>

#include "../enums/package_transport_enum.hpp"

/**
 * Deklarasi struct Package
 *
 * Struct package ini akan kita gunakan
 * untuk merapihkan data paket wisata,
 * untuk field pada struct yaitu :
 * - name         = untuk menyimpan nama paket
 * - description  = untuk menyimpan deskripsi
 *                  dari paket
 * - duration     = untuk menyimpan durasi
 *                  dari paket
 * - price        = untuk menyimpan harga
 *                  dari paket
 * - people       = untuk menyimpan jumlah orang
 *                 dalam satu paket
 * - transport    = untuk menyimpan jenis
 *                  transportasi yang digunakan
 *                  dalam paket
 * - facility     = untuk menyimpan fasilitas
 *                 yang didapat dalam paket
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
struct PackageStruct {
  std::string name, description;
  int duration, price, people;
  PackageTransport transport;
  std::string facility;
};

#endif // PACKAGE_STRUCT_HPP
