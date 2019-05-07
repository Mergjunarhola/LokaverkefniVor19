#include <fstream>
#include <iostream>
#include <string>
int main(void){
    char g = '&';
    string h="";
    h<<g<<g;
    std::ofstream out;
    out.open("ananas");
    out<<h;
    out.close();
    return 0;
}