#include <iostream>
#include <string>

using namespace std;
string errCode[]={"ok","Invalid input",};
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
    string get(){
        return this->ch;
    }

};
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
int naturalis() //работаем с натуральными
{
    Natur n1, n2;
    int isOk;
    cout<<"Введите два натуральный числа";
    n1.init(); n2.init();
    int funkType;
    cout<<"\nВыбирите функцию\n"<<"1 - сравнить\n"<<"2 - проверка на ноль\n"<<"3 - добавить 1\n"
    <<"4 - Сложить\n"<<" 5 - вычесть (из большего)\n"<<"6 - умножить на число\n"<<"7 - умножить на 10^k\n"
    <<"8 - перемножить\n"<<"9 - вычесть умноженное на число\n"<<"10 - первая цифра деления (большего на меньшее)\n"
    <<"11 - частное (большее/меньшее) с остатком\n"<<"12 - остаток от деления\n"<<"13 - НОД\n"<<"14 - НОК\n";
    cin>>funkType;
    switch (funkType){
        case 1: isOk=COM_NN_D(); break;
        default: return error(1);
    }
    if (!isOk) error(isOk);
    return isOk;
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