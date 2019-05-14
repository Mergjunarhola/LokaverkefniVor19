#include <fstream>
#include <iostream>
#include <string>
using namespace std;

class FractalMap
{
protected:
    float Ofset=4;
    float RaX=-2;
    float RaY=-2;
    int iter=30;
    unsigned int ResX=1000;
    unsigned int ResY=1000;
    unsigned int RaSize=ResX*ResY;
    float staX;
    float staY;
    int fjol=0;
    float Temp;
    float Xcar;
    float Ycar;
    int Maploc;
public:
    FractalMap(){
        cout<<"Fractal Type object created"<<endl;
    };
    void Zoom(float Zoomage){
        RaX=RaX+(Ofset-Ofset/Zoomage)/2;
        RaY=RaY+(Ofset-Ofset/Zoomage)/2;
        Ofset=Ofset-Ofset/Zoomage;
    };
    void Hlidra(float X,float Y){
        RaX=RaX+Ofset*X;
        RaY=RaY+Ofset*Y;
    };

};

class Mandelbrot: public FractalMap{
    public:
        unsigned int FormulaOutput(int X,int Y){
            staX=(X/((float)ResX/(Ofset)))+RaX;
            staY=(Y/((float)ResY/(Ofset)))+RaY;
            Xcar=0;
            Ycar=0;
            fjol=0;
            while ((fjol<iter)&&(Xcar*Xcar+Ycar*Ycar<=4))
            {
                Temp=Xcar*Xcar - Ycar*Ycar + staX;
                Ycar= 2*Ycar*Xcar + staY;
                Xcar=Temp;
                fjol++;
            }
            return fjol;
        };
};

class Julian: public FractalMap{
    private:
        float CX=-0.8;
        float CY=0.156;
    public:
        void Change_C(float X,float Y){
            CX=X;
            CY=Y;
        };
        unsigned int FormulaOutput(int X,int Y){
            staX=(X/((float)ResX/(Ofset)))+RaX;
            staY=(Y/((float)ResY/(Ofset)))+RaY;
            Xcar=0;
            Ycar=0;
            fjol=0;
            while ((fjol<iter)&&(Xcar*Xcar+Ycar*Ycar<=4))
            {
                Temp=Xcar*Xcar - Ycar*Ycar + staX + CX;
                Ycar= 2*Ycar*Xcar + staY + CY;
                Xcar=Temp;
                fjol++;
            }
            return fjol;
        };
};








int main(void)
{
    Julian Test;
    cout <<Test.FormulaOutput(500,500);
    return 0;
}


