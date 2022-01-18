#include <fstream>
#include <list>
#include <iostream>
#include <math.h>
using namespace std;



int is_zero(int check[], int size) {
    for (int i = 0; i < size; i++) {
        if (check[i] == 0)
            return i;
    }
}



void divHash(list<int>value_list, list<int>key_list,fstream &fp,int hashdiv[],int hashkey[],int size) {
    list<int>::iterator it, pi;
    int tmp[size];
    int tmp1[size];
    int check[size] = {0};
    int i = 0;
    for (i, it = value_list.begin(), pi = key_list.begin();
         i < size && it != value_list.end() && pi != key_list.end(); ++i, ++it, ++pi) {
        tmp[i] = *it;//wartosci
        tmp1[i] = *pi;//klucze
    }
    cout << "dziala";
    int j = 0;
    for (int j = 0; j < size; ++j) {
        if (check[tmp1[j] % size] != 1) {
            hashdiv[tmp1[j] % size] = tmp[j];
            hashkey[tmp1[j] % size] = tmp1[j];
            check[tmp1[j] % size] = 1;
        } else {
            hashdiv[is_zero(check, size)] = tmp[j];   //kolizja
            hashkey[is_zero(check, size)] = tmp1[j];
            check[is_zero(check, size)] = 1;
        }
    }

        for (int i = 0; i < size; i++) {
            fp << "tab[" << i << "]=" << hashdiv[i] << "\t klucz:" << hashkey[i] << "\tcheck[" << i << "]=" << check[i]
               << endl;
        }

    }

    void multiHash(list<int>value_list,fstream &fp,int hashmod[],int size,double A) {
        list<int>::iterator it, pi;
        int tmp[size];
        int check[size] = {0};
        int i = 0;
        for (i, it = value_list.begin(); i < size && it != value_list.end(); ++i, ++it)
            tmp[i] = *it;//wartosci
        int mod_kA;
        for (int j = 0; j < size; ++j) {
            mod_kA=size*((tmp[j]*A)-floor((tmp[j]*A)));
            //cout<<mod_kA;
            if (check[mod_kA] != 1) {
                hashmod[mod_kA] = tmp[j];
                check[mod_kA] = 1;
            } else {
                hashmod[is_zero(check, size)] = tmp[j];
                check[is_zero(check, size)] = 1;
            }
        }

        for (int i = 0; i < size; i++) {
            fp << "tab[" << i << "]=" << hashmod[i] << "\t klucz:" << A << "\tcheck[" << i << "]=" << check[i] << endl;

        }

    }
void print_to_file1(list<int>value_list,fstream &fp,double A)
{
    list<int>::iterator it;
    int i=0;
    for (it=value_list.begin();it!=value_list.end() ; ++it) {
        fp<<"tab["<<i<<"] ="<<*it<<"\t klucz:"<<A<<endl;
        i++;
    }

}

void print_to_file(list<int>value_list, list<int>key_list,fstream &fp){
    list<int>::iterator it,pi;
    int i=0;
    for (it=value_list.begin(),pi=key_list.begin();it!=value_list.end() && pi!=key_list.end() ; ++it,++pi) {
        fp<<"tab["<<i<<"] ="<<*it<<"\t klucz:"<<*pi<<endl;
        i++;
    }
}


int main() {
fstream fp;
fp.open("TH.txt",ios:: out);
if(fp.good())
    cout<<"otwarto plik"<<endl;

int size,key,value;
cout<<"podaj rozmiar tablicy:";
cin>>size;
int hashdiv[size];
int hashkey[size];
int hashmod[size];


    cout<<"----------------------------"<<endl;
cout<<"[1] div hashing"<<endl;
cout<<"[2] multi hashing"<<endl;
int q;
cin>>q;
    switch (q) {

        case 1:{
            list<int> value_list, key_list;                 //czy funkcja w c++ mozna jakos obejsc zwracanie list ?
            int a,b;
            for (int i = 1; i <= size; ++i) {
                cout<<"podaj wartosc:";
                cin>>a;
                value_list.push_back(a);
                cout<<"podaj klucz:";
                cin>>b;
                key_list.push_back(b);
            }

            fp<<"--BEZ HASHOWANIA--"<<endl;
            print_to_file(value_list, key_list,fp);
            fp<<"--DIV HASH--"<<endl;
            divHash(value_list,key_list,fp,hashdiv,hashkey,size);
            break;
        }
        case 2:
        {
            list<int> value_list;
            int a;
            for (int i = 1; i <= size; ++i) {
                cout << "podaj wartosc:";
                cin >> a;
                value_list.push_back(a);
            }

            cout<<endl;
            double A;
            cout<<"podaj stala A <0.1,1>"<<endl;
            cin>>A;

            fp<<"-----BEZ HASHOWANIA-----"<<endl;
            print_to_file1(value_list,fp,A);
            fp<<"--MULTI HASHING"<<endl;
            multiHash(value_list,fp,hashmod,size,A);
            break;
        }

    }

fp.close();
    return 0;
}
