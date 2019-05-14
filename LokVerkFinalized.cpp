#include <fstream>
#include <iostream>
#include <string>
#include "LokClas.h"
using namespace std;

int main(void){
    int colors[7]={0x3333FF,0x33FFFF,0x33FF33,0xFFFF33,0xFF3333,0xFF33FF,0x000000};
    unsigned int ColorCar;
    int iter=30;
    int Res=1000;
    float C1=0;
    float C2=0;
    int Aval;
    int Ival;
    cout<<"veldu 1 fyrir mandelbrot set"<<endl;
    cout<<"veldu 2 fyrir Julian set"<<endl;
    cin>>Aval;
    //Mandelbrot Preview;
    BmpH PreBmpH=BmpH(100);
    BmpH OutBmpH=BmpH(Res);
    if (Aval==1){
        Mandelbrot Mapid;
        Mandelbrot Preview;
        Preview.setResIt(100,iter-20);
        while(true){
            cout<<endl;
            cout<<"veldu 1 til ad hlidra"<<endl;
            cout<<"veldu 2 til ad zooma"<<endl;
            cout<<"veldu 3 til ad breyta gaedum"<<endl;
            cout<<"veldu 4 til ad breyta iterations"<<endl;
            cout<<"veldu 5 til ad prenta"<<endl;
            cout<<"veldu 6 til ad breaka"<<endl;
            cin>>Ival;
            //hliðrun
            if (Ival==1){
                //hliðra á Xás
                cout<<"hlidrun a X asnum: ";
                cin>>C1;
                //hliðra á Yás
                cout<<endl<<"hlidrun a Y asnum: ";
                cin>>C2;
                cout<<endl;
                Mapid.Hlidra(C1,C2);
                Preview.Hlidra(C1,C2);
            }
            //Zoom
            else if (Ival==2)
            {   cout<<"Hvad viltu zooma mikid: ";
                cin>>C1;
                cout<<endl;
                Mapid.Zoom(C1);
                Preview.Zoom(C1);
            }
            //Resolution
            else if (Ival==3)
            {   cout<<"Hvad viltu ad gaedin a myndini se: ";
                cin>>Res;
                cout<<endl;
                OutBmpH.ChRes(Res);
                Mapid.setResIt(Res,iter);
            }
            //Iterations
            else if (Ival==4)
            {   cout<<"Hvad viltu ad seu morg iterations: ";
                cin>>iter;
                cout<<endl;
                Preview.setResIt(100,iter-20);
                Mapid.setResIt(Res,iter);
            }
            //Print
            else if (Ival==5)
            {
                ofstream Setout;
                Setout.open("Set.bmp",ios::binary);
                for (int i = 0; i < 54; i++)
                {
                Setout<<(char)OutBmpH.GetSpecific(i);
                }
                for (int y = 0; y < Res; y++)
                    {
                    for (int x = 0; x < Res; x++)
                    {
                        ColorCar=Mapid.FormulaOutput(x,y);
                        if (ColorCar==iter){ColorCar=6;}
                        else{ColorCar=ColorCar%6;}
        
                        ColorCar=colors[ColorCar];
                        for(int i = 0;i < 0x3; i++){
                            Setout<<(char)(ColorCar%256);
                            ColorCar=ColorCar/256;
                        }
                    }
        
                }
                Setout.close();
            }
            else if (Ival==6)
            {
                break;
            }
            
            






    ofstream Pout;
    Pout.open("Preview.bmp",ios::binary);
    for (int i = 0; i < 54; i++)
    {
        Pout<<(char)PreBmpH.GetSpecific(i);
    }
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            ColorCar=Preview.FormulaOutput(x,y);
        if (ColorCar==iter-20){ColorCar=6;}
        else{ColorCar=ColorCar%6;}
        
        ColorCar=colors[ColorCar];
        for(int i = 0;i < 0x3; i++){
        Pout<<(char)(ColorCar%256);
        ColorCar=ColorCar/256;
        }
        }
        
    }
    Pout.close();




    }
    }
    else if (Aval==2){
        Julian Mapid;
        Julian Preview;
        Preview.setResIt(100,iter-20);
        while(true){
            cout<<endl;
            cout<<"veldu 1 til ad hlidra"<<endl;
            cout<<"veldu 2 til ad zooma"<<endl;
            cout<<"veldu 3 til ad breyta gaedum"<<endl;
            cout<<"veldu 4 til ad breyta iterations"<<endl;
            cout<<"veldu 5 til ad breyta C gildinu"<<endl;
            cout<<"veldu 6 til ad prenta"<<endl;
            cout<<"veldu 7 til ad breaka"<<endl;
            cin>>Ival;
            //hliðrun
            if (Ival==1){
                //hliðra á Xás
                cout<<"hlidrun a X asnum: ";
                cin>>C1;
                //hliðra á Yás
                cout<<endl<<"hlidrun a Y asnum: ";
                cin>>C2;
                cout<<endl;
                Mapid.Hlidra(C1,C2);
                Preview.Hlidra(C1,C2);
            }
            //Zoom
            else if (Ival==2)
            {   cout<<"Hvad viltu zooma mikid: ";
                cin>>C1;
                cout<<endl;
                Mapid.Zoom(C1);
                Preview.Zoom(C1);
            }
            //Resolution
            else if (Ival==3)
            {   cout<<"Hvad viltu ad gaedin a myndini se: ";
                cin>>Res;
                cout<<endl;
                OutBmpH.ChRes(Res);
                Mapid.setResIt(Res,iter);
            }
            //Iterations
            else if (Ival==4)
            {   cout<<"Hvad viltu ad seu morg iterations: ";
                cin>>iter;
                cout<<endl;
                Preview.setResIt(100,iter-20);
                Mapid.setResIt(Res,iter);
            }
            else if (Ival==5)
            {   //endurstaðsetja C á Xás
                cout<<"endurstadsetja C a X asnum: ";
                cin>>C1;
                //endurstaðsetja C á Yás
                cout<<endl<<"endurstadsetja C a Y asnum: ";
                cin>>C2;
                cout<<endl;
                Mapid.Change_C(C1,C2);
                Preview.Change_C(C1,C2);
            }
            //Print
            else if (Ival==6)
            {
                ofstream Setout;
                Setout.open("Set.bmp",ios::binary);
                for (int i = 0; i < 54; i++)
                {
                Setout<<(char)OutBmpH.GetSpecific(i);
                }
                for (int y = 0; y < Res; y++)
                    {
                    for (int x = 0; x < Res; x++)
                    {
                        ColorCar=Mapid.FormulaOutput(x,y);
                        if (ColorCar==iter){ColorCar=6;}
                        else{ColorCar=ColorCar%6;}
        
                        ColorCar=colors[ColorCar];
                        for(int i = 0;i < 0x3; i++){
                            Setout<<(char)(ColorCar%256);
                            ColorCar=ColorCar/256;
                        }
                    }
        
                }
                Setout.close();}
                else if (Ival==7)
                {
                break;
                }
            
            






    ofstream Pout;
    Pout.open("Preview.bmp",ios::binary);
    for (int i = 0; i < 54; i++)
    {
        Pout<<(char)PreBmpH.GetSpecific(i);
    }
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            ColorCar=Preview.FormulaOutput(x,y);
        if (ColorCar==iter-20){ColorCar=6;}
        else{ColorCar=ColorCar%6;}
        
        ColorCar=colors[ColorCar];
        for(int i = 0;i < 0x3; i++){
        Pout<<(char)(ColorCar%256);
        ColorCar=ColorCar/256;
        }
        }
        
    }
    Pout.close();}




    }
};