//
// Created by saverio on 06/03/20.
//

#include "Directory.h"
#include "CustomException.h"

//For the root object the Scott Meyer's Singleton pattern approch has been used.

/*The zero-initialization of all block-scope variables with static storage duration or thread storage duration is performed before any other initialization takes place.
 * Constant initialization of a block-scope entity with static storage duration, if applicable, is performed before its block is first entered.
 * An implementation is permitted to perform early initialization of other block-scope variables with static or thread storage duration under the same conditions that an implementation is permitted to statically initialize a variable with static or thread storage duration in namespace scope.
 * Otherwise such a variable is initialized the first time control passes through its declaration; such a variable is considered initialized upon the completion of its initialization. If the initialization exits by throwing an exception, the initialization is not complete, so it will be tried again the next time control enters the declaration.
 * If control enters the declaration concurrently while the variable is being initialized, the concurrent execution shall wait for completion of the initialization. If control re-enters the declaration recursively while the variable is being initialized, the behavior is undefined.*/

std::shared_ptr<Directory> Directory::getRoot() {

    static std::shared_ptr<Directory> root = std::shared_ptr<Directory>(new Directory{"/", std::weak_ptr<Directory>()});// std::weak_ptr initially is nullptr
    root->self = root;
    return root;
}

std::shared_ptr<Directory> Directory::addDirectory(std::string name) {

    //Check if name already exists or name is equal to "/" or "." or ".." (.compare() returns 0 in case of equality)
    if(files.find(name)!=std::end(files) || name == "/" || name == "." || name == "..")
        throw CustomException{"Directory already existing"};


    //With make_shared<T>(args) object and control block are stored continuously as a single things,
    //There is the necessity to access to the constructor of the object. args are the args of the constructor (is implicitly called by make_shared)
    auto dir_smart_ptr = std::shared_ptr<Directory>(new Directory(name,this->self));
    dir_smart_ptr->self= dir_smart_ptr;
    this->files.insert({name,dir_smart_ptr});

    //Like "dynamic_cast", allow a run-time check if to the Base type smart pointer is assigned a pointer to a derived type object
    return dir_smart_ptr;
}

std::shared_ptr<File> Directory::addFile(std::string name, uintmax_t size) {

    if(files.find(name)!=std::end(files))
        throw CustomException{"File already existing"};

    //With make_shared<T>(args) object and control block are stored continuously as a single things,
    //There is the necessity to access to the constructor of the object. args are the args of the constructor (is implicitly called by make_shared)
    std::shared_ptr<File> file_smart_ptr = std::make_shared<File>(name, size);
    this->files.insert({name,file_smart_ptr});
    std::shared_ptr<Base> ptr = files[name];
    return file_smart_ptr;
}

std::shared_ptr<Base> Directory::get(std::string name) {
    auto it = files.find(name);
    if(it ==std::end(files)){
        return std::shared_ptr<Base>(nullptr);
    }
    return it->second;
}

std::shared_ptr<Directory> Directory::getDir(std::string name) {
    if(name == ".")
        return (this->self).lock();

    if(name == "..")
        return (this->parent).lock();

    auto it = files.find(name);
    if(it == std::end(files) || (it->second->mType())!=1){ // check if exist the name and if the name is owned by a directory and not by a file
        return std::shared_ptr<Directory>(nullptr);
    }
    return std::dynamic_pointer_cast<Directory>(it->second);
}

std::shared_ptr<File> Directory::getFile(std::string name) {
    auto it = files.find(name);
    if(it ==std::end(files) || (it->second->mType())!=0){
        return std::shared_ptr<File>(nullptr);
    }
    return std::dynamic_pointer_cast<File>(it->second);
}

void Directory::remove(std::string name) {
    if(name == "." || name == ".."){
        throw CustomException{"Invalid deletion"};
    }

    auto it = files.find(name);
    if(it != std::end(files)){
        files.erase(it);
    }
}

void Directory::ls(int indent) const {
    std::cout << "[+] " << this->getName() << std::endl;

    if (std::empty(files))
        return;

    int i = 0;
    while (i <= indent) {
        std::cout << "\t";
        i++;
    }

    for (auto it = files.begin(); it != files.end(); it++)
        it->second->ls(indent++);
}

int Directory::mType() const {
    return 1;
}
