/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parsing.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sal-zuba <sal-zuba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 12:21:02 by sal-zuba          #+#    #+#             */
/*   Updated: 2024/06/17 12:15:44 by sal-zuba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/Lib.hpp"

int PortChecker(std::string Port)
{
	int p = 0;

	for (unsigned int i = 0;i < Port.length();i++)
	{
		if (!isdigit(Port[i]))
		{
			std::cerr << RED << "Please only enter digits as the Port!" << DEFAULT << std::endl;
			return 1;
		}
	}
	p = atoi(Port.c_str());
	if (p <= 6670 && p >= 6660)
		return 0;
	std::cerr << RED << "Please enter a valid Port!" << DEFAULT << std::endl;
	return 1;
}