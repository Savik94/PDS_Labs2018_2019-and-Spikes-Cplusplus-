//
// Created by saverio on 06/03/20.
//

#ifndef LAB02_2019_V2_DIRECTORY_H
#define LAB02_2019_V2_DIRECTORY_H

#include <memory>
#include <map>
#include "Base.h"
#include "File.h"
#include "CustomException.h"

//Multiton Design Pattern! So the constructor is private and there is a collection of static object
//stored inside a map. With the Singleton Design Pattern there is just one instance of the class, in this case
//there is a single instance of the class PER KEY.

class Directory: public Base{
private:

    Directory(std::string name, std::weak_ptr<Directory> parent):Base(){
        this->name = std::move(name); // with std::move, I can use the movement-constructor and avoid a copy of the string
        this-> parent = std::move(parent);//same thing as previous string variable.
        Base::getName();
    }

    //Putting an explicit declaretion of the operator = and the copy-constructor in private section and without a definition,
    //Allow to disable it.
    //The other possibility is to put an explicit declaration in public section, no futher definition again and put at the end of it "=delete", in order to disable it.
    Directory& operator=(const Directory&);
    Directory (const Directory&);

    //It's not possible inizialize a non-const static member in header .h
    //Declare here and inizialize it in .cpp
    //It's better to use a ref variable, the pointer is manages implicitly by the compiler
    //Reduce the possibility that the client holding the ref to the static variable could delete the referenced memory area.
    //To enhance this last aspect, better to explicitly put in private section the declaration of the destructor without a definition.

    std::weak_ptr<Directory> self;
    std::weak_ptr<Directory> parent;
    std::map<std::string, std::shared_ptr<Base>> files ;


public:

    static std::shared_ptr<Directory> getRoot();
    std::shared_ptr<Directory> addDirectory(std::string name);
    std::shared_ptr<File> addFile(std::string name, uintmax_t size);
    std::shared_ptr<Base> get(std::string name);
    std::shared_ptr<Directory> getDir(std::string name);
    std::shared_ptr<File> getFile(std::string name);
    void remove (std::string name);
    virtual int mType() const override;
    void ls(int indent = 0) const override;

};


#endif //LAB02_2019_V2_DIRECTORY_H
