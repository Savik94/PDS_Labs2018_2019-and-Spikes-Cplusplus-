//
// Created by saverio on 05/03/20.
//

#ifndef LAB01_2019_V2_STRINGBUFFER_H
#define LAB01_2019_V2_STRINGBUFFER_H

#include <string.h>

class StringBuffer {
private:

    size_t max_size = 2048; // 2047 caratteri più fine stringa
    size_t current_size = 0;
    char *str = nullptr;

public:

    StringBuffer() {
        this->str = new char[max_size];
        this->str[max_size-1] = '\0';
    }
    //Dovrei aggiungere check strlen < max_size
    StringBuffer(const char *str){
        this->current_size = strlen(str);
        this->str = new char[current_size +1 ];
        memcpy(this->str,str,current_size);
    }
    //Anche qui stesso check del costruttore precedente
    StringBuffer(const StringBuffer& sb):current_size(sb.current_size){
        this->str = new char[this->current_size + 1 ];
        memcpy(this->str,str,current_size);
    }
    ~StringBuffer(){
        delete[] str;
    }
    StringBuffer& operator=(const StringBuffer& sb){
        //NB: un modo più elegante e più sicuro sarebbe usare il paradigma copy&swap.
        //Il parametro passato però dovrebbe essere una copia del StringBuffer da copiare e non un suo ref.
        //Devo allora prestare io attenzione, quindi controllare di non star assegnando me stesso a me stesso (mi eliminerei da solo)
        if(this!=&sb){
            delete[] this->str;

            // il distruttore va a liberare area di memoria puntata.
            // Il riferimento all'area però rimane se non faccio così.
            // il rischio è quello che, a causa di un eccezione, il distruttore vada
            //a ricancellare la stessa area di memoria che non è più dello StringBuffer, ma chissà cosa contiene.
            this->str = nullptr;
            this->current_size = sb.current_size;
            this->str = new char[this->current_size +1 ];
            memcpy(this->str,sb.str,this->current_size);
            return *this; // io ritorno un reference, contiene un puntatore implicito.
                          // mi devo comportare come se avessi un oggetto e non un puntatore (dal punto di vista sintattico)
                          //Quindi, essendo che this è un puntatore, io ritorno l'oggetto puntato, *this, e poi implicitamente viene gestito il fatto che in realtà ritorno un ref,
                          //quindi un puntatore nascosto.
        }
    }

    size_t size() const;
    size_t capacity();
    void clear();
    void insert(const char *str, size_t pos);
    void insert(const StringBuffer& sb,size_t pos);
    void append(const char *str);
    void append(const StringBuffer& sb);
    const char *c_str();
    void set(const char*str);
    void set(const StringBuffer& s);
    void print();
};


#endif //LAB01_2019_V2_STRINGBUFFER_H
