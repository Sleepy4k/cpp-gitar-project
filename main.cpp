//=================================================================================
// Guider for Tour and Recreation (Gitar)
//--------------------------------------------------------------------------------
// Aplikasi ini merupakan aplikasi yang digunakan untuk membantu pengguna
// dalam melakukan perjalanan wisata dan rekreasi. Aplikasi ini memiliki
// beberapa fitur seperti menampilkan destinasi wisata, menambahkan destinasi
// wisata, mengubah destinasi wisata, menghapus destinasi wisata, menampilkan
// paket wisata, menambahkan paket wisata, mengubah paket wisata, menghapus
// paket wisata, autentikasi, dan keluar dari aplikasi.
//--------------------------------------------------------------------------------
// Development Team:
// 1. Apri Pandu Wicaksono (NIM: 2311102081)
// 2. Batsinah Adila Lidyanti (NIM: 2311102092)
// 3. Gumawang Sasongko (NIM: 2311102104)
//--------------------------------------------------------------------------------
// Version: 1.0.0
// Date: 2024-06-01
// License: MIT
// Environment: Console
// OS: Windows
// Language: C++
// Email: sarahpalastrin@gmail.com
//=================================================================================

#include <iostream>

#include "helpers/path.hpp"
#include "helpers/input_data.hpp"
#include "controllers/user_controller.hpp"
#include "controllers/package_controller.hpp"
#include "controllers/comment_controller.hpp"
#include "controllers/destination_controller.hpp"

int main(int argc, char* argv[]) {
  /**
   * Set path untuk file storage
   * 
   * karena kita menggunakan relative path
   * maka kita perlu menentukan path dari file
   * yang akan kita gunakan, berasal dari argv[0]
   * 
   * argv adalah array yang berisi argumen yang
   * diberikan pada program saat dijalankan
   * contoh : ./main arg1 arg2 arg3
   * argv[0] = ./main
   * argv[1] = arg1
   * argv[x] = argx
   */
  Path::setPath(argv[0]);

  /**
   * Import beberapa fungsi dari namespace std
   * 
   * std::cout = untuk menampilkan output ke user
   * std::endl = untuk memberikan baris baru
   * 
   * Note : Kita hanya menggunakan fungsi yang kita butuhkan saja
   */
  using std::cout;
  using std::endl;

  /**
   * Inisialisasi controller
   * 
   * Kita akan membuat object dari class controller
   * yang nantinya akan kita gunakan untuk menghandle
   * proses CRUD data
   */
  UserController userController;
  PackageController packageController;
  CommentController CommentController;
  DestinationController destinationController;

  // Inisiasi data pada controller
  // karena ada masalah pada default constructor nya
  // yang bikin segment fault, jadi kita pake manual aja
  userController.init();
  packageController.init();
  CommentController.init();
  destinationController.init();

  // Deklarasi variabel untuk menyimpan pilihan user
  // dan variabel untuk menentukan apakah program masih berjalan
  int choice, isRunning = 1;

  // Melakukan perulangan do-while
  // sehingga program akan berjalan terlebih dahulu
  // sebelum melakukan pengecekan kondisi
  do {
    system("cls"); // Untuk menghapus layar pada terminal

    cout << "=== Gitar - Guider for Tour and Recreation ===" << endl;
    cout << "| 1. Destinasi Wisata                        |" << endl;
    cout << "| 2. Paket Wisata                            |" << endl;
    cout << "| 3. Authentikasi                            |" << endl;
    cout << "| 4. Keluar                                  |" << endl;
    cout << "==============================================" << endl;

    choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan harus berupa angka! dan diantara 1 sampai 4!",
      1, 4
    );

    // Pilihan menu
    switch (choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method menu pada destinationController
      // untuk menampilkan menu destinasi wisata
      // dengan parameter userController untuk akses
      // data user yang sedang login
      destinationController.menu(userController, CommentController);

      // Menghentikan switch case
      break;
    // Jika user memilih menu 2
    case 2:
      // Memanggil method menu pada packageController
      // untuk menampilkan menu paket wisata
      // dengan parameter userController untuk akses
      // data user yang sedang login
      packageController.menu(userController);

      // Menghentikan switch case
      break;
    // Jika user memilih menu 3
    case 3:
      // Memanggil method menu pada userController
      // untuk menampilkan menu autentikasi
      userController.menu();

      // Menghentikan switch case
      break;
    // Jika user memilih menu 4
    case 4:
      // Menampilkan pesan terima kasih
      cout << "Terima kasih telah menggunakan aplikasi ini" << endl;

      // Mengubah nilai isRunning menjadi 0
      isRunning = 0;

      // Menghentikan switch case
      break;
    // Jika user memilih menu selain 1, 2, 3, 4
    default:
      cout << "Pilihan tidak valid, silahkan coba lagi" << endl;

      // Menghentikan switch case
      break;
    }
    // Melakukan perulangan selama isRunning bernilai 1
    // jika isRunning bernilai 0, maka perulangan akan berhenti
  } while (isRunning);

  return 0;
}
