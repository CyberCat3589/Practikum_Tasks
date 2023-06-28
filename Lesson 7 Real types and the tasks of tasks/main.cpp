#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return person_info_.at(person);
    }

    TaskStatus GetNextStatus(const TaskStatus status)
    {
        TaskStatus current_status = TaskStatus::NEW;
        switch(status)
        {
            case TaskStatus::NEW:
                current_status = TaskStatus::IN_PROGRESS;
                break;
            
            case TaskStatus::IN_PROGRESS:
                current_status = TaskStatus::TESTING;
                break;

            case TaskStatus::TESTING:
                current_status = TaskStatus::DONE;
                break;
            case TaskStatus::DONE:
                current_status = TaskStatus::DONE;
                break;
        }

        return current_status;
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person)
    {
        //person_tasks[person].insert({TaskStatus::NEW, 1});
        person_info_[person][TaskStatus::NEW] += 1;
        person_info_[person][TaskStatus::IN_PROGRESS] += 0;
        person_info_[person][TaskStatus::TESTING] += 0;
        person_info_[person][TaskStatus::DONE] += 0;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
    {
        TasksInfo tasks_to_update, untouched_tasks;

        if(person_info_.at(person).empty()) return tuple(tasks_to_update, untouched_tasks);
        
        for(auto &[status, count] : person_info_.at(person))
        {
            if(status == TaskStatus::DONE)
            {
                count += tasks_to_update[status];
                break;
            }
            
            if(task_count > count)
            {
                tasks_to_update[GetNextStatus(status)] = count;
                task_count -= count;
            }
            else
            {
                tasks_to_update[GetNextStatus(status)] = task_count;
                task_count = 0;
            }
        }

        for(auto &[status, count] : person_info_.at(person))
        {
            if(status == TaskStatus::DONE) break;

            untouched_tasks[status] = count - tasks_to_update[GetNextStatus(status)];
            count += tasks_to_update[status] - tasks_to_update[GetNextStatus(status)];
        }
 
        return tuple(tasks_to_update, untouched_tasks);
    }

private:
    map<string, TasksInfo> person_info_;
};

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь.
void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks"s
         << ", "s << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress"s
         << ", "s << tasks_info[TaskStatus::TESTING] << " tasks are being tested"s
         << ", "s << tasks_info[TaskStatus::DONE] << " tasks are done"s << endl;
}

int main() {
    TeamTasks tasks;
    tasks.AddNewTask("Ilia");
    for (int i = 0; i < 3; ++i) {
        tasks.AddNewTask("Ivan");
    }
    cout << "Ilia's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
    cout << "Ivan's tasks: ";
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));
  
    TasksInfo updated_tasks, untouched_tasks;
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
  
    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan", 2);
    cout << "Updated Ivan's tasks: ";
    PrintTasksInfo(updated_tasks);
    cout << "Untouched Ivan's tasks: ";
    PrintTasksInfo(untouched_tasks);
}