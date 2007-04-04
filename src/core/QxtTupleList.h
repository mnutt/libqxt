/****************************************************************************
**
** Copyright (C) Qxt Foundation. Some rights reserved.
**
** This file is part of the QxtCore module of the Qt eXTension library
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License as published by the Free Software Foundation; either
** version 2.1 of the License, or any later version.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** There is aditional information in the LICENSE file of libqxt.
** If you did not receive a copy of the file try to download it or
** contact the libqxt Management
** 
** <http://libqxt.sourceforge.net>  <aep@exys.org>
**
****************************************************************************/
QList<int> find( qxNull(T,args)[] )
	{
	QList<int> found;

	bool hit;			
	for(int i=0;i<list.count();i++)
		{
		hit=true;

		for (int h=0;h<count(args);h++)
 			if (!(args[h].isNull() or (list[i].[h]==args[h]))
				{ hit = false; break;}

		if (hit) found.append(i);
		}

  	return found;
  	}







