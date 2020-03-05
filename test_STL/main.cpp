#include <iostream>
#include <queue>
#include "Class.h"

int main() {
    std::priority_queue<int> queue;
    queue.push(1);
    queue.push(2);
    queue.push(3);
    queue.push(4);

    //TESTATO CON DEBUG, con top() ho in i una copia del primo valore nella PQ, con pop() non rischio un riferimento vuoto
    // Fosse una QUEUE, uso front() invece di top() ma ho stesso comportamento.
    int i = queue.top();
    std::cout << " Solo top() "<< i << std::endl;
    queue.pop();

    std::cout << "Con pop()  "<< i << std::endl;

    //test queue di oggetti Class aventi al loro interno un puntatore.
    std::queue<Class> queue2;

    int size = 3;
    queue2.emplace(3);
    queue2.emplace(4);
    Class obj {queue2.front()}; // costruttore di copia custo
    Class obj2 = queue2.front();// non è un assegnazione ma una costruzione (chiamo costruttore di copia essendo obj2 nonesistente in precedenza
    queue2.pop();



    return 0;
}