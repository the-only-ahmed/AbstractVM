/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 18:10:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/08 18:19:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TOperand.tpp"
#include "Factory.hpp"

/* ------------------------------ Exception ------------------------------ */

Factory::OverflowError::OverflowError(std::string error) throw()
	: std::runtime_error(error) {}

Factory::OverflowError::~OverflowError() throw() {}

const char*		Factory::OverflowError::what() const throw() {

	std::string was = "\033[31mOver Flow Exception : " + std::string(std::runtime_error::what()) + "\033[0m";
	return was.c_str();
}

Factory::UnderflowError::UnderflowError(std::string error) throw()
	: std::runtime_error(error) {}

Factory::UnderflowError::~UnderflowError() throw() {}

const char*		Factory::UnderflowError::what() const throw() {

	std::string was = "\033[31mUnder Flow Exception : " + std::string(std::runtime_error::what()) + "\033[0m";
	return was.c_str();
}

/* ------------------------------ Parsing ------------------------------ */

Factory::Factory() {}

Factory::~Factory() {}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) {

	if (type == e_typeError)
		throw std::runtime_error(("\033[31mType Error\033[0m"));
	if (type == e_int_8)
		return Factory::createInt8(value);
	if (type == e_int_16)
		return Factory::createInt16(value);
	if (type == e_int_32)
		return Factory::createInt32(value);
	if (type == e_float)
		return Factory::createFloat(value);
	if (type == e_double)
		return Factory::createDouble(value);
	return NULL;
}

IOperand const * Factory::createInt8( std::string const & value ) {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = std::stod(value);
	} catch (std::out_of_range &e) {
		throw std::runtime_error("\033[31mOut of range exception\033[0m");
	}	if (std::fetestexcept(FE_UNDERFLOW))
		throw UnderflowError("int8");
	if (std::fetestexcept(FE_OVERFLOW))
		throw OverflowError("int8");
	if (test < SCHAR_MIN)
		throw UnderflowError("int8");
	else if (test > SCHAR_MAX)
		throw OverflowError("int8");

	return new TOperand<int8_t>(static_cast<int8_t>(test), e_int_8);
}

IOperand const * Factory::createInt16( std::string const & value ) {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = std::stod(value);
	} catch (std::out_of_range &e) {
		throw std::runtime_error("\033[31mOut of range exception\033[0m");
	}	if (std::fetestexcept(FE_UNDERFLOW))
		throw UnderflowError("int16");
	if (std::fetestexcept(FE_OVERFLOW))
		throw OverflowError("int16");
	if (test < SHRT_MIN)
		throw UnderflowError("int16");
	else if (test > SHRT_MAX)
		throw OverflowError("int16");

	return new TOperand<int16_t>(static_cast<int16_t>(test), e_int_16);
}

IOperand const * Factory::createInt32( std::string const & value ) {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = std::stod(value);
	} catch (std::out_of_range &e) {
		throw std::runtime_error("\033[31mOut of range exception\033[0m");
	}	if (std::fetestexcept(FE_UNDERFLOW))
		throw UnderflowError("int32");
	if (std::fetestexcept(FE_OVERFLOW))
		throw OverflowError("int32");
	if (test < INT_MIN)
		throw UnderflowError("int32");
	else if (test > INT_MAX)
		throw OverflowError("int32");

	return new TOperand<int32_t>(static_cast<int32_t>(test), e_int_32);
}

IOperand const * Factory::createFloat( std::string const & value ) {

	long double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = std::stold(value);
	} catch (std::out_of_range &e) {
		throw std::runtime_error("\033[31mOut of range exception\033[0m");
	}
	if (std::fetestexcept(FE_UNDERFLOW))
		throw UnderflowError("float");
	if (std::fetestexcept(FE_OVERFLOW))
		throw OverflowError("float");

	if (test < FLT_MIN)
		throw UnderflowError("float");
	if (test > FLT_MAX)
		throw OverflowError("float");

	return new TOperand<float>(static_cast<float>(test), e_float);
}

IOperand const * Factory::createDouble( std::string const & value ) {

	long double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = std::stold(value);
	} catch (std::out_of_range &e) {
		throw std::runtime_error("\033[31mOut of range exception\033[0m");
	}
	if (std::fetestexcept(FE_UNDERFLOW))
		throw UnderflowError("double");
	if (std::fetestexcept(FE_OVERFLOW))
		throw OverflowError("double");

	if (test < FLT_MIN)
		throw UnderflowError("double");
	if (test > FLT_MAX)
		throw OverflowError("double");

	return new TOperand<double>(test, e_double);
}
