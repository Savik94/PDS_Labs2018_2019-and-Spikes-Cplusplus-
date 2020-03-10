//
// Created by saverio on 06/03/20.
//

#ifndef LAB02_2019_V2_FILE_H
#define LAB02_2019_V2_FILE_H
#include "Base.h"
#include <memory>
#include <iostream>

class File: public Base {
private:
    uintmax_t  size = 0;
public:
    uintmax_t getSize() const;
    void ls(int indent = 0) const override;
    int mType() const override;

    File(std::string name, uintmax_t size): Base(){
        this->name = name;
        this->size = size;
        Base::getName();
    }
};


#endif //LAB02_2019_V2_FILE_H
