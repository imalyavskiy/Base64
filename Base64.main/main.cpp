#pragma comment(lib, "Base64.lib")

#include <string>
#include <vector>
#include <cassert>
#include <fstream>

#include <base64.h>
int main()
{
  {
    const std::vector<int8_t> data{ 'a' };
    const std::string str = base64::encode(data);
    const std::vector<int8_t> bytes = base64::decode(str);
    assert(data == bytes);
  }

  {
    const std::vector<int8_t> data{ 'a', 'b' };
    const std::string str = base64::encode(data);
    const std::vector<int8_t> bytes = base64::decode(str);
    assert(data == bytes);
  }

  {
    const std::vector<int8_t> data{ 'a', 'b', 'c' };
    const std::string str = base64::encode(data);
    const std::vector<int8_t> bytes = base64::decode(str);
    assert(data == bytes);
  }

  {
    const std::vector<int8_t> data{ 'a', 'b', 'c' };
    const std::string str = base64::encode(data);
    const std::vector<int8_t> bytes = base64::decode(str);
    assert(data == bytes);
  }

  {
    std::string sourceStrData{
      "Изначально (1963 год) ASCII была разработана для кодирования символов,"
      "коды которых помещались в 7 бит(128 символов; 27 = 128), а старший бит "
      "№7(нумерация с нуля) использовался для контроля ошибок, возникших при "
      "передаче данных.В первой версии кодировались только заглавные буквы. "
      "Полосы(группы по 16 символов) № 6 и 7 (нумерация начинается с 0) были "
      "зарезервированы для дальнейшего расширения.Велись споры, использовать "
      "ли эту область для строчных букв или управляющих символов.\n"
      "В 1965 году была подготовлена новая редакция ASCII, которая так и не была "
      "опубликована.Она не использовалась нигде, кроме терминалов IBM 2260 / "
      "2848. Следующая спецификация была опубликована в 1967 году, и все "
      "содержащиеся в ней символы в дальнейшем не меняли своего положения в таблице.\n"
      "Со временем кодировка была расширена до 256 символов(28 = 256); коды первых "
      "128 символов не изменились.ASCII стала восприниматься как половина 8 - битной"
      " кодировки, а «расширенной ASCII» называли ASCII с задействованным 8 - м битом"
      "(например, КОИ - 8)."
    };

    std::vector<int8_t> sourceVecData;
    sourceVecData.insert(sourceVecData.begin(), sourceStrData.begin(), sourceStrData.end());

    const std::string str = base64::encode(sourceVecData);
    std::vector<int8_t> restoredVecData = base64::decode(str);

    std::string restoredStrData;
    restoredStrData.insert(restoredStrData.begin(), restoredVecData.begin(), restoredVecData.end());
    assert(sourceStrData == restoredStrData);
  }

  {
    std::string base64data;

    // read source
    {
      std::fstream image("image.png", std::ios_base::in | std::ios_base::binary);
      assert(image.is_open());

      std::streampos begin = image.tellg();
      image.seekg(0, std::ios_base::end);
      std::streampos end = image.tellg();
      std::streamoff diff = end - begin;
      std::vector<int8_t> data(diff, 0);
      image.seekg(0, std::ios_base::beg);
      std::streamsize read = image.read(reinterpret_cast<char*>(&data[0]), diff).gcount();
      assert(read == diff);
      image.close();

      base64data = base64::encode(data);
    }

    // write encoded
    {
      std::fstream intermediate("image.png.txt", std::ios_base::out);
      assert(intermediate.is_open());
      intermediate.write(&base64data[0], base64data.size());
      intermediate.close();
    }

    // write decoded
    {
      std::vector<int8_t> data = base64::decode(base64data);

      std::fstream image("image1.png", std::ios_base::out | std::ios_base::binary);
      assert(image.is_open());
      std::streampos begin = image.tellp();
      image.write(reinterpret_cast<char*>(&data[0]), data.size());
      std::streampos end = image.tellp();
      std::streamoff size = end - begin;
      assert(size == data.size());
      image.close();
    }
  }
  return 0;
}