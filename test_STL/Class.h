//
// Created by saverio on 29/08/19.
//

#ifndef TEST_STL_CLASS_H
#define TEST_STL_CLASS_H
#include <stdlib.h>

class Class {
    int *v;
    int size;

public:
    explicit Class (int size):size(size){
        v = (int*)malloc(size*sizeof(int));
    }

    Class (const Class& c){
            this->size = c.size;
            this->v = (int*)malloc(size*sizeof (int));
    }
    Class& operator=(Class& c){
        if(this!=&c){
            delete[] this->v;
            v = NULL;
            v = (int*)malloc(c.size*sizeof(int));
            return *this;
        }
    }
};


#endif //TEST_STL_CLASS_H
