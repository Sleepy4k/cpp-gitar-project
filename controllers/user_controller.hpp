#pragma once

#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <vector>
#include <iostream>

#include "../helpers/path.hpp"
#include "../helpers/system.hpp"
#include "../helpers/hashing.hpp"
#include "../enums/role_enum.hpp"
#include "../models/user_model.hpp"
#include "../helpers/input_data.hpp"
#include "../structs/user_struct.hpp"
#include "../helpers/file_storage.hpp"
#include "../handlers/linked_list.hpp"

/**
 * Deklarasi class UserController
 *
 * Class list ini kita gunakan untuk menghandle
 * proses autentikasi user, dimana nantinya
 * kita akan meminta inputan dari user berupa
 * username dan password, lalu kita akan
 * membandingkan data tersebut dengan data
 * yang sudah tersimpan di dalam file
 * user_data.txt
 *
 * Note : Class adalah tipe data yang ditentukan
 *        oleh pengguna untuk menyimpan banyak
 *        fungsi dan data yang disatukan dalam
 *        satu tempat atau wadah
 */
class UserController {
private:
  // Deklarasi variabel yang akan digunakan
  // untuk menyimpan data username dan password
  // dengan tipe data string
  std::string username, password;

  // Deklarasi variabel yang akan digunakan
  // untuk menyimpan data user yang sedang login
  UserStruct currentUser;

  // Deklarasi variabel yang akan digunakan
  // untuk menyimpan data user yang sudah terdaftar
  List<UserStruct> userList;

  /**
   * @brief Method untuk menampilkan form dasar
   * 
   * @return void
   */
  void basic_form() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Cek apakah user sudah login
    // jika sudah, maka tampilkan pesan anda sudah login
    if (isAlreadyLogin()) {
      // Mencetak pesan ke layar terminal
      cout << "Anda sudah masuk sebagai " << currentUser.username << endl;

      // Menghentikan eksekusi kode
      return;
    }

    // Meminta inputan dari user berupa username
    username = InputData::getInput(
      "Masukan nama pengguna : ",
      "Kata sandi tidak boleh kosong serta tidak boleh mengandung spasi"
    );

