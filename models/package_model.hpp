#pragma once

#ifndef PACKAGE_MODEL_HPP
#define PACKAGE_MODEL_HPP

#include <ctime>
#include <string>
#include <cstdlib>

#include "../helpers/path.hpp"
#include "../handlers/data_handler.hpp"
#include "../structs/package_struct.hpp"
#include "../enums/package_transport_enum.hpp"

// Path file data destinasi wisata
static const std::string PACKAGE_DATA_PATH = "/data/destination_data.csv";

/**
 * Deklarasi namespace PackageModel
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses CRUD data paket wisata
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace PackageModel {
  /**
   * @brief Membaca data paket dari file
   * 
   * @return std::vector<PackageStruct>   
   */
  std::vector<PackageStruct> read(int category = 1) {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + PACKAGE_DATA_PATH);

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variable length untuk menyimpan jumlah data
    // dalam satu paket destinasi wisata
    const int length = rand() % 3 + 1;

    // Inisialisasi variabel index untuk menyimpan index data
    // Jika index lebih dari length maka index akan di reset
    int index = 0, total = 0, gap = 0;

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<PackageStruct> data, temp;

    // Inisialisasi variabel row untuk menyimpan data yang sudah di baca
    std::vector<std::string> row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Get total data
    while (std::getline(ss, line, '\n')) {
      total++;
    }

    gap = total;
    gap -= total % length;

    ss = stringstream(fileData);

    // Melakukan perulangan untuk membaca data per baris
    while (std::getline(ss, line, '\n') && gap > 0) {
      // Inisialisasi variabel word untuk menyimpan data yang sudah di split
      std::string word;

      // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
      stringstream s(line);

      // Inisialisasi variabel package untuk menyimpan data paket
      PackageStruct package;

      // Melakukan perulangan untuk membaca data per kata
      while (std::getline(s, word, ',')) {
        // Menambahkan data ke dalam row
        row.push_back(word);
      }

      // Mengubah data dari string ke dalam tipe data yang sesuai
      // Jika data row sama dengan category yang diminta
      if (row[7] == std::to_string(category)) {
        // Mengisi data struct PackageStruct dengan data dari file
        package.name = row[0];
        package.description = row[0];
        package.duration = 0;
        package.price = std::stoi(row[4]);
        package.people = std::stoi(row[5]);
        package.transport = static_cast<PackageTransport>(rand() % 3 + 1);
        package.facility = getListOfFacility(package.transport);

        // Menambahkan data ke dalam variabel data
        temp.push_back(package);

        // Menambah nilai index
        index++;
      }

      // Membersihkan data pada row
      row.clear();

      // Mengurangi nilai dari variable gap
      gap--;
    }

    // Mengganti nilai total menjadi nilai index
    total = index;

    // Inisialisasi variabel highest untuk menyimpan nilai tertinggi
    int highest = 0, inc = 0, each = total / length;

    // Melakukan manipulasi data pada temp paket destinasi wisata
    // dengan logika yang sudah di tentukan dibawah
    // jika n = 3 dan l = 9 makan akan terbentuk data seperti ini
    // paket = [0, 3, 6], [1, 4, 7], [2, 5, 8]
    // dan untuk penamaan paket akan diambil dari index 0 pada
    // setiap nama paket seperti ini, Air, Udara, Tanah menjadi AUT
    // dan deskripsi akan di gabungkan dari nama paket
    // dan durasi, harga, jumlah orang, transportasi, fasilitas akan diambil
    // dari data yang sudah di split
    while (total > 0) {
      // Inisialisasi variabel package untuk menyimpan data paket
      PackageStruct package;
      package.people = 0;
      package.name = "Paket ";
      package.description = "Lokasi wisata yang dikunjungi : ";
      package.duration = rand() % 3 + 1;

      // Mengganti nilai index menjadi 0
      index = 0 + inc;

      // Mengubah data dari string ke dalam tipe data yang sesuai
      for (int i = 0; i <= each; i++) {
        package.name += toupper(temp[i + index].name[0]);
        package.description += temp[i + index].description;
        package.people += temp[i + index].people;
        package.price += temp[i + index].price;
        
        if (temp[i + index].transport > highest) {
          highest = temp[i + index].transport;
        }

        if (i < each) package.description += ", ";
        if (index < each) index += each;
      }

      package.price = package.price * package.duration;
      package.transport = static_cast<PackageTransport>(highest);
      package.facility = getListOfFacility(highest);

      // Menambahkan data ke dalam variabel data
      data.push_back(package);

      // Mengurangi nilai dari variable total
      total -= length;
      
      inc++;
    }

    // Mengembalikan data
    return data;
  }
}

#endif // PACKAGE_MODEL_HPP
