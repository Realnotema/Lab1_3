#include <iostream>
#include "marix.h"

namespace mx {
    int addElement(Matrix *mx) {
        const char *what[] = {"Enter number of line", "Enter number of column", "Enter value"};
        Line *new_line = nullptr;
        alloc(new_line);
        enter(new_line->number_row, what[0]);
        if (!mx->head) {
            mx->head = new_line;
            mx->tail = new_line;
        } else {
            mx->tail->next = new_line;
            mx->tail = mx->tail->next;
        }
        Element *temp = nullptr;
        alloc(temp);
        enter(temp->c_coordinate, what[1]);
        enter(temp->value, what[2]);
        if (!mx->tail->head) {
            mx->tail->head = temp;
            mx->tail->head = temp;
        } else {
            mx->tail->tail->next = temp;
            mx->tail->tail = mx->tail->tail->next;
        }
        return 0;
    }

    int printMatrix(Matrix *mx, int lines, int columns) {
        Line *line = mx->head;
        Element *element = line->head;
        for (int i = 0; i < lines; i++) {
            for (int j = 0; j < columns; j++) {
                if (line->number_row == i) {
                    if (element->c_coordinate == j) {
                        cout << element->value;
                        cout << " ";
                        if (element->next)
                            element = element->next;
                        else {
                            if (line->next) {
                                line = line->next;
                                element = line->head;
                            }
                        }
                    } else
                        cout << "0 ";
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
        }
    }
}
