/*
  Copyright (C) 2002 Mihai Vasilian

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the
  Free Software Foundation; either version 2 of the License, or (at your
  option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program. If not, see http://www.gnu.org/licenses/.

  contact: grayasm@gmail.com

*/


#ifndef __conducerea_focului_h__
#define __conducerea_focului_h__



#include "transport_de_foc.h"
#include "pregatire_completa.h"


class  conducerea_focului
{

public :
    conducerea_focului();
    ~conducerea_focului();

    void conducerea_focului_control();

private:
    void conducerea_focului_pregatire_completa();
    void conducerea_focului_transport_de_foc();

private:
    pregatire_completa  m_pregatire_completa;
    transport_de_foc    m_transport_de_foc;
};


#endif//__conducerea_focului_h__
