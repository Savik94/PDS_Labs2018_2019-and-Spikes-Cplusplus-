#include <iostream>
#include "StringBuffer.h"

int main() {
    StringBuffer s1{"Hello"};
    StringBuffer s2{"Hello"};
    StringBuffer s3 {"World!"};

    char s[200] = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua." ;
    /*s1.insert(s,4);
    s1.print();
    s2.insert(s3,3);
    s2.print();*/

   /* s1.append(s);
    s1.print();
    s2.append(s3);
    s2.print();

    s1.set(s);
    s1.print();
    s2.set(s3);
    s2.print();*/

    s1.append(" ");
    s1.append(s2);
    printf("%s\n",s1.c_str());
    s1.set("Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.");
    s1.append("\n");
    printf("%zu\n",s1.size());
    s2.clear();
    for(int i=0; i<10; i++)
        s2.append(s1);
    printf("%s\n",s2.c_str());
    printf("%zu\n",s2.size());

    return 0;
}