    // Meminta inputan dari user berupa password
    password = InputData::getInput(
      "Masukan kata sandi : ",
      "Kata sandi tidak boleh kosong serta tidak boleh mengandung spasi"
    );
  }

  /**
   * @brief Method untuk memproses autentikasi user
   * 
   * @return void
   */
  void process_signin() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Memanggil method findNodeData pada userList dengan
    // parameter 2 dan tempUser, lalu menyimpan hasilnya
    // ke dalam variabel result
    const UserStruct result = userList.findNodeData(2, UserStruct { username, password, Guest });

    // Cek apakah username dan password kosong
    // jika kosong, maka tampilkan pesan akun tidak ditemukan
    if (result.username.empty() || result.password.empty()) {
      // Mencetak pesan ke layar terminal
      cout << "Akun tidak ditemukan, silahkan registrasi" << endl;

      // Menghentikan eksekusi kode
      return;
    }

    // Membandingkan password yang diinputkan
    // oleh user dengan password yang sudah tersimpan
    // Jika password tidak sama, maka tampilkan pesan
    // kata sandi salah, silahkan coba lagi
    if (!Hashing::verify(password, result.password)) {
      // Mencetak pesan ke layar terminal
      cout << "Kata sandi salah, silahkan coba lagi" << endl;

      // Menghentikan eksekusi kode
      return;
    }

    // Menyimpan data user yang sedang login
    currentUser = result;

    // Mencetak pesan ke layar terminal
    cout << "Proses autentikasi berhasil, selamat datang " << result.username << endl;
  }

  /**
   * @brief Method untuk memproses registrasi user
   * 
   * @return void
   */
  void process_signup() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Deklarasi variabel tempUser
    // yang akan digunakan untuk menyimpan data user
    // yang sudah terdaftar dan data user yang akan
    // di autentikasi
    UserStruct tempUser = {username, password, Guest};

    // Memanggil method findNodeData pada userList dengan
    // parameter 2 dan tempUser, lalu menyimpan hasilnya
    // ke dalam variabel result
    const UserStruct result = userList.findNodeData(2, tempUser);

    // Cek apakah username dan password kosong
    // jika tidak kosong, maka tampilkan pesan akun sudah ada
    if (!result.username.empty() || !result.password.empty()) {
      // Mencetak pesan ke layar terminal
      cout << "Akun sudah ada, silahkan gunakan akun yang lain" << endl;

      // Menghentikan eksekusi kode
      return;
    }

    // Mengubah password yang diinputkan oleh user
    // menjadi password yang sudah dienkripsi
    tempUser.password = Hashing::encrypt(password);

    // Menambahkan data user yang baru ke dalam userList
    userList.insertHead(tempUser);

    // Menyimpan data user yang baru ke dalam file user_data.csv
    UserModel::insert(tempUser);

    // Menyimpan data user yang sedang login
    currentUser = tempUser;

    // Mencetak pesan ke layar terminal
    cout << "Akun berhasil di buat, silahkan autentikasi akun anda" << endl;
  }

  /**
   * @brief Method untuk menampilkan menu autentikasi
   * 
   * @return void
   */
  void signin() {
    // Memanggil method basic_form untuk menampilkan form dasar
    basic_form();

    // Memanggil method process_signin untuk memproses autentikasi user
    process_signin();

    // Memanggil method pause pada SYS
    // untuk menjeda layar terminal
    SYS::pause();
  }

  /**
   * @brief Method untuk menampilkan menu registrasi
   * 
   * @return void
   */
  void signup() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;
    // Menggunakan std::string
    using std::string;

    // Memanggil method basic_form untuk menampilkan form dasar
    basic_form();

    // Meminta inputan dari user berupa konfirmasi password
    const string password_confirmation = InputData::getInput(
      "Masukan ulang kata sandi : ",
      "Kata sandi tidak boleh kosong serta tidak boleh mengandung spasi"
    );

    // Membandingkan password yang diinputkan
    // oleh user dengan konfirmasi password
    // Jika password tidak sama, maka tampilkan pesan
    // kata sandi tidak sama, silahkan coba lagi
    if (password != password_confirmation) {
      // Mencetak pesan ke layar terminal
      cout << "Kata sandi tidak sama, silahkan coba lagi" << endl;

      // Menghentikan eksekusi kode
      return;
    }

    // Memanggil method process_signup untuk memproses registrasi user
    process_signup();

    // Memanggil method pause pada SYS
    // untuk menjeda layar terminal
    SYS::pause();
  }

  /**
   * @brief Method untuk logout
   * 
   * @return void
   */
  void logout() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Menghapus data user yang sedang login
    currentUser = UserStruct{};

    // Menhapus data username dan password
    username = password = "";

    // Menampilkan pesan ke layar terminal
    cout << "Anda berhasil keluar" << endl;

    // Memanggil method pause pada SYS
    // untuk menjeda layar terminal
    SYS::pause();
  }

  /**
   * @brief Method untuk menampilkan profile user
   * 
   * @return void
   */
  void myProfile() {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mencetak pesan ke layar terminal
    cout << "Profile" << endl;
    cout << "===================" << endl;
    cout << "Username : " << currentUser.username << endl;
    cout << "Role : " << roleToString(currentUser.role) << endl;
    cout << "===================" << endl;

    // Memanggil method pause pada SYS
    // untuk menjeda layar terminal
    SYS::pause();
  }

  /**
   * @brief Method untuk menampilkan menu user
   * 
   * @param choice
   * 
   * @return bool
   */
  bool guestMenu(int *choice) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mencetak pesan ke layar terminal
    cout << "List of User Menu" << endl;
    cout << "===================" << endl;
    cout << "1. Sign In" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Kembali" << endl;
    cout << "===================" << endl;

    // Meminta inputan dari user berupa pilihan menu
    *choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan tidak valid",
      1, 3
    );

    // Jika user memilih menu 3
    if (*choice == 3) return false;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Melakukan pengecekan pilihan user
    switch (*choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method signin untuk autentikasi user
      signin();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Memanggil method signup untuk registrasi user
      signup();

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2
    default:
      // Menampilkan pesan error
      cout << "Pilihan tidak ditemukan!" << endl;

      // Memanggil method pause pada SYS
      // untuk menjeda layar terminal
      SYS::pause();

      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan nilai true
    return true;
  }

  /**
   * @brief Method untuk menampilkan menu user
   * 
   * @param choice
   * 
   * @return bool
   */
  bool userMenu(int *choice) {
    // Menggunakan std::cout
    using std::cout;
    // Menggunakan std::endl
    using std::endl;

    // Mencetak pesan ke layar terminal
    cout << "List of User Menu" << endl;
    cout << "===================" << endl;
    cout << "1. Profile" << endl;
    cout << "2. Logout" << endl;
    cout << "3. Keluar" << endl;
    cout << "===================" << endl;

    // Meminta inputan dari user berupa pilihan menu
    *choice = InputData::getInputIntRange(
      "Pilih menu : ",
      "Pilihan tidak valid",
      1, 3
    );

    // Jika user memilih menu 3
    if (*choice == 3) return false;

    // Memanggil method clear pada SYS
    // untuk membersihkan layar terminal
    SYS::clear();

    // Melakukan pengecekan pilihan user
    switch (*choice) {
    // Jika user memilih menu 1
    case 1:
      // Memanggil method myProfile untuk menampilkan profile user
      myProfile();

      // Menghentikan pengecekan
      break;
    // Jika user memilih menu 2
    case 2:
      // Memanggil method logout untuk keluar dari sistem
      logout();

      // Menghentikan pengecekan
      break;
    // Jika user memilih selain 1, 2
    default:
      // Menampilkan pesan error
      cout << "Pilihan tidak ditemukan!" << endl;

      // Memanggil method pause pada SYS
      // untuk menjeda layar terminal
      SYS::pause();

      // Menghentikan pengecekan
      break;
    }

    // Mengembalikan nilai true
    return true;
  }

