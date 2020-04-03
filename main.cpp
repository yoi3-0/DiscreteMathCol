#include <iostream>
#include <string>
#include <utility>

using namespace std;
string errCode[]={"Действие выполнено успешно","Invalid input",};
/*
 * Классы чисел
 */
class Natur{
private:
    string ch; //само число
public:
    void init(){  //получение числа
        string str;
        cin>>str;
        this->ch=str;
    }
    void init(string str){  //получение числа
        this->ch=str;
    }
    explicit Natur(string i="0"): ch(move(i)){};
    string get(){
        return this->ch;
    }
    int size()
    {
        return this->get().length();
    }
    friend Natur operator+(Natur& left, Natur& right);
    friend Natur operator-(Natur& left, Natur& right);
    friend int COM_NN_D(Natur a, Natur b);
};
Natur operator+(Natur& left,Natur& right){
    string res,res2;
    Natur max;
    int n=0,min;
    if (left.size()<right.size()) {min=left.size(); max=right;} else {min=right.size(); max=left;}
    for (int i=1;i<=min; i++)
    {
        n+=(int)(left.get()[left.size()-i]-'0')+(int)(right.get()[right.size()-i]-'0');
        res+=(char)(n%10+'0');
       // cout<<res<<'\n'; //debug
        n/=10;
    }
    for (int i=min+1;i<=max.size(); i++)
    {
        n+=(int)(max.get()[max.size()-i]-'0');
        res+=(char)(n%10+'0');
       // cout<<res<<'\n'; //debug
        n/=10;
    }
    if (n!=0) res+=(char)(n%10+'0');
    for (int i=0;i<res.length();i++)
        res2+=res[res.length()-1-i];
    max.init(res2);
    return max;
}
Natur operator-(Natur& left, Natur& right)
{
    string a,b,rez="";
    int x,i;
    Natur res;
    if ((x=COM_NN_D(left,right))==2) {a=left.get(); b=right.get();}
    else { if (x==0) {res.init("0"); return res;} a=right.get(); b=left.get();}
    for (i=0;i<a.size()-b.size();i++) rez+=a[i];
    for (;i<a.size();i++) {
        if ((a[i] - '0') - (b[i-(a.size()-b.size())] - '0') < 0) {
            for (int j = i - 1; j >= 0; j--) {
                //cout << "debug";
                if ((rez[j] - '0') > 0) {
                    rez[j] = (char) (rez[j] - 1);
                    for (int z = j+1; z <= i - 1; z++) rez[z] = '9';
                    break;
                }
            }
            rez += (char) ((10 + a[i] - '0') - (b[i-(a.size()-b.size())] - '0') + '0');
        } else rez += (char) ((a[i] - '0') - (b[i-(a.size()-b.size())] - '0') + '0');
    }
    for (i=0;i<rez.length();i++) if (rez[i]=='0') rez.erase(i,1);
    res.init(rez);
    return res;
}
/*
 * Дополнительные функции
 */
int error(int type){  // вывод ошибки
    cerr<<errCode[type];
    return type;
}
/*
 * Функции основной работы
 */

