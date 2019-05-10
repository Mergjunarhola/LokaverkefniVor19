#include <fstream>
#include <iostream>
#include <string>
int main(void){
    /*
    char g[54];
    for(int i = 0; i < 54; i++){
        g[i]=0;
    }
    g[0]='B';
    g[1]='M';
    g[11]=0x36;
    g[0x0E]=0x28;
    g[0x1A]=1;
    g[0x1C]=32;
    */
    int colors[7]={0x3333FF,0x33FFFF,0x33FF33,0xFFFF33,0xFF3333,0xFF33FF,0xFFFFFF};
    char g[4];
    int lab=colors[1];
    for(int i = 0;i < 4; i++){
        g[i]=lab%256;
        lab=lab/256;
    }
    

    std::ofstream out;
    out.open("ananas");
    for(int i = 0;i < 4; i++){
        out<<g[i];
    }
    out.close();
    return 0;
}