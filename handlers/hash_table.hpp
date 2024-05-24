#pragma once

#ifndef HASH_TABLE_SALT
#define HASH_TABLE_SALT 97
#endif

#ifndef HASH_TABLE_MAX_SIZE
#define HASH_TABLE_MAX_SIZE 500
#endif

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <iostream>
#include <typeinfo>

#include "../helpers/parse.hpp"
#include "../structs/package_struct.hpp"
#include "../structs/reciept_struct.hpp"
#include "../structs/pagination_struct.hpp"
#include "../structs/hash_table_struct.hpp"

/**
 * Deklarasi class HashTable
 * 
 * Class ini akan digunakan untuk membuat hash key
 * dari data yang diberikan, hash key yang dihasilkan
 * akan unik dan tidak akan ada yang sama dengan
 * hash key lainnya pada vector generatedID
 * 
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
template <typename C>
class HashTable {
private:
  // Array untuk menyimpan data hash table yang telah dihasilkan
  // dengan ukuran maksimal menggunakan nilai dari HASH_TABLE_MAX_SIZE
  HashTableStruct<C> hashTable[HASH_TABLE_MAX_SIZE];

  // Vector untuk menyimpan nilai hash yang telah dihasilkan
  // mencegah hash yang sama dihasilkan
  std::vector<int> generatedID;

  /**
   * @brief Melakukan pengecekan apakah nilai hash sudah ada
   *       pada vector generatedID
   * 
   * @param hash Nilai hash yang akan dicek
   * 
   * @return bool
   */
  bool isHashExist(int hash) {
    // Melakukan pengecekan apakah nilai hash sudah ada
    // pada vector generatedID
    if (generatedID[hash] != -1) {
      // Jika iya maka akan mengembalikan nilai true
      return true;
    }

    // Jika tidak maka akan mengembalikan nilai false
    return false;
  }

  /**
   * @brief Melakukan pengecekan apakah nilai hash harus diresize
   * 
   * @param hash Nilai hash yang akan dicek
   * 
   * @return int
   */
  int isHashMustBeResize(int hash) {
    if (hash < generatedID.size()) return hash;

    // Deklarasi variabel isRecursived untuk mengetahui apakah
    // pproses resize harus dilakukan secara rekursif atau tidak
    bool isRecursived = false;

    // Mengubah nilai hash dengan cara mengambil
    // sisa hasil bagi dari nilai hash dengan
    // ukuran vector generatedID
    int tempHash = hash % generatedID.size();

    // Melakukan pengecekan apakah nilai tempHash sudah ada
    // pada vector generatedID, jika iya maka kita akan
    // menambahkan nilai 1 pada tempHash, hingga tempHash yang
    // dihasilkan belum ada pada vector generatedID
    while (isHashExist(tempHash)) {
      // Menambahkan nilai hash
      tempHash++;

      // Jika nilai hash yang dihasilkan lebih besar dari
      // ukuran vector generatedID, maka kita akan menghentikan
      // perulangan
      if (tempHash >= generatedID.size()) {
        // Mengubah nilai isRecursived menjadi true
        isRecursived = true;

        // Menghentikan perulangan
        break;
      }
    }

    // Melakukan pengecekan apakah proses resize harus dilakukan
    // secara rekursif atau tidak dengan cara memanggil fungsi
    // isHashMustBeResize dengan parameter hash yang telah dihasilkan
    // dibagi 2
    if (isRecursived) return isHashMustBeResize(hash / 2);

    // Mengembalikan nilai hash
    return (tempHash == hash) ? hash : tempHash;
  }

  /**
   * @brief Enkripsi data untuk mendapatkan hash yang unik
   * 
   * @tparam T
   * @param data Nilai data yang akan dienkripsi
   * 
   * @return int
   */
  template <typename T>
  int encrypt(T data) {
    // Deklarasi variabel hash untuk menyimpan nilai hash
    int hash = 0;

    // Jika tipe data adalah integer
    if (typeid(data).name() == typeid(int).name()) {
      // Kita akan mengkalikan data dengan 2 dan menambahkan
      // nilai dari salt yang telah didefinisikan kemudian
      // membagi hasilnya dengan 3
      hash =  ((std::stoi(data) * 2) + HASH_TABLE_SALT) / 3;
    } else if (typeid(data).name() == typeid(std::string).name()) { // Jika tipe data adalah string
      // Pada tipe data string, kita akan membuat hash key
      // dengan algoritma yang berbeda, yaitu dengan
      // mengambil huruf pertama dan terakhir dari string
      // kemudian mengalikan nilai ASCII dari kedua huruf
      // tersebut
      hash = (int)data[0] * (int)data[data.length() - 1];
    } else { // Jika tipe data adalah tipe data lainnya
      // Pada tipe data lainnya, kita akan menggunakan
      // algoritma yang berbeda, yaitu dengan mengalikan
      // nilai dari 12 dengan nilai dari salt yang telah
      // didefinisikan
      hash = 12 * HASH_TABLE_SALT;
    }

    // Melakukan pengecekan apakah nilai hash harus diresize
    hash = isHashMustBeResize(hash);

    // Menambahkan hash ke dalam vector
    generatedID[hash] = hash;

    // Mengembalikan nilai hash
    return hash;
  }

  /**
   * @brief Mendapatkan data dari hash table
   * 
   * @return std::vector<int>
   */
  std::vector<int> getFilledKeys() {
    // Deklarasi vector keys untuk menyimpan nilai key
    std::vector<int> keys;

    // Melakukan looping sebanyak nilai dari HASH_TABLE_MAX_SIZE
    for (int i = 0; i < HASH_TABLE_MAX_SIZE; i++) {
      // Melakukan pengecekan apakah nilai hash sudah ada
      // pada vector generatedID, jika tidak maka kita akan
      // melanjutkan proses ke nilai selanjutnya
      if (!isHashExist(i)) continue;

      // Menambahkan nilai key ke dalam vector keys
      keys.push_back(i);
    }

    // Mengembalikan nilai keys
    return keys;
  }

  /**
   * @brief Menampilkan data dari hash table
   * 
   * @param data Nilai data yang akan ditampilkan
   * 
   * @return void
   */
  void displayData(int key, RecieptStruct data, bool isDetail = false) {
    // Menampilkan data dari hash table
    cout << "ID Pembelian   : " << key << endl;
    cout << "Nama           : " << data.name << endl;
    cout << "Telepon        : " << data.phone << endl;
    cout << "Paket          : " << data.package << endl;
    cout << "Tanggal        : " << data.date << endl;

    // Melakukan pengecekan apakah isDetail bernilai true
    // jika iya maka kita akan menampilkan data lebih detail
    if (!isDetail) return;

    cout << "Durasi         : " << data.duration << " hari" << endl;
    cout << "Harga          : Rp. " << Parse::intToCurrencyFormat(data.price) << endl;
    cout << "Jumlah         : " <<  data.people << " orang" << endl;
  }

  /**
   * @brief Membuat hash key dari data yang diberikan
   * 
   * @param data Nilai data yang akan dienkripsi
   * 
   * @return int
   */
  int makeHash(RecieptStruct data) {
    // Membuat hash key dari data yang diberikan
    int hash = encrypt(data.name + data.phone + data.package);

    // Menyimpan data ke dalam hash table
    hashTable[hash] = {std::to_string(hash), data};

    // Mengembalikan nilai hash
    return hash;
  }

