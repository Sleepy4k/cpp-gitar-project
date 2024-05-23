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
  List<PackageStruct> packageList[TOTAL_TRANSPORT_ENUM];

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
   * @param category
   * 
   * @return void
   */
  void adminMenu(int *choice, int *index, int *page, int *pagination, int category) {
    while (true) {
      // Mencetak data dari pagination
      cout << "Menampilkan list Paket " << destinationTypeToString(category + 1) << " dari " << *page - *pagination << " - " << *page << " data" << endl;

      // Menginisialisasi variabel result untuk menyimpan data
      // dari linked list berdasarkan pilihan user
      PaginationStruct result = packageList[category].showAllNodes(*index, *pagination, true);

      // Mencetak garis untuk memisahkan antara data
      cout << endl;

      cout << "Menu Paket Wisata" << endl;
      cout << "===================" << endl;
      cout << "1. Lihat Jumlah Penjualan" << endl;
      cout << "2. Lanjut ke halaman berikutnya" << endl;
      cout << "3. Kembali ke halaman sebelumnya" << endl;
      cout << "4. Kembali" << endl;
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
      if (*choice == 4) return;

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
    }
  }

  /**
   * @brief Menampilkan menu paket wisata untuk user
   * 
   * @param choice
   * @param index 
   * @param page 
   * @param pagination 
   * @param category
   * 
   * @return void
   */
  void userMenu(int *choice, int *index, int *page, int *pagination, int category) {
    while (true) {
      // Mencetak data dari pagination
      cout << "Menampilkan list Paket " << destinationTypeToString(category + 1) << " dari " << *page - *pagination << " - " << *page << " data" << endl;

      // Menginisialisasi variabel result untuk menyimpan data
      // dari linked list berdasarkan pilihan user
      PaginationStruct result = packageList[category].showAllNodes(*index, *pagination, true);

      // Mencetak garis untuk memisahkan antara data
      cout << endl;

      cout << "Menu Paket Wisata" << endl;
      cout << "===================" << endl;
      cout << "1. Beli Paket Wisata" << endl;
      cout << "2. Lanjut ke halaman berikutnya" << endl;
      cout << "3. Kembali ke halaman sebelumnya" << endl;
      cout << "4. Kembali" << endl;
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
      if (*choice == 4) break;

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
    }
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
      // Membaca data dari file csv
      std::vector<std::vector<PackageStruct>> result = PackageModel::read();

      // Melakukan perulangan untuk menambahkan data ke dalam linked list
      // berdasarkan data yang sudah di baca dari file csv
      for (int k = 0; k < TOTAL_TRANSPORT_ENUM; k++) {
        // Mengecek apakah data destinasi kosong pada linked list
        // Jika kosong maka system akan membaca data dari file csv
        if (!packageList[k].isEmpty()) continue;

        std::vector<PackageStruct> data = result[k];

        for (int v = 0; v < data.size(); v++) {
          // Menambahkan data ke dalam linked list
          packageList[k].push(data[v]);
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
    int choice, index, page, pagination;

    do {
      choice = 0, index = 1, page = 5, pagination = 5;

      // Menghapus layar pada terminal
      system("cls");

      // Mencetak data dari pagination
      cout << "Menu Paket Wisata" << endl;
      cout << "===================" << endl;
      cout << "1. Lihat Paket Wisata Alam" << endl;
      cout << "2. Lihat Paket Wisata Sejarah" << endl;
      cout << "3. Lihat Paket Wisata Budaya" << endl;
      cout << "4. Keluar" << endl;
      cout << "===================" << endl;
      cout << "Pilihan : ";
      cin >> choice;

      // Menghapus layar pada terminal
      system("cls");

      // Cek apakah pilihan user tidak valid
      // Jika pilhan user kurang dari 1 atau lebih dari 4
      // maka system akan mencetak pesan pilihan tidak valid
      if (choice < 1 || choice > 4) {
        // Mencetak pesan pilihan tidak valid
        cout << "Pilihan tidak valid" << endl;

        // Menunggu user untuk menekan tombol apapun
        system("pause");

        // Mengulangi perulangan dari awal
        continue;
      }

      // Jika user memilih menu 4
      // maka system akan menghentikan perulangan
      if (choice == 4) break;

      // Melakukan pengecekan apakah user adalah admin atau tidak
      // Jika user adalah admin maka system akan menampilkan menu admin
      // Jika user bukan admin maka system akan menampilkan menu user
      if (userData.isUserAdmin()) adminMenu(&choice, &index, &page, &pagination, choice - 1);
      else userMenu(&choice, &index, &page, &pagination, choice - 1);
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }
};

#endif // PACKAGE_CONTROLLER_HPP
