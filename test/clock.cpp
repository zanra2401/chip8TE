#include <iostream>
#include <chrono>
#include <thread>

int count_cycle = 0;

void logger() {
  while (true) {
    std::cout << "1 detik: "  << count_cycle << std::endl;
    count_cycle = 0;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

int main() {
  std::thread worker_a(logger);
  double MS_PER_FRAME = 100;
  while (true) {
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 20; i++) {
      std::cout << "\033[48;2;0;0;255m  ";
    }
    auto end = std::chrono::high_resolution_clock::now();
    double elapsed = std::chrono::duration<float, std::milli>(end - start).count();
    count_cycle = count_cycle + 1;

    if (elapsed < MS_PER_FRAME) {
      double sisa = MS_PER_FRAME - elapsed;
      std::cout << "sisa waktu: " << sisa  << std::endl;
      std::this_thread::sleep_for(std::chrono::duration<double, std::milli> (sisa));
    }
  }
}
