/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Emulator.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 18:29:28 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/19 18:29:29 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "TOperand.tpp"
#include "Emulator.hpp"

Emulator::Emulator() : _vm(new VmStack<const IOperand*>()), _colorBegin("\033[0m"),
      _colorEnd("\033[0m"), _rainbow(true), _a(0), _b(31) {}

Emulator::~Emulator() {}

/* ------------------------------ Exception ------------------------------ */

Emulator::EmulatorException::EmulatorException(std::string error) throw()
   : std::runtime_error(error) {}

Emulator::EmulatorException::~EmulatorException() throw() {}

const char*		Emulator::EmulatorException::what() const throw() {

   std::string was = "Execution Fail : " + std::string(std::runtime_error::what());
   return was.c_str();
}

/* ---------------------------------------------------------------------- */

eOperandType   Emulator::_getType(std::string val) const {

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

std::string    Emulator::_getValue(std::string val) const {

   size_t   pos = val.find('(') + 1;
   size_t   posi = val.find(')');

   return (val.substr(pos, posi - pos));
}

/* ---------------------------------------------------------------------- */

void 				  Emulator::Execute(t_StrPair ins) {

   if (ins.first == "push")
      this->_Push(ins.second);
   else if (ins.first == "pop")
   {
      if (this->_vm->empty())
         throw EmulatorException(("\033[31mEmpty Stack !\033[0m"));
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

void 				  Emulator::_Push(std::string str) const {

   eOperandType type = this->_getType(str);
   if (type == e_typeError)
      throw std::runtime_error(("\033[31mType Error\033[0m"));
   std::string value = this->_getValue(str);
   this->_vm->push(Factory::createOperand(type, value));
}

void 				  Emulator::_Dump() {

   VmStack<const IOperand*>::iterator	ite = this->_vm->end();
   VmStack<const IOperand*>::iterator	it = this->_vm->begin();

   while (it != ite)
   {
      --ite;
      std::cout << this->_colorBegin << (*ite)->toString() << this->_colorEnd << std::endl;
      this->_ChangeColor();
   }
}

void 			  	  Emulator::_Add() const {

   if (_vm->size() < 2)
      throw EmulatorException(("\033[31mMissing values\033[0m"));
   const IOperand* a = _vm->top();
   _vm->pop();
   const IOperand* b = _vm->top();
   _vm->pop();
   const IOperand* x = *a + *b;
   this->_vm->push(x);
}

void 			  	  Emulator::_Sub() const {

   if (_vm->size() < 2)
      throw EmulatorException(("\033[31mMissing values\033[0m"));
   const IOperand* a = _vm->top();
   _vm->pop();
   const IOperand* b = _vm->top();
   _vm->pop();
   const IOperand* x = *a - *b;
   this->_vm->push(x);
}

void 			  	  Emulator::_Mul() const {

   if (_vm->size() < 2)
      throw EmulatorException(("\033[31mMissing values\033[0m"));
   const IOperand* a = _vm->top();
   _vm->pop();
   const IOperand* b = _vm->top();
   _vm->pop();
   const IOperand* x = (*a) * (*b);
   this->_vm->push(x);
}

void 			  	  Emulator::_Div() const {

   if (_vm->size() < 2)
      throw EmulatorException(("\033[31mMissing values\033[0m"));
   const IOperand* a = _vm->top();
   _vm->pop();
   const IOperand* b = _vm->top();
   _vm->pop();
   const IOperand* x = *a / *b;
   this->_vm->push(x);
}

void 			  	  Emulator::_Mod() const {

   if (_vm->size() < 2)
      throw EmulatorException(("\033[31mMissing values\033[0m"));
   const IOperand* a = _vm->top();
   _vm->pop();
   const IOperand* b = _vm->top();
   _vm->pop();
   const IOperand* x = *a % *b;
   this->_vm->push(x);
}

void 				  Emulator::_Print() {

   char	c = std::stoi(this->_vm->top()->toString());
   std::cout << this->_colorBegin << c << this->_colorEnd << std::endl;
   this->_ChangeColor();
}

void 				  Emulator::_Assert(std::string str) const {

   eOperandType type = this->_getType(str);
   if (type == e_typeError)
      throw EmulatorException(("\033[31mType Error\033[0m"));
   std::string value = this->_getValue(str);

   const IOperand* a = Factory::createOperand(type, value);
   const IOperand* b = this->_vm->top();
   if (!(*a == *b))
      throw EmulatorException(("\033[31mAssert Error ==> given value different from the last value on the stack\033[0m"));
}

void 				  Emulator::_ChangeColor() {

   if (this->_rainbow)
   {
      if (this->_colorBegin == "\033[37m")
         this->_colorBegin = "\033[31m";
      else
         this->_colorBegin = "\033[" + std::to_string(this->_b++) + "m";
   }
}
