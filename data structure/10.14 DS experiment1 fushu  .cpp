// #include <iostream>

// using namespace std;

// class z_number{

// public:

//     double a,b;

//     z_number()
//     {

//     }

//     z_number(double A,double B)
//     {
//         a=A;
//         b=B;
//     }

//     z_number operator + (z_number& it)
//     {
//         z_number res(a+it.a,b+it.b);
//         return res;
//     }

//     z_number operator - (z_number&it)
//     {
//         z_number res(a-it.a,b-it.b);
//         return res;
//     }

//     z_number operator * (z_number &it)
//     {
//         z_number res;
//         res.a=a*it.a-b*it.b;
//         res.b=b*it.a+a*it.b;

//         return res;
//     }

//     z_number operator / (z_number it)
//     {
//         z_number res;
//         double t=it.a*it.a + it.b*it.b;
//         it.b=-it.b;

//         res=(*this)*it;
//         res.a/=t;
//         res.b/=t;

//         return res;
//     }
// };

// void show(z_number & it)
// {
//     cout<< it.a<<'+'<<it.b<<'i';
// }

// int main()
// {
//     z_number a(1,6),b(6,7);

//     z_number c=a*b;

//     show(c);

//     cout<<endl;

//     c=a+b;

//     show(c);

//     cout<<endl;

//     c=a-b;

//     show(c);

//     cout<<endl;

//     c=a/b;

//     show(c);

//     cout<<endl;
    
//     cout<<endl;
//     system("pause");
//     return 0;
// }
