#pragma once

#ifndef PACKAGE_CONTROLLER_HPP
#define PACKAGE_CONTROLLER_HPP

#include <string>
#include <iostream>

#include "user_controller.hpp"
#include "../helpers/path.hpp"
#include "../handlers/linked_list.hpp"
#include "../helpers/file_storage.hpp"
#include "../models/package_model.hpp"
#include "../structs/package_struct.hpp"
#include "../structs/pagination_struct.hpp"
#include "../enums/package_transport_enum.hpp"

/**
 * Deklarasi class PackageController
 *
 * Class list ini kita gunakan untuk menghandle
 * semua proses yang berhubungan dengan paket
 * destinasi wisata
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
class PackageController {
private:
  // Insialisasi variable selledPackage untuk menyimpan data
  // paket yang sudah terjual
  int selledPackage;

  // Inisialisasi variabel userData untuk menyimpan data user
  // dari class UserController
  UserController userData;

  // Inisialisasi variabel packageList untuk menyimpan data paket destinasi
  // dari class LinkedList dengan tipe data PackageStruct
  List<PackageStruct> packageList;

  /**
   * @brief Menampilkan laporan penjualan paket wisata
   * 
   * @return void
   */
  void show_report() {

  }

  /**
   * @brief Membeli paket wisata
   * 
   * @return void
   */
  void buy_package() {

  }

  /**
   * @brief Menampilkan menu paket wisata untuk admin
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
    cout << "Menu Paket Wisata" << endl;
    cout << "===================" << endl;
    cout << "1. Lihat Jumlah Penjualan" << endl;
    cout << "2. Lanjut ke halaman berikutnya" << endl;
    cout << "3. Kembali ke halaman sebelumnya" << endl;
    cout << "4. Keluar" << endl;
    cout << "===================" << endl;
    cout << "Pilihan : ";
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
      // Memanggil method show_report
      // untuk menampilkan laporan penjualan
      show_report();

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

  /**
   * @brief Menampilkan menu paket wisata untuk user
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
    cout << "Menu Paket Wisata" << endl;
    cout << "===================" << endl;
    cout << "1. Beli Paket Wisata" << endl;
    cout << "2. Lanjut ke halaman berikutnya" << endl;
    cout << "3. Kembali ke halaman sebelumnya" << endl;
    cout << "4. Keluar" << endl;
    cout << "===================" << endl;
    cout << "Pilihan : ";
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
      // Memanggil method buy_package
      // untuk membeli paket wisata
      buy_package();

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
   * @brief Inisialisasi data paket wisata
   * 
   * @return void
   */
  void init() {
    // Mengecek apakah file destination_data.csv ada
    // Jika ada maka system akan membaca file tersebut
    // dan membuat data package wisata secara otomatis
    if (FileStorage::Exists(Path::getPath() + "/data/destination_data.csv")) {
      // Mengecek apakah data destinasi kosong pada linked list
      // Jika kosong maka system akan membaca data dari file csv
      if (packageList.isEmpty()) {
        // Membaca data dari file csv
        std::vector<PackageStruct> data = PackageModel::read();

        // Melakukan perulangan untuk menambahkan data ke dalam linked list
        // berdasarkan data yang sudah di baca dari file csv
        for (int i = 0; i < data.size(); i++) {
          // Menambahkan data ke dalam linked list
          packageList.push(data[i]);
        }
      }
    }
  }

  /**
   * @brief Menampilkan menu paket wisata
   * 
   * @param userController 
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

      // Memanggil method showAllNodes pada package wisata
      // untuk menampilkan semua data paket pada linked list
      PaginationStruct result = packageList.showAllNodes(index, pagination, false);

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

#endif // PACKAGE_CONTROLLER_HPP
