#pragma once

#ifndef DESTINATION_CONTROLLER_HPP
#define DESTINATION_CONTROLLER_HPP

#include <iostream>
#include <string>

#include "user_controller.hpp"
#include "../helpers/path.hpp"
#include "../enums/role_enum.hpp"
#include "../handlers/linked_list.hpp"
#include "../helpers/file_storage.hpp"
#include "../models/destination_model.hpp"
#include "../structs/pagination_struct.hpp"
#include "../structs/destination_struct.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/**
 * Deklarasi class DestinationController
 *
 * Class list ini kita gunakan untuk menghandle
 * proses CRUD data destinasi wisata, dimana
 * nantinya kita akan menampilkan data destinasi
 * wisata, menambahkan data destinasi wisata,
 * mengubah data destinasi wisata, dan menghapus
 * data destinasi wisata
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
class DestinationController {
private:
  // Inisialisasi variabel userData untuk menyimpan data user
  // dari class UserController
  UserController userData;

  // Inisialisasi variabel destinationList untuk menyimpan data destinasi
  // dari class LinkedList dengan tipe data DestinationStruct
  List<DestinationStruct> destinationList;

  /**
   * @brief Membuat form untuk mengisi data destinasi
   * 
   * @return DestinationStruct 
   */
  DestinationStruct form_destination() {
    // Inisialisasi variabel type dan data untuk menyimpan data
    int type;

    // Inisialisasi variabel data untuk menyimpan data destinasi
    DestinationStruct data;

    // Jika pada input sebelumnya ada yang tersisa
    // maka kita akan menghapusnya terlebih dahulu
    if (cin.peek() == '\n') cin.ignore();

    // Meminta input dari user untuk mengisi nama destinasi
    cout << "Masukan nama destinasi : ";
    getline(cin, data.name);

    // Meminta input dari user untuk mengisi deskripsi destinasi
    cout << "Masukan deskripsi destinasi : ";
    getline(cin, data.description);

    // Meminta input dari user untuk mengisi lokasi destinasi
    cout << "Masukan lokasi destinasi : ";
    getline(cin, data.location);

    // Meminta input dari user untuk mengisi jam operasional destinasi
    cout << "Masukan jam operasional : ";
    getline(cin, data.work_hours);

    // Meminta input dari user untuk mengisi jumlah orang per tiket
    cout << "Masukan jumlah orang per tiket : ";
    cin >> data.person;

    // Meminta input dari user untuk mengisi harga per tiket
    cout << "Masukan harga per tiket : ";
    cin >> data.price;

    // Meminta input dari user untuk mengisi jenis destinasi
    cout << "Jenis destinasi" << endl;
    cout << "==================" << endl;
    cout << "1. Alam" << endl;
    cout << "2. Sejarah" << endl;
    cout << "3. Budaya" << endl;
    cout << "==================" << endl;
    cout << "Masukan jenis destinasi : ";
    cin >> type;

    // Melakukan pengecekan jenis destinasi
    switch (type) {
    // Jika user memilih 1
    case 1:
      // Maka jenis destinasi akan menjadi alam
      data.type = Nature;

      // Menghentikan pengecekan
      break;
    // Jika user memilih 2
    case 2:
      // Maka jenis destinasi akan menjadi sejarah
      data.type = History;

      // Menghentikan pengecekan
      break;
    // Jika user memilih 3
    case 3:
      // Maka jenis destinasi akan menjadi budaya
      data.type = Culture;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3
    default:
      // Maka jenis destinasi akan menjadi alam secara default
      cout << "Pilihan tidak valid, jenis wisata akan menjadi alam secara default" << endl;

      // Menghentikan pengecekan
      data.type = Nature;

      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan data yang sudah di isi
    return data;
  }

  /**
   * @brief Fungsi untuk menambahkan data destinasi wisata
   * 
   * @return void
   */
  void insert_destination() {
    // Deklarasi varaible position untuk menyimpan posisi data
    int position;

    // Memanggil method form_destination untuk membuat form
    // dan mengisi dari data destinasi yang akan di inputkan
    DestinationStruct data = form_destination();

    // Memanggil method insert pada destinationList
    // untuk menambahkan data destinasi pada linked list
    destinationList.push(data);

    // Memanggil method insert pada Destination
    // untuk menambahkan data destinasi pada file csv
    DestinationModel::insert(data);
  }

  /**
   * @brief Menampilkan detail destinasi
   * 
   * @return void
   */
  void show_destination() {
    // Mencetak judul detail destinasi
    cout << "Detail Destinasi" << endl;

    // Mencetak garis untuk memisahkan antara judul
    cout << "===================" << endl;

    // Memanggil method showNodeData pada destination
    // untuk menampilkan data destinasi
    destinationList.showNodeData<DestinationStruct>(true);

    // Mencetak garis untuk memisahkan antara data
    cout << "===================" << endl;

    // Menunggu user untuk menekan tombol apapun
    // untuk melanjutkan proses
    system("pause");
  }

  /**
   * @brief Mengubah data destinasi
   * 
   * @return void
   */
  void update_destination() {
    // Deklarasi variabel oldData, newData, dan result
    // dengan tipe data DestinationStruct
    // untuk menyimpan data lama, data baru, dan hasil
    DestinationStruct result, oldData, newData;

    // Mencetak judul detail destinasi
    cout << "Detail Destinasi" << endl;

    // Mencetak garis untuk memisahkan antara judul
    cout << "===================" << endl;

    // Memanggil method showNodeData pada destination
    // untuk menampilkan data destinasi
    oldData = destinationList.showNodeData<DestinationStruct>(true);

    // Mencetak garis untuk memisahkan antara data
    cout << "===================" << endl;

    // Mencetak judul untuk mengubah destinasi
    cout << "Ubah Destinasi" << endl;

    // Memanggil method form_destination untuk membuat form
    // dan mengisi dari data destinasi yang akan di inputkan
    newData = form_destination();

    // Memanggil method update pada destinationList
    // untuk mengubah data destinasi pada linked list
    result = destinationList.update(oldData, newData);

    // Cek apakah hasil data yang di update kosong atau tidak
    // Jika kosong maka system akan mencetak pesan data tidak ditemukan
    // dan menghentikan proses
    if (result.name.empty() || result.description.empty() || result.location.empty()) {
      // Mencetak pesan data tidak ditemukan
      cout << "Data tidak ditemukan" << endl;

      // Menghentikan proses
      return;
    }

    // Memanggil method update pada Destination
    cout << "Data " << result.name << " berhasil diubah" << endl;

    // Menunggu user untuk menekan tombol apapun
    system("pause");
  }

  /**
   * @brief Menghapus data destinasi
   * 
   * @return void
   */
  void delete_destination() {
    // Deklarasi variabel data dengan tipe data DestinationStruct
    // untuk menyimpan data destinasi yang akan dihapus
    DestinationStruct data = destinationList.showNodeData<DestinationStruct>(true);

    // Deklarasi variabel confirmation
    char confirmation;

    // Meminta konfirmasi dari user apakah yakin
    cout << "Apakah kamu yakin mau menghapus? (y/N) : ";
    cin >> confirmation;

    // Jika konfirmasi tidak y maka menghentikan proses
    if (tolower(confirmation) != 'y') return;

    // Cek apakah data yang akan dihapus kosong atau tidak
    // Jika kosong maka system akan mencetak pesan data tidak ditemukan
    // dan menghentikan proses
    if (data.name.empty() || data.description.empty() || data.location.empty()) {
      // Mencetak pesan data tidak ditemukan
      cout << "Data tidak ditemukan" << endl;

      // Menghentikan proses
      return;
    }

    // Memanggil method delete pada Destination untuk menghapus data
    // pada linked list
    destinationList.removeByData(data);

    // Memanggil method delete pada Destination untuk menghapus data
    cout << "Data " << data.name << " berhasil dihapus" << endl;

    // Menunggu user untuk menekan tombol apapun
    system("pause");
  }

  /**
   * @brief Menampilkan menu destinasi
   * 
   * @param choice
   * @param index 
   * @param page 
   * @param pagination 
   * @param result 
   * 
   * @return bool 
   */
  bool adminMenu(int *choice, int *index, int *page, int *pagination, PaginationStruct result) {
    cout << "List of Destination Menu" << endl;
    cout << "===================" << endl;
    cout << "1. Detail Destinasi" << endl;
    cout << "2. Tambah Destinasi" << endl;
    cout << "3. Ubah Destinasi" << endl;
    cout << "4. Hapus Destinasi" << endl;
    cout << "5. Lanjut ke halaman berikutnya" << endl;
    cout << "6. Kembali ke halaman sebelumnya" << endl;
    cout << "7. Kembali" << endl;
    cout << "===================" << endl;
    cout << "Pilih menu : ";
    cin >> *choice;

    // Cek apakah pilihan user tidak valid
    // Jika pilhan user kurang dari 1 atau lebih dari 7
    // maka system akan mencetak pesan pilihan tidak valid
    if (*choice < 1 || *choice > 7) {
      // Mencetak pesan pilihan tidak valid
      cout << "Pilihan tidak valid" << endl;

      // Menunggu user untuk menekan tombol apapun
      system("pause");
    }

    // Jika user memilih menu 7
    if (*choice == 7) return false;

    // Menghapus layar pada terminal
    system("cls");

    // Melakukan pengecekan pilihan user
    switch (*choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method show_destination
      // untuk menampilkan detail destinasi
      show_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Memanggil method insert_destination
      // untuk menambahkan data destinasi
      insert_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 3
    case 3:
      // Memanggil method update_destination
      // untuk mengubah data destinasi
      update_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 4
    case 4:
      // Memanggil method delete_destination
      // untuk menghapus data destinasi
      delete_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 5
    case 5:
      // Mengecek apakah data selanjutnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.next) break;

      // Jika tidak kosong maka system akan menambahkan index dan page
      *index += 1;
      *page += *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 6
    case 6:
      // Mengecek apakah data sebelumnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.back) break;

      // Jika tidak kosong maka system akan mengurangi index dan page
      *index -= 1;
      *page -= *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3, 4, 5, 6
    default:
      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan nilai true
    return true;
  }

  /**
   * @brief Menampilkan menu destinasi
   * 
   * @param choice
   * @param index 
   * @param page 
   * @param pagination 
   * @param result 
   * 
   * @return bool 
   */
  bool userMenu(int *choice, int *index, int *page, int *pagination, PaginationStruct result) {
    cout << "List of Destination Menu" << endl;
    cout << "===================" << endl;
    cout << "1. Detail Destinasi" << endl;
    cout << "2. Lanjut ke halaman berikutnya" << endl;
    cout << "3. Kembali ke halaman sebelumnya" << endl;
    cout << "4. Kembali" << endl;
    cout << "===================" << endl;
    cout << "Pilih menu : ";
    cin >> *choice;

    // Cek apakah pilihan user tidak valid
    // Jika pilhan user kurang dari 1 atau lebih dari 4
    // maka system akan mencetak pesan pilihan tidak valid
    if (*choice < 1 || *choice > 4) {
      // Mencetak pesan pilihan tidak valid
      cout << "Pilihan tidak valid" << endl;

      // Menunggu user untuk menekan tombol apapun
      system("pause");
    }

    // Jika user memilih menu 4
    if (*choice == 4) return false;

    // Menghapus layar pada terminal
    system("cls");

    // Melakukan pengecekan pilihan user
    switch (*choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method show_destination
      // untuk menampilkan detail destinasi
      show_destination();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Mengecek apakah data selanjutnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.next) break;

      // Jika tidak kosong maka system akan menambahkan index dan page
      *index += 1;
      *page += *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 3
    case 3:
      // Mengecek apakah data sebelumnya kosong
      // Jika kosong maka system akan menghentikan proses
      if (!result.back) break;

      // Jika tidak kosong maka system akan mengurangi index dan page
      *index -= 1;
      *page -= *pagination;

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2, 3
    default:
      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan nilai true
    return true;
  }

public:
  /**
   * @brief Inisialisasi data destinasi
   * 
   * @return void
   */
  void init() {
    // Mengecek apakah file destination_data.csv tidak ada
    // Jika tidak ada maka system akan membuat file destination_data.csv
    // dan menambahkan data destinasi secara default
    if (!FileStorage::Exists(Path::getPath() + "/data/destination_data.csv")) {
      // Membuat file destination_data.csv
      FileStorage::Create(Path::getPath() + "/data/destination_data.csv");

      // Menambahkan data destinasi secara default
      DestinationModel::insert(DestinationStruct{"Taman Nasional Bromo Tengger Semeru", "Taman Nasional Bromo Tengger Semeru adalah sebuah kawasan konservasi alam di Jawa Timur", "Probolinggo Jawa Timur", "24 Jam", 1, 50000, Nature});
      DestinationModel::insert(DestinationStruct{"Candi Borobudur", "Candi Borobudur adalah sebuah candi Buddha yang terletak di Magelang Jawa Tengah", "Magelang Jawa Tengah", "06.00 - 17.00", 1, 50000, History});
    }

    // Mengecek apakah data destinasi kosong pada linked list
    // Jika kosong maka system akan membaca data dari file csv
    if (destinationList.isEmpty()) {
      // Membaca data dari file csv
      std::vector<DestinationStruct> data = DestinationModel::read();

      // Melakukan perulangan untuk menambahkan data ke dalam linked list
      // berdasarkan data yang sudah di baca dari file csv
      for (int i = 0; i < data.size(); i++) {
        // Menambahkan data ke dalam linked list
        destinationList.push(data[i]);
      }
    }
  }

  /**
   * @brief Menampilkan menu destinasi
   * 
   * @param user 
   * 
   * @return void
   */
  void menu(UserController user) {
    // Mengisi data user dari class UserController
    userData = user;

    // Deklarasi variabel isRunning, choice, index, page, pagination
    bool isRunning = true;
    int choice, index = 1, page = 5, pagination = 5;

    do {
      // Menghapus layar pada terminal
      system("cls");

      // Mencetak data dari pagination
      cout << "Menampilkan list dari " << page - pagination << " - " << page << " data" << endl;

      // Memanggil method showAllNodes pada destination
      // untuk menampilkan semua data destinasi pada linked list
      PaginationStruct result = destinationList.showAllNodes(index, pagination, false);

      // Mencetak garis untuk memisahkan antara data
      cout << endl;

      // Melakukan pengecekan apakah user adalah admin atau tidak
      // Jika user adalah admin maka system akan menampilkan menu admin
      // Jika user bukan admin maka system akan menampilkan menu user
      if (userData.isUserAdmin()) isRunning = adminMenu(&choice, &index, &page, &pagination, result);
      else isRunning = userMenu(&choice, &index, &page, &pagination, result);
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }
};

#endif // DESTINATION_CONTROLLER_HPP
