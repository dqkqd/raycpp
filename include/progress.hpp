#pragma once

#include <mutex>
#include <string_view>

class Progress {
public:
  explicit Progress(int chunks);
  // update line at chunk
  void update(int chunk, std::string_view status);

private:
  int chunks_;
  std::mutex mutex_;
};