public:
  /**
   * @brief Method untuk menginisialisasi data user
   * 
   * @return void
   */
  void init() {
    // Mengecek apakah file user_data.csv tidak ada
    // Jika tidak ada maka system akan membuat file user_data.csv
    // dan menambahkan data destinasi secara default
    if (!FileStorage::Exists(Path::getPath() + USER_DATA_PATH)) {
      // Menambahkan data user secara default
      UserModel::insert(UserStruct{"user", Hashing::encrypt("password"), Guest});
      UserModel::insert(UserStruct{"admin", Hashing::encrypt("password"), Admin});
    }

    // Mengecek apakah data destinasi kosong pada linked list
    // Jika kosong maka system akan membaca data dari file csv
    if (userList.isEmpty()) {
      // Membaca data dari file csv
      const std::vector<UserStruct> users = UserModel::read();

      // Melakukan perulangan untuk menambahkan data ke dalam linked list
      // berdasarkan data yang sudah di baca dari file csv
      for (UserStruct user : users) {
        // Menambahkan data ke dalam linked list
        userList.insertHead(user);
      }
    }
  }

  /**
   * @brief Method untuk mengecek apakah user sudah login
   * 
   * @return bool
   */
  bool isAlreadyLogin() {
    // Cek apakah username dan password kosong
    // Jika kosong, maka system akan mengembalikan nilai false
    return !currentUser.username.empty() && !currentUser.password.empty();
  }

  /**
   * @brief Method untuk mendapatkan username user yang sedang login
   * 
   * @return string
   */
  std::string getUsername() {
    // Memanggil method isAlreadyLogin untuk mengecek apakah user sudah login
    // Jika sudah login, maka system akan mengembalikan username user yang sedang login
    return isAlreadyLogin() ? currentUser.username : "Tamu";
  }

  /**
   * @brief Method untuk mengecek apakah user adalah admin
   * 
   * @return bool
   */
  bool isUserAdmin() {
    // Memanggil method isAlreadyLogin untuk mengecek apakah user sudah login
    const bool isLogged = isAlreadyLogin();

    // Cek apakah user sudah login
    // Jika belum login, maka system akan mengembalikan nilai false
    if (!isLogged) return false;

    // Cek apakah role user adalah admin
    if (currentUser.role == Admin) return true;

    // Mengembalikan nilai false
    return false;
  }

  /**
   * @brief Method untuk menampilkan menu autentikasi
   * 
   * @return void
   */
  void menu() {
    // Deklarasi variabel untuk menyimpan pilihan user
    int choice, isRunning = 1;

    do {
      // Memanggil method clear pada SYS
      // untuk membersihkan layar terminal
      SYS::clear();

      // Cek apakah user sudah login
      // Jika sudah, maka tampilkan pesan anda sudah login
      // Jika belum, maka tampilkan menu user
      if (isAlreadyLogin()) isRunning = userMenu(&choice);
      else isRunning = guestMenu(&choice);
    } while (isRunning); // Melakukan perulangan selama isRunning bernilai true
  }
};

#endif // USER_CONTROLLER_HPP
