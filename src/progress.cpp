#include "progress.hpp"
#include <format>
#include <iostream>
#include <mutex>
#include <string_view>

Progress::Progress(int chunks) : chunks_(chunks) {
  // One line for chunk
  for (int i = 0; i < chunks_; i++) {
    std::clog << '\n';
  }
  std::clog.flush();
}

void Progress::update(int chunk, std::string_view status) {
  const auto position = chunks_ - chunk;

  const std::scoped_lock lock{mutex_};
  // move `position` up, write, then move back
  std::clog << std::format("\x1b[{}A\r{}\x1b[K\x1b[{}B\r", position, status,
                           position);
  std::clog.flush();
}
