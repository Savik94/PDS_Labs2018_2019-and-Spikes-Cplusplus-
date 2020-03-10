//
// Created by saverio on 06/03/20.
//

#include "File.h"

uintmax_t File::getSize() const {
    return this->size;
}

int File::mType() const {
    return 0;
}

void File::ls(int indent) const {
    int i=0;
    while (i <= indent){
        std::cout <<"\t";
        i++;
    }
    std::cout << this->name << " " << this->size << std::endl;
}
