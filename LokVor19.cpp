//LokaverkefniVor19
//Dags: 1/5/2019
//Höfundur: Jón Benediktsson

/*      Efnis Yfirlit
þetta forrit verður til þess að koma framm formúlum í myndrænt form
efnis yfirlit:
    Hex Útskýring   : Lína 13
    BMP Útskýringar : Lína 22
*/


/*      Hex Útskýringar
1. þegar maður er að lesa hex þá er grúpað allt í tölur af tveimur hex og svo lesið afturábak 
   þannig talan 00 01 E3 mundi vera skrifuð E3 01 00. frekar ruglandi en maður þarf bara að díla við það.

2. bmp pixle arrray eru lesin þannig að fyrst er teiknað til vinstri svo upp. 
   það þarf líka að setja inn padding þannig að hver vertical layer er margfeldi af 4 í bytes,
   þetta er gott að vita þegar maður er að nota eithvað annað en 32 bit color

*/

/*      BMP Útskýringar
|staðsetning 
|    |stærð 
|    |   |Hex tala 
|    |   |             |Útskýring
+----+---+-------------+-------BMP Header-----------------------------------------------------------------
|  0h| 2 | 42 4D       |id feild. segir til um að þetta sé bitmap(BM) ef það er "42 4D"
|    |   |             |
|  2h| 4 | 46 00 00 00 |heildar stærðin á skjalinu í bytes
|    |   |             |
|  6h| 2 | 00 00       |segir "Application specific", veit ekkert hvað í fjáranum þetta tvent gerir
|  8h| 2 | 00 00       |
|    |   |             |
|  Ah| 4 | 36 00 00 00 | "h" staðsetningin sem er hægt að finna "Pixle Array"-ið á
|    |   |             |
+----+---+-------------+-------DIB Header-----------------------------------------------------------------
|  Eh| 4 | 28 00 00 00 | fjöldi bytes í DIB Header-inum
|    |   |             |
| 12h| 4 | 02 00 00 00 | breyddin á myndini
|    |   |             |
| 16h| 4 | 02 00 00 00 | hæð á myndini
|    |   |             |
| 1Ah| 2 | 01 00       | hefur eithvað að gera með "Color Planes"
|    |   |             |
| 1Ch| 2 | 18 00       | gefur mér 24 bit color
|    |   |             |
| 1Eh| 4 | 00 00 00 00 | hefur eithvað að gera með "BI_RGB"
|    |   |             |
| 22h| 4 | 00 00 00 00 | stærðin á "pixle_array"-inu í bytes
|    |   |             |
| 26h| 4 | 13 0B 00 00 | print resolution 72 DPI 
| 2Ah| 4 | 13 0B 00 00 |
|    |   |             |
| 2Eh| 4 | 00 00 00 00 | hefur eithvað að gera með "Number of colors in the palette"
|    |   |             |
| 32h| 4 | 00 00 00 00 | hefur eithvað að gera með "color importance"
|    |   |             |
+----+---+-------------+-------Pixle Array(Bitmap data)---------------------------------------------------
|    |   |             |
|    |   |             |
|    |   |             |
|    |   |             |
|    |   |             |
*/

/*  Lazy enianizer™
char g[4];
int lab=12333;
for(int i = 0;i < 4; i++){
    g[i]=lab%256;
    lab=lab/256;
}


*/

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
        //cout<<"Fractal Type object created"<<endl;
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

int main(void){
    //þetta er til að skrifa allt draslið sem er í BMP útskýringar
    char BmpDibH[54];
    int BmpTemp;
    for(int i = 0; i < 54; i++){
        BmpDibH[i]=0;
    }
    BmpDibH[0]='B';
    BmpDibH[1]='M';
    BmpDibH[10]=0x36;
    BmpDibH[0x0E]=0x28;
    BmpDibH[0x1A]=1;
    BmpDibH[0x1C]=0x18;
    
    
    int iter=30;
    int ResX=30;
    int ResY=30;
    int RaSize=ResX*ResY;
    unsigned int ColorCar;
    int colors[7]={0x3333FF,0x33FFFF,0x33FF33,0xFFFF33,0xFF3333,0xFF33FF,0x000000};

// til að endian-a stærð og annað
// ég veit að þetta er super lazy
    BmpTemp=ResX;
    for(int i = 0x12;i < 0x16; i++){
        BmpDibH[i]=BmpTemp%256;
        BmpTemp=BmpTemp/256;
    }
    BmpTemp=ResY;
    for(int i = 0x16;i < 0x1A; i++){
        BmpDibH[i]=BmpTemp%256;
        BmpTemp=BmpTemp/256;
    }
    BmpTemp=RaSize*3;
    for(int i = 0x22;i < 0x26; i++){
        BmpDibH[i]=BmpTemp%256;
        BmpTemp=BmpTemp/256;
    }
    BmpTemp=(RaSize*3)+54;
    for(int i = 2;i < 6; i++){
        BmpDibH[i]=BmpTemp%256;
        BmpTemp=BmpTemp/256;
    }

    ofstream out;
    out.open("julian1.bmp");
    for (int i = 0; i < 54; i++)
    {
        cout<<BmpDibH[i];
        out<<(char)BmpDibH[i];
    }


    Julian Mapid;




    
    for (int y = 0; y < ResY; y++)
    {
        for (int x = 0; x < ResX; x++)
        {
            ColorCar=Mapid.FormulaOutput(x,y);
        if (ColorCar==iter){ColorCar=6;}
        else{ColorCar=ColorCar%6;}
        
        ColorCar=colors[ColorCar];
        for(int i = 0;i < 0x3; i++){
        out<<(char)(ColorCar%256);
        ColorCar=ColorCar/256;
        }
            
        }
        
    }
    
    

    out.close();
    return 0;
}


