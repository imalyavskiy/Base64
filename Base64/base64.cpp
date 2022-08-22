#include <cstdint>
#include <string>
#include <vector>
#include <cassert>
#include "base64.h"

namespace base64 {
  static constexpr int8_t chars[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/" };
  std::string encode(const std::vector<int8_t>& data) {
    std::string result;

    size_t dataIndex = 0;
    while(dataIndex < data.size()) {
      uint32_t triplet = 0;

      // fill
      uint8_t tripletSize = 0;
      for (; tripletSize < 3 && dataIndex < data.size(); ++tripletSize, ++dataIndex) {
        const uint32_t shift = (8 * (2 - tripletSize));
        triplet |= (0xFF << shift) & (data[dataIndex] << shift);
      }

      // encode
      const uint8_t charsToPut = 4 - (3 - tripletSize);
      for(uint8_t i = 0; i < charsToPut; ++i) {
        const uint8_t index = (triplet >> (6 * (3 - i))) & 0x3F;
        assert(64 > index);
        result.push_back(chars[index]);
      }

      // pad
      for(uint8_t i = 0; i < 4 - charsToPut; ++i) {
        result.push_back('=');
      }
    }
    return result;
  }

  uint8_t GetIndex(int8_t ch);

  std::vector<int8_t> decode(const std::string& str) {
    std::vector<int8_t> data;
    size_t strIndex = 0;
    while (strIndex < str.size()) {
      uint32_t triplet = 0;

      // fill
      uint8_t items = 0;
      for (int i = 0; i < 4; ++i, ++strIndex) {
        const uint8_t index = GetIndex(str[strIndex]);
        if(index <= 0x3F) {
          triplet |= (index & 0x3F) << 6 * (3 - i);
          items++;
        }
      }

      // decode
      const uint8_t toDecode = 3 - (4 - items);
      for(int i = 0; i < toDecode; ++i)
      {
        auto byte = static_cast<int8_t>(triplet >> 8 * (2 - i));
        data.push_back(byte);
      }
    }
    return data;
  }

  uint8_t GetIndex(int8_t ch)
  {
    for (uint8_t i = 0; i < 64; ++i)
    {
      if (ch == chars[i])
        return i;
    }
    return -1;
  }
}