public:
  /**
   * @brief Konstruktor dari class HashTable
   * 
   * Konstruktor ini akan membuat vector generatedID
   * dengan ukuran HASH_TABLE_MAX_SIZE dan mengisi nilai dari
   * vector tersebut dengan -1
   */
  HashTable() {
    generatedID = std::vector<int>(HASH_TABLE_MAX_SIZE, -1);
  }

  /**
   * @brief Menampilkan semua data dari hash table
   * 
   * @param page Halaman yang akan ditampilkan
   * @param perpage Jumlah data yang akan ditampilkan
   * @param isDetail Status apakah data yang ditampilkan adalah detail atau tidak
   * @param username Nama pengguna yang akan ditampilkan
   * @param isAdmin Status apakah pengguna adalah admin atau bukan
   * 
   * @return void
   */
  PaginationStruct getAll(int page, int perpage, bool isDetail, std::string username, bool isAdmin) {
    // Insialisasi variable isBack dengan nilai false
    bool isBack = false;

    // Insialisasi variable isNext dengan nilai false
    bool isNext = false;

    // Memanggil fungsi getFilledKeys untuk mendapatkan
    // semua key yang telah diisi pada hash table
    std::vector<int> keys = getFilledKeys();

    // Melakukan pengecekan apakah nilai dari keys adalah 0
    // jika iya maka kita akan mengembalikan nilai struct PaginationStruct
    // karena belum ada data yang tersedia
    if (keys.size() == 0) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Mengembalikan nilai struct PaginationStruct dengan nilai default
      return PaginationStruct{isBack, isNext};
    }

    // Inisialisasi variable total dengan nilai 0
    int total = keys.size();

    // Inisialisasi variable offset
    // dengan nilai page dikurangi 1 dikali perpage
    int offset = page * perpage;

    // Inisialisasi variable start
    // dengan nilai offset dikurangi perpage
    int start = offset - perpage;

    // Insialisasi variable index dengan nilai 0
    int index = 0;

    // Deklarasi variabel key untuk menyimpan nilai key
    // dari data yang akan diambil dan loc yaitu data yang
    // sudah diambil
    int key, loc = 0;

    // Menampilkan separator untuk memisahkan data
    cout << "====================" << endl;

    // Melakukan looping hingga index sama dengan offset
    do {
      // Jika index sama atau lebih besar dari start
      // dan index lebih kecil dari total data
      // serta index lebih kecil dari offset
      // maka tampilkan data yang ada pada node
      if (index >= start && index < total && index < offset) {
        // Memberikan nilai key dengan nilai keys[i]
        key = keys[loc];

        // Menambahkan nilai loc
        loc++;

        // Melakukan pengecekan apakah pengguna adalah admin
        // dan data yang ditampilkan adalah data pengguna
        // jika tidak maka kita akan melanjutkan ke data selanjutnya
        if (!isAdmin && hashTable[key].value.name != username) {
          // Menambahkan nilai index
          index++;

          // Melanjutkan ke data selanjutnya
          continue;
        }

        // Menampilkan data dari hash table
        displayData(key, hashTable[key].value, isDetail);

        // Menampilkan separator untuk memisahkan data
        cout << "====================" << endl;
      }

      // Menambahkan nilai index
      index++;
    } while (index <= offset);

    // Jika offset lebih kecil dari total data
    // maka ubah nilai isNext menjadi true
    if (offset < total) isNext = true;

    // Jika page lebih besar dari 1
    // maka ubah nilai isBack menjadi true
    if (page > 1) isBack = true;

    // Mengembalikan nilai struct PaginationStruct
    return PaginationStruct{isBack, isNext};
  }

  /**
   * @brief Menambah data ke dalam hash table
   * 
   * @tparam T
   * @param data Nilai data yang akan dienkripsi
   * 
   * @return int
   */
  template <typename T>
  int insert(T data) {
    // Memanggil fungsi makeHash dengan parameter data
    // untuk membuat hash key dari data yang diberikan
    // dan menyimpan data ke dalam hash table
    int key = makeHash(data);

    // Mengembalikan nilai key
    return key;
  }

  /**
   * @brief Mendapatkan data dari hash table
   * 
   * @param hash Nilai hash yang akan dicari
   * 
   * @return HashTableStruct
   */
  C get(int hash) {
    // Melakukan pengecekan apakah nilai hash sudah ada
    // pada vector generatedID, jika tidak maka kita akan
    // menghentikan proses
    if (!isHashExist(hash)) return C{};

    // Mengembalikan data dari hash table
    return hashTable[hash].value;
  }

  /**
   * @brief Menghapus data dari hash table
   * 
   * @param hash Nilai hash yang akan dihapus
   * 
   * @return void
   */
  void removeHash(int hash) {
    // Melakukan pengecekan apakah nilai hash sudah ada
    // pada vector generatedID, jika tidak maka kita akan
    // menghentikan proses
    if (!isHashExist(hash)) return;

    // Menghapus data dari hash table
    hashTable[hash].key = "";
    hashTable[hash].value = NULL;

    // Menghapus nilai hash dari vector generatedID
    generatedID[hash] = -1;
  }
};

#endif // HASH_TABLE_HPP
