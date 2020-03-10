//
// Created by saverio on 10/03/20.
//

#ifndef LAB02_2019_V2_CUSTOMEXCEPTION_H
#define LAB02_2019_V2_CUSTOMEXCEPTION_H

#include <exception>
#include <string>

class CustomException: public std::exception {
public:

    explicit CustomException(const char* msg): std::exception(){
        this->msg = msg;
    }

    const char *what() const noexcept override{
        return msg;
    }

private:
    const char* msg;

};


#endif //LAB02_2019_V2_CUSTOMEXCEPTION_H
