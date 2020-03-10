#include <iostream>
#include "Directory.h"

int main() {
    try{
        std::shared_ptr <Directory> root = Directory::getRoot();
        auto alpha = root->addDirectory("alpha");
        alpha -> addDirectory("beta")-> addFile("beta1",100);
        alpha->getDir("beta") -> addFile("beta2",200);
        alpha->getDir("..")->ls();
        auto beta = alpha->getDir("beta");
        alpha->remove("alpha");
        root->ls();

        std::cout << beta->getName()<< std::endl;   // The block refered by beta is still alive,
        //until the last shared_ptr is still pointing it.

    }catch(std::exception& e){
        std::cerr << "Errore: " << e.what() << std::endl;
    }

    return 0;
}