#include "ComplexNumber.h"
#include "helper.h"

ComplexNumber::ComplexNumber()
{
    /* Your code here */
  number_type = COMPLEX;
  magnitude = 0.0;
  phase = 0.0;
  real_component = 0.0;
  imaginary_component = 0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    /* Your code here */
  number_type = COMPLEX;
  magnitude = sqrt(rval_real_component*rval_real_component + rval_imaginary_component*rval_imaginary_component);
  phase = calculate_phase(rval_real_component, rval_imaginary_component);//might be changed
  real_component = rval_real_component;
  imaginary_component = rval_imaginary_component;
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    /* Your code here */
  number_type = COMPLEX;
  magnitude = other.get_magnitude();
  phase = other.get_phase();
  real_component = other.get_real_component();
  imaginary_component = other.get_imaginary_component();
}

void ComplexNumber::set_real_component (double rval)
{
    /* Your code here */
  real_component = rval;
  magnitude = sqrt(real_component*real_component + imaginary_component*imaginary_component);
  phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_real_component() const
{
    /* Your code here */
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    /* Your code here */
  imaginary_component = rval;
  magnitude = sqrt(real_component*real_component + imaginary_component*imaginary_component);
  phase = calculate_phase(real_component, imaginary_component);
}

double ComplexNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
  double new_real = real_component + arg.get_real_component();
  double new_imag = imaginary_component + arg.get_imaginary_component();
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
  double new_real = real_component - arg.get_real_component();
  double new_imag = imaginary_component - arg.get_imaginary_component();
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
  double new_real = real_component * arg.get_real_component() - imaginary_component * arg.get_imaginary_component();
  double new_imag = imaginary_component * arg.get_real_component() + real_component * arg.get_imaginary_component();
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
  double denominator = arg.get_magnitude() * arg.get_magnitude();
  double new_real = (real_component * arg.get_real_component() + imaginary_component * arg.get_imaginary_component()) / denominator;
  double new_imag = (imaginary_component * arg.get_real_component() - real_component * arg.get_imaginary_component()) / denominator;
	return ComplexNumber(new_real, new_imag);
}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber((real_component + arg.get_real_component()), (imaginary_component));
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber((real_component - arg.get_real_component()), (imaginary_component));
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber((real_component * arg.get_real_component()), (imaginary_component * arg.get_real_component()));
}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber((real_component / arg.get_real_component()), (imaginary_component / arg.get_real_component()));
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber((real_component), (imaginary_component + arg.get_imaginary_component()));
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber((real_component), (imaginary_component - arg.get_imaginary_component()));
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber((-imaginary_component * arg.get_imaginary_component()), (real_component * arg.get_imaginary_component()));
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber((imaginary_component / arg.get_imaginary_component()), (-real_component / arg.get_imaginary_component()));
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}
