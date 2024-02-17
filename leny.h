#ifndef LENY_H
#define LENY_H

#include <string>

class leny
{
    protected:
        int vizmennyiseg;
        int tav;
        std::string nev;
        leny(std::string n,int v,int t=0): nev(n),vizmennyiseg(v),tav(t){}
    public:

        virtual ~leny() {}
        virtual void lepes(char nap)=0;
        bool el_e(){return vizmennyiseg>0;}
        int viz(){return vizmennyiseg;}
        std::string neve(){return nev;}
        int tavolsag(){return tav;}



};
class lepegeto: public leny
{
    public:
        lepegeto(std::string n,int v,int t=0):leny(n,v,t){}
        void lepes(char nap) override;
};
class homokjaro: public leny
{
    public:
        homokjaro(std::string n,int v, int t=0):leny(n,v,t){}
        void lepes(char nap) override;
};
class szivacs: public leny
{
    public:
        szivacs(std::string n,int v,int t=0):leny(n,v,t){}
        void lepes(char nap) override;
};
#endif // LENY_H
