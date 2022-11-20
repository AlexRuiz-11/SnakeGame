//------------------------------------------------------------------------------
// Copyright (c) 2012 Vicente Benjumea, University of Malaga, Spain
// 
// This file is part of the <MISC> Library
// 
// This library is free software: you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either
// version 2.1 of the License, or (at your option) any later
// version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General
// Public License along with this library. If not, see
// <http://www.gnu.org/licenses/>.
//------------------------------------------------------------------------------
#ifndef _misc_hpp_
#define _misc_hpp_
#include <iostream>
#include <cstdlib>
#include <ctime>
#if defined __unix__ || defined __APPLE__
#include <sys/time.h>
#elif defined __WIN32__
#include <windows.h>
#include <sys/types.h>
#include <sys/timeb.h>
#endif
namespace umalcc_misc {
#if defined __unix__ || defined __APPLE__
	inline void clear() {
		system("clear");
	}
	inline void pausa() {
		system("sh -c \"read -p 'press ENTER ' KEY\"");
	}
	inline void msleep(unsigned long milliseconds) {
		struct timespec ts;
		ts.tv_sec = time_t(milliseconds/1000);              // seconds
		ts.tv_nsec = (long int)((milliseconds%1000)*1000000);   // nanoseconds
		nanosleep(&ts, NULL);
		//usleep(milliseconds*1000);                // microseconds
	}
#elif defined __WIN32__
	inline void clear() {
		system("cls");
	}
	inline void pausa() {
		system("pause");
	}
	inline void msleep(unsigned long milliseconds) {
		Sleep(milliseconds);
	}
#else
	inline void clear() {
	}
	inline void pausa() {
		std::cout << "press ENTER";
		std::cin.ignore(1000,'\n');
	}
	inline void msleep(unsigned long milliseconds) {
	}
#endif
	namespace _impl_ {
		// Inicializa el generador de numeros aleatorios
		inline unsigned ini_aleatorio(unsigned x = 0) {
			if (x == 0) {
#if defined __unix__ || defined __APPLE__
				struct timeval tv;
				gettimeofday(&tv, NULL);
				x = unsigned(tv.tv_sec ^ tv.tv_usec);
#elif defined __WIN32__NO_DEFINIDO_
				struct _timeb tv;
				_ftime(&tv);
				x = (tv.time+1) * (tv.millitm+1);
#else
				x = (std::time(0)+1) * (std::clock()+1);
#endif
			}
			std::srand(x);
			return x;
		}
		static const unsigned _init = ini_aleatorio();
	} // namespace _impl_
	// Devuelve un numero aleatorio entre 0 y max (exclusive)
	inline unsigned aleatorio(unsigned max) {
		return unsigned(double(std::rand())*max/(RAND_MAX+1.0));
	}
	// devuelve un numero entre [inf..sup] ambos inclusive
	inline unsigned aleatorio(unsigned inf, unsigned sup) {
		return inf + aleatorio(sup - inf + 1);
	}
} //namespace umalcc_misc
using namespace umalcc_misc;
#endif
//-------------------------------------------------------------------------
