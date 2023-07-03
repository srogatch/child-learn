#include "translation.h"
#include <iostream>
#include <random>
#include <functional>
#include <fmt/core.h>

template<class T = std::mt19937_64, std::size_t N = T::state_size * sizeof(typename T::result_type)>
T ProperlySeededRandomEngine () {
    std::random_device source;
    std::random_device::result_type random_data[(N - 1) / sizeof(source()) + 1];
    std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
    std::seed_seq seeds(std::begin(random_data), std::end(random_data));
    return T(seeds);
}

int main() {
  std::mt19937_64 rng = ProperlySeededRandomEngine();
  std::uniform_int_distribution<int> dist(0, 20);
  Translator tr = Translator::Prompt();
  int iSample = 0, nCorrect = 0;
  for(;;iSample++) {
    const int a = dist(rng);
    const int b = dist(rng);
    for(int iAttempt=0; ;) {
      fmt::print("{} + {} = ", a, b);
      std::wstring sum;
      if(!std::getline(std::wcin, sum)) {
        return 0;
      }
      if(sum==L"stat") {
        const int total = (iAttempt == 0) ? iSample : iSample + 1;
        std::string format = tr.Get(MessageId::Stats);
        fmt::print(fmt::runtime(format), total, nCorrect, nCorrect*100.0 / total);
        continue;
      }
      int ans;
      try {
        ans = std::stoi(sum);
      }
      catch(...) {
        continue;
      }
      if(ans == a+b) {
        fmt::print("{}\n", tr.Get(MessageId::Correct));
        if(iAttempt == 0) {
          nCorrect++;
        }
        break;
      }
      fmt::print("{}\n", tr.Get(MessageId::Wrong));
      iAttempt++;
    }
  }
}
