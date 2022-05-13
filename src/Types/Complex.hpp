/**
 * reference LICENSE file provided.
 *
 * @file Complex.hpp
 * Declarations for Complex
 */

#ifndef COMPLEX_HPP
#define COMPLEX_HPP

#include <complex>
#include <iostream>

/**
 * @class Complex
 * Represents a complex number explicitly designed to serialize/deserialize
 *   as this library expects it to, for little-endian/big-endian.
 */
template <class T_c>
class Complex
{
public:

  /**
   * Initial values constructor; real/imaginary.
   * @param[in] arg_real Initial value for real component
   * @param[in] arg_imag Initial value for imaginary component
   */
  Complex(T_c arg_real, T_c arg_imag);

  /**
   * Copy constructor.
   * @param[in] arg_rhs Instance from which `this` will be copied.
   */
  Complex(const Complex<T_c>& arg_rhs);

  /**
   * Initial values constructor; real component with zero-imaginary.
   * @param[in] arg_real Initial value for real component.
   */
  Complex(T_c arg_real);

  /**
   * Default constructor; initializes to 0 + j0.
   */
  Complex();

  /**
   * Destroys the instance.
   */
  ~Complex() { } ;

  /**
   * Reports real component of this complex number.
   * @return Real component of this complex number instance.
   */
  T_c GetReal() const;

  /**
   * Reports imaginary component of this complex number.
   * @return Imaginary component of this complex number instance.
   */
  T_c GetImaginary() const;

  /**
   * Sets real component of this complex number.
   * @param[in] arg_real Value to which real component will be set.
   */
  void SetReal(T_c arg_real);

  /**
   * Sets imaginary component of this complex number.
   * @param[in] arg_imag Value to which imaginary component will be set.
   */
  void SetImaginary(T_c arg_imag);

  /**
   * Reports a `std::complex` that whose real and imaginary components equal
   * those of this instance.
   *
   * @return
   * An instance of std::complex whose real and imaginary components equal
   * those of this instance.
   */
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

