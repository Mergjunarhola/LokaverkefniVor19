
class FractalMap
{
protected:
    float Ofset=4;
    float RaX=-2;
    float RaY=-2;
    int iter=30;
    unsigned int Res=400;
    unsigned int RaSize=Res*Res;
    float staX;
    float staY;
    int fjol=0;
    float Temp;
    float Xcar;
    float Ycar;
    int Maploc;
public:
    FractalMap(){
        //cout<<"Fractal Type object created"<<endl;
    };
    void Zoom(float Zoomage){
        RaX=RaX+(Ofset/2-Ofset/(Zoomage*2));
        RaY=RaY+(Ofset/2-Ofset/(Zoomage*2));
        Ofset=Ofset/Zoomage;
    };
    void Hlidra(float X,float Y){
        RaX=RaX+Ofset*X;
        RaY=RaY+Ofset*Y;
    };
    void setResIt(int Resolution, int Iterations){
        Res=Resolution;
        iter=Iterations;
    };

};

class Mandelbrot: public FractalMap{
    public:
        unsigned int FormulaOutput(int X,int Y){
            staX=(X/((float)Res/(Ofset)))+RaX;
            staY=(Y/((float)Res/(Ofset)))+RaY;
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
            staX=(X/((float)Res/(Ofset)))+RaX;
            staY=(Y/((float)Res/(Ofset)))+RaY;
            Xcar=staX;
            Ycar=staY;
            fjol=0;
            while ((fjol<iter)&&(Xcar*Xcar+Ycar*Ycar<=4))
            {
                Temp=Xcar*Xcar - Ycar*Ycar+ CX;
                Ycar= 2*Ycar*Xcar + CY;
                Xcar=Temp;
                fjol++;
            }
            return fjol;
        };
};
