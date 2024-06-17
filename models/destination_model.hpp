#pragma once

// Path file data destinasi wisata
#ifndef DESTINATION_DATA_PATH
#define DESTINATION_DATA_PATH "/data/destination_data.csv"
#endif

#ifndef DESTINATION_MODEL_HPP
#define DESTINATION_MODEL_HPP

#include "../helpers/path.hpp"
#include "../handlers/data_handler.hpp"
#include "../structs/destination_struct.hpp"

/**
 * Deklarasi namespace DestinationModel
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses CRUD data destinasi wisata
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace DestinationModel {
  /**
   * @brief Membaca data destinasi dari file
   * 
   * @return std::vector<DestinationStruct> 
   */
  std::vector<DestinationStruct> read() {
    // Menggunakan std::ifstream untuk membaca data dari file
    using std::ifstream; // Import library ifstream
    // Menggunakan std::stringstream untuk mengkonversi data ke dalam string
    using std::stringstream; // Import library stringstream

    // Membaca data dari file dengan menggunakan FileStorage::Read
    std::string fileData = FileStorage::Read(Path::getPath() + DESTINATION_DATA_PATH);

    // Inisialisasi variabel line untuk menyimpan data yang di baca
    std::string line;

    // Inisialisasi variabel data untuk menyimpan data yang sudah di baca
    std::vector<DestinationStruct> data;

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

      // Melakukan perulangan untuk membaca data per kata
      while (std::getline(s, word, ',')) {
        // Menyimpan data yang sudah di split ke dalam row
        row.push_back(word);
      }

      // Inisialisasi struct DestinationStruct
      DestinationStruct destinasi;

      // Mengisi data struct DestinationStruct dengan data dari file
      destinasi.name = row[0];
      destinasi.description = row[1];
      destinasi.location = row[2];
      destinasi.work_hours = row[3];
      destinasi.price = std::stoi(row[4]);
      destinasi.person = std::stoi(row[5]);
      destinasi.pengunjung = std::stoi(row[6]);
      destinasi.type = static_cast<DestinationType>(std::stoi(row[7]));

      // Menyimpan data struct DestinationStruct ke dalam data
      data.push_back(destinasi);

      // Mengosongkan row
      row.clear();
    }

    // Mengembalikan data yang sudah di baca
    return data;
  }

  /**
   * @brief Menambahkan data destinasi ke dalam file
   * 
   * @param data DestinationStruct
   */
  void insert(const DestinationStruct &data) {
    std::string dataString = data.name + "," + data.description + "," + data.location + "," + data.work_hours + "," + std::to_string(data.person) + "," + std::to_string(data.price) + "," + std::to_string(data.pengunjung) + "," + std::to_string(data.type);

    // Menyimpan data ke dalam file dengan menggunakan DataHandler::insert
    DataHandler::insert(DESTINATION_DATA_PATH, dataString);
  }

  /**
   * @brief Mencari data destinasi berdasarkan nama
   * 
   * @param name string
   * 
   * @return DestinationStruct 
   */
  DestinationStruct findByName(const std::string &name) {
    // Membaca data dari file dengan menggunakan DestinationModel::read
    const std::vector<DestinationStruct> data = read();

    // Inisialisasi struct DestinationStruct
    DestinationStruct destination;

    // Melakukan perulangan untuk mencari data berdasarkan nama
    for (int i = 0; i < data.size(); i++) {
      // Cek apakah nama yang dicari sama dengan nama pada data
      // Jika tidak sama maka lanjut ke data selanjutnya
      if (data[i].name != name) continue;

      // Jika sama maka simpan data tersebut ke dalam variabel destination
      destination = data[i];

      // Menghentikan perulangan
      break;
    }

    // Mengembalikan data yang sudah di temukan
    return destination;
  }

  /**
   * @brief Mengubah data yang sudah ada di dalam file
   * 
   * @param filename string
   * @param data string
   * @param newData string
   * 
   * @return void
   */
  void update(const DestinationStruct &data, const DestinationStruct &newData) {
    // Merangkap data baru ke dalam string
    std::string newDataString = newData.name + "," + newData.description + "," + newData.location + "," + newData.work_hours + "," + std::to_string(newData.person) + "," + std::to_string(newData.price) + "," + std::to_string(newData.pengunjung) + "," + std::to_string(newData.type);

    // Merangkap data lama ke dalam string
    std::string dataString = data.name + "," + data.description + "," + data.location + "," + data.work_hours + "," + std::to_string(data.person) + "," + std::to_string(data.price) + "," + std::to_string(data.pengunjung) + "," + std::to_string(data.type);

    // Mengubah data yang sudah ada di dalam file dengan menggunakan DataHandler::update
    DataHandler::update(DESTINATION_DATA_PATH, dataString, newDataString);
  }

  /**
   * @brief Menghapus data yang sudah ada di dalam file
   * 
   * @param data string
   * 
   * @return void
   */
  void remove(const DestinationStruct &data) {
    // Merangkap data ke dalam string
    std::string dataString = data.name + "," + data.description + "," + data.location + "," + data.work_hours + "," + std::to_string(data.person) + "," + std::to_string(data.price) + "," + std::to_string(data.pengunjung) + "," + std::to_string(data.type);

    // Menghapus data yang sudah ada di dalam file dengan menggunakan DataHandler::remove
    DataHandler::remove(DESTINATION_DATA_PATH, dataString);
  }
}

#endif // DESTINATION_MODEL_HPP
