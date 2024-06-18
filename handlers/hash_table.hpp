#pragma once

#ifndef HASH_TABLE_MAX_SIZE
#define HASH_TABLE_MAX_SIZE 500
#endif // HASH_TABLE_MAX_SIZE

#ifndef HASH_TABLE_HPP
#define HASH_TABLE_HPP

#include <vector>
#include <iostream>

#include "../helpers/parse.hpp"
#include "../structs/comment_struct.hpp"
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
    // Jika nilai hash bukan -1 maka akan mengembalikan nilai true
    return generatedID[hash] != -1;
  }

  /**
   * @brief Melakukan pengecekan apakah nilai hash harus diresize
   * 
   * @param hash Nilai hash yang akan dicek
   * 
   * @return int
   */
  int isHashMustBeResize(int hash, int originalHash = -1) {
    // Jika nilai hash lebih kecil dari ukuran vector generatedID
    // dan nilai hash belum ada pada vector generatedID
    // maka akan mengembalikan nilai hash
    if (hash < generatedID.size() && !isHashExist(hash)) return hash;

    // Jika nilai originalHash sama dengan -1 maka berikan nilai hash
    // jika tidak maka berikan nilai originalHash
    originalHash = (originalHash == -1) ? hash : originalHash;

    do {
      // Menambahkan nilai hash dengan nilai originalHash
      hash++;

      // Jika nilai hash lebih besar dari ukuran vector generatedID
      if (hash >= generatedID.size()) {
        // Mengurangi nilai originalHash dengan nilai 2
        hash = originalHash / 2;

        // Mengganti nilai originalHash dengan nilai hash
        originalHash = hash;
      }

      // Jika nilai hash sudah ada pada vector generatedID
      // maka akan melakukan looping kembali
    } while (isHashExist(hash));

    // Mengembalikan nilai hash
    return hash;
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

    // Mengkonversi nilai data menjadi string
    data = Parse::toString(data);

    // Melakukan looping sebanyak panjang dari data
    for (char c : data) {
      // Menambahkan nilai hash dengan nilai ASCII dari karakter
      hash += static_cast<int>(c);
    }

    // Melakukan operasi modulus pada nilai hash dengan nilai dari HASH_TABLE_MAX_SIZE
    hash = hash % HASH_TABLE_MAX_SIZE;

    // Melakukan pengecekan apakah nilai hash harus diresize
    hash = isHashMustBeResize(hash);

    // Menambahkan hash ke dalam vector
    generatedID[hash] = hash;

    // Mengembalikan nilai hash
    return hash;
  }

  /**
   * @brief Membuat hash key dari data yang diberikan
   * 
   * @param data Nilai data yang akan dienkripsi
   * 
   * @return int
   */
  int makeHash(CommentStruct data) {
    // Membuat hash key dari data yang diberikan
    int hash = encrypt(data.username + data.comment + data.destination_name);

    // Menyimpan data ke dalam hash table
    hashTable[hash] = {std::to_string(hash), data};

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
   * @brief Mendapatkan total data yang telah diisi pada hash table
   * 
   * @return int
   */
  int totalFilledKeys(std::string destinationName) {
    // Deklarasi variabel total untuk menyimpan nilai total data
    int total = 0;

    // Melakukan looping sebanyak nilai dari HASH_TABLE_MAX_SIZE
    for (int i = 0; i < HASH_TABLE_MAX_SIZE; i++) {
      // Melakukan pengecekan apakah nilai hash sudah ada
      // pada vector generatedID, jika tidak maka kita akan
      // melanjutkan proses ke nilai selanjutnya
      if (!isHashExist(i)) continue;

      // Melakukan pengecekan apakah data yang ditampilkan adalah data pengguna
      // dan data yang ditampilkan adalah data destinasi
      // jika tidak maka kita akan melanjutkan ke data selanjutnya
      if (hashTable[i].value.destination_name == destinationName) {
        // Menambahkan nilai total
        total++;
      }
    }

    // Mengembalikan nilai total
    return total;
  }

  /**
   * @brief Menampilkan data dari hash table
   * 
   * @param key Nilai key yang akan ditampilkan
   * @param data Nilai data yang akan ditampilkan
   * @param isDetail Status apakah data yang ditampilkan adalah detail atau tidak
   * 
   * @return void
   */
  void displayData(int key, CommentStruct data, bool isDetail = false) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Melakukan pengecekan apakah nilai username dan comment kosong
    // jika iya maka akan menghentikan proses
    if (data.username.empty() || data.comment.empty()) return;

    // Menampilkan data dari hash table
    cout << "ID Pembelian   : " << key << endl;
    cout << "Nama Destinasi : " << data.destination_name << endl;
    cout << "Nama Pengguna : " << data.username << endl;
    cout << "Komentar : " << data.comment << endl;

    // Melakukan pengecekan apakah data yang ditampilkan adalah detail
    // jika tidak maka akan menghentikan proses
    if (!isDetail) return;

    // Melakukan pengecekan apakah nilai rating lebih kecil dari 1
    // atau lebih besar dari 5, jika iya maka akan menghentikan proses
    if (data.rating < 1 || data.rating > 5) return;

    // Menampilkan rating dari data yang ditampilkan
    // berdasarkan nilai dari data.rating
    switch (data.rating) {
    case 1:
      cout << "Rating : 1 (Sangat Buruk)" << endl;
      break;
    case 2:
      cout << "Rating : 2 (Buruk)" << endl;
      break;
    case 3:
      cout << "Rating : 3 (Cukup)" << endl;
      break;
    case 4:
      cout << "Rating : 4 (Baik)" << endl;
      break;
    case 5:
      cout << "Rating : 5 (Sangat Baik)" << endl;
      break;
    }
  }

  /**
   * @brief Mengecek apakah hash table kosong atau tidak
   * 
   * @return bool
   */
  bool isEmpty() {
    // Melakukan looping sebanyak nilai dari HASH_TABLE_MAX_SIZE
    for (int i = 0; i < HASH_TABLE_MAX_SIZE; i++) {
      // Melakukan pengecekan apakah nilai hash sudah ada
      // jika iya maka akan mengembalikan nilai false
      if (isHashExist(i)) return false;
    }

    // Mengembalikan nilai true
    return true;
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
   * @brief Mengecek apakah hash table kosong atau tidak
   * 
   * @return bool
   */
  bool empty() {
    return isEmpty();
  }

  /**
   * @brief Menampilkan data dari hash table
   * 
   * @param data Nilai data yang akan ditampilkan
   * @param isDetail Status apakah data yang ditampilkan adalah detail atau tidak
   * 
   * @return void
   */
  void displayData(C data, bool isDetail = false) {
    // Memanggil fungsi displayData dengan parameter 1
    // untuk menampilkan data dari hash table
    displayData(1, data, isDetail);
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
   * @brief Menghapus data dari hash table
   * 
   * @tparam T
   * @param data Nilai data yang akan dihapus
   * 
   * @return void
   */
  template <typename T>
  void remove(T data) {
    // Melakukan looping sebanyak nilai dari HASH_TABLE_MAX_SIZE
    // untuk mencari data yang akan dihapus
    for (int i = 0; i < HASH_TABLE_MAX_SIZE; i++) {
      // Melakukan pengecekan apakah nilai hash sudah ada
      // pada vector generatedID, jika tidak maka kita akan
      // melanjutkan proses ke nilai selanjutnya
      if (!isHashExist(i)) continue;

      // Melakukan pengecekan apakah data yang ditampilkan adalah data pengguna
      // dan data yang ditampilkan adalah data destinasi
      // jika tidak maka kita akan melanjutkan ke data selanjutnya
      if (hashTable[i].value.username != data.username) continue;

      // Melakukan pengecekan apakah data yang ditampilkan adalah data pengguna
      // dan data yang ditampilkan adalah data pengguna
      // jika tidak maka kita akan melanjutkan ke data selanjutnya
      if (hashTable[i].value.comment != data.comment) continue;

      // Mengganti nilai pada hash table dengan nilai default
      hashTable[i] = HashTableStruct<C>{};

      // Menghapus data dari hash table
      generatedID[i] = -1;

      // Menghentikan proses
      break;
    }
  }

  /**
   * @brief Menampilkan semua data dari hash table
   * 
   * @param page Halaman yang akan ditampilkan
   * @param perpage Jumlah data yang akan ditampilkan
   * @param isDetail Status apakah data yang ditampilkan adalah detail atau tidak
   * @param destinationName Nama destinasi yang akan ditampilkan
   * 
   * @return void
   */
  PaginationStruct showAll(int page, int perpage, bool isDetail, std::string destinationName) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

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
    if (keys.size() < 1) {
      // Menampilkan pesan bahwa belum ada data yang tersedia
      cout << "Belum ada data yang tersedia" << endl;

      // Mengembalikan nilai struct PaginationStruct dengan nilai default
      return PaginationStruct{isBack, isNext};
    }

    // Inisialisasi variable total dengan nilai 0
    int total = keys.size();

    // Inisialisasi variable spesificTotal dengan nilai totalFilledKeys
    int spesificTotal = totalFilledKeys(destinationName);

    // Inisialisasi variable offset
    // dengan nilai page dikurangi 1 dikali perpage
    int offset = page * perpage;

    // Inisialisasi variable start
    // dengan nilai offset dikurangi perpage
    int start = offset - perpage;

    // Insialisasi variable index dengan nilai 0
    int index = 0;

    // Deklarasi variabel key untuk menyimpan nilai key
    // dari data yang akan diambil dan found yaitu data yang
    // sudah ditemukan
    int key, found = 0;

    // Menampilkan separator untuk memisahkan data
    cout << "====================" << endl;

    // Melakukan looping hingga index sama dengan offset
    do {
      // Memberikan nilai key dengan nilai keys[index]
      key = keys[index];

      // Jika index lebih kecil dari total
      // dan found lebih kecil dari offset
      // serta data yang ditemukan adalah data destinasi
      // maka tampilkan data yang ada pada node
      if (index < total && found < offset
        && hashTable[key].value.destination_name == destinationName
      ) {
        // Melakukan pengecekan apakah nilai found lebih besar dari start
        // jika iya maka tampilkan data yang ada pada node
        if (found >= start) {
          cout << "ID Komentar : " << found + 1 << endl;

          // Menampilkan data dari hash table
          displayData(key, hashTable[key].value, isDetail);

          // Menampilkan separator untuk memisahkan data
          cout << "====================" << endl;
        }

        // Menambahkan nilai found
        found++;
      }

      // Menambahkan nilai index
      index++;
    } while (index < total);

    // Jika offset lebih kecil dari total data
    // maka ubah nilai isNext menjadi true
    if (offset < spesificTotal) isNext = true;

    // Jika page lebih besar dari 1
    // maka ubah nilai isBack menjadi true
    if (page > 1) isBack = true;

    // Mengembalikan nilai struct PaginationStruct
    return PaginationStruct{isBack, isNext};
  }

  /**
   * @brief Menampilkan data berdasarkan username
   * 
   * @param destinationName Nama destinasi yang akan ditampilkan
   * @param username Nama pengguna yang akan ditampilkan
   * 
   * @return void
   */
  void showByUsername(std::string destinationName, std::string username) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Deklarasi variabel found dengan nilai false
    bool found = false;

    // Memanggil fungsi getFilledKeys untuk mendapatkan
    // semua key yang telah diisi pada hash table
    std::vector<int> keys = getFilledKeys();

    // Melakukan looping sebanyak nilai dari keys
    for (int i = 0; i < keys.size(); i++) {
      // Melakukan pengecekan apakah data yang ditampilkan adalah data pengguna
      // dan data yang ditampilkan adalah data destinasi
      // jika tidak maka kita akan melanjutkan ke data selanjutnya
      if (hashTable[keys[i]].value.destination_name != destinationName) continue;

      // Melakukan pengecekan apakah data yang ditampilkan adalah data pengguna
      // dan data yang ditampilkan adalah data pengguna
      // jika tidak maka kita akan melanjutkan ke data selanjutnya
      if (hashTable[keys[i]].value.username != username) continue;

      // Menampilkan data dari hash table
      displayData(keys[i], hashTable[keys[i]].value, true);

      // Mengubah nilai found menjadi true
      found = true;

      // Menghetikan proses
      break;
    }

    // Melakukan pengecekan apakah data ditemukan
    // jika tidak maka tampilkan pesan bahwa data tidak ditemukan
    if (!found) cout << "Data tidak ditemukan" << endl;
  }
};

#endif // HASH_TABLE_HPP
