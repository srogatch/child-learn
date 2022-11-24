#pragma once

#include <cstdint>
#include <string>
#include <unordered_map>

enum class Language : uint32_t {
  None=0,
  English,
  Russian
};

enum class MessageId : uint32_t {
  None=0,
  Correct,
  Wrong,
  Stats,
};

struct Message {
  MessageId _mid;
  const char* const _eng;
  const char* const _rus;
};

class Translator {
  std::unordered_map<MessageId, std::string> _msgs;

public:
  explicit Translator(const Language lang);
  static Translator Prompt();
  const std::string& Get(const MessageId mid);
};
