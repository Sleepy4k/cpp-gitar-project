#pragma once

// Path file data destinasi wisata
#ifndef PACKAGE_DATA_PATH
#define PACKAGE_DATA_PATH "/data/destination_data.csv"
#endif

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
   * @return vector<std::vector<PackageStruct>>
   */
  std::vector<std::vector<PackageStruct>> read() {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + PACKAGE_DATA_PATH);

    // Inisialisasi random seed
    // untuk menghasilkan angka random yang berbeda
    // setiap kali program dijalankan
    srand(time(0));

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variable length untuk menyimpan jumlah data
    // dalam satu paket destinasi wisata
    int length = (rand() % 4) + 2;

    // Inisialisasi variabel index untuk menyimpan index data
    // Jika index lebih dari length maka index akan di reset
    int index[TOTAL_TRANSPORT_ENUM] = {0, 0, 0}, total[TOTAL_TRANSPORT_ENUM] = {0, 0, 0};

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<std::vector<PackageStruct>> data(TOTAL_TRANSPORT_ENUM), temp(TOTAL_TRANSPORT_ENUM);

    // Inisialisasi variabel row untuk menyimpan data yang sudah di baca
    std::vector<std::string> row;

    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    stringstream ss(fileData);

    // Melakukan perulangan untuk membaca data per baris
    while (std::getline(ss, line, '\n')) {
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
      package.transport = static_cast<PackageTransport>((rand() % 2) + 1);
      package.facility = getListOfFacility(package.transport);

      // Menambahkan data ke dalam variabel data
      temp[std::stoi(row[7]) - 1].push_back(package);

      // Menambah nilai total berdasarkan data type
      total[std::stoi(row[7]) - 1] += 1;

      // Membersihkan data pada row
      row.clear();
    }

    // Melakukan perulangan untuk mengecek semua data
    // Jika ada total data yang lebih dari 0 dan kurang dari length
    // maka data length akan di ubah menjadi total data
    // sehingga mencegah error karena data yang kurang
    for (int i = 0; i < TOTAL_TRANSPORT_ENUM; i++) {
      // Jika total kurang dari 1 atau lebih dari length
      // maka akan di skip
      if (total[i] < 1 || total[i] > length) continue;

      // Jika total lebih dari length maka length akan di ubah
      // menjadi total data
      length = total[i];
    }

    // Melakukan perulangan untuk mengurangi nilai total
    // berdasarkan length yang sudah di tentukan
    // jika total lebih dari 0 maka akan di kurangi
    // dengan total modulus length
    for (int i = 0; i < TOTAL_TRANSPORT_ENUM; i++) {
      // Jika total kurang dari 1 maka akan di skip
      if (total[i] < 1) continue;

      // Mengurangi nilai total berdasarkan hasil modulus
      total[i] -= total[i] % length;
    }

    // Inisialisasi variabel highest untuk menyimpan nilai tertinggi
    // dan variabel inc untuk menyimpan nilai increment
    // serta variabel iter untuk menyimpan nilai iterasi perulangan
    int highest[TOTAL_TRANSPORT_ENUM] = {0, 0, 0}, inc[TOTAL_TRANSPORT_ENUM] = {0, 0, 0}, iter = 0;

    // Melakukan manipulasi data pada temp paket destinasi wisata
    // dengan logika yang sudah di tentukan dibawah
    // jika n = 3 dan l = 9 makan akan terbentuk data seperti ini
    // paket = [0, 3, 6], [1, 4, 7], [2, 5, 8]
    // dan untuk penamaan paket akan diambil dari index 0 pada
    // setiap nama paket seperti ini, Air, Udara, Tanah menjadi AUT
    // dan deskripsi akan di gabungkan dari nama paket
    // dan durasi, harga, jumlah orang, transportasi, fasilitas akan diambil
    // dari data yang sudah di split
    for (int x = 0; x < TOTAL_TRANSPORT_ENUM; x++) {
      // Jika total kurang dari 1 maka akan di skip
      if (temp[x].size() < 1) continue;

      // Ubah nilai iter menjadi 0 pada setiap perulangan
      iter = 0;

      // Melakukan perulangan untuk menggabungkan data
      // berdasarkan length yang sudah di tentukan
      // dan ketika total data kurang dari length
      // maka perulangan akan di hentikan
      while (total[x] > 0) {
        // Inisialisasi variabel package untuk menyimpan data paket
        PackageStruct package;

        // Mengisi data struct dengan nilai default
        // mencegah terjadinya error karena nilai yang kosong
        package.name = "Paket ";
        package.description = "Lokasi wisata yang dikunjungi : ";
        package.people = 0;
        package.price = 0;
        package.duration = (rand() % 3) + 1;
        package.type = static_cast<DestinationType>(x + 1);

        // Mengganti nilai index menjadi 0
        // pada setiap perulangan
        index[x] = 0;

        // Melakukan perulangan untuk menggabungkan data
        // berdasarkan length yang sudah di tentukan
        for (int z = 0; z < length; z++) {
          // Mengecek jika nilai z lebih dari 0 dan kurang dari length
          // jika benar maka nilai index akan di tambah dengan length - 1
          if (z > 0 && z < length) index[x] += length - 1;

          // Mengecek jika total kurang dari length dan iterasi sama dengan 0
          // maka nilai index akan di set menjadi 0
          // menghindari error karena nilai index yang lebih dari total
          // dimana terdapat case jika total data sama dengan length
          // maka kita tidak perlu menambahkan nilai index
          // sehingga menghasilkan data [0, 1, 2, ...]
          if (total[x] <= length && iter == 0) index[x] = 0;

          // Mengecek jika nilai length pangkat 2 lebih dari total
          // maka nilai index akan di set menjadi 0, menghindari error
          // karena nilai index yang lebih dari total data
          // sehingga menghasilkan data [0, 1, 2, ...]
          if (length * length > total[x]) index[x] = 0;

          // Menambahkan data ke dalam variabel package
          package.name += toupper(temp[x][z + index[x] + iter].name[0]);
          package.description += temp[x][z + index[x] + iter].description;
          package.people += temp[x][z + index[x] + iter].people;
          package.price += temp[x][z + index[x] + iter].price;

          // Jika paket transportasi tertinggi dari sebelumnya
          // maka variable highest akan di ganti dengan nilai tersebut
          if (temp[x][z + index[x] + iter].transport > highest[x]) {
            highest[x] = temp[x][z + index[x] + iter].transport;
          }

          // Jika z kurang dari length - 1 maka akan menambahkan koma
          if (z < length - 1) package.description += ", ";
        }

        // Mengubah harga paket dengan mengalikan harga dengan durasi
        package.price = package.price * package.duration;

        // Mengubah data dari integer ke dalam tipe data yang sesuai
        package.transport = static_cast<PackageTransport>(highest[x]);

        // Menambahkan fasilitas berdasarkan transportasi tertinggi
        package.facility = getListOfFacility(highest[x]);

        // Menambahkan data ke dalam variabel data
        data[x].push_back(package);

        // Mengurangi nilai dari variable total
        total[x] -= length;

        // Menambahkan nilai iterasi perulangan
        // karena perulangan sudah mencapai akhir
        // sehingga nilai iterasi akan di tambah
        // sampai nilai total kurang dari 1
        iter++;
      }
    }

    // Mengembalikan data
    return data;
  }
}

#endif // PACKAGE_MODEL_HPP
