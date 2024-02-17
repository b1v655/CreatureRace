#include "leny.h"


void lepegeto::lepes(char nap)
{
    if ( el_e() ){
        switch(nap){
            case 'e':vizmennyiseg+=3;tav+=1;if(vizmennyiseg>12)vizmennyiseg=12;
                    break;
            case 'n':vizmennyiseg-=2;tav+=1;
                    break;
            case 'f':vizmennyiseg-=1;tav+=2;
                    break;
        }
    }
}

void szivacs::lepes(char nap)
{
    if ( el_e() ){
        switch(nap){
            case 'e':vizmennyiseg+=6;tav+=3;if(vizmennyiseg>20)vizmennyiseg=20;
                    break;
            case 'n':vizmennyiseg-=4;tav+=0;
                    break;
            case 'f':vizmennyiseg-=1;tav+=1;
                    break;
        }
    }
}

void homokjaro::lepes(char nap)
{
    if ( el_e() ){
        switch(nap){
            case 'e':vizmennyiseg+=3;tav+=0;if(vizmennyiseg>8)vizmennyiseg=8;
                    break;
            case 'n':vizmennyiseg-=1;tav+=3;
                    break;
            case 'f':vizmennyiseg-=0;tav+=1;
                    break;
        }
    }
}
