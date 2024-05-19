#pragma once

#ifndef USER_CONTROLLER_HPP
#define USER_CONTROLLER_HPP

#include <vector>
#include <string>
#include <iostream>

#include "../helpers/path.hpp"
#include "../helpers/hashing.hpp"
#include "../enums/role_enum.hpp"
#include "../models/user_model.hpp"
#include "../structs/user_struct.hpp"
#include "../helpers/file_storage.hpp"
#include "../handlers/linked_list.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;

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
  string username, password;
  UserStruct currentUser;
  List<UserStruct> userList;

  void basic_form() {
    if (isAlreadyLogin()) {
      cout << "Anda sudah masuk sebagai " << currentUser.username << endl;
      return;
    }

    cout << "Masukan nama pengguna : ";
    cin >> username;

    cout << "Masukan kata sandi : ";
    cin >> password;
  }

  void process_signin() {
    UserStruct result, tempUser = {username, password, Guest};
    result = userList.findNodeData(2, tempUser);

    if (result.username.empty() || result.password.empty()) {
      cout << "Akun tidak ditemukan, silahkan registrasi" << endl;
      return;
    }

    if (!Hashing::verify(password, result.password)) {
      cout << "Kata sandi salah, silahkan coba lagi" << endl;
      return;
    }

    currentUser = result;
    cout << "Proses autentikasi berhasil, selamat datang " << result.username << endl;
  }

  void process_signup() {
    UserStruct result, tempUser = {username, password, Guest};
    result = userList.findNodeData(2, tempUser);

    if (!result.username.empty() || !result.password.empty()) {
      cout << "Akun sudah ada, silahkan gunakan akun yang lain" << endl;
      return;
    }

    tempUser.password = Hashing::encrypt(password);
    userList.push(tempUser);
    UserModel::insert(tempUser);
    currentUser = tempUser;

    cout << "Akun berhasil di buat, silahkan autentikasi akun anda" << endl;
  }

  void signin() {
    basic_form();
    process_signin();
    system("pause");
  }

  void signup() {
    basic_form();

    string password_confirmation;

    cout << "Masukan ulang kata sandi : ";
    cin >> password_confirmation;

    if (password != password_confirmation) {
      cout << "Kata sandi tidak sama, silahkan coba lagi" << endl;
      return;
    }

    process_signup();
    system("pause");
  }

  void logout() {
    currentUser = UserStruct{};
    cout << "Anda berhasil keluar" << endl;
    system("pause");
  }

  bool guestMenu(int *choice) {
    cout << "List of User Menu" << endl;
    cout << "===================" << endl;
    cout << "1. Sign In" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Kembali" << endl;
    cout << "===================" << endl;
    cout << "Pilih menu : ";
    cin >> *choice;

    if (*choice < 1 || *choice > 3) {
      cout << "Pilihan tidak valid" << endl;
      system("pause");
    }

    if (*choice == 3) return false;
    system("cls");

    switch (*choice) {
    case 1:
      signin();
      break;
    case 2:
      signup();
      break;
    default:
      break;
    }

    return true;
  }

  bool userMenu(int *choice) {
    cout << "List of User Menu" << endl;
    cout << "===================" << endl;
    cout << "1. Logout" << endl;
    cout << "2. Keluar" << endl;
    cout << "===================" << endl;
    cout << "Pilih menu : ";
    cin >> *choice;

    if (*choice < 1 || *choice > 2) {
      cout << "Pilihan tidak valid" << endl;
      system("pause");
    }

    if (*choice == 2) return false;
    system("cls");

    switch (*choice) {
    case 1:
      currentUser = UserStruct{};
      cout << "Anda berhasil keluar" << endl;
      system("pause");
      break;
    default:
      break;
    }

    return true;
  }

public:
  void init() {
    if (!FileStorage::Exists(Path::getPath() + "/data/user_data.csv")) {
      UserModel::insert(UserStruct{"user", Hashing::encrypt("password"), Guest});
      UserModel::insert(UserStruct{"admin", Hashing::encrypt("password"), Admin});
    }

    if (userList.isEmpty()) {
      std::vector<UserStruct> data = UserModel::read();

      for (int i = 0; i < data.size(); i++) {
        userList.push(data[i]);
      }
    }
  }

  bool isAlreadyLogin() {
    if (currentUser.username.empty() || currentUser.password.empty())
      return false;

    return true;
  }

  bool isUserAdmin() {
    const bool isLogged = isAlreadyLogin();

    if (!isLogged) return false;
    if (currentUser.role == Admin) return true;

    return false;
  }

  void menu() {
    int choice, isRunning = 1;

    do {
      system("cls");

      if (isAlreadyLogin()) isRunning = userMenu(&choice);
      else isRunning = guestMenu(&choice);
    } while (isRunning);
  }
};

#endif // USER_CONTROLLER_HPP
