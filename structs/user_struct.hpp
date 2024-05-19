#pragma once

#ifndef USER_STRUCT_HPP
#define USER_STRUCT_HPP

#include <string>

#include "../enums/role_enum.hpp"

/**
 * Deklarasi struct User
 *
 * Struct user ini akan kita gunakan untuk
 * merapihkan data user pada autentikasi,
 * untuk field pada struct yaitu :
 * - username = untuk menyimpan nama user
 * - password = untuk menyimpan kata sandi
 * - role     = untuk menyimpan privilege user
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
struct UserStruct {
  std::string username, password;
  Role role;
};

#endif // USER_STRUCT_HPP
