#include "translation.h"
#include <exception>
#include <stdexcept>
#include <iostream>
#include <fmt/core.h>

static Message gMessages[] = {
  {MessageId::None, "None", "Ничего"},
  {MessageId::Correct, "Correct", "Правильно"},
  {MessageId::Wrong, "Wrong", "Неправильно"},
  {MessageId::Stats, "Total {}, correct {}: {}%\n", "Всего {}, правильных {}: {}%\n"},
};

Translator::Translator(const Language lang) {
  for(const Message& msg : gMessages) {
    std::string cur;
    switch(lang) {
    case Language::English:
      cur = msg._eng;
      break;
    case Language::Russian:
      cur = msg._rus;
      break;
    default:
      throw std::runtime_error("Unhandled language");
    }
    _msgs[msg._mid] = std::move(cur);
  }
}

const std::string& Translator::Get(const MessageId mid) {
  auto it = _msgs.find(mid);
  if(it == _msgs.end()) {
    throw std::runtime_error("Unhandled message");
  }
  return it->second;
}

Translator Translator::Prompt() {
  std::locale::global (std::locale ("en_US.UTF-8"));
  Language lang = Language::None;
  while(lang == Language::None) {
    fmt::print("{} English\n", uint32_t(Language::English));
    fmt::print("{} Русский\n", uint32_t(Language::Russian));
    std::wstring choice;
    if(!std::getline(std::wcin, choice)) {
      throw std::runtime_error("End of input");
    }
    try {
      lang = Language(std::stoi(choice));
      switch(lang) {
      case Language::English:
      case Language::Russian:
        break;
      default:
        lang = Language::None;
        break;
      }
    } catch(...) {
    }
  }
  return Translator(lang);
}
