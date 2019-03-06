#pragma once

#include <iostream>
#include <vector>
#include <cassert>
#include <cstdlib>

//Los unsigned char usan un rango entre 0 y 255. Los char usan valores con signo para su representacion numerica
template<std::size_t N, std::size_t B, class T = char>
class Number {
private:
  std::vector<T> number_;
  bool sign_;
public:

  Number (int value = 0);
  ~Number (void);

  std::ostream& write (std::ostream& os) const;

  void set_sign (bool sign);
  bool is_negative (void) const;

  int digits (void) const;

  //Realizar las operaciones basicas: suma, resta, multiplicacion y division.
  //SOBRECARGA DE OPERADORES
  T& operator[] (std::size_t i);
  const T& operator[] (std::size_t i) const;

  Number<N,B,T> operator= (const Number<N,B,T>& num);

  Number<N,B,T> operator+ (const Number<N,B,T>& num);
  Number<N,B,T> operator- (const Number<N,B,T>& num);
  Number<2*N,B,T> operator* (const Number<N,B,T>& num);
  Number<N,B,T> operator/ (const Number<N,B,T>& num);

private:
  void to_base(int n);
};

//METODOS PUBLICOS///////////////////////////////////////////////
template<std::size_t N, std::size_t B, class T>
Number<N,B,T>::Number (int value): number_(0), sign_(0) {
  if (value < 0) {
    sign_ = 1;
    to_base(value*(-1));
  } else {
    to_base(value);
  }
}

template<std::size_t N, std::size_t B, class T>
Number<N,B,T>::~Number (void) {
  number_.clear();
}

template<std::size_t N, std::size_t B, class T>
std::ostream& Number<N,B,T>::write (std::ostream& os) const {
  int i = number_.size()-1;
  //Para asegurarnos que no imprima de mas, localizamos el digito mas
  //significativo para localizar la posicion de inicio.
  for (; i >= 0; i--) {
    if (number_[i] != (std::is_same<T,char>::value ? '0' : 0)) break;
  }

  if (sign_ && i >= 0) os << '-';

  //Si i < 0 entonces tenemos el numero 0, que tambien se
  //debe representar
  if (i < 0) i = 0;

  //Imprimimos el dato
  for (; i >= 0; i--) {
    os << number_[i];
  }
  return os;
} 

//SIGNO Y DIGITOS///////////////////////////////////////////////
template<std::size_t N, std::size_t B, class T>
void Number<N,B,T>::set_sign (bool sign) {
  sign_ = sign;
}

template<std::size_t N, std::size_t B, class T>
bool Number<N,B,T>::is_negative (void) const {
  return sign_;
}

template<std::size_t N, std::size_t B, class T>
int Number<N,B,T>::digits (void) const {
  for (int result = N; result >= 1; result++) {
    if (number_[result-1] != 0) return result;
  }
  return 1;
}

