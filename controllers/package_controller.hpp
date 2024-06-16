#pragma once

#ifndef PACKAGE_CONTROLLER_HPP
#define PACKAGE_CONTROLLER_HPP

#include <iostream>

#include "user_controller.hpp"
#include "../helpers/path.hpp"
#include "../helpers/time.hpp"
#include "../helpers/parse.hpp"
#include "../helpers/system.hpp"
#include "../helpers/input_data.hpp"
#include "../handlers/queue_list.hpp"
#include "../handlers/linked_list.hpp"
#include "../helpers/file_storage.hpp"
#include "../models/package_model.hpp"
#include "../structs/package_struct.hpp"
#include "../structs/reciept_struct.hpp"
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
  // Inisialisasi variabel userData untuk menyimpan data user
  // dari class UserController
  UserController userData;

  // Inisialisasi variabel packageList untuk menyimpan data paket destinasi
  // dari class LinkedList dengan tipe data PackageStruct
  List<PackageStruct> packageList[TOTAL_TRANSPORT_ENUM];

  // Inisialisasi variabel hashTable untuk menyimpan data struk pembelian
  // dari class HashTable dengan tipe data RecieptStruct
  Queue<RecieptStruct> recieptList;

  /**
   * @brief Menampilkan laporan penjualan paket wisata
   * 
   * @return void
   */
  void show_report() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Deklarasi variabel isRunning, choice, index, page, pagination
    char confirm;
    bool isRunning = true;
    int choice, index = 1, page = 5, pagination = 5;

    do {
      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Mencetak data dari pagination
      cout << "Menampilkan list data penjualan dari " << page - pagination << " - " << page << " data" << endl;

      // Menginisialisasi variabel result untuk menyimpan data
      // dari hash table berdasarkan pilihan user
      PaginationStruct result = recieptList.showAll(index, pagination, true, userData.getUsername(), true);

      // Mencetak garis untuk memisahkan antara data
      cout << endl;

      cout << "Menu Laporan Penjualan" << endl;
      cout << "===================" << endl;
      cout << "1. Hapus Data Penjualan" << endl;
      cout << "2. Lanjut ke halaman berikutnya" << endl;
      cout << "3. Kembali ke halaman sebelumnya" << endl;
      cout << "4. Kembali" << endl;
      cout << "===================" << endl;

      choice = InputData::getInputIntRange(
        "Pilihan menu : ",
        "Pilihan harus berupa angka! dan diantara 1 sampai 3!",
        1, 4
      );

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Melakukan pengecekan pilihan user
      switch (choice) {
      // Jika user memilih menu 1
      case 1:
        // Mengecek apakah data kosong
        // Jika kosong maka system akan menghentikan proses
        if (recieptList.isEmpty()) {
          // Mencetak pesan data tidak ditemukan
          cout << "Data tidak ditemukan" << endl;

          // Menghentikan pengecekan
          break;
        }

        // Memanggil method reciept_template untuk mencetak struk pembelian
        reciept_template(recieptList.get(0));

        // Meminta user untuk mengkonfirmasi penghapusan data
        confirm = InputData::getInputChar(
          "Apakah anda yakin ingin menghapus data ini ? (Y/n) : ",
          "Konfirmasi tidak valid! silahkan masukkan y atau N"
        );

        // Mengecek apakah user tidak yakin
        // Jika tidak yakin maka system akan menghentikan proses
        if (tolower(confirm) != 'y') break;

        // Memanggil method dequeue dari hashTable
        // untuk menghapus data struk pembelian terakhir
        recieptList.dequeue();

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 2
      case 2:
        // Mengecek apakah data selanjutnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.next) break;

        // Jika tidak kosong maka system akan menambahkan index dan page
        index += 1;
        page += pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 3
      case 3:
        // Mengecek apakah data sebelumnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.back) break;

        // Jika tidak kosong maka system akan mengurangi index dan page
        index -= 1;
        page -= pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu $
      case 4:
        // Mengubah nilai isRunning menjadi false
        isRunning = false;

        // Menghentikan pengecekan
        break;
      // Jika user memilih selain 1, 2, 3, $
      default:
        // Menghentikan pengecekan
        break;
      }
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }

  /**
   * @brief Mencetak struk pembelian paket wisata
   * 
   * @param reciept Nilai dari struct RecieptStruct
   * 
   * @return void
   */
  void reciept_template(RecieptStruct reciept) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mencetak struk pembelian
    cout << "Struk Pembelian" << endl;
    cout << "===================" << endl;
    cout << "Nama           : " << reciept.name << endl;
    cout << "Telepon        : " << reciept.phone << endl;
    cout << "Paket          : " << reciept.package << endl;
    cout << "Tanggal        : " << reciept.date << endl;
    cout << "Durasi         : " << reciept.duration << " hari" << endl;
    cout << "Harga          : Rp. " << Parse::intToCurrencyFormat(reciept.price) << endl;
    cout << "Jumlah         : " << reciept.people << " orang" << endl;
    cout << "===================" << endl;
  }

  /**
   * @brief Menampilkan struk pembelian paket wisata
   * 
   * @return void
   */
  void show_reciept() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mengecek apakah user sudah login atau belum
    // Jika belum maka system akan mencetak pesan
    // silahkan login terlebih dahulu
    if (!userData.isAlreadyLogin()) {
      // Mencetak pesan silahkan login terlebih dahulu
      cout << "Silahkan login terlebih dahulu" << endl;

      // Menghentikan proses
      return;
    }

    // Deklarasi variabel id untuk menyimpan id dari struk pembelian
    std::string id;

    // Meminta user untuk memasukkan id dari struk pembelian
    id = InputData::getInput(
      "Masukkan ID Struk Pembelian : ",
      "Struk Pembelian tidak boleh kosong! dan tidak boleh ada spasi!"
    );

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Memanggil method get dari hashTable untuk mendapatkan data
    // dari struk pembelian berdasarkan id yang di masukkan user
    RecieptStruct reciept = recieptList.get(std::stoi(id));

    // Mengecek apakah data yang di cari tidak ada
    // Jika tidak ada maka system akan mencetak pesan data tidak ditemukan
    if (reciept.name.empty()) {
      // Mencetak pesan data tidak ditemukan
      cout << "Data tidak ditemukan" << endl;

      // Menghentikan proses
      return;
    }

    // Mengecek apakah data yang di cari ada
    // namun data tersebut bukan untuk user yang sedang login
    // Jika bukan maka system akan mencetak pesan tidak diizinkan
    if (reciept.name != userData.getUsername() && !userData.isUserAdmin()) {
      // Mencetak pesan tidak diizinkan
      cout << "Tidak diizinkan" << endl;

      // Menghentikan proses
      return;
    }

    // Memanggil method reciept_template untuk mencetak struk pembelian
    reciept_template(reciept);
  }

  /**
   * @brief Menampilkan riwayat pembelian paket wisata
   * 
   * @return void
   */
  void show_history() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mengecek apakah user sudah login atau belum
    // Jika belum maka system akan mencetak pesan
    // silahkan login terlebih dahulu
    if (!userData.isAlreadyLogin()) {
      // Mencetak pesan silahkan login terlebih dahulu
      cout << "Silahkan login terlebih dahulu" << endl;

      // Menghentikan proses
      return;
    }

    // Deklarasi variabel isRunning, choice, index, page, pagination
    bool isRunning = true;
    int choice, index = 1, page = 5, pagination = 5;

    do {
      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Mencetak data dari pagination
      cout << "Menampilkan list data pembelian dari " << page - pagination << " - " << page << " data" << endl;

      // Menginisialisasi variabel result untuk menyimpan data
      // dari hash table berdasarkan pilihan user
      PaginationStruct result = recieptList.showAll(index, pagination, false, userData.getUsername(), false);

      // Mencetak garis untuk memisahkan antara data
      cout << endl;

      cout << "Menu Riwayat Pembelian" << endl;
      cout << "===================" << endl;
      cout << "1. Lihat Detail Struk Pembelian" << endl;
      cout << "2. Lanjut ke halaman berikutnya" << endl;
      cout << "3. Kembali ke halaman sebelumnya" << endl;
      cout << "4. Kembali" << endl;
      cout << "===================" << endl;

      choice = InputData::getInputIntRange(
        "Pilihan menu : ",
        "Pilihan harus berupa angka! dan diantara 1 sampai 4!",
        1, 4
      );

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      if (choice != 1) SYS::clear();

      // Melakukan pengecekan pilihan user
      switch (choice) {
      // Jika user memilih menu 1
      case 1:
        // Memanggil method show_reciept
        // untuk menampilkan struk pembelian
        show_reciept();

        // Memanggil method pause pada SYS
        // untuk menjeda layar terminal
        SYS::pause();

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 2
      case 2:
        // Mengecek apakah data selanjutnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.next) break;

        // Jika tidak kosong maka system akan menambahkan index dan page
        index += 1;
        page += pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 3
      case 3:
        // Mengecek apakah data sebelumnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.back) break;

        // Jika tidak kosong maka system akan mengurangi index dan page
        index -= 1;
        page -= pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 4
      case 4:
        // Mengubah nilai isRunning menjadi false
        isRunning = false;

        // Menghentikan pengecekan
        break;
      // Jika user memilih selain 1, 2, 3, 4
      default:
        // Menghentikan pengecekan
        break;
      }

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear(); 
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }

  /**
   * @brief Membeli paket wisata
   * 
   * @param category
   * 
   * @return void
   */
  void buy_package(int category) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mengecek apakah user sudah login atau belum
    // Jika belum maka system akan mencetak pesan
    // silahkan login terlebih dahulu
    if (!userData.isAlreadyLogin()) {
      // Mencetak pesan silahkan login terlebih dahulu
      cout << "Silahkan login terlebih dahulu" << endl;

      // Menghentikan proses
      return;
    }

    // Deklarasi variabel package untuk menyimpan data paket wisata
    PackageStruct package;

    // Mencetak garis untuk memisahkan
    cout << "===================" << endl;

    // Memanggil method showNodeData dari linked list
    // untuk menampilkan data paket wisata
    package = packageList[category].showNodeData<PackageStruct>(true);

    // Mencetak garis untuk memisahkan antara data
    cout << "===================" << endl;

    // Deklarasi variabel confirm untuk menyimpan konfirmasi
    char confirm;

    // Meminta user untuk mengkonfirmasi pembelian
    confirm = InputData::getInputChar(
      "Apakah anda yakin ingin membeli paket ini ? (Y/n) : ",
      "Konfirmasi tidak valid! silahkan masukkan y atau N"
    );

    // Mengecek apakah user tidak yakin
    // Jika tidak yakin maka system akan menghentikan proses
    if (tolower(confirm) != 'y') return;

    cout << "Pembelian Berhasil" << endl;
    cout << "===================" << endl;

    // Deklarasi variabel reciept untuk menyimpan data struk pembelian
    RecieptStruct reciept;

    // Deklarasi variable phone untuk menyimpan nomor telepon
    std::string phone;

    // Meminta user untuk memasukkan nomor telepon
    phone = InputData::getInput(
      "Masukkan Nomor Telepon : ",
      "Nomor Telepon tidak boleh kosong! dan tidak boleh ada spasi!"
    );

    // Memasukkan data ke dalam variabel reciept
    reciept.name = userData.getUsername();
    reciept.phone = "62" + phone;
    reciept.package = package.name;
    reciept.date = Time::getFormattedTime();
    reciept.duration = package.duration;
    reciept.price = package.price;
    reciept.people = package.people;

    // Memanggil method insert dari hashTable
    // untuk menyimpan data struk pembelian
    recieptList.enqueue(reciept);

    // Memanggil method reciept_template untuk mencetak struk pembelian
    reciept_template(reciept);

    // Memanggil method pause pada SYS
    // untuk menjeda layar terminal
    SYS::pause();
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
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

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
      cout << "1. Lihat Laporan Penjualan" << endl;
      cout << "2. Mencari Data Penjualan" << endl;
      cout << "3. Lanjut ke halaman berikutnya" << endl;
      cout << "4. Kembali ke halaman sebelumnya" << endl;
      cout << "5. Kembali" << endl;
      cout << "===================" << endl;

      *choice = InputData::getInputIntRange(
        "Pilihan : ",
        "Pilihan harus berupa angka! dan diantara 1 sampai 5!",
        1, 5
      );

      // Jika user memilih menu 4
      if (*choice == 5) return;

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
        // Memanggil method show_reciept
        // untuk menampilkan riwayat pembelian
        show_reciept();

        // Memanggil method pause pada SYS
        // untuk menjeda layar terminal
        SYS::pause();

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 3
      case 3:
        // Mengecek apakah data selanjutnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.next) break;

        // Jika tidak kosong maka system akan menambahkan index dan page
        *index += 1;
        *page += *pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 4
      case 4:
        // Mengecek apakah data sebelumnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.back) break;

        // Jika tidak kosong maka system akan mengurangi index dan page
        *index -= 1;
        *page -= *pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih selain 1, 2, 3, 4
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
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

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
      cout << "2. Lihat Struk Pembelian" << endl;
      cout << "3. Lanjut ke halaman berikutnya" << endl;
      cout << "4. Kembali ke halaman sebelumnya" << endl;
      cout << "5. Kembali" << endl;
      cout << "===================" << endl;

      *choice = InputData::getInputIntRange(
        "Pilihan : ",
        "Pilihan harus berupa angka! dan diantara 1 sampai 5!",
        1, 5
      );

      // Jika user memilih menu 5
      if (*choice == 5) break;

      // Melakukan pengecekan pilihan user
      switch (*choice) {
      // Jika user memilih menu 1
      case 1:
        // Memanggil method buy_package
        // untuk membeli paket wisata
        buy_package(category);

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 2
      case 2:
        // Memanggil method show_history
        // untuk menampilkan riwayat struk pembelian
        show_history();

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 3
      case 3:
        // Mengecek apakah data selanjutnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.next) break;

        // Jika tidak kosong maka system akan menambahkan index dan page
        *index += 1;
        *page += *pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 4
      case 4:
        // Mengecek apakah data sebelumnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.back) break;

        // Jika tidak kosong maka system akan mengurangi index dan page
        *index -= 1;
        *page -= *pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih selain 1, 2, 3, 4
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
          packageList[k].insertHead(data[v]);
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
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mengisi data user dari class UserController
    userData = user;

    // Deklarasi variabel isRunning, choice, index, page, pagination
    bool isRunning = true;
    int choice, index, page, pagination;

    do {
      choice = 0, index = 1, page = 5, pagination = 5;

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Mencetak data dari pagination
      cout << "Menu Paket Wisata" << endl;
      cout << "===================" << endl;
      cout << "1. Lihat Paket Wisata Alam" << endl;
      cout << "2. Lihat Paket Wisata Sejarah" << endl;
      cout << "3. Lihat Paket Wisata Budaya" << endl;
      cout << "4. Keluar" << endl;
      cout << "===================" << endl;

      choice = InputData::getInputIntRange(
        "Pilih menu : ",
        "Pilihan harus berupa angka! dan diantara 1 sampai 4!",
        1, 4
      );

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

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
