#pragma once

#ifndef PACKAGE_MODEL_HPP
#define PACKAGE_MODEL_HPP

#include <ctime>
#include <string>
#include <cstdlib>

#include "../helpers/path.hpp"
#include "../handlers/data_handler.hpp"
#include "../structs/package_struct.hpp"
#include "../enums/destination_type_enum.hpp"
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
  std::vector<PackageStruct> read() {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + PACKAGE_DATA_PATH);

    // Inisialisasi random seed
    // untuk menghasilkan angka random yang berbeda
    // setiap kali program dijalankan
    srand(time(NULL));

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variable length untuk menyimpan jumlah data
    // dalam satu paket destinasi wisata
    const int length = (rand() % 4) + 2;

    // Inisialisasi variabel index untuk menyimpan index data
    // Jika index lebih dari length maka index akan di reset
    int index = 0, total = 0, gap = 0;

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<PackageStruct> data, temp;

    // Inisialisasi variabel row untuk menyimpan data yang sudah di baca
    std::vector<std::string> row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Menghitung total data yang ada pada file
    while (std::getline(ss, line, '\n')) {
      // Jika pada baris tersebut tidak terdapat data "\n" maka akan di skip
      // Jika ada maka akan di tambahkan ke dalam total
      total++;
    }

    // Mengubah nilai gap menjadi total
    gap = total;

    // Mengubah nilai gap menjadi gap dikurangi total modulo length
    // Menghindari data yang tidak lengkap pada paket destinasi wisata
    gap -= total % length;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    // karena ss sudah di gunakan sebelumnya maka kita harus membuat ulang
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

      // Mengisi data struct PackageStruct dengan data dari file
      package.name = row[0];
      package.description = row[0];
      package.duration = 0;
      package.price = std::stoi(row[4]);
      package.people = std::stoi(row[5]);
      package.type = static_cast<DestinationType>(std::stoi(row[7]));
      package.transport = static_cast<PackageTransport>((rand() % 3) + 1);
      package.facility = getListOfFacility(package.transport);

      // Menambahkan data ke dalam variabel data
      temp.push_back(package);

      // Menambah nilai index
      index++;

      // Membersihkan data pada row
      row.clear();

      // Mengurangi nilai dari variable gap
      gap--;
    }

    // Mengganti nilai total menjadi nilai index
    total = index;

    // Inisialisasi variabel highest untuk menyimpan nilai tertinggi
    int highest = 0, inc = 0, each = length;

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
      package.duration = (rand() % 3) + 1;

      // Mengganti nilai index menjadi 0
      index = inc;

      // Mengubah data dari string ke dalam tipe data yang sesuai
      for (int i = 0; i < each; i++) {
        // Menambahkan data ke dalam variabel package
        package.name += toupper(temp[i + index].name[0]);
        package.description += temp[i + index].description;
        package.people += temp[i + index].people;
        package.price += temp[i + index].price;

        // Jika paket transportasi tertinggi dari sebelumnya
        // maka variable highest akan di ganti dengan nilai tersebut
        if (temp[i + index].transport > highest) {
          highest = temp[i + index].transport;
        }

        // Jika i kurang dari each - 1 maka akan menambahkan koma
        if (i < each - 1) package.description += ", ";
      }

      // Mengubah harga paket dengan mengalikan harga dengan durasi
      package.price = package.price * package.duration;

      // Mengubah data dari integer ke dalam tipe data yang sesuai
      package.transport = static_cast<PackageTransport>(highest);

      // Menambahkan fasilitas berdasarkan transportasi tertinggi
      package.facility = getListOfFacility(highest);

      // Menambahkan data ke dalam variabel data
      data.push_back(package);

      // Mengurangi nilai dari variable total
      total -= length;

      // Menambah nilai inc dengan length - 1
      inc += length - 1;
    }

    // Mengembalikan data
    return data;
  }
}

#endif // PACKAGE_MODEL_HPP
