static char sqla_program_id[292] = 
{
 172,0,65,69,65,85,65,73,55,65,111,67,68,88,71,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,72,68,85,77,32,32,
 32,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,83,65,77,80,76,69,50,32,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0
};

#include "sqladef.h"

static struct sqla_runtime_info sqla_rtinfo = 
{{'S','Q','L','A','R','T','I','N'}, sizeof(wchar_t), 0, {' ',' ',' ',' '}};


static const short sqlIsLiteral   = SQL_IS_LITERAL;
static const short sqlIsInputHvar = SQL_IS_INPUT_HVAR;


#line 1 "sample2.sqc"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 6 "sample2.sqc"


int main(int argc, char *argv[]) {
	int i;
	char pubidstr[10];

	
/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 12 "sample2.sqc"

		char db[6] = "cs348";
		sqlint32 pubid;
		char title[30];
	
/*
EXEC SQL END DECLARE SECTION;
*/

#line 16 "sample2.sqc"


	printf("Sample C program: SAMPLE2\n");

	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 20 "sample2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 20 "sample2.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 20 "sample2.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 20 "sample2.sqc"
      sql_setdlist[0].sqldata = (void*)db;
#line 20 "sample2.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 20 "sample2.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 20 "sample2.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 20 "sample2.sqc"
  sqlastop(0L);
}

#line 20 "sample2.sqc"


	printf("Connected to DB2\n");

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 24 "sample2.sqc"


	for (i=1; i<argc; i++) {
		strncpy(pubidstr, argv[i], 8);
		pubid = atoi(pubidstr);

		
/*
EXEC SQL WHENEVER NOT FOUND GO TO nope;
*/

#line 30 "sample2.sqc"

		
/*
EXEC SQL SELECT title INTO :title
				 FROM publication
				 WHERE pubid = :pubid;
*/

{
#line 33 "sample2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 33 "sample2.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 33 "sample2.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 33 "sample2.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 33 "sample2.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 33 "sample2.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 33 "sample2.sqc"
  sqlaaloc(3,1,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 33 "sample2.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 30;
#line 33 "sample2.sqc"
      sql_setdlist[0].sqldata = (void*)title;
#line 33 "sample2.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 33 "sample2.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 33 "sample2.sqc"
  sqlacall((unsigned short)24,1,2,3,0L);
#line 33 "sample2.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 33 "sample2.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto nope;
  }
#line 33 "sample2.sqc"
  sqlastop(0L);
}

#line 33 "sample2.sqc"


		printf("%d: %s\n",pubid,title);
		continue;
	nope:
		printf("%d: *** not found *** \n", pubid);
	};

	
/*
EXEC SQL COMMIT;
*/

{
#line 41 "sample2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 41 "sample2.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 41 "sample2.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 41 "sample2.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto nope;
  }
#line 41 "sample2.sqc"
  sqlastop(0L);
}

#line 41 "sample2.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 42 "sample2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 42 "sample2.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 42 "sample2.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 42 "sample2.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto nope;
  }
#line 42 "sample2.sqc"
  sqlastop(0L);
}

#line 42 "sample2.sqc"

	exit(0);

error:
	check_error("My error", &sqlca);
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 47 "sample2.sqc"

	
/*
EXEC SQL ROLLBACK;
*/

{
#line 48 "sample2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 48 "sample2.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 48 "sample2.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto nope;
  }
#line 48 "sample2.sqc"
  sqlastop(0L);
}

#line 48 "sample2.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 49 "sample2.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 49 "sample2.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 49 "sample2.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto nope;
  }
#line 49 "sample2.sqc"
  sqlastop(0L);
}

#line 49 "sample2.sqc"

	exit(1);
}
