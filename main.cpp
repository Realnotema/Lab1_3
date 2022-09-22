#include <iostream>
#include "marix.h"

using namespace mx;

int Menu (Matrix *mx, Dim *dim) {
    if (mx == nullptr || dim == nullptr)
        return -1;
    const char *what[] = {"\nChoose next step", "1. Add element", "2. Print matrix",
                          "3. Individual task", "4. Exit", "Enter number of line to sort"};
    int flag = 0;
    int choose = 0;
    do {
        for (int i = 1; i < 5; i++)
            cout << what[i] << endl;
        enter(flag, what[0]);
        switch (flag) {
            case 1:
                addElement(mx);
                break;
            case 2:
                printMatrix (mx, dim->lines, dim->columns);
                break;
            case 3:
                enter(choose, what[5]);
                individual(mx, dim, choose);
                break;
            case 4:
                delMatrix(mx);
                delete dim;
                return 0;
            default:
                cout << "Try again" << endl;
        }
    } while (flag != 4);
    return 0;
}

int main() {
    const char *what[] = {"Enter count of lines", "Enter count of columns"};
    Matrix *mx = nullptr;
    Dim *dim = nullptr;
    alloc(mx);
    mx->head = nullptr;
    mx->tail = nullptr;
    alloc(dim);
    enter(dim->lines, what[0]);
    enter(dim->columns, what[1]);
    Menu(mx, dim);
    return 0;
}
