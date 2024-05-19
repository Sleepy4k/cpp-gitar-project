#pragma once

#ifndef PAGINATION_STRUCT_HPP
#define PAGINATION_STRUCT_HPP

/**
 * Deklarasi struct Pagination
 *
 * Struct pagination ini akan kita gunakan untuk
 * merapihkan return data pada fitur show all data,
 * sehingga memudahkan dalam mengelola paginasi
 * untuk field pada struct yaitu :
 * - back = untuk menyimpan status apakah bisa
 *          kembali ke laman sebelum nya atau tidak
 * - next = untuk menyimpan status apakah bisa
 *          lanjut ke laman setelah nya atau tidak
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
struct PaginationStruct {
  bool back, next;
};

#endif // PAGINATION_STRUCT_HPP
