#ifndef LAB1_2_MARIX_H
#define LAB1_2_MARIX_H
#include <iostream>

namespace mx {
    using std::cin;
    using std::cout;
    using std::endl;
    using std::bad_alloc;

    typedef struct Element {
        int value;
        int c_coordinate;
        Element *next;
    } Element;

    typedef struct Line {
        int number_row;
        Element *head;
        Line *next;
    } Line;

    typedef struct Matrix {
        Line *head;
        Line *tail;
    } Matrix;

    template <class T>
    int alloc (T *&a) {
        try {
            a = new T;
        } catch (bad_alloc &err){
            cout << err.what() << endl;
            return 1;
        }
        return 0;
    }

    template <class T>
    int enter (T &a, const char *what) {
        cout << what << endl;
        cin >> a;
        if (!cin.good()) {
            cout << "Error with cin \n Try again" << endl;
            return 1;
        } else
            return 0;
    }
}

#endif //LAB1_2_MARIX_H
