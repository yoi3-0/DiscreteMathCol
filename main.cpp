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
    explicit Natur(string i): ch(move(i)){};
    string get(){
        return this->ch;
    }
    int size()
    {
        return this->get().length();
    }
    friend const Natur operator+(const Natur& left, const Natur& right);
};
const Natur operator+(const Natur& left, const Natur& right){
    string res;
    int n=0;





    
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

int COM_NN_D(Natur a, Natur b) //1 if 1e>; 2 if <; 3 if ==
{
    if (a.size()>b.size()) return 1; else if (a.size()<b.size()) return 2;
    else for (int i=0;i<a.size();i++)
        if (a.get()[i]>b.get()[i]) return 1; else  if (a.get()[i]<b.get()[i]) return 2;
    return 3;
}
int NZER_N_B(Natur a) //0 if ==0, 1 if !=0
{
    if (a.get()[0]=='0' && a.size()==1) return 0; else return 1;
}
int naturalis() //работаем с натуральными
{
    Natur n1, n2;
    int res, isOk;
    cout<<"Введите два натуральных числа";
    n1.init(); n2.init();
    int funkType;
    cout<<"\nВыбирите функцию\n"<<"1 - сравнить\n"<<"2 - проверка на ноль\n"<<"3 - добавить 1\n"
    <<"4 - Сложить\n"<<" 5 - вычесть (из большего)\n"<<"6 - умножить на число\n"<<"7 - умножить на 10^k\n"
    <<"8 - перемножить\n"<<"9 - вычесть умноженное на число\n"<<"10 - первая цифра деления (большего на меньшее)\n"
    <<"11 - частное (большее/меньшее) с остатком\n"<<"12 - остаток от деления\n"<<"13 - НОД\n"<<"14 - НОК\n";
    cin>>funkType;
    switch (funkType){
        case 1: if((res=COM_NN_D(n1,n2))==1) cout<<"Первое больше"; else res==2? cout<<"Второе больше": cout<<"Числа равны"; break;
        case 2: cout<<"Какое число сравниваем: 1е или 2е? (Введите цифру)\n";  cin>>res;
        if (res==1) res=NZER_N_B(n1); else if (res==2) res=NZER_N_B(n2); else return error(1);
        if (res==1) cout<<"Число не является нулём\n"; else cout<<"Число является нулём\n"; break;
        case 3: out<<"Какое число сравниваем: 1е или 2е? (Введите цифру)\n";  cin>>res;
            if (res==1) res=ADD_1N_N(n1); else if (res==2) res=ADD_1N_N(n2); else return error(1);  cout<<"Получилось число"<<res<<'\n'; break;
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