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
    const int pagination = 5;
    int choice = 0, index = 1, page = 5;

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
          cout << "Belum ada data yang tersedia untuk dihapus" << endl;

          // Memanggil method pause pada SYS
          // untuk menjeda layar terminal
          SYS::pause();

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
  void reciept_template(const RecieptStruct &reciept) {
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

    // Meminta user untuk memasukkan id dari struk pembelian
    const std::string id = InputData::getInput(
      "Masukkan ID Struk Pembelian : ",
      "Struk Pembelian tidak boleh kosong! dan tidak boleh ada spasi!"
    );

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Memanggil method get dari hashTable untuk mendapatkan data
    // dari struk pembelian berdasarkan id yang di masukkan user
    const RecieptStruct reciept = recieptList.get(std::stoi(id));

    // Mengecek apakah data yang di cari tidak ada
    // Jika tidak ada maka system akan mencetak pesan data tidak ditemukan
    if (reciept.name.empty()) {
      // Mencetak pesan data tidak ditemukan
      cout << "Belum ada data yang tersedia" << endl;

      // Menghentikan proses
      return;
    }

    // Mengecek apakah data yang di cari ada
    // namun data tersebut bukan untuk user yang sedang login
    // Jika bukan maka system akan mencetak pesan tidak diizinkan
    if (reciept.name != userData.getUsername() && !userData.isUserAdmin()) {
      // Mencetak pesan tidak diizinkan
      cout << "Anda tidak memiliki akses untuk struk ini!" << endl;

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

      // Memanggil method pause pada SYS
      // untuk menjeda layar terminal
      SYS::pause();

      // Menghentikan proses
      return;
    }

    // Deklarasi variabel isRunning, choice, index, page, pagination
    bool isRunning = true;
    const int pagination = 5;
    int choice, index = 1, page = 5;

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

      // Mencetak menu riwayat pembelian
      cout << "Menu Riwayat Pembelian" << endl;
      cout << "===================" << endl;
      cout << "1. Lihat Detail Struk Pembelian" << endl;
      cout << "2. Lanjut ke halaman berikutnya" << endl;
      cout << "3. Kembali ke halaman sebelumnya" << endl;
      cout << "4. Kembali" << endl;
      cout << "===================" << endl;

      // Meminta user untuk memilih menu
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
        // Menampilkan pesan error
        cout << "Pilihan tidak ditemukan!" << endl;

        // Memanggil method pause pada SYS
        // untuk menjeda layar terminal
        SYS::pause();

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
   * @param category Jenis paket wisata yang akan di beli
   * 
   * @return void
   */
  void buy_package(const int &category) {
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

      // Memanggil method pause pada SYS
      // untuk menjeda layar terminal
      SYS::pause();

      // Menghentikan proses
      return;
    }

    // Mencetak garis untuk memisahkan
    cout << "===================" << endl;

    // Memanggil method showNodeData dari linked list
    // untuk menampilkan data paket wisata
    const PackageStruct package = packageList[category].showNodeData<PackageStruct>(true);

    // Mencetak garis untuk memisahkan antara data
    cout << "===================" << endl;

    // Meminta user untuk mengkonfirmasi pembelian
    const char confirm = InputData::getInputChar(
      "Apakah anda yakin ingin membeli paket ini ? (Y/n) : ",
      "Konfirmasi tidak valid! silahkan masukkan y atau N"
    );

    // Mengecek apakah user tidak yakin
    // Jika tidak yakin maka system akan menghentikan proses
    if (tolower(confirm) != 'y') return;

    cout << "Pembelian Berhasil" << endl;
    cout << "===================" << endl;

    // Meminta user untuk memasukkan nomor telepon
    const std::string phone = InputData::getInput(
      "Masukkan Nomor Telepon : ",
      "Nomor Telepon tidak boleh kosong! dan tidak boleh ada spasi!"
    );

    // Deklarasi variabel reciept untuk menyimpan data struk pembelian
    RecieptStruct reciept;

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
   * @param choice variabel untuk menyimpan pilihan user
   * @param index yaitu untuk menyimpan halaman data
   * @param page yaitu untuk menyimpan jumlah data per halaman
   * @param pagination yaitu untuk menyimpan jumlah data per pagination
   * @param category yaitu untuk menyimpan jenis paket wisata
   * 
   * @return void
   */
  void adminMenu(int *choice, int *index, int *page, const int &pagination, const int &category) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    do {
      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Mencetak data dari pagination
      cout << "Menampilkan list Paket " << destinationTypeToString(category + 1) << " dari " << *page - pagination << " - " << *page << " data" << endl;

      // Menginisialisasi variabel result untuk menyimpan data
      // dari linked list berdasarkan pilihan user
      const PaginationStruct result = packageList[category].showAllNodes(*index, pagination, true);

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

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

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
        *page += pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 4
      case 4:
        // Mengecek apakah data sebelumnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.back) break;

        // Jika tidak kosong maka system akan mengurangi index dan page
        *index -= 1;
        *page -= pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih selain 1, 2, 3, 4
      default:
        // Menampilkan pesan error
        cout << "Pilihan tidak ditemukan!" << endl;

        // Memanggil method pause pada SYS
        // untuk menjeda layar terminal
        SYS::pause();

        // Menghentikan pengecekan
        break;
      }
    } while (true);
  }

  /**
   * @brief Menampilkan menu paket wisata untuk user
   * 
   * @param choice variabel untuk menyimpan pilihan user
   * @param index yaitu untuk menyimpan halaman data
   * @param page yaitu untuk menyimpan jumlah data per halaman
   * @param pagination yaitu untuk menyimpan jumlah data per pagination
   * @param category yaitu untuk menyimpan jenis paket wisata
   * 
   * @return void
   */
  void userMenu(int *choice, int *index, int *page, const int &pagination, const int &category) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    do {
      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Mencetak data dari pagination
      cout << "Menampilkan list Paket " << destinationTypeToString(category + 1) << " dari " << *page - pagination << " - " << *page << " data" << endl;

      // Menginisialisasi variabel result untuk menyimpan data
      // dari linked list berdasarkan pilihan user
      const PaginationStruct result = packageList[category].showAllNodes(*index, pagination, true);

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

      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

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
        *page += pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih menu 4
      case 4:
        // Mengecek apakah data sebelumnya kosong
        // Jika kosong maka system akan menghentikan proses
        if (!result.back) break;

        // Jika tidak kosong maka system akan mengurangi index dan page
        *index -= 1;
        *page -= pagination;

        // Menghentikan pengecekan
        break;
      // Jika user memilih selain 1, 2, 3, 4
      default:
        // Menampilkan pesan error
        cout << "Pilihan tidak ditemukan!" << endl;

        // Memanggil method pause pada SYS
        // untuk menjeda layar terminal
        SYS::pause();

        // Menghentikan pengecekan
        break;
      }
    } while (true);
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
    if (FileStorage::Exists(Path::getPath() + PACKAGE_DATA_PATH)) {
      // Membaca data dari file csv
      const std::vector<std::vector<PackageStruct>> result = PackageModel::read();

      // Melakukan perulangan untuk menambahkan data ke dalam linked list
      // berdasarkan data yang sudah di baca dari file csv
      for (int k = 0; k < TOTAL_TRANSPORT_ENUM; k++) {
        // Mengecek apakah data destinasi kosong pada linked list
        // Jika kosong maka system akan membaca data dari file csv
        if (!packageList[k].isEmpty()) continue;

        // Menginisialisasi variabel data untuk menyimpan data
        // dari file csv berdasarkan jenis paket wisata
        const std::vector<PackageStruct> packages = result[k];

        // Melakukan perulangan untuk menambahkan data ke dalam linked list
        // sebanayak data yang sudah di baca dari file csv
        for (PackageStruct package : packages) {
          // Menambahkan data ke dalam linked list
          packageList[k].insertHead(package);
        }
      }
    }
  }

  /**
   * @brief Menampilkan menu paket wisata
   * 
   * @param userController variabel untuk menyimpan data user
   * 
   * @return void
   */
  void menu(const UserController &user) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mengisi data user dari class UserController
    userData = user;

    // Deklarasi variabel isRunning, choice, index, page, pagination
    bool isRunning = true;
    int choice, index, page;
    const int pagination = 5;

    do {
      // Menginisialisasi variabel dengan nilai default
      // sehingga system akan menampilkan data dari pagination
      choice = 0, index = 1, page = 5;

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

      // Meminta user untuk memilih menu
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
      if (userData.isUserAdmin()) adminMenu(&choice, &index, &page, pagination, choice - 1);
      else userMenu(&choice, &index, &page, pagination, choice - 1);
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }
};

#endif // PACKAGE_CONTROLLER_HPP
