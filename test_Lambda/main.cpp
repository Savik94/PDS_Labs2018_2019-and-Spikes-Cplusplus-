#include <iostream>
#include <queue>
#include <functional>

std::function <void(int)> makeFunction(int* i) { return [i](int j)->void {(*i)+=j;};}

int main() {
    int i = 1;
    auto f = [i](int v)mutable->int{ i+=v; return i;}; //Essendo la creazione implicita di un funtore nella closure devo avere solo il nome della variabile e non il tipo e deve già esistere (come chiamata a costruttore classico)
                                                       // ho creato funtore con copia di i (interna non ref) voglio usarlo come accumulatore.
                                                       // Per poterlo fare devo usare "mutable che mi permette di modificare l'attributo interno (il valore non ref nelle quadre)
                                                       //la variabile "i" non cambia, nella lambda ho copia e basta

    std::cout << f(1) << "  " << i << std::endl;//2
    std::cout << f(1) << "  " << i<<std::endl;//3

    std::cout << f(1) << "  " << i<< std::endl;//4

    std::cout << std::endl << "Test lambda per ref" << std::endl<<std::endl;

    //auto g = [&i](int j)->void { i+=j;}; Commento questa riga e uso versione makeFunction() riportata sopra
    auto g = makeFunction(&i); // creo funtore e passo riferimento a i (passaggio per valore puntatore!)
    //auto g = makeFunction(i); // facendo così, per la sintassi del C++, potrebbe essere i passata per ref (ref ha stessa sintassi passaggio per valore)
    //std::function <void(int)> makeFunction(int& i) { return [&i](int j)->void {i+=j;};} // sarebbe da scrivere questa versione

    for(int j = 0;j<3;j++){
        g(j);
        std::cout << i <<std::endl;
    }


    return 0;
}