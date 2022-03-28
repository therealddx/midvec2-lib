/**
 *
 * reference LICENSE file provided.
 *
 * Complex.hpp
 * 
 * Represents a complex number that explicitly serializes/deserializes
 * the way this library expects it to, for little-endian/big-endian.
 *
 */

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <complex>
#include <iostream>

template <class T_c>
class Complex
{
public:

  // Ctor.
  // Requires initial values for real and imaginary components.
  // 
  Complex<T_c>(T_c arg_real, T_c arg_imag);

  // Copy ctor.
  // 
  Complex<T_c>(const Complex<T_c>& arg_rhs);

  // Real ctor.
  Complex<T_c>(T_c);

  // Empty ctor.
  // 
  Complex<T_c>();

  // Dtor.
  // Nothing to do. Backing data is stack-allocated.
  // 
  ~Complex<T_c>() { } ;

  // GetReal.
  // Return real component of this complex value.
  // 
  T_c GetReal() const;

  // GetImaginary.
  // Return imaginary component of this complex value.
  // 
  T_c GetImaginary() const;

  // SetReal.
  // Store argument real component into this complex number.
  // 
  void SetReal(T_c arg_real);

  // SetImaginary.
  // Store argument imaginary component into this complex number.
  // 
  void SetImaginary(T_c arg_imag);

  // GetStandard.
  // Return a std::complex of matching types, to 
  // take advantage of standard library implementations.
  // 
  std::complex<T_c> GetStandard() const;

  // Assignment operator '='.
  // 
  Complex<T_c>& operator=(const Complex<T_c>& arg_cpx)
  {
    SetReal(arg_cpx.GetReal());
    SetImaginary(arg_cpx.GetImaginary());
    return *this;
  }

  // Addition operator '+'.
  // 
  Complex<T_c> operator+(const Complex<T_c>& arg_rhs) const
  {
    Complex<T_c> rtn(
      this->GetReal() + arg_rhs.GetReal(),
      this->GetImaginary() + arg_rhs.GetImaginary());

    return rtn;
  }

  // Self-addition operator '+='.
  // 
  Complex<T_c>& operator+=(const Complex<T_c>& arg_rhs) // NOT const
  {
    this->SetReal(
      this->GetReal() + arg_rhs.GetReal());
    this->SetImaginary(
      this->GetImaginary() + arg_rhs.GetImaginary());

    return *this;
  }

  // Subtraction operator '-'.
  // 
  Complex<T_c> operator-(const Complex<T_c>& arg_rhs) const
  {
    Complex<T_c> rtn(
      this->GetReal() - arg_rhs.GetReal(),
      this->GetImaginary() - arg_rhs.GetImaginary());

    return rtn;
  }

  // Self-addition operator '-='.
  // 
  Complex<T_c>& operator-=(const Complex<T_c>& arg_rhs) // NOT const
  {
    this->SetReal(
      this->GetReal() - arg_rhs.GetReal());
    this->SetImaginary(
      this->GetImaginary() - arg_rhs.GetImaginary());

    return *this;
  }

  // Multiplication operator '*'.
  // 
  Complex<T_c> operator*(const Complex<T_c>& arg_rhs) const
  {
    // this == (a + jb)
    // arg_rhs == (c + jd)
    // 
    // (a + jb)(c + jd) =>
    //   ac + jad + jbc + (-1)bd =>
    //     (ac - bd) + j(ad + bc)
    // 
    // a == this->GetReal()   ; b == this->GetImaginary()
    // c == arg_rhs.GetReal() ; d == arg_rhs.GetImaginary()
    // 
    Complex<T_c> rtn
      ( this->GetReal() * arg_rhs.GetReal() - ( this->GetImaginary() * arg_rhs.GetImaginary() )
      , this->GetReal() * arg_rhs.GetImaginary() + this->GetImaginary() * arg_rhs.GetReal()
      );

    return rtn;
  }

  // Self-multiplication operator '*='.
  // 
  Complex<T_c>& operator*=(const Complex<T_c>& arg_rhs) // NOT const
  {
    this->SetReal(
      this->GetReal() * arg_rhs.GetReal() - ( this->GetImaginary() * arg_rhs.GetImaginary() )
      );

    this->SetImaginary(
      this->GetReal() * arg_rhs.GetImaginary() + this->GetImaginary() * arg_rhs.GetReal()
      );

    return *this;
  }

private:

  // On little-endian platforms, complex values are stored as:
  //   <index 0>   <index 1>
  //   R0R1R2...R7|I0I1I2...I7
  // 
  // On big-endian platforms, complex values shall be stored as:
  //   <index 0>   <index 1>
  //   I7I6I5...I0|R7R6R5...R0
  // 
  T_c _value[2];
};

// Extraction operator.
// 'Since they take the user-defined type,
//   they must be implemented as non-members.' (cppreference)
// 
template <class T_c>
std::ostream& operator<<(std::ostream& arg_os, const Complex<T_c>& arg_cpx)
{
  arg_os << "'" << arg_cpx.GetReal() << " + " << arg_cpx.GetImaginary() << "i'";
  return arg_os;
}

#endif // COMPLEX_HPP

