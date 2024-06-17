#pragma once

#ifndef COMMENT_STRUCT_HPP
#define COMMENT_STRUCT_HPP

/**
 * Deklarasi struct Comment
 *
 * Struct comment ini akan kita gunakan
 * untuk merapihkan data komentar,
 * untuk field pada struct yaitu :
 * - destination_name = untuk menyimpan nama destinasi
 * - username         = untuk menyimpan username
 * - comment          = untuk menyimpan komentar
 * - rating           = untuk menyimpan rating
 *
 * Note : Struct adalah tipe data yang dapat
 *        menyimpan beberapa tipe data dan
 *        dapat digunakan untuk membuat object
 */
struct CommentStruct {
  std::string destination_name, username, comment;
  int rating;
};

#endif // COMMENT_STRUCT_HPP
