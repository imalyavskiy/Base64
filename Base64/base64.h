#ifndef __BASE64_H__
#define __BASE64_H__
namespace base64
{
  /**
   *
   */
  std::string encode(const std::vector<int8_t>& data);

  /**
   *
   */
  std::vector<int8_t> decode(const std::string& str);
}
#endif // __BASE64_H__
