#include "translation.h"
#include <iostream>
#include <random>
#include <functional>

template<class T = std::mt19937_64, std::size_t N = T::state_size * sizeof(typename T::result_type)>
auto ProperlySeededRandomEngine () -> typename std::enable_if<N, T>::type {
    std::random_device source;
    std::random_device::result_type random_data[(N - 1) / sizeof(source()) + 1];
    std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
    std::seed_seq seeds(std::begin(random_data), std::end(random_data));
    return T(seeds);
}

int main() {
  std::mt19937_64 rng = ProperlySeededRandomEngine();
  std::uniform_int_distribution<uint32_t> dist(0, 10);
  Translator tr = Translator::Prompt();
  int iSample = 0, nCorrect = 0;
  for(;;iSample++) {
    const uint32_t a = dist(rng);
    const uint32_t b = dist(rng);
    for(int iAttempt=0; ;) {
      std::wcout << a << " + " << b << " = ";
      std::wstring sum;
      if(!std::getline(std::wcin, sum)) {
        if(iAttempt > 0) {
          iSample++;
        }
        std::wcout << std::endl << "Total " << iSample << ", correct " << nCorrect
          << ", percentage=" << nCorrect*100.0 / iSample << std::endl;
        return 0;
      }
      int ans;
      try {
        ans = std::stoi(sum);
      }
      catch(...) {
        continue;
      }
      if(ans == a+b) {
        std::wcout << tr.Get(MessageId::Correct) << std::endl;
        if(iAttempt == 0) {
          nCorrect++;
        }
        break;
      }
      std::wcout << tr.Get(MessageId::Wrong) << std::endl;
      iAttempt++;
    }
  }
}
