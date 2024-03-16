#include <string>
#include <cstddef>

class Editor
{
  public:
    Editor();
    // сдвинуть курсор влево
    void Left();
    // сдвинуть курсор вправо
    void Right();
    // вставить символ token
    void Insert(char token);
    // вырезать не более tokens символов, начиная с текущей позиции курсора
    void Cut(size_t tokens = 1);
    // cкопировать не более tokens символов, начиная с текущей позиции курсора
    void Copy(size_t tokens = 1);
    // вставить содержимое буфера в текущую позицию курсора
    void Paste();
    // получить текущее содержимое текстового редактора
    string GetText() const;
};