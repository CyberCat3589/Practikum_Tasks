#include <algorithm>
#include <cassert>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Породы кошек
enum class CatBreed
{
    Bengal,
    Balinese,
    Persian,
    Siamese,
    Siberian,
    Sphynx,
};

// Пол
enum class Gender
{
    Male,
    Female,
};

struct Cat
{
    string name;
    Gender gender;
    CatBreed breed;
    int age;
};

string CatBreedToString(CatBreed breed)
{
    switch (breed)
    {
        case CatBreed::Bengal: return "Bengal"s;
        case CatBreed::Balinese: return "Balinese"s;
        case CatBreed::Persian: return "Persian"s;
        case CatBreed::Siamese: return "Siamese"s;
        case CatBreed::Siberian: return "Siberian";
        case CatBreed::Sphynx: return "Sphynx"s;
        default: throw invalid_argument("Invalid cat breed"s);
    }
}

ostream& operator<<(ostream& out, CatBreed breed)
{
    out << CatBreedToString(breed);
    return out;
}

ostream& operator<<(ostream& out, Gender gender)
{
    out << (gender == Gender::Male ? "male"s : "female"s);
    return out;
}

ostream& operator<<(ostream& out, const Cat& cat)
{
    out << '{' << cat.name << ", "s << cat.gender;
    out << ", breed: "s << cat.breed << ", age:"s << cat.age << '}';
    return out;
}

// Возвращает массив указателей на элементы вектора cats, отсортированные с использованием
// компаратора comp. Компаратор comp - функция, принимающая два аргумента типа const Cat&
// и возвращающая true, если значения упорядочены, и false в ином случае
template <typename Comparator> 
vector<const Cat*> GetSortedCats(const vector<Cat>& cats, const Comparator& comp)
{
    vector<const Cat*> sorted_cat_pointers;

    /*
    Напишите тело функции самостоятельно. Подсказка:
    1) Поместите в массив sorted_cat_pointers адреса объектов из массива cats.
    2) Отсортируйте массив sorted_cat_pointers с помощью переданного компаратора comp.
       Так как comp сравнивает ссылки на объекты, а отсортировать нужно указатели,
       передайте в sort лямбда функцию, принимающую указатели и сравнивающую объекты
       при помощи компаратора comp:
       [comp](const Cat* lhs, const Cat* rhs) {
           return comp(*lhs, *rhs);
       }
    */
    return sorted_cat_pointers;
}

// Выводит в поток out значения объектов, на который ссылаются указатели вектора cat_pointers.
// Пример вывода элементов vector<const Cat*>:
// {{Tom, male, breed: Bengal, age:2}, {Charlie, male, breed: Balinese, age:7}}
void PrintCatPointerValues(const vector<const Cat*>& cat_pointers, ostream& out)
{
    // Напишите функцию самостоятельно
}

int main()
{
    const vector<Cat> cats = {
        {"Tom"s, Gender::Male, CatBreed::Bengal, 2},      {"Leo"s, Gender::Male, CatBreed::Siberian, 3},
        {"Luna"s, Gender::Female, CatBreed::Siamese, 1},  {"Charlie"s, Gender::Male, CatBreed::Balinese, 7},
        {"Ginger"s, Gender::Female, CatBreed::Sphynx, 5}, {"Tom"s, Gender::Male, CatBreed::Siamese, 2},
    };

    {
        auto sorted_cats =
            GetSortedCats(cats, [](const Cat& lhs, const Cat& rhs) { return tie(lhs.breed, lhs.name) < tie(rhs.breed, rhs.name); });

        cout << "Cats sorted by breed and name:"s << endl;
        PrintCatPointerValues(sorted_cats, cout);
        cout << endl;
    }

    {
        auto sorted_cats =
            GetSortedCats(cats, [](const Cat& lhs, const Cat& rhs) { return tie(lhs.gender, lhs.breed) < tie(rhs.gender, rhs.breed); });

        cout << "Cats sorted by gender and breed:"s << endl;
        PrintCatPointerValues(sorted_cats, cout);
        cout << endl;
    }
    return 0;
}