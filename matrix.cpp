#include <iostream>
#include "marix.h"

namespace mx {
    int addElement(Matrix *mx) {
        const char *what[] = {"Enter number of line", "Enter number of column", "Enter value"};
        int row = 0;
        Line *new_line = nullptr;
        enter(row, what[0]);
        if ((mx->tail != nullptr && row != mx->tail->number_row) || mx->head == nullptr) {
            alloc(new_line);
            if (mx->tail && mx->head) {
                new_line->number_row = row;
                mx->tail->next = new_line;
                mx->tail = new_line;
            }
        } else
            new_line = mx->tail;
        if (!mx->head) {
            mx->head = new_line;
            mx->tail = new_line;
        }
        if (mx->head && mx->tail && mx->head != mx->tail) {
            mx->tail->next = new_line;
            mx->tail = mx->tail->next;
        }
        Element *temp = nullptr;
        alloc(temp);
        enter(temp->c_coordinate, what[1]);
        enter(temp->value, what[2]);
        if (!mx->tail->head) {
            mx->tail->head = temp;
            mx->tail->tail = temp;
        } else {
            mx->tail->tail->next = temp;
            mx->tail->tail = temp;
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
        return 0;
    }

    int delMatrix (Matrix *mx) {
        Line *line_to_delete = mx->head;
        Line *line_save = mx->head->next;
        Element *el_to_delete;
        Element *el_save;
        while (line_to_delete) {
            el_to_delete = line_to_delete->head;
            el_save = line_to_delete->head->next;
            while (el_to_delete) {
                delete el_to_delete;
                el_to_delete = el_save;
                if (el_save)
                    el_save = el_save->next;
            }
            delete line_to_delete;
            line_to_delete = line_save;
            if (line_save)
                line_save = line_save->next;
        }
        delete mx;
        return 0;
    }

    Element *copyElement (Element *el) {
        if (el == nullptr)
            return nullptr;
        Element *new_el = nullptr;
        alloc(new_el);
        new_el->next = nullptr;
        new_el->value = el->value;
        new_el->c_coordinate = 0;
        return new_el;
    }

    Line *copyLine (Line *old_line) {
        Line *new_line = nullptr;
        alloc(new_line);
        new_line->head = nullptr;
        new_line->next = nullptr;
        new_line->tail = nullptr;
        new_line->number_row = old_line->number_row;
        Element *temp = old_line->head;
        Element *new_el;
        while (temp) {
            new_el = copyElement(temp);
            if (new_line->head == nullptr) {
                new_line->head = new_el;
                new_line->tail = new_el;
            } else {
                new_line->tail->next = new_el;
                new_line->tail = new_el;
            }
            temp = temp->next;
        }
        return new_line;
    }

    int smartAdd (Line *line, Element *el) {
        if (!line || !el)
            return 1;
        Element *temp = line->head;
        if (temp->value >= el->value) {
            el->next = line->head;
            line->head = el;
            return 0;
        }
        if (temp->value < el->value) {
            while (temp && temp->next && temp->next->value <= el->value)
                temp = temp->next;
            if (!temp)
                line->tail->next = el;
            else {
                el->next = temp->next;
                temp->next = el;
            }
        }
        return 0;
    }

    Line *smartCopyLine (Line *old_line) {
        Line *sorted = nullptr;
        alloc(sorted);
        sorted->head = nullptr;
        sorted->next = nullptr;
        sorted->tail = nullptr;
        Element *temp = old_line->head;
        Element *new_el;
        while (temp) {
            new_el = copyElement(temp);
            if (sorted->head == nullptr) {
                sorted->head = new_el;
                sorted->tail = new_el;
            } else {
                smartAdd(sorted, new_el);
            }
            temp = temp->next;
        }
        return sorted;
    }

    int indexing (Line *line) {
        if (!line)
            return 1;
        Element *temp = line->head;
        int i = 0;
        while (temp) {
            temp->c_coordinate = i;
            i++;
            temp = temp->next;
        }
        return 0;
    }

    int individual (Matrix *mx, Dim *dim, int i_line) {
        if (mx == nullptr || dim == nullptr)
            return 1;
        Matrix *new_m = nullptr;
        alloc(new_m);
        new_m->tail = nullptr;
        new_m->head = nullptr;
        Line *temp = mx->head;
        Line *new_line;
        while (temp) {
            if (temp->number_row == i_line) {
                new_line = smartCopyLine(temp);
                if (new_m->head) {
                    new_m->tail->next = new_line;
                    new_m->tail = new_line;
                } else {
                    new_m->head = new_line;
                    new_m->tail = new_line;
                }
                indexing(new_line);
            } else {
                new_line = copyLine(temp);
                if (new_m->head == nullptr) {
                    new_m->head = new_line;
                    new_m->tail = new_line;
                } else {
                    new_m->tail->next = new_line;
                    new_m->tail = new_line;
                }
            }
            temp = temp->next;
        }
        printMatrix(new_m, dim->lines, dim->columns);
        delMatrix(new_m);
        return 0;
    }
}