int COM_NN_D(Natur a, Natur b) //2 if 1e>; 1 if <; 0 if ==
{
    if (a.size()>b.size()) return 2; else if (a.size()<b.size()) return 1;
    else for (int i=0;i<a.size();i++)
        if (a.get()[i]>b.get()[i]) return 2; else  if (a.get()[i]<b.get()[i]) return 1;
    return 0;
}
int NZER_N_B(Natur a) //0 if ==0, 1 if !=0
{
    if (a.get()[0]=='0' && a.size()==1) return 0; else return 1;
}
string ADD_1N_N(Natur a){
    Natur a2("1");
    return (a+a2).get();
}
string ADD_NN_N(Natur a, Natur b){
    return (a+b).get();
}
string SUB_NN_N(Natur a, Natur b){
    return (a-b).get();
}
string MUL_ND_N(Natur a, int b){
    string res="",rez="";
    int x=0; //promejutochniy result
    for (int i=a.size()-1;i>=0;i--)
    {
        x+=(a.get()[i]-'0')*b;
        res+=(char)(x%10+'0');
        x/=10;
    }
    if (x!=0) res+=(char)(x+'0'); //result<=81 that's why it should work (c) yoi3.0
    for (int i=0;i<res.length();i++)
        rez+=res[res.length()-1-i];
    return rez;
}
string MUL_Nk_N(Natur a, int k)
{
    string res=a.get();
    for (int i=0;i<k;i++) res+='0';
    return res;
}
int naturalis() //работаем с натуральными
{
    Natur n1, n2;
    int res, isOk,mnoj;
    string resStr;
    cout<<"Введите два натуральных числа";
    n1.init(); n2.init();
    int funkType;
    cout<<"\nВыбирите функцию\n"<<"1 - сравнить\n"<<"2 - проверка на ноль\n"<<"3 - добавить 1\n"
    <<"4 - Сложить\n"<<" 5 - вычесть (из большего)\n"<<"6 - умножить на число\n"<<"7 - умножить на 10^k\n"
    <<"8 - перемножить\n"<<"9 - вычесть умноженное на число\n"<<"10 - первая цифра деления (большего на меньшее)\n"
    <<"11 - частное (большее/меньшее) с остатком\n"<<"12 - остаток от деления\n"<<"13 - НОД\n"<<"14 - НОК\n";
    cin>>funkType;
    switch (funkType){
        case 1: if((res=COM_NN_D(n1,n2))==2) cout<<"Первое больше"; else res==1? cout<<"Второе больше": cout<<"Числа равны"; break;
        case 2: cout<<"Какое число сравниваем: 1е или 2е? (Введите цифру)\n";  cin>>res;
        if (res==1) res=NZER_N_B(n1); else if (res==2) res=NZER_N_B(n2); else return error(1);
        if (res==1) cout<<"Число не является нулём\n"; else cout<<"Число является нулём\n"; break;
        case 3: cout<<"Какое число сравниваем: 1е или 2е? (Введите цифру)\n";  cin>>res;
            if (res==1) resStr=ADD_1N_N(n1); else if (res==2) resStr=ADD_1N_N(n2); else return error(1);  cout<<"Получилось число "<<resStr<<'\n'; break;
        case 4: cout<<"Получилось число "<<ADD_NN_N(n1, n2)<<'\n'; break;
        case 5: cout<<"Результат вычитания "<<SUB_NN_N(n1,n2)<<'\n'; break;
        case 6: cout<<"Какое число умножаем: 1е или 2е (Введите цифру)? Затем введите множитель (тип int)\n";  cin>>res; cin>>mnoj;
            if (cin.fail() || mnoj<0) return error(1);
            if (res==1) cout<<"Результат умножения "<<MUL_ND_N(n1, mnoj)<<'\n';
            else if (res==2) cout<<"Результат умножения "<<MUL_ND_N(n2, mnoj)<<'\n'; else return error(1); break;
        case 7: cout<<"Какое число умножаем: 1е или 2е (Введите цифру)? Затем введите степень k (тип int)\n";  cin>>res; cin>>mnoj;
            if (cin.fail() || mnoj<0) return error(1);
            if (res==1) cout<<"Результат умножения "<<MUL_Nk_N(n1, mnoj)<<'\n';
            else if (res==2) cout<<"Результат умножения "<<MUL_Nk_N(n2, mnoj)<<'\n'; else return error(1); break;
        default: return error(1);
    }
    return 0;
}
int main() {
    int mode, isOk;
    cout<<"Выбери тип переменных\n"<<"1 - Натуральные\n";
    cin>>mode;
    switch(mode){
        case 1: isOk=naturalis(); break;
        default: return error(1);
    }
    return isOk;
}