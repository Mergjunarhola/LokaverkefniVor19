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
    
    float Ofset=4;
    float RaX1=-2;
    float RaX2=RaX1+Ofset;
    float RaY1=-2;
    float RaY2=RaY1+Ofset;
    int iter=30;
    int ResX=1000;
    int ResY=1000;
    int RaSize=ResX*ResY;
    unsigned char Mapid[RaSize];
    float staX;
    float staY;
    int fjol=0;
    float Temp;
    float Xcar;
    float Ycar;
    int Maploc;
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


    for (int y = 0; y < ResY; y++)
    {
        for (int x = 0; x < ResX; x++)
        {
            staX=(x/((float)ResX/(RaX2-RaX1)))+RaX1;
            staY=(y/((float)ResY/(RaY2-RaY1)))+RaY1;
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
            //cout<<fjol;
            Maploc=y*ResY+x;
            Mapid[Maploc]=fjol;
        }
        
    }
    
    ofstream out;
    out.open("Set77.bmp");
    for (int i = 0; i < 54; i++)
    {
        out<<BmpDibH[i];
    }

    for (int x = 0; x < RaSize; x++)
    {
        //cout<<Mapid;
        
        fjol=Mapid[x]%6;
        if (Mapid[x]==iter){fjol=6;}
        Maploc=colors[fjol];
        for(int i = 0;i < 0x3; i++){
        out<<(char)(Maploc%256);
        Maploc=Maploc/256;
        }
    }
    


    out.close();
    return 0;
}


