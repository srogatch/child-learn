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
};

struct Message {
  MessageId _mid;
  const wchar_t* const _eng;
  const wchar_t* const _rus;
};

class Translator {
  std::unordered_map<MessageId, std::wstring> _msgs;

public:
  explicit Translator(const Language lang);
  static Translator Prompt();
  const std::wstring& Get(const MessageId mid);
};
