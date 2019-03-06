#pragma once

#include <iostream>
#include <cassert>
#include <cstdlib>

//Los unsigned char usan un rango entre 0 y 255. Los char usan valores con signo para su representacion numerica
template<std::size_t N, std::size_t B, class T = char>
class Number {
private:
  T* number_;
  bool sign_;
public:

  Number (int value = 0);
  Number (const Number<N,B,T>& A);
  ~Number (void);

  std::ostream& write (std::ostream& os) const;

  void set_sign (bool sign);
  bool is_negative (void) const;

  int digits (void) const;

  Number<N,B,T> abs (void) const;
  Number<N,B,T> reverse (void) const;

  //Asignadores
  T& operator[] (std::size_t i);
  const T operator[] (std::size_t i) const;
  Number<N,B,T>& operator= (const Number<N,B,T>& num);

  //Operadores
  Number<N,B,T> operator+ (const Number<N,B,T>& num);
  Number<N,B,T> operator- (const Number<N,B,T>& num);
  Number<N,B,T> operator* (const Number<N,B,T>& num);
  Number<N,B,T> operator/ (const Number<N,B,T>& num);

  //Comparadores
  bool operator> (const Number<N,B,T>& num) const;
  bool operator< (const Number<N,B,T>& num) const;
  bool operator== (const Number<N,B,T>& num) const;


private:
  void to_base(int n);

  //Metodos de operaciones en valor absoluto
  Number<N,B,T> add (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2);
  Number<N,B,T> sub (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2);
  Number<N,B,T> mult (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2);
};

//METODOS PUBLICOS///////////////////////////////////////////////
template<std::size_t N, std::size_t B, class T>
Number<N,B,T>::Number (int value): number_(NULL), sign_(0) {

  number_ = new T [N];

  //Inicializamos los valores
  for (int i = 0; i < N; i++) {
    if (std::is_same<T,char>::value) {
      number_[i] = '0';
    } else {
      number_[i] = 0;
    }
  }

  if (value < 0) {
    sign_ = 1;
    to_base(value*(-1));
  } else {
    to_base(value);
  }
}

template <std::size_t N, std::size_t B, class T>
Number<N, B, T>::Number(const Number<N, B, T> &A) : number_(new T [N]), sign_(0) {
  *this = A;
}

template<std::size_t N, std::size_t B, class T>
Number<N,B,T>::~Number (void) {
  delete [] number_;
  number_ = NULL;
}

