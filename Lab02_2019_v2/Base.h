//
// Created by saverio on 06/03/20.
//

#ifndef LAB02_2019_V2_BASE_H
#define LAB02_2019_V2_BASE_H


#include <string>

class Base {
protected:
    std::string name;

public:
    std::string getName() const;
    virtual int mType() const = 0;
    virtual void ls(int indent=0) const = 0;

};


#endif //LAB02_2019_V2_BASE_H
