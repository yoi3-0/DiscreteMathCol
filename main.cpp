#include <iostream>
#include <string>
#include<locale.h>
#include <utility>
#include <map>

using namespace std;
string errCode[]={"Действие выполнено успешно","Invalid input", "Давайте без стрельбы в колено"};
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
        this->init(str);
    }
    void init(string str){  //получение числа
       // for (size_t i=0;i<str.length(); i++ ) if(!isdigit(str[i])){ this->ch="inv"; return;}
        this->ch=str;
    }
    explicit Natur(string i="0"): ch(move(i)){};
    string get() const {
        return this->ch;
    }
    int size()
    {
        return this->get().length();
    }
    friend Natur operator+(Natur& left, Natur& right);
    friend Natur operator-(Natur& left, Natur& right);
    friend Natur operator*(Natur& left, Natur& right);
    friend int COM_NN_D(Natur a, Natur b);
    friend string MUL_Nk_N(Natur a, int k);
    friend string MUL_ND_N(Natur a, int b);
    friend string DIV_NN_Dk(Natur a, Natur b);
    friend string MUL_NN_N(Natur a, Natur b);
    friend string SUB_NN_N(Natur a, Natur b);
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
    for (i=0; rez[i]=='0' ;)  rez.erase(i,1);
    if (rez=="") rez="0";
    res.init(rez);
    return res;
}
Natur operator*(Natur& left, Natur& right){
    Natur helper;
    Natur result;
    result.init("0");
    if (left.get()=="0") return result;
    for (int i=0;i<right.size();i++)
    {
        helper.init(MUL_ND_N(left, right.get()[right.size()-1-i]-'0'));
        //cout<<MUL_ND_N(left, right.get()[i]-'0')<<'\n';
        helper.init(MUL_Nk_N(helper, i));
        result=result+helper;
    }
    return result;
}
Natur operator/(Natur& left, Natur& right) {
    Natur delim(left.get()), helper;
    Natur result,init("0");
    while (COM_NN_D(delim,right)==2 || COM_NN_D(delim,right)==0)
    {
        helper.init(DIV_NN_Dk(delim, right)); //первая цифра деления на 10^k
       // cout<<helper.get()<<" - первая цифра деления";
       // cout<<"Число="<<helper.get()<<'\n';
        result = result + helper;
      //  cout<<"Итог="<<result.get()<<'\n';
        helper=right*helper; //умножение a*b
      //  cout<<"делитель на частное="<<helper.get()<<'\n';
        delim=delim-helper; //ычитание меньшего
        //cout<<"Делимое="<<delim.get()<<'\n';
        //321/10 => 321-100*3-10*2+1
    }
    return result;
}
Natur operator%(Natur& left, Natur& right) {
    Natur delim(left.get()), helper;
    Natur result,init("0");
    while (COM_NN_D(delim,right)==2 || COM_NN_D(delim,right)==0)
    {
        helper.init(DIV_NN_Dk(delim, right)); //первая цифра деления на 10^k
       // cout<<"Число="<<helper.get()<<'\n';
        result = result + helper;
        // cout<<"Итог="<<result.get()<<'\n';
        helper=right*helper; //умножение a*b
       // cout<<"делитель на частное="<<helper.get()<<'\n';
        delim=delim-helper; //ычитание меньшего
       // cout<<"Делимое="<<delim.get()<<'\n';
        //321/10 => 321-100*3-10*2+1
    }
    return delim;
}
class Zahlen{
private:
    Natur ch;
    short int znak;
public:
    void init(){  //получение числа
        string str;
        short int zn;
        cin>>str;
        if (str[0]=='-'){ zn=-1; str.erase(0,1);}
        else zn=1;
        this->ch.init(str);
        this->znak=zn;
    }
    void init(string str){  //получение числа
        int zn;
        if (str[0]=='-'){ zn=-1; str.erase(0,1);}
        else zn=1;
        this->ch.init(str);
        this->znak=zn;
    }
    void init(string str, int zn){  //получение числа
        if (str[0]=='-') str.erase(0,1);
        this->ch.init(str);
        this->znak=zn;
    }
    void init(Natur a){  //получение числа
        this->ch=a;
        this->znak=1;
    }
    void mulZnak(int i)
    {this->znak*=i;}
    string get(){
        return this->znak==-1?('-'+this->ch.get()):this->ch.get();
    }
    string abs(){
        return this->ch.get();
    }
    Natur absN()
    {return this->ch;}
    int getZnak()
    { return this->znak;}
    friend Zahlen operator+(Zahlen& left, Zahlen& right);
    friend Zahlen operator-(Zahlen& left, Zahlen& right);
    friend Zahlen operator*(Zahlen& left, Zahlen& right);
    friend Zahlen operator/(Zahlen& left, Zahlen& right);
    friend Zahlen operator%(Zahlen& left, Zahlen& right);
};
Zahlen operator+(Zahlen& left, Zahlen& right)
{
   Natur a,b;
   Zahlen res;
   int x;
   a=left.absN(); b=right.absN();
   if (left.getZnak()==right.getZnak()) {res.init(a+b); res.mulZnak(left.getZnak());}
   else { res.init(a-b);
       if ((x=COM_NN_D(left.absN(), right.absN())) == 2) res.mulZnak(left.getZnak());
       else if (x==1) res.mulZnak(right.getZnak());
   }
   return res;
}
Zahlen operator-(Zahlen& left, Zahlen& right)
{
    right.mulZnak(-1);
    return left+right;
}
Zahlen operator*(Zahlen& left, Zahlen& right)
{
    Natur a,b;
    Zahlen res;
    a=left.absN();b=right.absN();
    res.init(a*b); res.mulZnak(left.getZnak()*right.getZnak()) ;
    return res;
}
Zahlen operator/(Zahlen& left, Zahlen& right)
{
   Natur a=left.absN(),b=right.absN(), helper("1");
   Zahlen res;
   if (left.getZnak()==-1) {
      if ((a%b).get()=="0") a = a / b;
      else{
           a = a / b;
           a=a+helper;
      }
   } else{
       a=a/b;
   }
   if (left.getZnak()==right.getZnak()) res.init(a); else
   {
       res.init(a);
       res.mulZnak(-1);
   }
   return res;
}
Zahlen operator%(Zahlen& left, Zahlen& right)
{
    Zahlen res;
    res=left/right;
    res=right*res;
    res=left-res;
    return res;
}
string ADD_ZZ_Z (Zahlen, Zahlen);
string LCM_NN_N(Natur a, Natur b);
string DIV_NN_N(Natur, Natur);
string DIV_ZZ_Z(Zahlen,Zahlen);
string GCF_NN_N(Natur, Natur);
string MUL_ZZ_Z(Zahlen, Zahlen);
class Ratio{
private:
    Zahlen ch;
    Natur zn;
public:
    void exchange()
    {
        Natur a;
        a=this->ch.absN();
        this->ch.init(this->zn.get(),this->ch.getZnak());
        this->zn=a;
    }
    void mulZnak(int x)
    {
        this->ch.mulZnak(x);
    }
    Zahlen getCh(){
        return this->ch;
    }
    Natur getZn(){
        return this->zn;
    }
    string get(){
        string res="";
        if (this->ch.get()=="0") return "0"; //если что-то отвалится - я не виноват 5.04.20
        res+=this->ch.get();
        res+='/';
        res+=this->zn.get();
        return res;
    }
    void init(Zahlen a,Natur b)
    {
        this->ch=a;
        this->zn=b;
    }
    void init(Zahlen a)
    {
        this->ch=a;
        this->zn.init("1");
    }
    void init()
    {
        string str, helper="";
        cin>>str;
        int i;
        for (i=0;str[i]!='/' && i<str.length();i++)
        helper+=str[i];
        Zahlen a; Natur b;
        a.init(helper);
       if(i!=str.length())
       {
           helper="";
           for (i=i+1;i<str.length();i++)
            helper+=str[i];
           b.init(helper);
       }
        else b.init("1");
        this->ch=a;
        this->zn=b;
    }
    void init(string str)
    {
        string helper="";
        int i;
       // cout<<str;
        for (i=0;str[i]!='/' && i<str.length();i++) {
            helper += str[i];
        }
        Zahlen a; Natur b;
        a.init(helper);
        if(i!=str.length())
        {
            helper="";
            for (i=i+1;i<str.length();i++)
                helper+=str[i];
            b.init(helper);
        }
        else b.init("1");
        this->ch=a;
        this->zn=b;
    }
    friend Ratio operator+(Ratio& left, Ratio& right);
    friend Ratio operator-(Ratio& left, Ratio& right);
    friend Ratio operator*(Ratio& left, Ratio& right);
    friend Ratio operator/(Ratio& left, Ratio& right);
    friend string RED_Q_Q(Ratio);
};
Ratio operator+(Ratio& left, Ratio& right)
{
    string c;
    Natur e, help1, help2;
    Zahlen Ch1, Ch2;
    Ratio d, a, b;
    a.init (left.get()); b.init(right.get());
    if (COM_NN_D(a.getZn(), b.getZn()) == 0) { c = ADD_ZZ_Z(a.getCh(), b.getCh()); c += "/"; c += a.getZn().get(); d.init(c); d.init(RED_Q_Q(d)); return d;}
    else e.init(LCM_NN_N(a.getZn(), b.getZn())); // Нок знаменателей
    help1.init(DIV_NN_N(e, a.getZn())); help2.init(DIV_NN_N(e, b.getZn())); Zahlen n1, n2; n1.init(help1); n2.init(help2); // на что нужно домножить числители
    Ch1.init(MUL_ZZ_Z(a.getCh(), n1)); Ch2.init(MUL_ZZ_Z(b.getCh(), n2)); // получение "умноженных" числителей
    c = ADD_ZZ_Z(Ch1, Ch2); c += "/"; c += e.get(); d.init(c);
    b.init(RED_Q_Q(d));
    return b;
}
Ratio operator-(Ratio& left, Ratio& right)
{
    Ratio b;
    b.init(right.get());
    b.mulZnak(-1);
    return (left+b);

}
Ratio operator*(Ratio& left, Ratio& right)
{
    Zahlen a,b;
    Natur d,c;
    Ratio res; res.init("0");
    a=left.getCh(); b=right.getCh();
    if(a.get()=="-0" || b.get()=="-0") return res;
    c=left.getZn(); d=right.getZn();
    a=a*b;
    //cout<<"Числите"<<a.get();
    c=c*d;
    //cout<<"  Знамен`"<<c.get();
    res.init(a,c);
    res.init(RED_Q_Q(res));
    return res;
}
Ratio operator/(Ratio& left, Ratio& right)
{
    Ratio b;
    b.init(right.get());
    b.exchange();
    b=left*b;
    b.init(RED_Q_Q(b));
    return b;
}
string MUL_QQ_Q(Ratio, Ratio);
struct Compare{
    bool operator()(const Natur &a,const Natur &b)const{
        return (COM_NN_D(a,b)==2);
    }
};
class Polinomen{
public:
    map<Natur,Ratio,Compare> koef;
    Natur deg;
    void init ()
    {
        string str;
        cin>>str;
        this->init(str);

    }
    void init(string str)
    {
        string subStr; // subStr- lля записи коефицента и х например, 109x^10
        Ratio x;
        map<Natur,Ratio,Compare> k;
        Natur max, a; ///вместо этой ж0пPl бьем на одночлены и уже из одночленов вынимаем коеф и степень
        max.init("0");
        int j=0, i;
        string::size_type posZnak,posX; ///posZnak -позиция знака,  posX - позиция X
        for (i=0;i<str.length();i++)
        {
            if (str[i]=='+' || str[i]=='-')
            {
                //cout<<"Хоба, я тут"<<i<<'\n';
                subStr=str.substr(j,i-j);
                if (str[j]=='+') j=1; else j=0;
                posX=subStr.find("x");
                if (posX!=string::npos) {                               ///если x есть - берем коэфицент
                    if ((posX!=0 && posX!=1 )||  (posX==1 && subStr[0]!='+' && subStr[0]!='-')) x.init(subStr.substr(j,posX-j));
                    else if(subStr[0]=='+' || posX==0) x.init("1");else if(subStr[0]=='-') x.init("-1");//но если коэфицента нет - то решает -1 или 1 в него ставить
                    if (subStr[posX+1]=='^') a.init(subStr.substr(posX+2,subStr.length()-posX-2));
                    else a.init("1");
                    if (COM_NN_D(a,max)==2) max=a;
                }
                else  //если икса нет - то это свободный коэфицент
                {
                    x.init(subStr.substr(j,subStr.length()-j));
                    a.init("0");
                }
                j=i;
            }
            k[a]=x; //push in map
           // cout<<"k["<<a.get()<<"]="<<x.get()<<'\n';
        }
        subStr=str.substr(j,i-j);
        if (str[j]=='+') j=1; else j=0;
        posX=subStr.find("x");
        if (posX!=string::npos) {                               //если x есть - берем коэфицент
            if ((posX!=0 && posX!=1 )||  (posX==1 && subStr[0]!='+' && subStr[0]!='-')) x.init(subStr.substr(j,posX-j));
            else if(subStr[0]=='+' || posX==0) x.init("1");else if(subStr[0]=='-') x.init("-1"); //но если коэфицента нет - то решает -1 или 1 в него ставить
            if (subStr[posX+1]=='^') a.init(subStr.substr(posX+2,subStr.length()-posX-2));
            else a.init("1");
            if (COM_NN_D(a,max)==2) max=a;
        }
        else  //если икса нет - то это свободный коэфицент
        {
            x.init(subStr.substr(j,subStr.length()-j));
            a.init("0");
        }
        k[a]=x; //push in map
        //cout<<"k["<<a.get()<<"]="<<x.get()<<'\n';
        this->deg=max;
        this->koef=k;
    }
    Polinomen()
    {
        deg.init("0");
        Natur x; x.init("0");
        Ratio y; y.init("0");
        koef[x]=y;
    }
    void debug() //ф-ия-член для дебага, сюда не смотрим
    {
        for(auto& item : this->koef)
        {
            cout << item.first.get() << " : " << item.second.get() << endl; //Вывод ключей и значений
        }
    }
    void checkout() //Сокращение палинома,  if нулевые коэфиценты
    {
        map<Natur,Ratio,Compare> kof;
        Natur d; //степень тоже может "съехать"
        d.init("0");
        for(auto& item : this->koef)
        {
            if (this->koef[item.first].get()=="0" && item.first.get()!="0");
            else {
                kof[item.first] = this->koef[item.first];
                if (COM_NN_D(item.first,d)==2) d=item.first;
            }
        }
        this->deg=d;
        this->koef=kof;
    }
    string get()
    {
        this->checkout();
        string str="";
        for(auto& item : this->koef)
        {
            if(item.second.get()[0]!='-') str+='+';
            str+=item.second.get();
            if(item.first.get()!="0") {
                str+="x^";
                str+=item.first.get();
            }
        }

        return str;
    }
    friend Polinomen ADD_PP_P(Polinomen,Polinomen);
    friend Polinomen SUB_PP_P(Polinomen, Polinomen);
    friend Polinomen MUL_Pxk_P(Polinomen, Natur);
    friend Polinomen MUL_PQ_P(Polinomen, Ratio);
    friend Natur DEG_P_N(Polinomen);
    friend Polinomen MUL_PP_P(Polinomen, Polinomen);
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
// Polinomen
Polinomen ADD_PP_P(Polinomen a,Polinomen b)
{
    for(auto& item : b.koef)
    {
       // cout<<a.koef[item.first].get()<<'+'<<b.koef[item.first].get()<<'\n'; //тут была найдена проблма в init()
       a.koef[item.first]=a.koef[item.first]+b.koef[item.first];
    }
    return a;
}
Polinomen SUB_PP_P(Polinomen a,Polinomen b)
{
    for(auto& item : b.koef)
    {
        a.koef[item.first]=a.koef[item.first]-b.koef[item.first];
    }
    return a;
}
Polinomen MUL_PQ_P(Polinomen a,Ratio b)
{
    a.checkout();
   // cout<<a.get()<<" lol\n";
    for(auto& item : a.koef)
    {
       if (a.koef[item.first].getCh().absN().get()!="0") a.koef[item.first]=a.koef[item.first]*b;
        //cout<<a.koef[item.first].get()<<' ';
    }
    return a;
}
Polinomen MUL_Pxk_P(Polinomen a, Natur k)
{
    Natur helper;
    map<Natur,Ratio,Compare> kof;
    for(auto& item : a.koef)
    {
        helper=item.first;
        kof[helper+k]=a.koef[item.first];
    }
    a.koef=kof;
    return a;
}
Ratio LED_P_Q(Polinomen a)
{
    a.checkout();
    return a.koef[a.deg];
}
Natur DEG_P_N(Polinomen a)
{
    a.checkout();
    return a.deg;
}
void FAC_P_Q(Polinomen a)
{
    Natur nod;
    Natur nok;
    Zahlen nodZ, nokZ;
   /// Natur helper;               /// А го сделаем тип функций string, нам же точно не понадобится в каждой функции дальше
    for(auto& item : a.koef)                 ///делать какоую-то переменную, чтобы преобразовывать string к нашим классам
    {                                                                           ///(с) yoi 3.0
        if (a.koef[item.first].get()==a.koef[a.deg].get()) {
            nod =item.second.getCh().absN();
            nok=item.second.getZn();
        } else
        {
            nod.init(GCF_NN_N(nod,item.second.getCh().absN())); // поледовательно ищем нок и нод, очередного нока и нода и следующих чисел
            nok.init(LCM_NN_N(nok,item.second.getZn()));
        }
    }
    cout<<"Результат: ";
    cout<<"("<<nod.get()<<'/'<<nok.get()<<")*(";
    for(auto& item : a.koef)
    {
        nodZ.init(nod);
        nodZ.init(DIV_ZZ_Z(a.koef[item.first].getCh(),nodZ));
        nokZ.init(DIV_NN_N(nok,a.koef[item.first].getZn()));
        if (item.first.get()!="0") cout<<((nokZ*nodZ).getZnak()==1?"+":"-")<<(nokZ*nodZ).get()<<"x^"<<item.first.get();
        else cout<<((nokZ*nodZ).getZnak()==1?"+":"-")<<(nokZ*nodZ).get();
    }
    cout<<")";

}
Polinomen MUL_PP_P(Polinomen a, Polinomen b)
{
    Polinomen res,helper;
    for(auto& item : b.koef)
    {
        helper=MUL_PQ_P(a,b.koef[item.first]);
       // cout<<"после умножения на коэф"<<helper.get()<<'\n';
        res=ADD_PP_P(res,MUL_Pxk_P(helper,item.first));
    }
    return res;
}
Polinomen DIV_PP_P(Polinomen a, Polinomen b)
{
    Polinomen delim, res;        ///delim - делитель в текущий момент, res - результат
    Ratio mnoj;                  /// множитель для умножения делителя
    Natur helper;                  ///бесполезный костыль, но лучше пока не трогат
     map <Natur,Ratio,Compare> ::iterator it = b.koef.begin(), iter;
     //it--;
     //        cout<<b.get()<<"Первый"<<(*(it)).second.get()<<' ';
    b.checkout();
   // cout<<(*iter).first.get();
    while (COM_NN_D(a.deg,b.deg)!=1 && a.deg.get()!="0") {
        a.checkout();
        if (COM_NN_D(a.deg,b.deg)==1) break;
        //cout<<"многочлен "<<a.get()<<" ";
        iter=a.koef.begin();
        mnoj = (*iter).second / b.koef[b.deg];
        helper.init(SUB_NN_N((*iter).first,b.deg));
        res.koef[helper]=mnoj;
        //cout<<helper.get()<<'\n';
        delim = MUL_PQ_P(b, mnoj);
        delim = MUL_Pxk_P(delim, helper);
        //cout<<delim.get()<<'\n';
        a = SUB_PP_P(a, delim);
    }
    res.checkout();
    return res;
}
Polinomen MOD_PP_P(Polinomen a, Polinomen b)
{
    Polinomen delim;/// res;        ///delim - делитель в текущий момент, res - результат
    Ratio mnoj;                  /// множитель для умножения делителя
    Natur helper;                  ///бесполезный костыль, но лучше пока не трогать
    map <Natur,Ratio,Compare> ::iterator it = b.koef.begin(), iter;// it--;
    //it--;
      //cout<<b.get()<<"Первый"<<' ';
    b.checkout();
    // cout<<(*iter).first.get();
    while (COM_NN_D(a.deg,b.deg)!=1 && a.deg.get()!="0") {
        while (COM_NN_D(a.deg,b.deg)!=1 && a.deg.get()!="0") {
            a.checkout();
            if (COM_NN_D(a.deg,b.deg)==1) break;
            //cout<<"многочлен "<<a.get()<<" ";
            iter=a.koef.begin();
            mnoj = (*iter).second / b.koef[b.deg];
            helper.init(SUB_NN_N((*iter).first,b.deg));
            //res.koef[helper]=mnoj;
            //cout<<helper.get()<<'\n';
            delim = MUL_PQ_P(b, mnoj);
            delim = MUL_Pxk_P(delim, helper);
            //cout<<delim.get()<<'\n';
            a = SUB_PP_P(a, delim);
        }
    }
    a.checkout();
    return a;
}
Polinomen GCF_PP_P(Polinomen a, Polinomen b)
{
    Natur min; min.init("1");
    Polinomen helper;
    Ratio assis; assis.init("1");
    helper.init("1");
    a.checkout(); b.checkout();
    while (a.deg.get()!="0" && b.deg.get()!="0")
    {
        if(COM_NN_D(a.deg,b.deg)==2)
        {
            a=MOD_PP_P(a,b);
            a.checkout();
        }else
            {
            b=MOD_PP_P(b,a);
            b.checkout();
        }
        a.checkout();
        b.checkout();
    }
   if (a.get()=="0" || a.get()=="+0" || a.get()=="-0") {
        /*for(auto& item : b.koef)
        {
           b.koef[item.first]=assis;
        } */
        return b;
    }else
    if (b.get()=="0" || b.get()=="+0" || b.get()=="-0") {
      /*  for(auto& item : a.koef)
        {
            a.koef[item.first]=assis;
        } */
        return a;
    }
    else return helper;
}
Polinomen DER_P_P(Polinomen a) //by kill_soap && yoi3.0
{
    Polinomen res;
    map <Natur,Ratio,Compare> resM;
    Zahlen help;
    Ratio b; Natur One, helper; One.init("1");
    for (auto& item : a.koef)
    {
        if (item.first.get()!="0")
        {
            helper.init(SUB_NN_N(item.first,One));
            help.init(item.first);
            b.init(help);
            b.init(MUL_QQ_Q(b,item.second));
            resM[helper]=b;
        }
    }
    helper.init("0");
    res.koef=resM;
    if(resM[helper].get()=="0") { b.init("0");  res.koef[helper]=b;} ///Чтобы не вывести пустоту, если только свободный член был
    res.checkout();
    return res;
}
Polinomen NMR_P_P(Polinomen a)  // wrong answer
{
    Polinomen der;
    der=DER_P_P(a);
    der=GCF_PP_P(a,der);
    return DIV_PP_P(a,der);

}
//Zahlen
string ABS_Z_N(Zahlen a)
{
    return a.abs();
}
string POZ_Z_D(Zahlen a)
{
    if (a.abs()=="0") return "0";
    if (a.getZnak()==-1) return "1"; else return "2";
}
string MUL_ZM_Z(Zahlen a)
{
    a.mulZnak(-1);
    return a.get();
}
string ADD_ZZ_Z(Zahlen a, Zahlen b)
{
    return(a+b).get();
}
string SUB_ZZ_Z(Zahlen a, Zahlen b)
{
    return (a-b).get();
}
string MUL_ZZ_Z(Zahlen a, Zahlen b)
{
    return (a*b).get();
}
string DIV_ZZ_Z(Zahlen a,Zahlen b)
{
    int x;
    if ((x=COM_NN_D(a.absN(),b.absN()))==2) return (a/b).get();
    else return (b/a).get();
}
string MOD_ZZ_Z(Zahlen a, Zahlen b)
{
   return (a%b).get();
}
//Naturalis
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
    if (b==0) return "0";
    int x=0; //promejutochniy result
    for (int i=a.size()-1;i>=0;i--)
    {
        x+=(a.get()[i]-'0')*b;
        res+=(char)(x%10+'0');
        x/=10;
    }
    while (x!=0) {res+=(char)(x%10+'0'); x/=10;}; //result<=81 that's why it should work (c) yoi3.0
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
string MUL_NN_N(Natur a, Natur b){
    return (a*b).get();
}
string SUB_NDN_N(Natur a, Natur b, int mnoj)
{
    a.init(MUL_ND_N(a, mnoj));
    return (a-b).get();
}
string DIV_NN_Dk(Natur a, Natur b) {
    string c = ""; int i = 0;
    Natur Middle;
    int x = COM_NN_D(a,b);
    if (x == 2) {
        if (NZER_N_B(b) == 0) return "Error";
        if (a.get()[0]>b.get()[0]) for (i = 0; i < b.size(); i++) { c += a.get()[i]; }
        else for (i = 0; i < b.size()+1; i++) { c += a.get()[i]; }
        Middle.init(c);
        x = a.size() - c.length();
        i = 0;
        while (COM_NN_D(Middle, b) != 1) {
            Middle.init(SUB_NN_N(Middle, b));
            i++;
        }
        c = (char)(i + '0');
        Middle.init(c);
        Middle.init(c = MUL_Nk_N(Middle, x));
        return Middle.get();
    }
    else if (x == 1) {
        if (NZER_N_B(a) == 0) return "Error";
        if (b.get()[0] > a.get()[0]) for (i = 0; i < a.size(); i++) { c += b.get()[i]; }
        else for (i = 0; i < a.size() + 1; i++) { c += b.get()[i]; }
        Middle.init(c);
        x = b.size() - c.length();
        i = 0;
        while (COM_NN_D(Middle, a) != 1) {
            Middle.init(SUB_NN_N(Middle, a));
            i++;
        }
        c = (char)(i + '0');
        Middle.init(c);
        Middle.init(c = MUL_Nk_N(Middle, x));
        return Middle.get();
    }
    else return "1";
}
string DIV_NN_N(Natur a, Natur b)
{
    if(COM_NN_D(a,b)==2) return (a/b).get();
    else return (b/a).get();
}
string MOD_NN_N(Natur a, Natur b)
{
    if(COM_NN_D(a,b)==2) return (a%b).get();
    else return (b%a).get();
}
string GCF_NN_N(Natur a, Natur b)
{
    while (a.get()!="0" && b.get()!="0")
    {  if(COM_NN_D(a,b)==2) a=a%b; else b=b%a; }
    return (a+b).get();
}
string LCM_NN_N(Natur a, Natur b)
{
    Natur gcd(GCF_NN_N(a,b));
    a=a*b;
    return (a/gcd).get();
}
//Ratio
string RED_Q_Q(Ratio a)
{
    Natur helper, helper2;
    Zahlen helperZ1, helperZ2;
    helper.init(GCF_NN_N(a.getCh().absN(),a.getZn()));
    //cout<<"Нод"<<helper.get();
    helperZ2=a.getCh();
    helperZ1.init(helper);
    helper2=a.getZn();
    //cout<<"268/4=";
    a.init(helperZ2/helperZ1,helper2/helper);
    if (a.getCh().get()=="0") a.init("0");
    return a.get();
}
string INT_Q_B(Ratio a)   //by kill_soap
{
    Natur d; d=a.getCh().absN();
    if (MOD_NN_N(d, a.getZn()) == "0" || a.getZn().get()=="1") return "Число является целым\n";
    else return "Число не является целым";
}
string ADD_QQ_Q(Ratio a, Ratio b) //by kill_soap
{
  return (a+b).get();
}
string SUB_QQ_Q(Ratio a, Ratio b)
{
    return (a-b).get();
}
string MUL_QQ_Q(Ratio a, Ratio b)
{
    return (a*b).get();
}
string DIV_QQ_Q(Ratio a, Ratio b)
{
    return (a/b).get();
}
int Naturalis() //работаем с натуральными
{
    Natur n1, n2;
    int res, isOk,mnoj;
    string resStr;
    cout<<"Введите два натуральных числа"<<'\n';
    n1.init(); n2.init();
    //if (n1.get()=="inv" || n2.get()=="inv") return error(2);
    int funkType;
    cout<<"\nВыбирите функцию\n"<<"1 - сравнить\n"<<"2 - проверка на ноль\n"<<"3 - добавить 1\n"
    <<"4 - Сложить\n"<<"5 - вычесть (из большего)\n"<<"6 - умножить на число\n"<<"7 - умножить на 10^k\n"
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
        case 8:  cout<<"Результат умножения "<<MUL_NN_N(n1, n2)<<'\n'; break;
        case 9: cout<<"Какое число умножаем: 1е или 2е (Введите цифру)? Затем введите множитель (тип int)\n";  cin>>res; cin>>mnoj;
            if (cin.fail() || mnoj<0) return error(1);
            if (res==1) cout<<"Результат вычитания "<<SUB_NDN_N(n1, n2, mnoj)<<'\n';
            else if (res==2) cout<<"Результат вычитания "<<SUB_NDN_N(n2, n1, mnoj)<<'\n'; else return error(1); break;
        case 10:  cout<<"Первая цифра деления: "<<DIV_NN_Dk(n1, n2)<<'\n'; break; //сделано kill_soap
        case 11: cout<<"Частное равно "<<DIV_NN_N(n1,n2)<<'\n'; break;
        case 12: cout<<"Остаток от деления большего на меньшее равен "<<MOD_NN_N(n1,n2); break;
        case 13: cout<<"НОД равен "<<GCF_NN_N(n1,n2); break;
        case 14: cout<<"НОК равен "<<LCM_NN_N(n1,n2); break;
        default: return error(1);
    }
    return 0;
}
int Integer()
{
    int funkType, res;
    string reZ;
    Zahlen n1,n2;
    cout<<"Введите два целых числа"<<'\n';
    n1.init(); n2.init();
    //if (n1.absN().get()=="inv" || n2.absN().get()=="inv") return error(2);
    cout << "\nВыбирите функцию\n"<< "1 - модуль числа\n"<< "2 - проверить на знак\n"<< "3 - умножить на -1\n"
     <<"4 - сложить\n"<< "5 - вычесть\n"
    <<"6 - перемножить\n" <<"7 - частное от деления \n" << "8 - остаток от деления\n";
    cin>> funkType;
    switch (funkType) {
        case 1: cout<<"Модуль какого числа хотите (Введите 1 или 2)?\n"; cin>>res;
        if (res==1) cout<<"Модуль первого числа равен "<<ABS_Z_N(n1); else if (res==2) cout<<"Модуль второго числа равен "<<ABS_Z_N(n2);
        else return error(1); break;
        case 2: cout<<"Какое число проверить (1 или 2)?\n"; cin>>res; if (res==1) reZ=POZ_Z_D(n1); else if (res==2) reZ=POZ_Z_D(n2); else return error(1);
            if (reZ=="1") cout<<"Число отрицательное"; else if (reZ=="2") cout<<"Число положительное"; else cout<<"Число является нулём";
            break;
        case 3: cout<<"Какое число умножить на -1? (1 или 2)\n"; cin>>res; if (res==1) cout<<"Результат "<<MUL_ZM_Z(n1); else
            if (res==2) cout<<"Результат "<<MUL_ZM_Z(n2); else return error(1); break;
        case 4: cout<<"Результат сложения: "<<ADD_ZZ_Z(n1,n2); break;
        case 5: cout<<"Результат вычитания: "<<SUB_ZZ_Z(n1,n2); break;
        case 6: cout<<"Результат умножения: "<<MUL_ZZ_Z(n1,n2); break;
        case 7: cout<<"Частное от деления: "<<DIV_ZZ_Z(n1,n2); break;
        case 8: cout<<"Остаток от деления: "<<MOD_ZZ_Z(n1,n2); break;
        default: return error(1);
    }
    return 0;
}

