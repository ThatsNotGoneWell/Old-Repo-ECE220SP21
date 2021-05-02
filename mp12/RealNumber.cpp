#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    /* Your code here */
  number_type = REAL;
  magnitude = 0.0;
  phase = 0.0;
  real_component = 0.0;
}

RealNumber::RealNumber(double rval)
{
    /* Your code here */
  number_type = REAL;
  magnitude = abs(rval);
  phase = calculate_phase(rval, 0.0);
  real_component = rval;
}

RealNumber::RealNumber( const RealNumber& other )
{
    /* Your code here */
  number_type = REAL;
  magnitude = other.get_magnitude();
  phase = other.get_phase();
  real_component = other.get_real_component();
}

void RealNumber::set_real_component (double rval)
{
    /* Your code here */
  real_component = rval;
  phase = calculate_phase(rval, 0.0);
  magnitude = abs(rval);
}

double RealNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component + arg.get_real_component());
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component - arg.get_real_component());
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component * arg.get_real_component());
}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component / arg.get_real_component());
}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, -arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(real_component * arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(-real_component / arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
  double new_real = real_component + arg.get_real_component();
  double new_imag = 0.0 + arg.get_imaginary_component();
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
  double new_real = real_component - arg.get_real_component();
  double new_imag = 0.0 - arg.get_imaginary_component();
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
  double new_real = real_component * arg.get_real_component();
  double new_imag = real_component * arg.get_imaginary_component();
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){//might be changed
    /* Your code here */
  double denominator = arg.get_magnitude() * arg.get_magnitude();
  double new_real = (real_component * arg.get_real_component()) / denominator;
  double new_imag = (real_component * (-arg.get_imaginary_component())) / denominator;
	return ComplexNumber(new_real, new_imag);
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}