template<std::size_t N, std::size_t B, class T>
std::ostream& Number<N,B,T>::write (std::ostream& os) const {
  int i = N-1;
  //Para asegurarnos que no imprima de mas, localizamos el digito mas
  //significativo para localizar la posicion de inicio.
  for (; i >= 0; i--) {
    if (number_[i] != (std::is_same<T,char>::value ? '0' : 0)) break;
  }

  // Si la base no es binaria, el valor negativo se representa con '-'
  // Si B == 2 entonces el numero esta escrito en complemento a 2 y no hay que hacer nada
  if (sign_ && i >= 0 && B != 2) os << '-';

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

template<std::size_t N, std::size_t B, class T>
Number<N,B,T> Number<N,B,T>::abs (void) const {
  if (sign_) {
    Number<N,B,T> copy (*this);
    copy.set_sign(0);
    return copy;
  } else {
    return *this;
  }
}

template<std::size_t N, std::size_t B, class T>
Number<N,B,T> Number<N,B,T>::reverse (void) const {
  Number<N,B,T> copy = *this;
  copy.set_sign(!is_negative());
  return copy;
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
  const T Number<N,B,T>::operator[] (std::size_t i) const {
    assert(i >= 0 && i < N);
    return number_[i];
  }

  template<std::size_t N, std::size_t B, class T>
  Number<N,B,T>& Number<N,B,T>::operator= (const Number<N,B,T>& num) {

    for (int i = 0; i < N; i++) {
      number_[i] = num.number_[i];
    }

    sign_ = num.is_negative();

    return *this;
  }  

  template<std::size_t N, std::size_t B, class T>
  Number<N,B,T> Number<N,B,T>::operator+ (const Number<N,B,T>& num) {
    //Creamos el objeto que almacenará el resultado
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
      if (*this > num) {
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
      if (*this > num) {
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
  Number<N,B,T> Number<N,B,T>::operator* (const Number<N,B,T>& num) {
    Number<N,B,T> result;

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
    assert(!(num == 0));
    if(*this < num) return Number<N,B,T>();

    int cociente = 0;
    Number<N,B,T> resto = *this;

    do {
      resto = sub(resto,num);
      cociente++;
    } while (resto > num || resto == num); // resto >= num

    Number<N,B,T> coc(cociente);

    if (sign_ == num.is_negative()) {
      coc.set_sign(0);
    } else {
      coc.set_sign(1);
    }
    return coc;
  }
  
template<std::size_t N, std::size_t B, class T>
bool Number<N,B,T>::operator> (const Number<N,B,T>& num) const {
  for (int i = N-1; i >= 0; i--) {
    if (number_[i] != num[i]) {
      if (number_[i] > num[i]) return true;
      else return false;
    }
  }
  return false;
}

template<std::size_t N, std::size_t B, class T>
bool Number<N,B,T>::operator< (const Number<N,B,T>& num) const {
  for (int i = N-1; i >= 0; i--) {
    if (number_[i] != num[i]) {
      if (number_[i] > num[i]) return false;
      else return true;
    }
  }
  return false;
}

template<std::size_t N, std::size_t B, class T>
bool Number<N,B,T>::operator== (const Number<N,B,T>& num) const {
  for (int i = N-1; i >= 0; i--) {
    if (number_[i] != num[i]) {
      return false;
    }
  }
  return true;
}


//METODOS PRIVADOS///////////////////////////////////////////
template<std::size_t N, std::size_t B, class T>
void Number<N,B,T>::to_base (int n) {
  assert((std::is_same<T,char>::value) || B <= 10); //Para tipo 'int' la base no puede ser > 10.
  int div = n, it = 0;
  do {
    assert(it+1 <= N);
    number_[it++] = (div%B >= 10 ? div%B+55 : div%B + (std::is_same<T, char>::value ? '0' : 0));
    div /= B;
  } while (div >= B);
  if (div != 0) number_[it] = (div >= 10 ? div+55 : div + (std::is_same<T, char>::value ? '0' : 0));
}

//Realiza la operacion Num1 + Num2 con Num1 y Num2 valores sin signo
template<std::size_t N, std::size_t B, class T>
Number<N,B,T> Number<N,B,T>::add (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2) {
  bool carry = 0;
  int sum = 0;

  T* result = new T [N];

  //Inicializamos los valores a 0
  for (int i = 0; i < N; i++) {
    if (std::is_same<T,char>::value) {
      result[i] = '0';
    } else {
      result[i] = 0;
    }
  }

  //Esto es debido a que el vector almacena el numero de forma invertida
  for (int i = 0; i < N; i++) { 
    int num1 = 0, num2 = 0;
    //Si el numero tiene un valor >= 10 significa que es una letra
    if ((std::is_same<T,char>::value) && Num1[i] >= 65) {
      num1 = Num1[i] - 55;
    } else {
      num1 = Num1[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Igual para el otro valor
    if ((std::is_same<T,char>::value) && Num2[i] >= 65) {
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

  //Liberamos memoria de result
  delete [] result;
  result = NULL;

  return final_number;
}

//Realiza la operacion Num1 - Num2 con Num1 y Num2 valores sin signo
template<std::size_t N, std::size_t B, class T>
Number<N,B,T> Number<N,B,T>::sub (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2) {
  bool carry = 0;
  int rest = 0;

  T* result = new T[N];

  //Inicializamos los valores a 0
  for (int i = 0; i < N; i++) {
    if (std::is_same<T, char>::value) {
      result[i] = '0';
    } else {
      result[i] = 0;
    }
  }

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

  //Liberamos memoria de result
  delete[] result;
  result = NULL;

  return final_number;
}

template<std::size_t N, std::size_t B, class T>
Number<N,B,T> Number<N,B,T>::mult (const Number<N,B,T>& Num1, const Number<N,B,T>& Num2) {
  int carry = 0;
  int mult = 0;
  int num1, num2;

  //Almacena los diferentes resultados para sumarlos todos
  //Se usa 2*N para asegurarnos el correcto funcionamiento de la multiplicacion
  Number<2*N,B,T>* result = new Number<2*N,B,T> [Num2.digits()];

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

  Number<2*N,B,T> sum;
  for (int i = 0; i < Num2.digits(); i++) {
    sum = sum + result[i];
  }

  //Nos aseguramos que no se pase del tamaño N
  for (int i = 2*N-1; i <= N; i++) {
    assert(sum[i] == 0); //Si ocurriera lo contrario (sum[i] != 0) habria overflow
  }

  //Convertimos a un Number de N digitos, que es lo que buscamos
  Number<N,B,T> final_result;
  for (int i = 0; i < N; i++) {
    final_result[i] = sum[i];
  }

  //Liberamos memoria de result y Nresult
  delete[] result;
  result = NULL;

  return final_result;
}

// CLASE ESPECIAL PARA BASE = 2 ////////////////////////////////////////////////////////////////////
template <std::size_t N, class T>
class Number<N,2,T> {
private:
  T* number_;
public:

  Number (int value = 0);
  Number (const Number<N,2,T>& A);
  ~Number (void);

  std::ostream& write (std::ostream& os) const;

  void set_sign (bool sign);
  bool is_negative (void) const;

  int digits (void) const;

  Number<N,2,T> abs (void) const;
  Number<N,2,T> reverse (void) const;

  //Asignadores
  T& operator[] (std::size_t i);
  const T operator[] (std::size_t i) const;
  Number<N,2,T>& operator= (const Number<N,2,T>& num);

  //Operadores
  Number<N,2,T> operator+ (const Number<N,2,T>& num);
  Number<N,2,T> operator- (const Number<N,2,T>& num);
  Number<N,2,T> operator* (const Number<N,2,T>& num);
  Number<N,2,T> operator/ (const Number<N,2,T>& num);

  //Comparadores
  bool operator> (const Number<N,2,T>& num) const;
  bool operator< (const Number<N,2,T>& num) const;
  bool operator== (const Number<N,2,T>& num) const;


private:
  void to_base(int n);

  //Metodos de operaciones en valor absoluto
  Number<N,2,T> add (const Number<N,2,T>& Num1, const Number<N,2,T>& Num2);
  Number<N,2,T> sub (const Number<N,2,T>& Num1, const Number<N,2,T>& Num2);
  Number<N,2,T> mult (const Number<N,2,T>& Num1, const Number<N,2,T>& Num2);
};

//METODOS PUBLICOS///////////////////////////////////////////////
template<std::size_t N, class T>
Number<N,2,T>::Number (int value): number_(NULL) {

  number_ = new T [N];

  //Inicializamos los valores
  for (int i = 0; i < N; i++) {
    if (std::is_same<T,char>::value) {
      number_[i] = '0';
    } else {
      number_[i] = 0;
    }
  }

  if (value < 0) {
    to_base(value*(-1)); //Nos generara el numero en binario natural
    set_sign(1); //Cambiamos a negativo
  } else if (value > 0) {
    to_base(value);
  }
}

template <std::size_t N, class T>
Number<N,2,T>::Number(const Number<N, 2, T> &A) : number_(NULL) {
  
  number_ = new T [N];

  *this = A;
}

template<std::size_t N, class T>
Number<N,2,T>::~Number (void) {
  delete [] number_;
  number_ = NULL;
}

template <std::size_t N, class T>
std::ostream &Number<N, 2, T>::write(std::ostream &os) const
{
  //Imprimimos el dato
  for (int i = N - 1; i >= 0; i--)
  {
    os << number_[i];
  }
  return os;
}

//SIGNO Y DIGITOS///////////////////////////////////////////////
template <std::size_t N, class T>
void Number<N, 2, T>::set_sign(bool sign) //Convierte el numero al signo indicado 
{
  if ((number_[N-1] == (std::is_same<T,char>::value ? '1' : 1) && sign == 0) || (number_[N-1] == (std::is_same<T,char>::value ? '0' : 0) && sign == 1)) {
    //Realizamos el complemento a dos
    bool complement = false;
    for (int i = 0; i < N; i++) {
      if (complement == true) {
        if (number_[i] == (std::is_same<T,char>::value ? '0' : 0)) {
          number_[i] = (std::is_same<T, char>::value ? '1' : 1);
        } else {
          number_[i] = (std::is_same<T, char>::value ? '0' : 0);
        }
      }
      else if (number_[i] == (std::is_same<T, char>::value ? '1' : 1)) {
        complement = true;
      }
    }
  }
}

template <std::size_t N, class T>
bool Number<N, 2, T>::is_negative(void) const
{
  return (number_[N-1] == (std::is_same<T,char>::value ? '1' : 1));
}

template <std::size_t N, class T>
int Number<N, 2, T>::digits(void) const
{
  return N;
}

template <std::size_t N, class T>
Number<N, 2, T> Number<N, 2, T>::abs(void) const
{
  if (number_[N-1] == 0) {
    return Number<N,2,T>(*this);
  } else {
    Number<N,2,T> copy(*this);
    copy.set_sign(0);
    return copy;
  }
}

template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::reverse (void) const {
  Number<N,2,T> copy = *this;
  copy.set_sign(!copy.is_negative());
  return copy;
}

//SOBRECARGA DE OPERADORES///////////////////////////////////
template<std::size_t N, class T>
std::ostream& operator<< (std::ostream& os, const Number<N,2,T>& number) {
  number.write(os);
  return os;
}

template<std::size_t N, class T>
T& Number<N,2,T>::operator[] (std::size_t i) {
  assert(i >= 0 && i < N);
  return number_[i];
}

template<std::size_t N, class T>
const T Number<N,2,T>::operator[] (std::size_t i) const {
  assert(i >= 0 && i < N);
  return number_[i];
}

template<std::size_t N, class T>
Number<N,2,T>& Number<N,2,T>::operator= (const Number<N,2,T>& num) {

  for (int i = 0; i < N; i++) {
    number_[i] = num.number_[i];
  }
  return *this;
}

template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::operator+ (const Number<N,2,T>& num) {
  /* En complemento a 2 la propia suma nos dira el signo del resultado, por lo que nos basta con sumar */
  return add(*this, num);
}

template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::operator- (const Number<N,2,T>& num) {
  /*
  La resta en binario se puede traducir a realizar el complemento a 2 al segundo valor y sumar el primero
  dicho resultado
  */
  return sub(*this,num); //El metodo 'sub' se encargara de hacer lo mencionado arriba
}

template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::operator* (const Number<N,2,T>& num) {
  Number<N,2,T> result;

  //Casos posibles
  // (+A) x (+B) = (+)(AxB)
  // (-A) x (-B) = (+)(AxB)
  // (+A) x (-B) = (-)(AxB)
  // (-A) x (+B) = (-)(AxB)

  

  result = mult(*this, num);

  return result;
}

template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::operator/ (const Number<N,2,T>& num) {
  assert(!(num == 0));
  if(*this < num) return Number<N,2,T>();

  int cociente = 0;
  Number<N,2,T> resto = abs();
  Number<N,2,T> coc;

  do {
    resto = sub(resto,num.abs());
    cociente++;
  } while (resto > num.abs() || resto == num.abs()); // resto >= num

  coc = cociente;

  if (is_negative() == num.is_negative()) {
    coc.set_sign(0);
  } else {
    coc.set_sign(1);
  }

  return coc;
}

template <std::size_t N, class T>
bool Number<N, 2, T>::operator>(const Number<N, 2, T> &num) const
{
  if (is_negative() == num.is_negative()) {
    //Si tienen distinto mismo signo, realizamos la comprobacion por digitos (en valor absoluto)
    for (int i = N-1; i >= 0; i--) {
      if (abs()[i] != num.abs()[i]) {
        if (number_[i] > num[i]) {
          return true;
        } else {
          return false;
        }
      }
    }
    return false;
  } else {
    //Si tienen distinto signo signo, el mayor es el positivo
    return (is_negative() == 0 ? true : false);
  }
}

template <std::size_t N, class T>
bool Number<N, 2, T>::operator<(const Number<N, 2, T> &num) const
{
  if (is_negative() == num.is_negative()) {
    //Si tienen distinto mismo signo, realizamos la comprobacion por digitos (en valor absoluto)
    for (int i = N-1; i >= 0; i--) {
      if (abs()[i] != num.abs()[i]) {
        if (number_[i] < num[i]) {
          return true;
        } else {
          return false;
        }
      }
    }
    return false;
  } else {
    //Si tienen distinto signo signo, el menor es el negativo
    return (is_negative() == 1 ? true : false);
  }
}

template <std::size_t N, class T>
bool Number<N, 2, T>::operator==(const Number<N, 2, T> &num) const
{
if (is_negative() == num.is_negative()) {
    //Si tienen distinto mismo signo, realizamos la comprobacion por digitos (en valor absoluto)
    for (int i = N-1; i >= 0; i--) {
      if (abs()[i] != num.abs()[i]) {
        return false;
      }
    }
    return true;
  } else {
    //Si tienen distinto signo signo, evidentenmente son diferentes
    return false;
  }
}

//METODOS PRIVADOS///////////////////////////////////////////
template<std::size_t N, class T>
void Number<N,2,T>::to_base (int n) {
  assert((std::is_same<T,char>::value)); //Para tipo 'int' la base no puede ser > 10.
  int div = n, it = 0;
  do {
    assert(it+1 <= N);
    number_[it++] = (div%2 >= 10 ? div%2+55 : div%2 + (std::is_same<T, char>::value ? '0' : 0));
    div /= 2;
  } while (div >= 2);
  if (div != 0) number_[it] = (div >= 10 ? div+55 : div + (std::is_same<T, char>::value ? '0' : 0));
}

//Realiza la operacion Num1 + Num2 con Num1 y Num2 valores sin signo
template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::add (const Number<N,2,T>& Num1, const Number<N,2,T>& Num2) {
  bool carry = 0;
  int sum = 0;

  T* result = new T [N];

  //Inicializamos los valores a 0
  for (int i = 0; i < N; i++) {
    if (std::is_same<T,char>::value) {
      result[i] = '0';
    } else {
      result[i] = 0;
    }
  }

  //Esto es debido a que el vector almacena el numero de forma invertida
  for (int i = 0; i < N; i++) { 
    int num1 = 0, num2 = 0;
    //Si el numero tiene un valor >= 10 significa que es una letra
    if ((std::is_same<T,char>::value) && Num1[i] >= 65) {
      num1 = Num1[i] - 55;
    } else {
      num1 = Num1[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Igual para el otro valor
    if ((std::is_same<T,char>::value) && Num2[i] >= 65) {
      num2 = Num2[i] - 55;
    } else {
      num2 = Num2[i] - (std::is_same<T,char>::value ? '0' : 0);
    }
    //Realizamos la suma
    sum = carry + num1 + num2;
    if (sum >= 2) {
      sum = sum-2;
      carry = 1;
    } else {
      carry = 0;
    }
    if (std::is_same<T,char>::value && sum >= 10) result[i] = sum + 55;
    else result[i] = sum + (std::is_same<T,char>::value ? '0' : 0);
  }

  //Comprobamos el overflow
  if (Num1.is_negative() == Num2.is_negative()) { //Si los signos son iguales, hay posible overflow
    assert(result[N-1] == Num1[N-1]);
  }

  Number<N,2,T> final_number;
  for (int i = 0; i < N; i++) {
    final_number[i] = result[i];
  }

  //Liberamos memoria de result
  delete [] result;
  result = NULL;

  return final_number;
}

//Realiza la operacion Num1 - Num2 con Num1 y Num2 valores sin signo
template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::sub (const Number<N,2,T>& Num1, const Number<N,2,T>& Num2) {
  /* En este caso la resta se traduce a realizar el complemento a 2 (invertir el signo) de Num2 y sumarle Num1 */
  return add(Num1,Num2.reverse());
}

template<std::size_t N, class T>
Number<N,2,T> Number<N,2,T>::mult (const Number<N,2,T>& Num1, const Number<N,2,T>& Num2) {
  int carry = 0;
  int mult = 0;
  int num1, num2;

  //Almacena los diferentes resultados para sumarlos todos
  //Se usa 2*N para asegurarnos el correcto funcionamiento de la multiplicacion
  Number<2*N,2,T>* result = new Number<2*N,2,T> [Num2.digits()];

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
      while(mult >= 2) {
        mult -= 2;
        carry++;
      }

      if (std::is_same<T,char>::value && mult >= 10) { //Se trata de una letra
        result[i][j+i] = mult + 55;
      } else {
        result[i][j+i] = mult + (std::is_same<T,char>::value ? '0' : 0);
      }
    }
  }

  Number<2*N,2,T> sum;
  for (int i = 0; i < Num2.digits(); i++) {
    sum = sum + result[i];
  }

  //Nos aseguramos que no se pase del tamaño N
  for (int i = 2*N-1; i <= N; i++) {
    assert(sum[i] == 0); //Si ocurriera lo contrario (sum[i] != 0) habria overflow
  }

  //Convertimos a un Number de N digitos, que es lo que buscamos
  Number<N,2,T> final_result;
  for (int i = 0; i < N; i++) {
    final_result[i] = sum[i];
  }

  //Liberamos memoria de result y Nresult
  delete[] result;
  result = NULL;

  return final_result;
}
