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







