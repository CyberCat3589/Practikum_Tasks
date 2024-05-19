#include "people.h"

#include <stdexcept>

using namespace std;

Programmer::Programmer(const string& name, int age, Gender gender) {
    // Напишите тело конструктора
}

const string& Programmer::GetName() const {
    // Заглушка, реализуйте метод самостоятельно
    throw std::logic_error("Not implemented"s);
}

int Programmer::GetAge() const {
    // Заглушка, реализуйте метод самостоятельно
    return 0;
}

Gender Programmer::GetGender() const {
    // Заглушка, реализуйте метод самостоятельно
    return Gender::MALE;
}

void Programmer::AddProgrammingLanguage(ProgrammingLanguage language) {
    // Заглушка, реализуйте метод самостоятельно
}

bool Programmer::CanProgram(ProgrammingLanguage language) const {
    // Заглушка, реализуйте метод самостоятельно
    return false;
}

Worker::Worker(const string& name, int age, Gender gender) {
    // Заглушка, реализуйте конструктор самостоятельно
}

const string& Worker::GetName() const {
    // Заглушка, реализуйте метод самостоятельно
    throw std::logic_error("Not implemented"s);
}

int Worker::GetAge() const {
    // Заглушка, реализуйте метод самостоятельно
    return 0;
}

Gender Worker::GetGender() const {
    return Gender::MALE;
}

void Worker::AddSpeciality(WorkerSpeciality speciality) {
    // Заглушка, реализуйте метод самостоятельно
}

bool Worker::HasSpeciality(WorkerSpeciality speciality) const {
    // Заглушка, реализуйте метод самостоятельно
    return false;
}