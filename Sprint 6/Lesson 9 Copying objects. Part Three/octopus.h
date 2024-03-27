#pragma once

// Тут можно подключить scopedptr.h и ptrvector.h,
// если они вам понадобятся.
#include "ptrvector.h"
#include <cstddef>

#include <new>  // Для исключения bad_alloc
#include <vector>

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