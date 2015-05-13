/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Factory.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-kadh <ael-kadh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/08 18:10:17 by ael-kadh          #+#    #+#             */
/*   Updated: 2015/05/08 18:19:04 by ael-kadh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FACTORY_HPP
# define FACTORY_HPP

#include "TOperand.tpp"
#include "VmStack.tpp"

class Factory
{
private:
	VmStack<const IOperand*> *_vm;

	IOperand const * createInt8( std::string const & value ) const;
	IOperand const * createInt16( std::string const & value ) const;
	IOperand const * createInt32( std::string const & value ) const;
	IOperand const * createFloat( std::string const & value ) const;
	IOperand const * createDouble( std::string const & value ) const;

	void 				  _Push(std::string str) const;
	void 				  _Assert(std::string str) const;
	void 				  _Dump() const;
	void 				  _Add() const;
	void 				  _Sub() const;
	void 				  _Mul() const;
	void 				  _Mod() const;
	void 				  _Print() const;

	eOperandType     _getType(std::string val) const;
	std::string      _getValue(std::string val) const;

public:
	Factory();
	~Factory();

	IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	void				  Execute(t_StrPair ins) const;
	void 				  Show() const;
};

#endif