int Rational_Numbers()
{
    int funkType;
    int res;
    cout<<"Введите два рациональных числа (Пример: -1/2)"<<'\n';
    Ratio n2,n1;
    n1.init();n2.init();
    /*if (n1.getCh().absN().get()=="inv" || n2.getCh().absN().get()=="inv" || n1.getZn().get()=="inv" || n2.getZn().get()=="inv")
        return error(2); */
    cout <<"\nВыбирите функцию\n" <<"1 - сокращение дроби\n"<< "2 - проверка на целое\n" <<"3 - Сложение дробей\n" <<"4 - Вычитание дробей\n"
    << "5 - Умножение дробей\n"<<"6 - Деление дробей\n";
    cin>> funkType;
    switch (funkType) {
        case 1: cout<<"Сократить какую дробь хотите (Введите 1 или 2)?\n"; cin>>res;
            if (res==1) cout<<"Сокращенная дробь: "<<RED_Q_Q(n1); else if (res==2) cout<<"Сокращенная дробь: "<<RED_Q_Q(n2);
            else return error(1); break;
        case 2: cout<<"Проверить какую дробь хотите (Введите 1 или 2)?\n"; cin>>res;
            if (res==1) cout<<INT_Q_B(n1); else if (res==2) cout<<INT_Q_B(n2);
            else return error(1); break;
        case 3: cout<<"Результат сложения: "<<ADD_QQ_Q(n1,n2); break;
        case 4: cout<<"Результат вычитания: "<<SUB_QQ_Q(n1,n2); break;
        case 5: cout<<"Результат умножения: "<<MUL_QQ_Q(n1,n2); break;
        case 6: cout<<"Результат деления: "<<DIV_QQ_Q(n1,n2); break;
        default: return error(1);
    }
    return 0;
}
int Polynomial()
{
    int funkType;
    Polinomen n1, n2;
    Ratio x;
    Natur k;
    int res;
    string str;
    cout<<"Введите два полинома. Пример ввода: 10+x^2-10x^3\n";
    n1.init(); n2.init();
    cout <<"\nВыбирите функцию\n" <<"1 - Сложение многочленов\n" <<"2 - Вычитание многочленов\n"<< "3 - Умножение многочлена на рациональное число\n"
    <<"4 - Умножение многочлена на x^k\n" <<"5 - Старший коэффициент многочлена\n" <<"6 - Степень многочлена\n" <<"7 - Вынесение из многочлена НОК знаменателей коэффициентов и НОД числителей\n"
    <<"8 - Умножение многочленов\n"<< "9 - Частное от деления многочлена на многочлен\n"<< "10 - Остаток от деления многочлена на многочлен\n"
    <<"11 - НОД многочленов\n"<<"12 - Производная многочлена\n"<< "13 - Преобразование многочлена — кратные корни в простые\n";
    cin >>funkType;
    switch (funkType) {
        case 1: cout<<"Результат сложения: "<<ADD_PP_P(n1,n2).get(); break;
        case 2: cout<<"Результат вычитания: "<<SUB_PP_P(n1,n2).get(); break;
        case 3: cout<<"Введите рациональное число для умножения\n"; cin>>str; x.init(str); cout<<"Какой палином умножаем? (1 или 2)\n";
        cin>>res; if (res==1) cout<<"Результат: "<<MUL_PQ_P(n1,x).get(); else if (res==2) cout<<"Результат: "<<MUL_PQ_P(n2,x).get(); else return error(1); break;
        case 4:cout<<"Введите натуральное число - степень x для умножения\n"; cin>>str; k.init(str); cout<<"Какой палином умножаем? (1 или 2)\n";
            cin>>res; if (res==1) cout<<"Результат: "<<MUL_Pxk_P(n1,k).get(); else if (res==2) cout<<"Результат: "<<MUL_Pxk_P(n2,k).get();
        else return error(1); break;
        case 5: cout<<"Старший коэфицент какого полинома вывести? (1 или 2)\n";
            cin>>res; if (res==1) cout<<"Результат: "<<LED_P_Q(n1).get(); else if (res==2) cout<<"Результат: "<<LED_P_Q(n2).get(); else return error(1); break;
        case 6: cout<<"Степень какого полинома вывести? (1 или 2)\n";
            cin>>res; if (res==1) cout<<"Результат: "<<DEG_P_N(n1).get(); else if (res==2) cout<<"Результат: "<<DEG_P_N(n2).get(); else return error(1); break;
        case 7: cout<<"Сократить какой полином? (1 или 2)\n";
            cin>>res; if (res==1) FAC_P_Q(n1); else if (res==2) FAC_P_Q(n2); else return error(1); break;
        case 8: cout<<"Результат умножения: "<<MUL_PP_P(n1,n2).get(); break;
        case 9: cout<<"Частное деления "<<DIV_PP_P(n1,n2).get(); break;
        case 10: cout<<"Остаток от деления "<<MOD_PP_P(n1,n2).get();break;
        case 11: cout<<"НОД полиномов "<<GCF_PP_P(n1,n2).get(); break;
        case 12: cout<<"Производную какого полинома вывести? (1 или 2)\n"; cin>>res; cout<<"Производная полинома: ";
        if (res==1) cout<<DER_P_P(n1).get(); else if (res==2) cout<<DER_P_P(n2).get(); else return error(1); break;
        case 13: cout<<"В каком полиноме убрать кратные корни? (1 или 2)\n"; cin>>res; cout<<"Полином-результат: ";
            if (res==1) cout<<NMR_P_P(n1).get(); else if (res==2) cout<<NMR_P_P(n2).get(); else return error(1); break;
        default: return error(1);
    }
    return 0;
}
int main() {
    setlocale(LC_ALL, "Rus");
    int mode, isOk;
    cout <<"Выбери тип переменных\n"<< "1 - Натуральные числа\n" <<"2 - Целые числа\n" <<"3 - Рациональные числа\n" <<"4 - Многочлен с рациональными коэффициентами\n";
    cin>> mode;
    switch (mode) {
        case 1: isOk = Naturalis(); break;
        case 2: isOk = Integer(); break;
        case 3: isOk = Rational_Numbers(); break;
        case 4: isOk = Polynomial(); break;
        default: return error(1);
    }
    return isOk;
}