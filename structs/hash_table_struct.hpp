#pragma once

#ifndef HASH_TABLE_STRUCT_HPP
#define HASH_TABLE_STRUCT_HPP

/**
 * Deklarasi struct HashTable
 *
 * Struct hash table ini akan kita gunakan
 * untuk menyimpan data pada hash table, pada
 * struct ini terdapat dua field yaitu :
 * - key = untuk menyimpan key dari data yang
 *         akan kita masukkan ke dalam hash table
 * - value = untuk menyimpan value dari data
 *           yang akan kita masukkan ke dalam
 *           hash table
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
template <typename T>
struct HashTableStruct {
  std::string key;
  T value;
};

#endif // HASH_TABLE_STRUCT_HPP
