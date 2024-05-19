#pragma once

#ifndef DESTINATION_STRUCT_HPP
#define DESTINATION_STRUCT_HPP

#include <string>

#include "../enums/destination_type_enum.hpp"

/**
 * Deklarasi struct Destination
 *
 * Struct destination ini akan kita gunakan
 * untuk merapihkan data destinasi wisata,
 * untuk field pada struct yaitu :
 * - name         = untuk menyimpan nama wisata
 * - description  = untuk menyimpan deskripsi
 *                  dari wisata
 * - location     = untuk menyimpan lokasi wisata
 * - work_hours   = untuk menyimpan jam kerja
 *                  dari wisata
 * - person       = untuk menyimpan jumlah orang
 *                  dalam satu tiket masuk wisata
 * - price        = untuk menyimpan harga untuk
 *                  satu tiket wisata
 * - type         = untuk menyimpan jenis destinasi
 *                  wisata yang dibuat berdasarkan
 *                  enumerasi Type
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
struct DestinationStruct {
  std::string name, description, location, work_hours;
  int person, price, pengunjung;
  DestinationType type;
};

#endif // DESTINATION_STRUCT_HPP
