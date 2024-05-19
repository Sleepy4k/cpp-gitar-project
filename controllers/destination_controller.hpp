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
  UserController userData;
  List<DestinationStruct> destinationList;

  DestinationStruct form_destination() {
    int type;
    DestinationStruct data;

    // Clear buffer
    if (cin.peek() == '\n') cin.ignore();

    cout << "Masukan nama destinasi : ";
    getline(cin, data.name);

    cout << "Masukan deskripsi destinasi : ";
    getline(cin, data.description);

    cout << "Masukan lokasi destinasi : ";
    getline(cin, data.location);

    cout << "Masukan jam operasional : ";
    getline(cin, data.work_hours);

    cout << "Masukan jumlah orang per tiket : ";
    cin >> data.person;

    cout << "Masukan harga per tiket : ";
    cin >> data.price;

    cout << "Jenis destinasi" << endl;
    cout << "1. Alam" << endl;
    cout << "2. Sejarah" << endl;
    cout << "3. Budaya" << endl;
    cout << "==================" << endl;
    cout << "Masukan jenis destinasi : ";
    cin >> type;

    switch (type) {
    case 1:
      data.type = Nature;
      break;
    case 2:
      data.type = History;
      break;
    case 3:
      data.type = Culture;
      break;
    default:
      cout << "Pilihan tidak valid, jenis wisata akan menjadi alam secara default" << endl;
      data.type = Nature;
      break;
    }

    return data;
  }

  void insert_destination() {
    int position;

    DestinationStruct data = form_destination();
    destinationList.push(data);
  }

  void show_destination() {
    cout << "Detail Destinasi" << endl;
    cout << "===================" << endl;

    destinationList.showNodeData<DestinationStruct>(true);

    cout << "===================" << endl;
    system("pause");
  }

  void update_destination() {
    DestinationStruct result, newData = form_destination(), data = destinationList.findNodeData<DestinationStruct>(2);

    result = destinationList.update(data, newData);

    if (result.name.empty() || result.description.empty() || result.location.empty()) {
      cout << "Data tidak ditemukan" << endl;
      return;
    }

    cout << "Data " << result.name << " berhasil diubah" << endl;
    system("pause");
  }

  void delete_destination() {
    char confirmation;

    cout << "Apakah kamu yakin mau menghapus? (y/N)" << endl;
    cin >> confirmation;

    if (tolower(confirmation) != 'y') return;

    DestinationStruct data = destinationList.findNodeData<DestinationStruct>(2);

    if (data.name.empty() || data.description.empty() || data.location.empty()) {
      cout << "Data tidak ditemukan" << endl;
      return;
    }

    destinationList.removeByData(data);

    cout << "Data " << data.name << " berhasil dihapus" << endl;
    system("pause");
  }

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

    if (*choice < 1 || *choice > 7) {
      cout << "Pilihan tidak valid" << endl;
      system("pause");
    }

    if (*choice == 7) return false;
    system("cls");

    switch (*choice) {
    case 1:
      show_destination();
      break;
    case 2:
      insert_destination();
      break;
    case 3:
      update_destination();
      break;
    case 4:
      delete_destination();
      break;
    case 5:
      if (!result.next) break;

      *index += 1;
      *page -= *pagination;
      break;
    case 6:
      if (!result.back) break;

      *index -= 1;
      *page -= *pagination;
      break;
    default:
      break;
    }

    return true;
  }

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

    if (*choice < 1 || *choice > 4) {
      cout << "Pilihan tidak valid" << endl;
      system("pause");
    }

    if (*choice == 4) return false;
    system("cls");

    switch (*choice) {
    case 1:
      show_destination();
      break;
    case 2:
      if (!result.next) break;

      *index += 1;
      *page += *pagination;
      break;
    case 3:
      if (!result.back) break;

      *index -= 1;
      *page -= *pagination;
      break;
    default:
      break;
    }

    return true;
  }

public:
  void init() {
    if (!FileStorage::Exists(Path::getPath() + "/data/destination_data.csv")) {
      FileStorage::Create(Path::getPath() + "/data/destination_data.csv");
      DestinationModel::insert(DestinationStruct{"Taman Nasional Bromo Tengger Semeru", "Taman Nasional Bromo Tengger Semeru adalah sebuah kawasan konservasi alam di Jawa Timur", "Probolinggo Jawa Timur", "24 Jam", 1, 50000, Nature});
      DestinationModel::insert(DestinationStruct{"Candi Borobudur", "Candi Borobudur adalah sebuah candi Buddha yang terletak di Magelang Jawa Tengah", "Magelang Jawa Tengah", "06.00 - 17.00", 1, 50000, History});
    }

    if (destinationList.isEmpty()) {
      std::vector<DestinationStruct> data = DestinationModel::read();

      for (int i = 0; i < data.size(); i++) {
        destinationList.push(data[i]);
      }
    }
  }

  void menu(UserController user) {
    userData = user;

    bool isRunning = true;
    int choice, index = 1, page = 5, pagination = 5;

    do {
      system("cls");

      cout << "Menampilkan list dari " << page - pagination << " - " << page << " data" << endl;

      PaginationStruct result = destinationList.showAllNodes(index, pagination, false);

      if (userData.isUserAdmin()) isRunning = adminMenu(&choice, &index, &page, &pagination, result);
      else isRunning = userMenu(&choice, &index, &page, &pagination, result);
    } while (isRunning);
  }
};

#endif // DESTINATION_CONTROLLER_HPP
