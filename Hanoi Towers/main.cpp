#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tower 
{
public:
    // конструктор и метод SetDisks нужны, чтобы правильно создать башни
    Tower(int disks_num) 
    {
        FillTower(disks_num);
    }

    int GetDisksNum() const 
    {
        return disks_.size();
    }

    void SetDisks(int disks_num) 
    {
        FillTower(disks_num);
    }

    // добавляем диск на верх собственной башни
    // обратите внимание на исключение, которое выбрасывается этим методом
    void AddToTop(int disk) 
    {
        int top_disk_num = disks_.size() - 1;
        if (0 != disks_.size() && disk >= disks_[top_disk_num]) 
        {
            throw invalid_argument("Невозможно поместить большой диск на маленький");
        } else 
        {
            disks_.push_back(disk);
        }
    }

    // вы можете дописывать необходимые для вашего решения методы

    void MoveTower(int disks_num, Tower& tower1, Tower& tower2, Tower& temp)
    {
        if (disks_num == 0) 
        {
            return;
        }
        MoveTower(disks_num - 1, tower1, temp, tower2);
        MoveTopTo(tower2);
        MoveTower(disks_num - 1, temp, tower2, tower1);
    }

    void MoveDisks(int disks_num, Tower& destination, Tower& buffer) 
    {
        MoveTower(disks_num, *this, destination, buffer);
    }

    void MoveTopTo(Tower& t) 
    {
        int disk = disks_.size() - 1;
        try {
            t.AddToTop(disks_[disk]);
        }
        catch (const invalid_argument& ia) {
            cout << ia.what() << '\n';
            throw;
        }
        disks_.pop_back();
    }

    void ViewDisks()
    {
        int disk = disks_.size();
        if(disk == 0)
        {
            cout << "0 0 0" << endl;
            return;
        }
        while(disk != 0)
        {
            cout << disk << " ";
            --disk;
        }

        cout << endl;
    }

private:
    vector<int> disks_;

    // используем приватный метод FillTower, чтобы избежать дубликации кода
    void FillTower(int disks_num) 
    {
        for (int i = disks_num; i > 0; i--) 
        {
            disks_.push_back(i);
        }
    }
};

void SolveHanoi(vector<Tower>& towers) 
{
    int disks_num = towers[0].GetDisksNum();

    // допишите функцию, чтобы на towers[0] было 0 дисков,
    // на towers[1] 0 дисков,
    // и на towers[2] было disks_num дисков
    towers[0].MoveDisks(disks_num, towers[2], towers[1]);
}

void ViewTowers(vector<Tower> towers)
{
    cout << "Башня 1: ";
    towers[0].ViewDisks();
    cout << "Башня 2: ";
    towers[1].ViewDisks();
    cout << "Башня 3: ";
    towers[2].ViewDisks();
}

int main() 
{
    int towers_num = 3;
    int disks_num = 3;
    vector<Tower> towers;
    // добавим в вектор три пустые башни
    for (int i = 0; i < towers_num; ++i) 
    {
        towers.push_back(0);
    }
    // добавим на первую башню три кольца
    towers[0].SetDisks(disks_num);

    ViewTowers(towers);
    SolveHanoi(towers);
    ViewTowers(towers);
}