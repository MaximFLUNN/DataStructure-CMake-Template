// Copyright 2022 Filatov Maxim

#include "set.h"
#include "bitfield.h"
#include <vector>

void test_bitfield() {
    int maxnum, count;
    int iter = 1;

    setlocale(LC_ALL, "Russian");
    std::cout << "Решето Эратосфена (TBitField)" << "\n";
    std::cout << "Предел максимального числа: ";
    std::cin >> maxnum;
    TBitField s(maxnum + 1);
    // заполнение множества
    for (int i = 2; i <= maxnum; i++) {
        s.setbit(i);
    }
    // проверка до sqrt(n) и удаление кратных
    for (int i = 2; i * i <= maxnum; i++) {
        // если m в s, удаление кратных
        if (s.getbit(i)) {
            for (int g = 2 * i; g <= maxnum; g += i) {
                s.resetbit(g);
            }
        }
    }
    // оставшиеся в s элементы - простые числа
    std::cout << std::endl << "Печать множества некратных чисел" << "\n" << s << "\n";
    std::cout << std::endl << "Печать простых чисел" << "\n";
    count = 0;
    for (int i = 2; i <= maxnum; i++) {
        if (s.getbit(i)) {
            count++;
            std::cout << "\t" << i << " ";
            if (iter++ % 10 == 0)
                std::cout << "\n";
        }
    }
    std::cout << "\n";
    std::cout << "В первых " << maxnum << " числах " << count << " простых" << "\n";
}

void test_set() {
    int maxnum, count;
    int iter = 1;

    setlocale(LC_ALL, "Russian");
    std::cout << "Решето Эратосфена (TSet)" << "\n";
    std::cout << "Предел максимального числа: ";
    std::cin >> maxnum;
    TSet s(maxnum + 1);
    // заполнение множества
    for (int i = 2; i <= maxnum; i++) {
        s.InsElem(i);
    }
    // проверка до sqrt(n) и удаление кратных
    for (int i = 2; i * i <= maxnum; i++) {
        // если м в s, удаление кратных
        if (s.IsMember(i)) {
            for (int g = 2 * i; g <= maxnum; g += i) {
                s.DelElem(g);
            }
        }
    }
    // оставшиеся в s элементы - простые числа
    std::cout << "\n" << "Печать множества некратных чисел" << "\n" << s << "\n";
    std::cout << "\n" << "Печать простых чисел" << "\n";
    count = 0;
    for (int i = 2; i <= maxnum; i++) {
        if (s.IsMember(i)) {
            count++;
            std::cout << "\t" << i << " ";
            if (iter++ % 10 == 0) {
                std::cout << "\n";
            }
        }
    }
    std::cout << "\n";
    std::cout << "В первых " << maxnum << " числах " << count << " простых" << "\n";
}

class Film {
public:
    int id;
    std::string name;
    std::string author;
    int year;

    Film() : id(0), name("Unknown"), author("Unknown"), year(NULL) {}
    Film(int _id, std::string _name, std::string _author, int _year) {
        id = _id;
        name = _name;
        author = _author;
        year = _year;

    }
    ~Film() {}
};

class FilmLibrary {
public:
    std::vector<Film> films;
    TSet set = TSet(1);
    FilmLibrary() : films(std::vector<Film>(1)), set(TSet(1)) {}
    FilmLibrary(std::vector<Film> _films) {
        films = _films;
        set = TSet(_films.size());
    }
    ~FilmLibrary() {}

    void activate_film(int id) {
        set.InsElem(id);
    }

    void deactivate_film(int id) {
        set.DelElem(id);
    }

    void add_new_film(Film film) {
        TSet tmp_set = TSet(films.size() + 1);
        this->set = tmp_set + this->set;
        this->set.InsElem(film.id);
        films.push_back(film);
    }

    void print_all_films() {
        for (int i = 0; i < films.size(); i++) {
            std::cout << "----------------------\n" 
                << "Id: " << films[i].id << "\n"
                << "Author: " << films[i].author << "\n"
                << "Name: " << films[i].name << "\n"
                << "Year: " << films[i].year << "\n";
        }
        std::cout << "----------------------\n";
    }

    void print_active_films() {
        bool flag = false;
        for (int i = 0; i < films.size(); i++) {
            if (set.IsMember(films[i].id)) {
                flag = true;
                std::cout << "----------------------\n"
                    << "Id: " << films[i].id << "\n"
                    << "Author: " << films[i].author << "\n"
                    << "Name: " << films[i].name << "\n"
                    << "Year: " << films[i].year << "\n";
            }
        }
        if (flag) {
            std::cout << "----------------------\n";
        }
    }
};


void test_film_library() {
    setlocale(LC_ALL, "Russian");
    std::cout << "Тест библиотеки фильмов (демонстрационный вариант)" << "\n\n";
    std::vector<Film> films = { Film(0, "Krytoy film", "Ya", 2000), Film(1, "Good film", "Ktoto", 1998), Film(2, "Ne top film", "NE Ya", 1999) };
    FilmLibrary filmLib = FilmLibrary(films);
    std::cout << "\nНапечатем все фильмы" << "\n";
    filmLib.print_all_films();
    std::cout << "\nАктивируем первый и последний и напечатаем только активированные" << "\n\n";
    filmLib.activate_film(0);
    filmLib.activate_film(filmLib.films.size() - 1);
    filmLib.print_active_films();
    std::cout << "\nДобавим новый фильм и сразу активируем его" << "\n\n";
    filmLib.add_new_film(Film(3, "New film", "...", 2077));
    filmLib.activate_film(filmLib.films.size() - 1);
    filmLib.print_active_films();
    std::cout << "\nДеактивируем все фильмы кроме последнего и напечатаем активные фильмы" << "\n\n";
    for (int i = 0; i < filmLib.films.size() - 1; i++) {
        filmLib.deactivate_film(filmLib.films[i].id);
    }
    filmLib.print_active_films();
}