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

    TaskStatus GetNextStatus(const TaskStatus current_status)
    {
        switch(current_status)
        {
            case TaskStatus::NEW:
            return TaskStatus::IN_PROGRESS;
            break;

            case TaskStatus::IN_PROGRESS:
            return TaskStatus::TESTING;
            break;

            case TaskStatus::TESTING:
            return TaskStatus::DONE;
            break;

            case TaskStatus::DONE:
            return TaskStatus::DONE;
            break;

            default:
            return TaskStatus::NEW;
            break;
        } 
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person)
    {
        //person_tasks[person].insert({TaskStatus::NEW, 1});
        person_info_[person][TaskStatus::NEW] += 1;
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(const string& person, int task_count)
    {
        TasksInfo tasks_to_update, untouched_tasks;

        if(person_info_.at(person).empty()) return tuple(tasks_to_update, untouched_tasks);
        
        for(auto &[status, count] : person_info_.at(person))
        {
            if(status == TaskStatus::DONE) break;
            
            
        }
 
        /*for(auto &[status, count] : person_info_.at(person))
        {
            if(untouched_tasks.count(status))
            {
                count = untouched_tasks[status];
            } 
            else if(tasks_to_update.count(status))
            {
                count += tasks_to_update[status];
            }
        }*/

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
    
    tasks.AddNewTask("Ivan"s);

    cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));

    TasksInfo updated_tasks, untouched_tasks;

    tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 1000);
    cout << "Updated Ivan's tasks: "s;
    PrintTasksInfo(updated_tasks);
    // cout << "Untouched Ivan's tasks: "s;
    // PrintTasksInfo(untouched_tasks);

    // tie(updated_tasks, untouched_tasks) = tasks.PerformPersonTasks("Ivan"s, 2);
    // cout << "Updated Ivan's tasks: "s;
    // PrintTasksInfo(updated_tasks);
    // cout << "Untouched Ivan's tasks: "s;
    // PrintTasksInfo(untouched_tasks);

    // cout << "Ivan's tasks: "s;
    PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"s));
}