#pragma once

#ifndef RECIEPT_STRUCT_HPP
#define RECIEPT_STRUCT_HPP

/**
 * Deklarasi struct Reciept
 *
 * Struct reciept ini akan kita gunakan
 * untuk merapihkan data reciept, untuk
 * field pada struct yaitu :
 * - name     = untuk menyimpan nama
 *              dari customer
 * - phone    = untuk menyimpan nomor
 *              telepon dari customer
 * - package  = untuk menyimpan nama
 *              paket yang dipilih
 * - date     = untuk menyimpan tanggal
 *              pemesanan
 * - duration = untuk menyimpan durasi
 *              dari paket
 * - price    = untuk menyimpan harga
 *              dari paket
 * - people   = untuk menyimpan jumlah
 *              orang dalam satu paket
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
struct RecieptStruct {
  std::string name, phone, package, date;
  int duration, price, people;
};

#endif // RECIEPT_STRUCT_HPP
