#include <bits/stdc++.h>

using namespace std;
typedef int ll;
#define pb push_back

int n;
string s;
int se_pojavila_karta[5][13];
int nesmije_koristiti_boju[6][6];
string igraci[5]={"SONJA","VIKTOR","IGOR","LEA","MARINO"};
vector< pair<int,int> > paradoksi;

int main(){
    cin>>n;
    int ig=0;   //tko pocinje rundu - 1. rundu zapocinje SONJA pa imamo ig=0
    int pob,najboj,najk,boja_runde;
    for(int i=1;i<=n;i++){
        int tren=ig; //trenutni igrac
        for(int j=0;j<5;j++){

            cin>>s;
            char boja=s[0]; int boj,br=(int)(s[1]-'0');
            if(boja=='C'){boj=0;}
            if(boja=='P'){boj=1;}
            if(boja=='Y'){boj=2;}
            if(boja=='Z'){boj=3;}

            if(j==0){boja_runde=boj; najboj=boj; najk=br; pob=ig; }

            if(se_pojavila_karta[boj][br] || nesmije_koristiti_boju[tren][boj]){
                paradoksi.pb({i,tren});
                tren++;
                if(tren>=5){tren-=5;}
                continue;
            }
            se_pojavila_karta[boj][br]=1;
            if(boj!=boja_runde){nesmije_koristiti_boju[tren][boja_runde]=1;}

            if((boj!=najboj && boj==0) || (boj==najboj && br>najk)){
                najboj=boj; najk=br; pob=tren;
            }

            tren++;
            if(tren>=5){tren-=5;}
        }
        ig=pob;
    }

    int p=(int)paradoksi.size();
    cout<<p<<endl;
    for(int i=0;i<p;i++){
        int x=paradoksi[i].first,y=paradoksi[i].second;
        cout<<x<<" "<<igraci[y]<<endl;
    }
    return 0;
}

