//
// Created by saverio on 05/03/20.
//

#include <iostream>
#include "StringBuffer.h"

size_t StringBuffer::size() const {
    return this->current_size;
}

size_t StringBuffer::capacity() {
    return this->max_size;
}

void StringBuffer::clear() {
    this->current_size = 0;
}

void StringBuffer::insert(const char *str, size_t pos) {
    size_t tmp_size = strlen(str);
    size_t new_size = 0;
    size_t n_spaces = 0;

    if(tmp_size >= this->max_size || pos >= this->max_size){
        std::cout << "Invalid operation" <<std::endl;
        exit(-1);
    }

    if(pos >= this->current_size) {
        n_spaces = pos - this->current_size;
        new_size = tmp_size + this->current_size + n_spaces;

        if (new_size >= this->max_size) {
            std::cout << "Invalid operation" << std::endl;
            exit(-1);
        }

        //se il vecchio blocco non era sufficientemente grande,
        //si cerca un altro blocco e se si trova si alloca, si copia il contenuto
        //del vecchio blocco e questo viene rilasciato (NO MEMORY LEAK!)
        //Se non c è sufficiente memoria, il vecchio blocco non viene toccato e si ritorna
        //un puntatore a nullptr (possibile lanciare l'eccezione std::bad_alloc)
        if (void *tmp_ptr = std::realloc(this->str, new_size + 1))
            this->str = static_cast<char *>(tmp_ptr);
        else{
            std::cout << "Invalid operation" << std::endl;
            return;
        }

        for(int i = 0;i < n_spaces;i++){
            this->str[this->current_size +i ]= ' ';
        }
        this->str[new_size] = '\0';
        this->current_size = new_size;
    }

    else{
        if(pos + tmp_size >= this->current_size){
            new_size = this->current_size + (tmp_size-pos);

            if (new_size >= this->max_size) {
                std::cout << "Invalid operation" << std::endl;
                exit(-1);
            }

            //se il vecchio blocco non era sufficientemente grande,
            //si cerca un altro blocco e se si trova si alloca, si copia il contenuto
            //del vecchio blocco e questo viene rilasciato (NO MEMORY LEAK!)
            //Se non c è sufficiente memoria, il vecchio blocco non viene toccato e si ritorna
            //un puntatore a nullptr (possibile lanciare l'eccezione std::bad_alloc)
            if (void *tmp_ptr = std::realloc(this->str, new_size + 1))
                this->str = static_cast<char *>(tmp_ptr);
            else{
                std::cout << "Invalid operation" << std::endl;
                exit(-1);
            }
            this->str[new_size] = '\0';
            this->current_size = new_size;
        }
    }

    memcpy(this->str+pos,str,strlen(str));
}

void StringBuffer::insert(const StringBuffer &sb, size_t pos) {
    if(this == &sb){
        std::cout << "Invalid operation" <<std::endl;
        exit(-1);
    }

    size_t new_size = 0;
    size_t n_spaces = 0;

    if(sb.current_size >= this->max_size || pos >= this->max_size){
        std::cout << "Invalid operation" <<std::endl;
        exit(-1);
    }

    if(pos >= this->current_size) {
        n_spaces = pos - this->current_size;
        new_size = sb.current_size + this->current_size + n_spaces;

        if (new_size >= this->max_size) {
            std::cout << "Invalid operation" << std::endl;
            exit(-1);
        }

        //se il vecchio blocco non era sufficientemente grande,
        //si cerca un altro blocco e se si trova si alloca, si copia il contenuto
        //del vecchio blocco e questo viene rilasciato (NO MEMORY LEAK!)
        //Se non c è sufficiente memoria, il vecchio blocco non viene toccato e si ritorna
        //un puntatore a nullptr (possibile lanciare l'eccezione std::bad_alloc)
        if (void *tmp_ptr = std::realloc(this->str, new_size + 1))
            this->str = static_cast<char *>(tmp_ptr);
        else{
            std::cout << "Invalid operation" << std::endl;
            return;
        }

        for(int i = 0;i < n_spaces;i++){
            this->str[this->current_size +i ]= ' ';
        }
        this->str[new_size] = '\0';
        this->current_size = new_size;
    }

    else{
        if(pos + sb.current_size >= this->current_size){
            new_size = this->current_size + (sb.current_size-pos);

            if (new_size >= this->max_size) {
                std::cout << "Invalid operation" << std::endl;
                exit(-1);
            }

            //se il vecchio blocco non era sufficientemente grande,
            //si cerca un altro blocco e se si trova si alloca, si copia il contenuto
            //del vecchio blocco e questo viene rilasciato (NO MEMORY LEAK!)
            //Se non c è sufficiente memoria, il vecchio blocco non viene toccato e si ritorna
            //un puntatore a nullptr (possibile lanciare l'eccezione std::bad_alloc)
            if (void *tmp_ptr = std::realloc(this->str, new_size + 1))
                this->str = static_cast<char *>(tmp_ptr);
            else{
                std::cout << "Invalid operation" << std::endl;
                exit(-1);
            }
            this->str[new_size] = '\0';
            this->current_size = new_size;
        }
    }

    memcpy(this->str+pos,str,strlen(str));
}

void StringBuffer::append(const char *str) {
    size_t tmp_size = strlen(str);
    size_t new_size = tmp_size + this->current_size;

    if(new_size >= this->max_size){
        std::cout << "Invalid operation" <<std::endl;
        exit(-1);
    }

    if (void *tmp_ptr = std::realloc(this->str, new_size + 1))
        this->str = static_cast<char *>(tmp_ptr);
    else{
        std::cout << "Invalid operation" << std::endl;
        exit(-1);
    }

    memcpy(this->str+this->current_size,str,tmp_size);
    this->str[new_size] = '\0';
    this->current_size = new_size;
}

void StringBuffer::append(const StringBuffer &sb) {
    if(this == &sb){
        std::cout << "Invalid operation" <<std::endl;
        exit(-1);
    }

    size_t tmp_size = sb.current_size;
    size_t new_size = tmp_size + this->current_size;

    if(new_size >= this->max_size){
        std::cout << "Invalid operation" <<std::endl;
        exit(-1);
    }

    if (void *tmp_ptr = std::realloc(this->str, new_size + 1))
        this->str = static_cast<char *>(tmp_ptr);
    else{
        std::cout << "Invalid operation" << std::endl;
        exit(-1);
    }

    memcpy(this->str+this->current_size,sb.str,tmp_size);
    this->str[new_size] = '\0';
    this->current_size = new_size;
}

const char *StringBuffer::c_str() {
    return this->str;
}

void StringBuffer::set(const char *str) {
    size_t new_length = strlen(str);

    if(new_length >= this->max_size){
        std::cout << "Invalid operation" << std::endl;
        exit(-1);
    }
    if(new_length >= this->current_size){

        if (void *tmp_ptr = std::realloc(this->str, new_length + 1))
            this->str = static_cast<char *>(tmp_ptr);
        else{
            std::cout << "Invalid operation" << std::endl;
            exit(-1);
        }
    }

    this->current_size = new_length;
    memcpy(this->str, str, this->current_size + 1); // con il +1 includo anche il '\0'
}

void StringBuffer::print() {
    std::cout << this->str << std::endl;
}

void StringBuffer::set(const StringBuffer &s) {

}
