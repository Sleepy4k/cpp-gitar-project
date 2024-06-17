#pragma once

#ifndef TIME_HELPER_HPP
#define TIME_HELPER_HPP

#include <ctime>

/**
 * Deklarasi namespace Time
 * 
 * Namespace ini berfungsi untuk membantu dalam
 * proses pengolahan waktu
 * 
 * Note : Namespace adalah kumpulan fungsi dan
 *       variabel yang dikelompokkan dalam satu 
 *       wadah, yang dapat digunakan untuk
 *       menghindari konflik nama
 */
namespace Time {
  /**
   * @brief Mengambil waktu saat ini
   * 
   * @return time_t
   */
  static std::time_t getCurrentTime() {
    // Menginisialisasi variabel currentTime dengan waktu saat ini
    // menggunakan fungsi time(0), dimana 0 adalah argumen yang diberikan
    // untuk mendapatkan waktu saat ini
    std::time_t currentTime = time(0);

    // Mengembalikan nilai currentTime
    return currentTime;
  }

  /**
   * @brief Mengkonversi waktu menjadi string dengan format
   *      "DD-MM-YYYY"
   * 
   * @return string
   */
  static std::string getFormattedTime() {
    // Memanggil fungsi getCurrentTime untuk mendapatkan waktu saat ini
    std::time_t currentTime = getCurrentTime();

    // Menginisialisasi variabel timeInfo dengan waktu saat ini
    // menggunakan fungsi dar localtime dengan argumen currentTime
    // yang merupakan waktu saat ini
    std::tm *timeInfo = localtime(&currentTime);

    // Menginisialisasi variabel formatted_date dengan panjang 11
    // Bertipe data char untuk menyimpan hasil format waktu
    // panjang 11 karena format waktu adalah "dd-mm-yyyy\0"
    // 2 karakter untuk tanggal, 2 karakter untuk bulan, 4 karakter untuk tahun
    // dan 1 karakter untuk null terminator
    char formatted_date[11];

    // Menggunakan std::strftime untuk memformat waktu
    // dengan format "dd-mm-yyyy" dan menyimpannya ke dalam formatted_date
    // sizeof(formatted_date) digunakan untuk mengetahui panjang dari formatted_date
    // timeInfo digunakan untuk menyimpan waktu yang akan diformat
    std::strftime(formatted_date, sizeof(formatted_date), "%d-%m-%Y", timeInfo);

    // Mengembalikan nilai result
    return formatted_date;
  }
}

#endif // TIME_HELPER_HPP
