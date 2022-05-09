/**
 * reference LICENSE file provided.
 * 
 * @file Complex.cpp
 * Implements Complex.hpp
 * 
 */

#include <Message/MessageConstants.hpp>
#include "Complex.hpp"

template <class T_c>
Complex<T_c>::Complex(T_c arg_real, T_c arg_imaginary)
{
  SetReal(arg_real);
  SetImaginary(arg_imaginary);
}

template <class T_c>
Complex<T_c>::Complex(const Complex<T_c>& arg_rhs)
{
  SetReal(arg_rhs.GetReal());
  SetImaginary(arg_rhs.GetImaginary());
}

template <class T_c>
Complex<T_c>::Complex(T_c arg_real)
{
  SetReal(arg_real);
  SetImaginary(0);
}

template <class T_c>
Complex<T_c>::Complex()
{
  SetReal(0);
  SetImaginary(0);
}

template <class T_c>
T_c Complex<T_c>::GetReal() const
{
  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    return _value[0];
  }
  else
  {
    return _value[1];
  }
}

template <class T_c>
T_c Complex<T_c>::GetImaginary() const
{
  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    return _value[1];
  }
  else
  {
    return _value[0];
  }
}

template <class T_c>
void Complex<T_c>::SetReal(T_c arg_real)
{
  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    _value[0] = arg_real;
  }
  else
  {
    _value[1] = arg_real;
  }
}

template <class T_c>
void Complex<T_c>::SetImaginary(T_c arg_imaginary)
{
  if (MessageConstants::IS_LITTLE_ENDIAN == true)
  {
    _value[1] = arg_imaginary;
  }
  else
  {
    _value[0] = arg_imaginary;
  }
}

template <class T_c>
std::complex<T_c> Complex<T_c>::GetStandard() const
{
  return std::complex<T_c>(GetReal(), GetImaginary());
}

template class Complex<float>;
template class Complex<double>;
template class Complex<long double>;

