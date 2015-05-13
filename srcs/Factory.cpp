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

#include "Factory.hpp"

Factory::Factory() : _vm(new VmStack<const IOperand*>()) {};

Factory::~Factory() {}

IOperand const * Factory::createOperand( eOperandType type, std::string const & value ) const {

	if (type == e_typeError)
		throw std::runtime_error(("\033[31mType Error\033[0m"));
	if (type == e_int_8)
		return this->createInt8(value);
	if (type == e_int_16)
		return this->createInt16(value);
	if (type == e_int_32)
		return this->createInt32(value);
	if (type == e_float)
		return this->createFloat(value);
	if (type == e_double)
		return this->createDouble(value);
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
}

void 				  Factory::_Push(std::string str) const {

	eOperandType type = this->_getType(str);
	if (type == e_typeError)
		throw std::runtime_error(("\033[31mType Error\033[0m"));
	std::string value = this->_getValue(str);
	this->_vm->push(this->createOperand(type, value));
}

void 				  Factory::Show() const {

	for (auto& x : *_vm)
		std::cout << x->toString() << std::endl;
}
