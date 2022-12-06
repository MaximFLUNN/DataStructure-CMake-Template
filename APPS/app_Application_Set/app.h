// Copyright 2022 Filatov Maxim

#include "set.h"
#include "bitfield.h"
#include <vector>

void test_bitfield() {
    int maxnum, count;
    int iter = 1;

    setlocale(LC_ALL, "Russian");
    std::cout << "������ ���������� (TBitField)" << "\n";
    std::cout << "������ ������������� �����: ";
    std::cin >> maxnum;
    TBitField s(maxnum + 1);
    // ���������� ���������
    for (int i = 2; i <= maxnum; i++) {
        s.setbit(i);
    }
    // �������� �� sqrt(n) � �������� �������
    for (int i = 2; i * i <= maxnum; i++) {
        // ���� m � s, �������� �������
        if (s.getbit(i)) {
            for (int g = 2 * i; g <= maxnum; g += i) {
                s.resetbit(g);
            }
        }
    }
    // ���������� � s �������� - ������� �����
    std::cout << std::endl << "������ ��������� ��������� �����" << "\n" << s << "\n";
    std::cout << std::endl << "������ ������� �����" << "\n";
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
    std::cout << "� ������ " << maxnum << " ������ " << count << " �������" << "\n";
}

void test_set() {
    int maxnum, count;
    int iter = 1;

    setlocale(LC_ALL, "Russian");
    std::cout << "������ ���������� (TSet)" << "\n";
    std::cout << "������ ������������� �����: ";
    std::cin >> maxnum;
    TSet s(maxnum + 1);
    // ���������� ���������
    for (int i = 2; i <= maxnum; i++) {
        s.InsElem(i);
    }
    // �������� �� sqrt(n) � �������� �������
    for (int i = 2; i * i <= maxnum; i++) {
        // ���� � � s, �������� �������
        if (s.IsMember(i)) {
            for (int g = 2 * i; g <= maxnum; g += i) {
                s.DelElem(g);
            }
        }
    }
    // ���������� � s �������� - ������� �����
    std::cout << "\n" << "������ ��������� ��������� �����" << "\n" << s << "\n";
    std::cout << "\n" << "������ ������� �����" << "\n";
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
    std::cout << "� ������ " << maxnum << " ������ " << count << " �������" << "\n";
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
    std::cout << "���� ���������� ������� (���������������� �������)" << "\n\n";
    std::vector<Film> films = { Film(0, "Krytoy film", "Ya", 2000), Film(1, "Good film", "Ktoto", 1998), Film(2, "Ne top film", "NE Ya", 1999) };
    FilmLibrary filmLib = FilmLibrary(films);
    std::cout << "\n��������� ��� ������" << "\n";
    filmLib.print_all_films();
    std::cout << "\n���������� ������ � ��������� � ���������� ������ ��������������" << "\n\n";
    filmLib.activate_film(0);
    filmLib.activate_film(filmLib.films.size() - 1);
    filmLib.print_active_films();
    std::cout << "\n������� ����� ����� � ����� ���������� ���" << "\n\n";
    filmLib.add_new_film(Film(3, "New film", "...", 2077));
    filmLib.activate_film(filmLib.films.size() - 1);
    filmLib.print_active_films();
    std::cout << "\n������������ ��� ������ ����� ���������� � ���������� �������� ������" << "\n\n";
    for (int i = 0; i < filmLib.films.size() - 1; i++) {
        filmLib.deactivate_film(filmLib.films[i].id);
    }
    filmLib.print_active_films();
}