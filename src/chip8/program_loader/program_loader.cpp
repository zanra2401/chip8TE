#include "program_loader.hpp"


PLoader::PLoader() {
}

PLoader::~PLoader() {
  if (bytes != nullptr) delete[] bytes;
}

void PLoader::load_from_file(const char *file_name) {
  std::ifstream ifs;  
  ifs.open(file_name, std::ios::binary | std::ios::ate);
  
  if (!ifs.is_open()) {
      std::cerr << "Error: File ROM '" << file_name << "' tidak ditemukan atau tidak bisa dibuka!" << std::endl;
      std::exit(-1);
  }
  
  file_size = ifs.tellg();
  if (file_size <= 0) {
      std::cerr << "Error: File ROM kosong atau invalid!" << std::endl;
      std::exit(-1);
  }
  ifs.seekg(0);

  // ALOKASI MANUAL: Memesan memori di Heap sebesar file_size
  this->bytes = new uint8_t[file_size];

  // Cara Cepat & Efisien: Baca seluruh isi file sekaligus ke memori heap
  ifs.read(reinterpret_cast<char*>(this->bytes), file_size);
  
  ifs.close();
}

void PLoader::ddebug() {
  std::cout << file_size << " bytes" << std::endl;
  for (int i = 0; i < file_size; i++) {
    printf("%0b ", bytes[i]);
  }
}

int PLoader::get_file_size() {
  return this->file_size;
}

uint8_t *PLoader::get_bytes() {
  return bytes;
}


