#pragma once

#ifndef NODE_STRUCT_HPP
#define NODE_STRUCT_HPP

/**
 * Deklarasi struct Node
 *
 * Struct node ini akan kita gunakan untuk
 * merapihkan data pada linked list, untuk
 * linked list sendiri kita menggunakan double
 * circular linked list agar mempermudah data
 * untuk field pada struct yaitu :
 * - data = untuk menyimpan data dari struct
 *          berikan, jika kita memberikan type
 *          struct Destination, maka data akan
 *          bertipe data destination
 * - next = untuk menyimpan data node setelah
 *          nya, jika kosong akan diisi dengan
 *          nilai nullptr
 * - prev = untuk menyimpan data node sebelum
 *          nya, jika kosong akan diisi dengan
 *          nilai nullptr
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
template <typename T>
struct NodeStruct {
  T data;
  NodeStruct<T> *next, *prev;
};

#endif // NODE_STRUCT_HPP
