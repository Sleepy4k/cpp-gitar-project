#pragma once

#ifndef ROLE_ENUM_HPP
#define ROLE_ENUM_HPP

/**
 * Deklarasi Enum atau Enumeration Role
 *
 * Yaitu sebuah tipe data yang merepresentasikan
 * integral konstan, yang mana pada kasus ini,
 * kita membuat enum untuk menyimpan data role,
 * yang nantinya kita gunakan untuk autentikasi
 */
enum Role {
  Guest = 1,
  Admin = 2
};

#endif // ROLE_ENUM_HPP
