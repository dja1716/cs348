static char sqla_program_id[292] = 
{
 172,0,65,69,65,85,65,73,68,66,55,52,71,97,71,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,72,68,85,77,32,32,
 32,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,66,73,66,67,79,78,84,69,0,0,0,0,0,0,0,0,
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


#line 1 "bibcontent.sqc"
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


#line 6 "bibcontent.sqc"



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 8 "bibcontent.sqc"

	char db[6] = "cs348";
	sqlint32 mainPubid;
	sqlint32 aPubid, startPage, endPage, appearsIn, year, count;
	char type[12];
	char aName[10], title[25];
	

/*
EXEC SQL END DECLARE SECTION;
*/

#line 15 "bibcontent.sqc"



void NameByAscending() {

    
/*
EXEC SQL DECLARE temp CURSOR FOR
    SELECT a.name
    FROM author a, wrote w
    WHERE w.publication = :aPubid
    AND w.author = a.aid
    ORDER BY a.name asc;
*/

#line 25 "bibcontent.sqc"


}


int main(int argc, char *argv[]) {

	if (argc!=2) {
      printf("Usage: bibcontent <journal or proceedings pubid>\n");
      exit(1);
	};
	mainPubid = atoi(argv[1]);
	
	
/*
EXEC SQL DECLARE report CURSOR FOR
		with
		Info(pubid, type, year) as (
			SELECT j.pubid, 'JOURNAL' as type, j.year
			FROM journal j, publication p
			where j.pubid = :mainPubid
			UNION
			select pr.pubid, 'PROCEEDINS' as type, pr.year
			from proceedings pr, publication p
			where pr.pubid = :mainPubid
		),
		MyArticle(pubid, year, appearsIn, startPage, endPage, title) as (
			select a.pubid, i.year, a.appears_in, a.startpage, a.endpage, p.title
			from article a, Info i, publication p
			where a.appears_in = i.pubid
			and p.pubid = a.pubid
		)
		SELECT *
		FROM MyArticle;
*/

#line 56 "bibcontent.sqc"




		
	
	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 62 "bibcontent.sqc"

	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 63 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 63 "bibcontent.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 63 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 63 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)db;
#line 63 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 63 "bibcontent.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 63 "bibcontent.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 63 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 63 "bibcontent.sqc"
  sqlastop(0L);
}

#line 63 "bibcontent.sqc"


	
/*
EXEC SQL OPEN report;
*/

{
#line 65 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 65 "bibcontent.sqc"
  sqlaaloc(2,2,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[2];
#line 65 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 65 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)&mainPubid;
#line 65 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 65 "bibcontent.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 65 "bibcontent.sqc"
      sql_setdlist[1].sqldata = (void*)&mainPubid;
#line 65 "bibcontent.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 65 "bibcontent.sqc"
      sqlasetdata(2,0,2,sql_setdlist,0L,0L);
    }
#line 65 "bibcontent.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 65 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 65 "bibcontent.sqc"
  sqlastop(0L);
}

#line 65 "bibcontent.sqc"

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO end;
*/

#line 66 "bibcontent.sqc"


	for(;;) {
		
/*
EXEC SQL FETCH report INTO :aPubid, :year, :appearsIn, :startPage, :endPage, :title;
*/

{
#line 69 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 69 "bibcontent.sqc"
  sqlaaloc(3,6,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[6];
#line 69 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 69 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)&aPubid;
#line 69 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 69 "bibcontent.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 69 "bibcontent.sqc"
      sql_setdlist[1].sqldata = (void*)&year;
#line 69 "bibcontent.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 69 "bibcontent.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 69 "bibcontent.sqc"
      sql_setdlist[2].sqldata = (void*)&appearsIn;
#line 69 "bibcontent.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 69 "bibcontent.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 69 "bibcontent.sqc"
      sql_setdlist[3].sqldata = (void*)&startPage;
#line 69 "bibcontent.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 69 "bibcontent.sqc"
      sql_setdlist[4].sqltype = 496; sql_setdlist[4].sqllen = 4;
#line 69 "bibcontent.sqc"
      sql_setdlist[4].sqldata = (void*)&endPage;
#line 69 "bibcontent.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 69 "bibcontent.sqc"
      sql_setdlist[5].sqltype = 460; sql_setdlist[5].sqllen = 25;
#line 69 "bibcontent.sqc"
      sql_setdlist[5].sqldata = (void*)title;
#line 69 "bibcontent.sqc"
      sql_setdlist[5].sqlind = 0L;
#line 69 "bibcontent.sqc"
      sqlasetdata(3,0,6,sql_setdlist,0L,0L);
    }
#line 69 "bibcontent.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 69 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 69 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 69 "bibcontent.sqc"
  sqlastop(0L);
}

#line 69 "bibcontent.sqc"

		
/*
EXEC SQL select count(author) INTO :count
		from wrote
		where publication = :aPubid;
*/

{
#line 72 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 72 "bibcontent.sqc"
  sqlaaloc(2,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 72 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 72 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)&aPubid;
#line 72 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 72 "bibcontent.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 72 "bibcontent.sqc"
  sqlaaloc(3,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 72 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 72 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)&count;
#line 72 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 72 "bibcontent.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 72 "bibcontent.sqc"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 72 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 72 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 72 "bibcontent.sqc"
  sqlastop(0L);
}

#line 72 "bibcontent.sqc"


		


		printf("Pubid: %d\n", aPubid);
		printf("Type: ARTICLE\n");
		printf("Title: %s\n", title);
		
		NameByAscending();

		printf("Authors:");

		
/*
EXEC SQL OPEN temp;
*/

{
#line 85 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 85 "bibcontent.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 85 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 85 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)&aPubid;
#line 85 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 85 "bibcontent.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 85 "bibcontent.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 85 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 85 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 85 "bibcontent.sqc"
  sqlastop(0L);
}

#line 85 "bibcontent.sqc"

		
/*
EXEC SQL FETCH temp INTO :aName;
*/

{
#line 86 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 86 "bibcontent.sqc"
  sqlaaloc(3,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 86 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 86 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 86 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 86 "bibcontent.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 86 "bibcontent.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 86 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 86 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 86 "bibcontent.sqc"
  sqlastop(0L);
}

#line 86 "bibcontent.sqc"

		if(count > 0) {
			printf(" %s", aName);
		}
			
		for(int i = 0; i < count - 1; i++) {
			
/*
EXEC SQL FETCH temp INTO :aName;
*/

{
#line 92 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 92 "bibcontent.sqc"
  sqlaaloc(3,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 92 "bibcontent.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 92 "bibcontent.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 92 "bibcontent.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 92 "bibcontent.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 92 "bibcontent.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 92 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 92 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 92 "bibcontent.sqc"
  sqlastop(0L);
}

#line 92 "bibcontent.sqc"

			printf(", %s", aName);
		}
			
		printf("\n");
		
/*
EXEC SQL CLOSE temp;
*/

{
#line 97 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 97 "bibcontent.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 97 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 97 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 97 "bibcontent.sqc"
  sqlastop(0L);
}

#line 97 "bibcontent.sqc"


		printf("In: %d\n", appearsIn);
		printf("Pages: %d--%d\n", startPage, endPage);

	};



end:
	// need to close report cursor
	
/*
EXEC SQL CLOSE report;
*/

{
#line 108 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 108 "bibcontent.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 108 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 108 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 108 "bibcontent.sqc"
  sqlastop(0L);
}

#line 108 "bibcontent.sqc"

	
/*
EXEC SQL COMMIT;
*/

{
#line 109 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 109 "bibcontent.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 109 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 109 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 109 "bibcontent.sqc"
  sqlastop(0L);
}

#line 109 "bibcontent.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 110 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 110 "bibcontent.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 110 "bibcontent.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 110 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 110 "bibcontent.sqc"
  sqlastop(0L);
}

#line 110 "bibcontent.sqc"

	exit(0);


error:
	check_error("Error occurred", &sqlca);
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 116 "bibcontent.sqc"


	
/*
EXEC SQL ROLLBACK;
*/

{
#line 118 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 118 "bibcontent.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 118 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 118 "bibcontent.sqc"
  sqlastop(0L);
}

#line 118 "bibcontent.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 119 "bibcontent.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 119 "bibcontent.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 119 "bibcontent.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 119 "bibcontent.sqc"
  sqlastop(0L);
}

#line 119 "bibcontent.sqc"

	exit(1);
}
