static char sqla_program_id[292] = 
{
 172,0,65,69,65,85,65,73,89,66,54,88,67,88,71,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,72,68,85,77,32,32,
 32,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,83,65,77,80,76,69,49,32,0,0,0,0,0,0,0,0,
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


#line 1 "sample1.sqc"
#include <stdio.h>
#include <stdlib.h>
#include "util.h"


/*
EXEC SQL INCLUDE SQLCA;
*/

/* SQL Communication Area - SQLCA - structures and constants */
#include "sqlca.h"
struct sqlca sqlca;


#line 5 "sample1.sqc"


int main(int argc, char *srgv[]) {
	char * getpass();

	
/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 10 "sample1.sqc"

		char db[6] = "cs348";
	
/*
EXEC SQL END DECLARE SECTION;
*/

#line 12 "sample1.sqc"


	printf("Sample c Program: CONNECT\n");

	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 16 "sample1.sqc"


	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 18 "sample1.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 18 "sample1.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 18 "sample1.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 18 "sample1.sqc"
      sql_setdlist[0].sqldata = (void*)db;
#line 18 "sample1.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 18 "sample1.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 18 "sample1.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 18 "sample1.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 18 "sample1.sqc"
  sqlastop(0L);
}

#line 18 "sample1.sqc"


	printf("Connected to DB2\n");

	
/*
EXEC SQL COMMIT;
*/

{
#line 22 "sample1.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 22 "sample1.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 22 "sample1.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 22 "sample1.sqc"
  sqlastop(0L);
}

#line 22 "sample1.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 23 "sample1.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 23 "sample1.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 23 "sample1.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 23 "sample1.sqc"
  sqlastop(0L);
}

#line 23 "sample1.sqc"

	exit(0);

	error:
		check_error("My error", &sqlca);
		
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 28 "sample1.sqc"


		
/*
EXEC SQL ROLLBACK;
*/

{
#line 30 "sample1.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 30 "sample1.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 30 "sample1.sqc"
  sqlastop(0L);
}

#line 30 "sample1.sqc"

		
/*
EXEC SQL CONNECT reset;
*/

{
#line 31 "sample1.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 31 "sample1.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 31 "sample1.sqc"
  sqlastop(0L);
}

#line 31 "sample1.sqc"

		exit(1);
}
