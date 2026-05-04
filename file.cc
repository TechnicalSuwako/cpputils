#include "file.hh"

#include <iostream>
#include <fstream>

vector<u8> read_file(const string &filename) {
  std::ifstream file(filename, std::ios::binary | std::ios::ate);
  if (!file) {
    throw std::runtime_error("ファイルを開くに失敗： " + filename);
  }

  const auto size = file.tellg();
  file.seekg(0);
  vector<u8> data(static_cast<size_t>(size));
  if (!file.read(reinterpret_cast<char *>(data.data()), size)) {
    throw std::runtime_error("ファイルの読み込みに失敗。");
  }

  file.close();

  return data;
}