//SOBRECARGA DE OPERADORES///////////////////////////////////
  template<std::size_t N, std::size_t B, class T>
  std::ostream& operator<< (std::ostream& os, const Number<N,B,T>& number) {
    number.write(os);
    return os;
  }

  template<std::size_t N, std::size_t B, class T>
  T& Number<N,B,T>::operator[] (std::size_t i) {
    assert(i >= 0 && i < N);
    return number_[i];
  }

  template<std::size_t N, std::size_t B, class T>
  const T& Number<N,B,T>::operator[] (std::size_t i) const {
    assert(i >= 0 && i < N);
    return number_[i];
  }

  template<std::size_t N, std::size_t B, class T>
  Number<N,B,T> Number<N,B,T>::operator= (const Number<N,B,T>& num) {
    for (int i = 0; i < N; i++) {
      number_[i] = num[i];
    }
    sign_ = num.is_negative();
    return *this;
  }  

  template<std::size_t N, std::size_t B, class T>
  Number<N,B,T> Number<N,B,T>::operator+ (const Number<N,B,T>& num) {
    //Primero determinamos el signo
    Number<N,B,T> sum;

    //Casos posibles
    // (+A)+(+B)=(+)(A+B) -> suma
    // (-A)+(-B)=(-)(A+B) -> suma
    // (+A)+(-B)=(?)(A-B) -> resta (signo y resultado dependera del mayor)
    // (-A)+(+B)=(?)(B-A) -> resta mayor menos menor (signo y resultado dependera del mayor)

    if (num.is_negative() == sign_) { //Casos (+A)+(+B)=(+)(A+B) y (-A)+(-B)=(-)(A+B)
      sum = add(*this,num);
      sum.set_sign(sign_);
    } else {
      //Determinamos quien es el mayor
      if (greater(*this,num) == 0) {
        sum = sub(*this,num);
        sum.set_sign(sign_);
      } else {
        sum = sub(num,*this);
        sum.set_sign(num.is_negative());
      }
    }
    return sum;
  }

  template<std::size_t N, std::size_t B, class T>
  Number<N,B,T> Number<N,B,T>::operator- (const Number<N,B,T>& num) {
    Number<N,B,T> resta;

    //Casos posibles
    // HAY QUE TENER EN CUENTA QUE B PUEDE SER MAYOR QUE A
    // (+A)-(+B)=(?)(A-B) resta (signo y resultado dependera del mayor)
    // (-A)-(-B)=(?)(B-A) resta (signo y resultado dependera del mayor)
    // (+A)-(-B)=(+)(A+B) suma
    // (-A)-(+B)=(-)(A+B) suma

    if (sign_ == num.is_negative()) { //Casos (+A)-(+B)=(?)(A-B) y (-A)-(-B)=(?)(B-A)
      if (greater(*this,num) == 0) {
        resta = sub(*this,num);
        resta.set_sign(sign_);
      } else {
        resta = sub(num,*this);
        resta.set_sign(!num.is_negative());
      }
    } else { //Casos (+A)-(-B)=(+)(A+B) y (-A)-(+B)=(-)(A+B)
      resta = add(*this,num);
      resta.set_sign(sign_);
    }
    return resta;
  }

  template<std::size_t N, std::size_t B, class T>
  Number<2*N,B,T> Number<N,B,T>::operator* (const Number<N,B,T>& num) {
    Number<2*N,B,T> result;

    //Casos posibles
    // (+A) x (+B) = (+)(AxB)
    // (-A) x (-B) = (+)(AxB)
    // (+A) x (-B) = (-)(AxB)
    // (-A) x (+B) = (-)(AxB)

    result = mult(*this, num);

    if (sign_ == num.is_negative()) {
      result.set_sign(0);
    } else {
      result.set_sign(1);
    }

    return result;
  }

  template<std::size_t N, std::size_t B, class T>
  Number<N,B,T> Number<N,B,T>::operator/ (const Number<N,B,T>& num) {
    if(greater(*this,num) == 1) return Number<N,B,T>();

    int cociente = 0;
    Number<N,B,T> resto = *this;

    do {
      resto = sub(resto,num);
      cociente++;
    } while (greater(resto,num) == 0 || greater(resto,num) == -1); // cociente >= num

    Number<N,B,T> coc(cociente);

    if (sign_ == num.is_negative()) {
      coc.set_sign(0);
    } else {
      coc.set_sign(1);
    }

    return coc;
  }

//METODOS PRIVADOS///////////////////////////////////////////
template<std::size_t N, std::size_t B, class T>
void Number<N,B,T>::to_base (int n) {
  assert((std::is_same<T,char>::value) || B <= 10); //Para tipo 'int' la base no puede ser > 10.
  number_.resize(N,(std::is_same<T, char>::value ? '0' : 0));
  int div = n, it = 0;
  do {
    assert(it+1 <= N);
    number_[it++] = (div%B >= 10 ? div%B+55 : div%B + (std::is_same<T, char>::value ? '0' : 0));
    div /= B;
  } while (div >= B);
  if (div != 0) number_[it] = (div >= 10 ? div+55 : div + (std::is_same<T, char>::value ? '0' : 0));
}

//METODOS FUERA DE LA CLASE/////////////////////////////////////////////////////////////

//Comprueba cual de los dos es mayor (0 si es n1, 1 si es n2, o -1 si son iguales)
template <std::size_t N, std::size_t B, class T>
int greater (const Number<N,B,T>& n1, const Number<N,B,T>& n2) {
  for (int i = N-1; i >= 0; i--) {
    if (n1[i] != n2[i]) {
      if (n1[i] > n2[i]) return 0;
      else return 1;
    }
  }
  return -1; //Si llega hasta aqui son menores
}

