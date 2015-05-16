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

Factory::FactoryException::FactoryException(std::string error) throw()
	: std::runtime_error(error) {}

Factory::FactoryException::~FactoryException() throw() {}

const char*		Factory::FactoryException::what() const throw() {

	std::string was = "Execution Fail : " + std::string(std::runtime_error::what());
	return was.c_str();
}

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

Factory::Factory() : _vm(new VmStack<const IOperand*>()) {};

Factory::~Factory() {}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {

	if (type == e_typeError)
		throw FactoryException(("\033[31mType Error\033[0m"));
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

IOperand const * Factory::createInt8( std::string const & value ) const {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = stod(value);
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

IOperand const * Factory::createInt16( std::string const & value ) const {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = stod(value);
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

IOperand const * Factory::createInt32( std::string const & value ) const {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = stod(value);
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

IOperand const * Factory::createFloat( std::string const & value ) const {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = stod(value);
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

IOperand const * Factory::createDouble( std::string const & value ) const {

	double test;
	std::feclearexcept(FE_OVERFLOW);
	std::feclearexcept(FE_UNDERFLOW);
	try {
		test = stod(value);
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

/* ---------------------------------------------------------------------- */
eOperandType   Factory::_getType(std::string val) const {

	size_t   pos = val.find('(');
	size_t   posi = val.find(')');
	if (pos == std::string::npos || posi == std::string::npos || posi <= pos)
		return e_typeError;
	std::string t = val.substr(0, pos);

	if (t == "int8")
		return e_int_8;
	if (t == "int16")
		return e_int_16;
	if (t == "int32")
		return e_int_32;
	if (t == "float")
		return e_float;
	if (t == "double")
		return e_double;

	return e_typeError;
}

std::string    Factory::_getValue(std::string val) const {

	size_t   pos = val.find('(') + 1;
	size_t   posi = val.find(')');

	return (val.substr(pos, posi - pos));
}

/* ---------------------------------------------------------------------- */
void 				  Factory::Execute(t_StrPair ins) const {

	if (ins.first == "push")
		this->_Push(ins.second);
	else if (ins.first == "pop")
	{
		if (this->_vm->empty())
			throw FactoryException(("\033[31mEmpty Stack !\033[0m"));
		this->_vm->pop();
	}
	else if (ins.first == "add")
		this->_Add();
	else if (ins.first == "sub")
		this->_Sub();
	else if (ins.first == "mul")
		this->_Mul();
	else if (ins.first == "div")
		this->_Div();
	else if (ins.first == "mod")
		this->_Mod();
	else if (ins.first == "dump")
		this->_Dump();
	else if (ins.first == "print")
		this->_Print();
	else if (ins.first == "assert")
		this->_Assert(ins.second);
}

void 				  Factory::_Push(std::string str) const {

	eOperandType type = this->_getType(str);
	if (type == e_typeError)
		throw std::runtime_error(("\033[31mType Error\033[0m"));
	std::string value = this->_getValue(str);
	this->_vm->push(this->createOperand(type, value));
}

void 				  Factory::_Dump() const {

	VmStack<const IOperand*>::iterator	ite = this->_vm->end();
	VmStack<const IOperand*>::iterator	it = this->_vm->begin();

	while (it != ite)
	{
		--ite;
		std::cout << (*ite)->toString() << std::endl;
	}
}

void 			  	  Factory::_Add() const {

	if (_vm->size() < 2)
		throw FactoryException(("\033[31mMissing values\033[0m"));
	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a + *b;
	this->_vm->push(x);
}

void 			  	  Factory::_Sub() const {

	if (_vm->size() < 2)
		throw FactoryException(("\033[31mMissing values\033[0m"));
	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a - *b;
	this->_vm->push(x);
}

void 			  	  Factory::_Mul() const {

	if (_vm->size() < 2)
		throw FactoryException(("\033[31mMissing values\033[0m"));
	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = (*a) * (*b);
	this->_vm->push(x);
}

void 			  	  Factory::_Div() const {

	if (_vm->size() < 2)
		throw FactoryException(("\033[31mMissing values\033[0m"));
	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a / *b;
	this->_vm->push(x);
}

void 			  	  Factory::_Mod() const {

	if (_vm->size() < 2)
		throw FactoryException(("\033[31mMissing values\033[0m"));
	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a % *b;
	this->_vm->push(x);
}

void 				  Factory::_Print() const {

	char	c = std::stoi(this->_vm->top()->toString());
	std::cout << c << std::endl;
}

void 				  Factory::_Assert(std::string str) const {

	eOperandType type = this->_getType(str);
	if (type == e_typeError)
		throw FactoryException(("\033[31mType Error\033[0m"));
	std::string value = this->_getValue(str);

	const IOperand* a = Factory().createOperand(type, value);
	const IOperand* b = this->_vm->top();
	if (!(*a == *b))
		throw FactoryException(("\033[31mAssert Error ==> given value different from the last value on the stack\033[0m"));
}
