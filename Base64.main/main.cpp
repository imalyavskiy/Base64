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
      "���������� (1963 ���) ASCII ���� ����������� ��� ����������� ��������,"
      "���� ������� ���������� � 7 ���(128 ��������; 27 = 128), � ������� ��� "
      "�7(��������� � ����) ������������� ��� �������� ������, ��������� ��� "
      "�������� ������.� ������ ������ ������������ ������ ��������� �����. "
      "������(������ �� 16 ��������) � 6 � 7 (��������� ���������� � 0) ���� "
      "��������������� ��� ����������� ����������.������ �����, ������������ "
      "�� ��� ������� ��� �������� ���� ��� ����������� ��������.\n"
      "� 1965 ���� ���� ������������ ����� �������� ASCII, ������� ��� � �� ���� "
      "������������.��� �� �������������� �����, ����� ���������� IBM 2260 / "
      "2848. ��������� ������������ ���� ������������ � 1967 ����, � ��� "
      "������������ � ��� ������� � ���������� �� ������ ������ ��������� � �������.\n"
      "�� �������� ��������� ���� ��������� �� 256 ��������(28 = 256); ���� ������ "
      "128 �������� �� ����������.ASCII ����� �������������� ��� �������� 8 - ������"
      " ���������, � ������������ ASCII� �������� ASCII � ��������������� 8 - � �����"
      "(��������, ��� - 8)."
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