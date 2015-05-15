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

Factory::Factory() : _vm(new VmStack<const IOperand*>()) {};

Factory::~Factory() {}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {

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

IOperand const * Factory::createInt8( std::string const & value ) const {
	return new TOperand<int8_t>(static_cast<int8_t>(std::stoi(value)), e_int_8);
}

IOperand const * Factory::createInt16( std::string const & value ) const {
	return new TOperand<int16_t>(static_cast<int16_t>(std::stoi(value)), e_int_16);
}

IOperand const * Factory::createInt32( std::string const & value ) const {
	return new TOperand<int32_t>(static_cast<int32_t>(std::stoi(value)), e_int_32);
}

IOperand const * Factory::createFloat( std::string const & value ) const {
	return new TOperand<float>(static_cast<float>(::atof(value.c_str())), e_float);
}

IOperand const * Factory::createDouble( std::string const & value ) const {
	return new TOperand<double>(static_cast<double>(::atof(value.c_str())), e_double);
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
		this->_vm->pop();
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
	std::cout << std::endl;
}

void 			  	  Factory::_Add() const {

	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a + *b;
	this->_vm->push(x);
}

void 			  	  Factory::_Sub() const {

	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a - *b;
	this->_vm->push(x);
}

void 			  	  Factory::_Mul() const {

	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = (*a) * (*b);
	this->_vm->push(x);
}

void 			  	  Factory::_Div() const {

	const IOperand* a = _vm->top();
	_vm->pop();
	const IOperand* b = _vm->top();
	_vm->pop();
	const IOperand* x = *a / *b;
	this->_vm->push(x);
}

void 			  	  Factory::_Mod() const {

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
		throw std::runtime_error(("\033[31mType Error\033[0m"));
	std::string value = this->_getValue(str);

	const IOperand* a = Factory().createOperand(type, value);
	const IOperand* b = this->_vm->top();
	if (*a == *b)
		std::cout << "TRUE" << std::endl;
	else
		std::cout << "FALSE" << std::endl;
}