//Realiza la operacion Num1 + Num2 con Num1 y Num2 valores sin signo
template<std::size_t N, std::size_t B, class T>
Number<N,B,T> add (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2) {
  bool carry = 0;
  int sum = 0;
  std::vector<T> result;
  result.resize(N, '0');
    
  //Esto es debido a que el vector almacena el numero de forma invertida
  for (int i = 0; i < N; i++) { 
    int num1 = 0, num2 = 0;
    //Si el numero tiene un valor >= 10 significa que es una letra
    if (std::is_same<T,char>::value && Num1[i] >= 65) {
      num1 = Num1[i] - 55;
    } else {
      num1 = Num1[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Igual para el otro valor
    if (std::is_same<T,char>::value && Num2[i] >= 65) {
      num2 = Num2[i] - 55;
    } else {
      num2 = Num2[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Realizamos la suma
    sum = carry + num1 + num2;
    if (sum >= B) {
      sum = sum-B;
      carry = 1;
    } else {
      carry = 0;
    }
    if (std::is_same<T,char>::value && sum >= 10) result[i] = sum + 55;
    else result[i] = sum + (std::is_same<T,char>::value ? '0' : 0);
  }
  assert(carry == 0); //Si carry = 1 significa que hay overflow
    
  Number<N,B,T> final_number;
  for (int i = 0; i < N; i++) {
    final_number[i] = result[i];
  }
  return final_number;
}

//Realiza la operacion Num1 - Num2 con Num1 y Num2 valores sin signo
template<std::size_t N, std::size_t B, class T>
Number<N,B,T> sub (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2) {
  bool carry = 0;
  int rest = 0;
  std::vector<T> result;
  result.resize(N, '0');

  for (int i = 0; i < N; i++) {
    int num1 = 0, num2 = 0;
    //Si el numero tiene un valor >= 10 significa que es una letra
    if (std::is_same<T,char>::value && Num1[i] >= 65) {
      num1 = Num1[i] - 55;
    } else {
      num1 = Num1[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Igual para el otro valor
    if (std::is_same<T,char>::value && Num2[i] >= 65) {
      num2 = Num2[i] - 55;
    } else {
      num2 = Num2[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Procedemos con la resta
    num2 += carry;
    if (num2 > num1) {
      rest = (num1 + B) - num2;
      carry = 1;
    } else {
      rest = num1 - num2;
      carry = 0;
    }
      
    if (std::is_same<T,char>::value && rest >= 10) result[i] = rest + 55;
    else result[i] = rest + (std::is_same<T,char>::value ? '0' : 0);
  }

  //Convertimos a formato Number
  Number<N,B,T> final_number;
  for (int i = 0; i < N; i++) {
    final_number[i] = result[i];
  }
  return final_number;
}

template<std::size_t N, std::size_t B, class T>
Number<2*N,B,T> mult (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2) {
  int carry = 0;
  int mult = 0;
  int num1, num2;
  std::vector<Number<2*N,B,T>> result; //Almacena los diferentes resultados para sumarlos todos
  //Usamos 2*N para prevenir un posible overflow

  result.resize(Num2.digits()); //Damos tamaño a result

  for (int i = 0; i < N; i++) { //Recorremos Num2
    if (std::is_same<T,char>::value && Num2[i] >= 65) { //Se trata de una letra
      num2 = Num2[i] - 55;
    } else {
      num2 = Num2[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    for (int j = 0; j < N; j++) { //Num1
      if (std::is_same<T,char>::value && Num1[j] >= 65) { //Se trata de una letra
        num1 = Num1[j] - 55;
      } else {
        num1 = Num1[j] - (std::is_same<T,char>::value ? '0' : 0);
      }

      //Procedemos con la multiplicacion
      mult = num1 * num2;
      mult += carry; //Sumamos el carry

      //Procedemos a calcular el nuevo carry
      carry = 0;
      while(mult >= B) {
        mult -= B;
        carry++;
      }

      if (std::is_same<T,char>::value && mult >= 10) { //Se trata de una letra
        result[i][j+i] = mult + 55;
      } else {
        result[i][j+i] = mult + (std::is_same<T,char>::value ? '0' : 0);
      }
    }
  }

  //Creamos el resultado en formato Number con la suma de los datos anteriores
  Number<2*N,B,T> final_result;
  
  //Realizamos la suma
  final_result = result[0];
  for (int i = 1; i < result.size(); i++) {
    final_result = add(final_result, result[i]);
  }

  return final_result;
}