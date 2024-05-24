#pragma once

#ifndef TIME_HELPER_HPP
#define TIME_HELPER_HPP

#include <ctime>
#include <string>

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
  std::time_t getCurrentTime() {
    // Menginisialisasi variabel currentTime dengan waktu saat ini
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
  std::string getFormattedTime() {
    // Memanggil fungsi getCurrentTime untuk mendapatkan waktu saat ini
    std::time_t currentTime = getCurrentTime();

    // Menginisialisasi variabel timeInfo dengan waktu saat ini
    std::tm *timeInfo = localtime(&currentTime);

    char formatted_date[11]; // Room for "dd-mm-yyyy\0"

    std::strftime(formatted_date, sizeof(formatted_date), "%d-%m-%Y", timeInfo);

    // Mengembalikan nilai result
    return formatted_date;
  }
}

#endif // TIME_HELPER_HPP
