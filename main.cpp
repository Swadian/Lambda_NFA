#include <fstream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;
struct tranzitie
{
  int destinatie;
  char litera;
};
int main()
{
    vector<tranzitie> l[1000];
    string cuv;
    unordered_set<int> setF;
    unordered_set<int> setCurrent;
    unordered_set<int>setNext;
    ofstream fout("date.out");
    ifstream fin("date.in");
    int n;
    fin>>n;
    int dump;
    for(int i=0;i<n;i++)
        fin>>dump;//eliminam numerele starilor din fisier, nu ne trebuie
    int m;
    fin>>m;
    tranzitie trn;
    int x;
    for(int i=0;i<m;i++)
    {
        fin>>x>>trn.destinatie>>trn.litera;
        l[x].push_back(trn);
    }//adaug tranzitiile in listele corespunzatoare
    int s;fin>>s;
    int nrF;fin>>nrF;
    int state;
    for(int i=0;i<nrF;i++)
    {fin>>state; setF.insert(state);}//adaug starile finale in setul respectiv
    int currentstate;
    int nrCuv;
    fin>>nrCuv;
    bool accepted;
    for(int i=0;i<nrCuv;i++)//procesarea pe cuvant
    {
        accepted=false;
        fin>>cuv;
        setCurrent.clear();
        setNext.clear();
        setCurrent.insert(s);//adaug starea initiala
        for(int j=0;j<(int)cuv.size();j++)//procesarea pe litere
        {
            for(auto it=setCurrent.begin();it!=setCurrent.end();++it)
            {
                currentstate=*it;
                for(int k=0;k<(int)l[currentstate].size();k++)//ii parcurg lista de adiacenta pt lambda
                 {
                    if(l[currentstate][k].litera=='*')//consider * ca fiind lambda
                        setCurrent.insert(l[currentstate][k].destinatie);//pun in set toate in care poate ajunge
                }
            }
            for(auto it=setCurrent.begin();it!=setCurrent.end();++it)
            {
                currentstate=*it;//scot starea curenta din set
                for(int k=0;k<(int)l[currentstate].size();k++)//ii parcurg lista de adiacenta
                {
                    if(l[currentstate][k].litera==cuv[j])
                        {
                            setNext.insert(l[currentstate][k].destinatie);
                        }//adaug starile in care poate ajunge
                }
            }
            setCurrent=setNext;
            setNext.clear();
        }
        for(auto it=setCurrent.begin();it!=setCurrent.end();++it)//verific daca a ajuns la vreo stare finala
            {
                currentstate=*it;//scot starea curenta din set
            if(setF.count(currentstate)!=0)
            {
                fout<<"DA\n";
                accepted=true;
                break;
            }
        }
        if(!accepted)fout<<"NU\n";
    }
    fin.close();
    fout.close();
    return 0;
}
