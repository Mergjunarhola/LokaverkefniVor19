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

2. BMP pixle arrray eru lesin þannig að fyrst er teiknað til vinstri svo upp. 
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

#include <string>
#include <fstream>
#include <iostream>


/*
DIB      40
Header   14

total    54

rest: hæð*(breidd*(bit_color/8)+(4%(breidd*(bit_color/8))))
eða: hæð*(breidd*3+4%(breidd*3))




*/





int main(void){
    int X1= -2;
    int X2= 2;
    int Y1= -2;
    int Y2= 2;
    int resX=200;
    int resY=200;
    int iter= 7;
    

}