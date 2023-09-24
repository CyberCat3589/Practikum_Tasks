#include <algorithm>
#include <deque>
#include <string>
#include <iostream>

using namespace std;

struct Ticket 
{
    int id;
    string name;
};

class TicketOffice 
{
public:
    // добавить билет в систему
    void PushTicket(const string& name) 
    {
        tickets_.push_back({++last_id_, name});
    }

    // получить количество доступных билетов
    int GetAvailable() const 
    {
        return static_cast<int>(tickets_.size());
    }

    // получить количество доступных билетов определённого типа
    int GetAvailable(const string& name) const 
    {
        // реализуйте метод
        int result = count_if(tickets_.begin(), tickets_.end(), 
            [&name](Ticket ticket)
            { 
                return ticket.name == name; 
            });

        return result;
    }

    // отозвать старые билеты (до определённого id)
    void Invalidate(int minimum) 
    {
        if(minimum < last_id_ && !tickets_.empty())
        {
            for(int i = tickets_.at(0).id; i < last_id_; ++i)
            {
                tickets_.pop_front();
            }
        }
    }

private:
    int last_id_ = 0;
    deque<Ticket> tickets_;
};

int main()
{
    TicketOffice tickets;

    tickets.PushTicket("Swan Lake"); // id - 0
    tickets.PushTicket("Swan Lake"); // id - 1
    tickets.PushTicket("Boris Godunov"); // id - 2
    tickets.PushTicket("Boris Godunov"); // id - 3
    tickets.PushTicket("Swan Lake"); // id - 4
    tickets.PushTicket("Boris Godunov"); // id - 5
    tickets.PushTicket("Boris Godunov"); // id - 6

    cout << tickets.GetAvailable() << endl; // Вывод: 7
    cout << tickets.GetAvailable("Swan Lake") << endl; // Вывод: 3
    cout << tickets.GetAvailable("Boris Godunov") << endl; // Вывод: 4

    // Invalidate удалит билеты с номерами 0, 1, 2:
    tickets.Invalidate(3);

    cout << tickets.GetAvailable() << endl; // Вывод: 4
    cout << tickets.GetAvailable("Swan Lake") << endl; // Вывод: 1
    cout << tickets.GetAvailable("Boris Godunov") << endl; // Вывод: 3

    tickets.PushTicket("Swan Lake"); // id - 7
    tickets.PushTicket("Swan Lake"); // id - 8

    cout << tickets.GetAvailable("Swan Lake") << endl; // Вывод: 3
}