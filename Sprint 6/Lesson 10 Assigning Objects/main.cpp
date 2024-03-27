#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

using namespace std;

// Используйте эту заготовку PtrVector или замените её на свою реализацию
template <typename T> 
class PtrVector
{
  public:
    PtrVector() = default;

    // Создаёт вектор указателей на копии объектов из other
    PtrVector(const PtrVector& other)
    {
        // Резервируем место в vector-е для хранения нужного количества элементов
        // Благодаря этому при push_back не будет выбрасываться исключение
        items_.reserve(other.items_.size());

        try
        {
            for (auto p : other.items_)
            {
                // Копируем объект, если указатель на него ненулевой
                auto p_copy = p ? new T(*p) : nullptr;  // new может выбросить исключение

                // Не выбросит исключение, т. к. в vector память уже зарезервирована
                items_.push_back(p_copy);
            }
        }
        catch (...)
        {
            // удаляем элементы в векторе и перевыбрасываем пойманное исключение
            DeleteItems();
            throw;
        }
    }

    // Деструктор удаляет объекты в куче, на которые ссылаются указатели,
    // в векторе items_
    ~PtrVector()
    {
        DeleteItems();
    }

    // Возвращает ссылку на вектор указателей
    vector<T*>& GetItems() noexcept
    {
        return items_;
    }

    // Возвращает константную ссылку на вектор указателей
    vector<T*> const& GetItems() const noexcept
    {
        return items_;
    }

    PtrVector& operator=(const PtrVector& rhs)
    {
        if(this != &rhs)
        {
            PtrVector rhs_copy = rhs;
            this->GetItems().swap(rhs_copy.GetItems());
        }
        
        return *this;
    }

  private:
    void DeleteItems() noexcept
    {
        for (auto p : items_)
        {
            delete p;
        }
    }

    vector<T*> items_;
};

// Щупальце
class Tentacle
{
  public:
    explicit Tentacle(int id) noexcept : id_(id)
    {
    }

    int GetId() const noexcept
    {
        return id_;
    }

    Tentacle* GetLinkedTentacle() const noexcept
    {
        return linked_tentacle_;
    }
    void LinkTo(Tentacle& tentacle) noexcept
    {
        linked_tentacle_ = &tentacle;
    }
    void Unlink() noexcept
    {
        linked_tentacle_ = nullptr;
    }

  private:
    int id_ = 0;
    Tentacle* linked_tentacle_ = nullptr;
};

// Осьминог
class Octopus
{
  public:
    Octopus() : Octopus(8)
    {
    }

    explicit Octopus(int num_tentacles)
    {
        Tentacle* t = nullptr;
        try
        {
            for (int i = 1; i <= num_tentacles; ++i)
            {
                t = new Tentacle(i);      // Может выбросить исключение bad_alloc
                tentacles_.GetItems().push_back(t);  // Может выбросить исключение bad_alloc

                // Обнуляем указатель на щупальце, которое уже добавили в tentacles_,
                // чтобы не удалить его в обработчике catch повторно
                t = nullptr;
            }
        }
        catch (const std::bad_alloc&)
        {
            // Удаляем щупальце, которое создали, но не добавили в tentacles_
            delete t;
            // Конструктор не смог создать осьминога с восемью щупальцами,
            // поэтому выбрасываем исключение, чтобы сообщить вызывающему коду об ошибке
            // throw без параметров внутри catch выполняет ПЕРЕВЫБРОС пойманного исключения
            throw;
        }
    }

    // Добавляет новое щупальце с идентификатором,
    // равным (количество_щупалец + 1):
    // 1, 2, 3, ...
    // Возвращает ссылку на добавленное щупальце
    Tentacle& AddTentacle()
    {
        Tentacle* new_tentacle = new Tentacle(tentacles_.GetItems().size() + 1);
        tentacles_.GetItems().push_back(new_tentacle);
        return *new_tentacle;
    }

    int GetTentacleCount() const noexcept
    {
        return static_cast<int>(tentacles_.GetItems().size());
    }

    const Tentacle& GetTentacle(size_t index) const
    {
        return *tentacles_.GetItems().at(index);
    }
    Tentacle& GetTentacle(size_t index)
    {
        return *tentacles_.GetItems().at(index);
    }

  private:
    
    // Вектор хранит указатели на щупальца. Сами объекты щупалец находятся в куче
    PtrVector<Tentacle> tentacles_;
};

int main() 
{
    // Проверка присваивания осьминогов
    {
        Octopus octopus1(3);

        // Настраиваем состояние исходного осьминога
        octopus1.GetTentacle(2).LinkTo(octopus1.GetTentacle(1));

        // До присваивания octopus2 имеет своё собственное состояние
        Octopus octopus2(10);

        octopus2 = octopus1;

        // После присваивания осьминогов щупальца копии имеют то же состояние,
        // что и щупальца присваиваемого объекта
        assert(octopus2.GetTentacleCount() == octopus1.GetTentacleCount());
        for (int i = 0; i < octopus2.GetTentacleCount(); ++i) {
            auto& tentacle1 = octopus1.GetTentacle(i);
            auto& tentacle2 = octopus2.GetTentacle(i);
            assert(&tentacle2 != &tentacle1);
            assert(tentacle2.GetId() == tentacle1.GetId());
            assert(tentacle2.GetLinkedTentacle() == tentacle1.GetLinkedTentacle());
        }
    }

    // Проверка самоприсваивания осьминогов
    {
        Octopus octopus(3);

        // Настраиваем состояние осьминога
        octopus.GetTentacle(0).LinkTo(octopus.GetTentacle(1));

        vector<pair<Tentacle*, Tentacle*>> tentacles;
        // Сохраняем информацию о щупальцах осьминога и его копии
        for (int i = 0; i < octopus.GetTentacleCount(); ++i) {
            tentacles.push_back({&octopus.GetTentacle(i), octopus.GetTentacle(i).GetLinkedTentacle()});
        }

        // Выполняем самоприсваивание
        octopus = octopus;

        // После самоприсваивания состояние осьминога не должно измениться
        assert(octopus.GetTentacleCount() == static_cast<int>(tentacles.size()));
        for (int i = 0; i < octopus.GetTentacleCount(); ++i) {
            auto& tentacle_with_link = tentacles.at(i);
            assert(&octopus.GetTentacle(i) == tentacle_with_link.first);
            assert(octopus.GetTentacle(i).GetLinkedTentacle() == tentacle_with_link.second);
        }
    }
}