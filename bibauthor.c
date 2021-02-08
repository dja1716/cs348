static char sqla_program_id[292] = 
{
 172,0,65,69,65,85,65,73,106,66,54,52,71,97,71,107,48,49,49,49,
 49,32,50,32,32,32,32,32,32,32,32,32,8,0,72,68,85,77,32,32,
 32,32,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,8,0,66,73,66,65,85,84,72,79,0,0,0,0,0,0,0,0,
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


#line 1 "bibauthor.sqc"
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


#line 6 "bibauthor.sqc"



/*
EXEC SQL BEGIN DECLARE SECTION;
*/

#line 8 "bibauthor.sqc"

	char db[6] = "cs348";
	char aName[10], title[25], type[12], publisher[10], bName[10];
	sqlint32 aid, pubid, year, volume, number;
	sqlint32 count, appearsIn, startPage, endPage;
	

/*
EXEC SQL END DECLARE SECTION;
*/

#line 14 "bibauthor.sqc"



void NameByAscending() {

    
/*
EXEC SQL DECLARE temp CURSOR FOR
    SELECT a.name
    FROM author a, wrote w
    WHERE w.publication = :pubid
    AND w.author = a.aid
    ORDER BY a.name asc;
*/

#line 24 "bibauthor.sqc"


}


int main(int argc, char *argv[]) {

	if (argc!=2) {
      printf("Usage: bibauthor <author name>\n");
      exit(1);
   };


	
	
/*
EXEC SQL WHENEVER SQLERROR GO TO error;
*/

#line 38 "bibauthor.sqc"

	
/*
EXEC SQL CONNECT TO :db;
*/

{
#line 39 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 39 "bibauthor.sqc"
  sqlaaloc(2,1,1,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 39 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 6;
#line 39 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)db;
#line 39 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 39 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 39 "bibauthor.sqc"
  sqlacall((unsigned short)29,4,2,0,0L);
#line 39 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 39 "bibauthor.sqc"
  sqlastop(0L);
}

#line 39 "bibauthor.sqc"



	strcpy(aName, argv[1]);

	
/*
EXEC SQL DECLARE report CURSOR FOR
		WITH
		commonInfo(pubid, title, name) as (
			SELECT w.publication, p.title, a.name
			FROM wrote w, author a, publication p
			WHERE a.name = :aName
			AND a.aid = w.author
			AND w.publication = p.pubid
		),
		MyBook(pubid, title, type, year, name) as (
			select ci.pubid, ci.title, 'BOOK' as type, b.year, a.name
			from commonInfo ci, book b, author a
			where ci.pubid = b.pubid
			and a.name <= all (
				select aut.name 
				from wrote w, publication p, author aut
				where aut.aid = w.author
				and p.pubid = w.publication
			)
		),
		MyArticleYear(pubid, year) as (
			select a.pubid, pr.year
			from proceedings pr, commonInfo ci, article a
			where ci.pubid = a.pubid
			and a.appears_in = pr.pubid
			UNION
			select a.pubid, j.year
			from journal j, commonInfo ci, article a
			where ci.pubid = a.pubid
			and a.appears_in = j.pubid
		),
		MyJournal(pubid, title, type, year, name) as (
			select ci.pubid, ci.title, 'JOURNAL' as type, j.year, '' as name
			from commonInfo ci,  journal j, author a
			where ci.pubid = j.pubid
		),
		MyProceedings(pubid, title, type, year, name) as (
			select ci.pubid, ci.title, 'PROCEEDINGS' as type, pr.year, '' as name
			from commonInfo ci,  proceedings pr, author a
			where ci.pubid = pr.pubid
		),
		MyArticle(pubid, title, type, year, name) as (
			select ci.pubid, ci.title, 'ARTICLE' as type, ma.year, a.name
			from commonInfo ci, article b, MyArticleYear ma, author a
			where ci.pubid = b.pubid
			and ma.pubid = b.pubid
			and a.name <= all (
				select aut.name 
				from wrote w, publication p, author aut
				where aut.aid = w.author
				and p.pubid = w.publication
			)
		)
		SELECT pubid, title, type, year, name
		FROM MyBook
		UNION
		SELECT pubid, title, type, year, name
		FROM MyArticle
		UNION
		SELECT pubid, title, type, year, name
		FROM MyJournal
		UNION
		SELECT pubid, title, type, year, name
		FROM MyProceedings
		ORDER BY year desc, name asc;
*/

#line 108 "bibauthor.sqc"

		

	
/*
EXEC SQL OPEN report;
*/

{
#line 111 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 111 "bibauthor.sqc"
  sqlaaloc(2,1,2,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 111 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 111 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 111 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 111 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 111 "bibauthor.sqc"
  sqlacall((unsigned short)26,2,2,0,0L);
#line 111 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 111 "bibauthor.sqc"
  sqlastop(0L);
}

#line 111 "bibauthor.sqc"

	
/*
EXEC SQL WHENEVER NOT FOUND GO TO end;
*/

#line 112 "bibauthor.sqc"


	for(;;) {
		
/*
EXEC SQL FETCH report INTO :pubid, :title, :type, :year, :bName;
*/

{
#line 115 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 115 "bibauthor.sqc"
  sqlaaloc(3,5,3,0L);
    {
      struct sqla_setdata_list sql_setdlist[5];
#line 115 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 115 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 115 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 115 "bibauthor.sqc"
      sql_setdlist[1].sqltype = 460; sql_setdlist[1].sqllen = 25;
#line 115 "bibauthor.sqc"
      sql_setdlist[1].sqldata = (void*)title;
#line 115 "bibauthor.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 115 "bibauthor.sqc"
      sql_setdlist[2].sqltype = 460; sql_setdlist[2].sqllen = 12;
#line 115 "bibauthor.sqc"
      sql_setdlist[2].sqldata = (void*)type;
#line 115 "bibauthor.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 115 "bibauthor.sqc"
      sql_setdlist[3].sqltype = 496; sql_setdlist[3].sqllen = 4;
#line 115 "bibauthor.sqc"
      sql_setdlist[3].sqldata = (void*)&year;
#line 115 "bibauthor.sqc"
      sql_setdlist[3].sqlind = 0L;
#line 115 "bibauthor.sqc"
      sql_setdlist[4].sqltype = 460; sql_setdlist[4].sqllen = 10;
#line 115 "bibauthor.sqc"
      sql_setdlist[4].sqldata = (void*)bName;
#line 115 "bibauthor.sqc"
      sql_setdlist[4].sqlind = 0L;
#line 115 "bibauthor.sqc"
      sqlasetdata(3,0,5,sql_setdlist,0L,0L);
    }
#line 115 "bibauthor.sqc"
  sqlacall((unsigned short)25,2,0,3,0L);
#line 115 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 115 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 115 "bibauthor.sqc"
  sqlastop(0L);
}

#line 115 "bibauthor.sqc"

		printf("Pubid: %d\n",pubid);
		printf("Type: %s\n", type);
		printf("Title: %s\n", title);
		if(strcmp(type, "BOOK") == 0) {
			
/*
EXEC SQL select b.publisher INTO :publisher
			from book b
			where b.pubid = :pubid;
*/

{
#line 122 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 122 "bibauthor.sqc"
  sqlaaloc(2,1,4,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 122 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 122 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 122 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 122 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 122 "bibauthor.sqc"
  sqlaaloc(3,1,5,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 122 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 122 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)publisher;
#line 122 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 122 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 122 "bibauthor.sqc"
  sqlacall((unsigned short)24,3,2,3,0L);
#line 122 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 122 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 122 "bibauthor.sqc"
  sqlastop(0L);
}

#line 122 "bibauthor.sqc"


			
/*
EXEC SQL select count(author) INTO :count
			from wrote
			where publication = :pubid;
*/

{
#line 126 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 126 "bibauthor.sqc"
  sqlaaloc(2,1,6,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 126 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 126 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 126 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 126 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 126 "bibauthor.sqc"
  sqlaaloc(3,1,7,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 126 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 126 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&count;
#line 126 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 126 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 126 "bibauthor.sqc"
  sqlacall((unsigned short)24,4,2,3,0L);
#line 126 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 126 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 126 "bibauthor.sqc"
  sqlastop(0L);
}

#line 126 "bibauthor.sqc"


			NameByAscending();


			
			printf("Authors:");
			
			
/*
EXEC SQL OPEN temp;
*/

{
#line 134 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 134 "bibauthor.sqc"
  sqlaaloc(2,1,8,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 134 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 134 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 134 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 134 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 134 "bibauthor.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 134 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 134 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 134 "bibauthor.sqc"
  sqlastop(0L);
}

#line 134 "bibauthor.sqc"

			
/*
EXEC SQL FETCH temp INTO :aName;
*/

{
#line 135 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 135 "bibauthor.sqc"
  sqlaaloc(3,1,9,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 135 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 135 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 135 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 135 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 135 "bibauthor.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 135 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 135 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 135 "bibauthor.sqc"
  sqlastop(0L);
}

#line 135 "bibauthor.sqc"

			if(count > 0) {
				printf(" %s", aName);
			}
			
			for(int i = 0; i < count - 1; i++) {
				
/*
EXEC SQL FETCH temp INTO :aName;
*/

{
#line 141 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 141 "bibauthor.sqc"
  sqlaaloc(3,1,10,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 141 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 141 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 141 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 141 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 141 "bibauthor.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 141 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 141 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 141 "bibauthor.sqc"
  sqlastop(0L);
}

#line 141 "bibauthor.sqc"

				printf(", %s", aName);
			}
			
			printf("\n");
			
/*
EXEC SQL CLOSE temp;
*/

{
#line 146 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 146 "bibauthor.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 146 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 146 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 146 "bibauthor.sqc"
  sqlastop(0L);
}

#line 146 "bibauthor.sqc"

			

			printf("Publisher: %s\n", publisher);
			printf("Year: %d\n", year);
		}
		if (strcmp(type, "ARTICLE") == 0) {
			
/*
EXEC SQL select a.appears_in, a.startpage, a.endpage INTO :appearsIn, :startPage, :endPage
			from article a
			where a.pubid = :pubid;
*/

{
#line 155 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 155 "bibauthor.sqc"
  sqlaaloc(2,1,11,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 155 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 155 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 155 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 155 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 155 "bibauthor.sqc"
  sqlaaloc(3,3,12,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 155 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 155 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&appearsIn;
#line 155 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 155 "bibauthor.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 155 "bibauthor.sqc"
      sql_setdlist[1].sqldata = (void*)&startPage;
#line 155 "bibauthor.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 155 "bibauthor.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 155 "bibauthor.sqc"
      sql_setdlist[2].sqldata = (void*)&endPage;
#line 155 "bibauthor.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 155 "bibauthor.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 155 "bibauthor.sqc"
  sqlacall((unsigned short)24,5,2,3,0L);
#line 155 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 155 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 155 "bibauthor.sqc"
  sqlastop(0L);
}

#line 155 "bibauthor.sqc"


			
/*
EXEC SQL select count(author) INTO :count
			from wrote
			where publication = :pubid;
*/

{
#line 159 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 159 "bibauthor.sqc"
  sqlaaloc(2,1,13,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 159 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 159 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 159 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 159 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 159 "bibauthor.sqc"
  sqlaaloc(3,1,14,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 159 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 159 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&count;
#line 159 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 159 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 159 "bibauthor.sqc"
  sqlacall((unsigned short)24,6,2,3,0L);
#line 159 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 159 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 159 "bibauthor.sqc"
  sqlastop(0L);
}

#line 159 "bibauthor.sqc"


			NameByAscending();

			printf("Authors:");

			
/*
EXEC SQL OPEN temp;
*/

{
#line 165 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 165 "bibauthor.sqc"
  sqlaaloc(2,1,15,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 165 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 165 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 165 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 165 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 165 "bibauthor.sqc"
  sqlacall((unsigned short)26,1,2,0,0L);
#line 165 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 165 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 165 "bibauthor.sqc"
  sqlastop(0L);
}

#line 165 "bibauthor.sqc"

			
/*
EXEC SQL FETCH temp INTO :aName;
*/

{
#line 166 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 166 "bibauthor.sqc"
  sqlaaloc(3,1,16,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 166 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 166 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 166 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 166 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 166 "bibauthor.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 166 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 166 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 166 "bibauthor.sqc"
  sqlastop(0L);
}

#line 166 "bibauthor.sqc"

			if(count > 0) {
				printf(" %s", aName);
			}
			
			for(int i = 0; i < count - 1; i++) {
				
/*
EXEC SQL FETCH temp INTO :aName;
*/

{
#line 172 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 172 "bibauthor.sqc"
  sqlaaloc(3,1,17,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 172 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 460; sql_setdlist[0].sqllen = 10;
#line 172 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)aName;
#line 172 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 172 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 172 "bibauthor.sqc"
  sqlacall((unsigned short)25,1,0,3,0L);
#line 172 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 172 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 172 "bibauthor.sqc"
  sqlastop(0L);
}

#line 172 "bibauthor.sqc"

				printf(", %s", aName);
			}
			
			printf("\n");
			
/*
EXEC SQL CLOSE temp;
*/

{
#line 177 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 177 "bibauthor.sqc"
  sqlacall((unsigned short)20,1,0,0,0L);
#line 177 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 177 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 177 "bibauthor.sqc"
  sqlastop(0L);
}

#line 177 "bibauthor.sqc"


			printf("In: %d\n", appearsIn);
			printf("pages: %d--%d\n", startPage, endPage);
			


		}
		if (strcmp(type, "JOURNAL") == 0) {
			
/*
EXEC SQL select j.volume, j.number, j.year INTO :volume, :number, :year
			from journal j
			where j.pubid = :pubid;
*/

{
#line 188 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 188 "bibauthor.sqc"
  sqlaaloc(2,1,18,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 188 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 188 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 188 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 188 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 188 "bibauthor.sqc"
  sqlaaloc(3,3,19,0L);
    {
      struct sqla_setdata_list sql_setdlist[3];
#line 188 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 188 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&volume;
#line 188 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 188 "bibauthor.sqc"
      sql_setdlist[1].sqltype = 496; sql_setdlist[1].sqllen = 4;
#line 188 "bibauthor.sqc"
      sql_setdlist[1].sqldata = (void*)&number;
#line 188 "bibauthor.sqc"
      sql_setdlist[1].sqlind = 0L;
#line 188 "bibauthor.sqc"
      sql_setdlist[2].sqltype = 496; sql_setdlist[2].sqllen = 4;
#line 188 "bibauthor.sqc"
      sql_setdlist[2].sqldata = (void*)&year;
#line 188 "bibauthor.sqc"
      sql_setdlist[2].sqlind = 0L;
#line 188 "bibauthor.sqc"
      sqlasetdata(3,0,3,sql_setdlist,0L,0L);
    }
#line 188 "bibauthor.sqc"
  sqlacall((unsigned short)24,7,2,3,0L);
#line 188 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 188 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 188 "bibauthor.sqc"
  sqlastop(0L);
}

#line 188 "bibauthor.sqc"


			printf("Volume: %d\n", volume);
			printf("Number: %d\n", number);
			printf("Yeaer: %d\n", year);
		}
		if (strcmp(type, "PROCEEDINGS") == 0) {
			
/*
EXEC SQL select p.year INTO :year
			from proceedings p
			where p.pubid = :pubid;
*/

{
#line 197 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 197 "bibauthor.sqc"
  sqlaaloc(2,1,20,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 197 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 197 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&pubid;
#line 197 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "bibauthor.sqc"
      sqlasetdata(2,0,1,sql_setdlist,0L,0L);
    }
#line 197 "bibauthor.sqc"
  sqlaaloc(3,1,21,0L);
    {
      struct sqla_setdata_list sql_setdlist[1];
#line 197 "bibauthor.sqc"
      sql_setdlist[0].sqltype = 496; sql_setdlist[0].sqllen = 4;
#line 197 "bibauthor.sqc"
      sql_setdlist[0].sqldata = (void*)&year;
#line 197 "bibauthor.sqc"
      sql_setdlist[0].sqlind = 0L;
#line 197 "bibauthor.sqc"
      sqlasetdata(3,0,1,sql_setdlist,0L,0L);
    }
#line 197 "bibauthor.sqc"
  sqlacall((unsigned short)24,8,2,3,0L);
#line 197 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 197 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 197 "bibauthor.sqc"
  sqlastop(0L);
}

#line 197 "bibauthor.sqc"


			printf("Year: %d\n", year);
		}



	};

end:
	
/*
EXEC SQL CLOSE report;
*/

{
#line 207 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 207 "bibauthor.sqc"
  sqlacall((unsigned short)20,2,0,0,0L);
#line 207 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 207 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 207 "bibauthor.sqc"
  sqlastop(0L);
}

#line 207 "bibauthor.sqc"

	
/*
EXEC SQL COMMIT;
*/

{
#line 208 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 208 "bibauthor.sqc"
  sqlacall((unsigned short)21,0,0,0,0L);
#line 208 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 208 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 208 "bibauthor.sqc"
  sqlastop(0L);
}

#line 208 "bibauthor.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 209 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 209 "bibauthor.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 209 "bibauthor.sqc"
  if (sqlca.sqlcode < 0)
  {
    sqlastop(0L);
    goto error;
  }
#line 209 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 209 "bibauthor.sqc"
  sqlastop(0L);
}

#line 209 "bibauthor.sqc"

	exit(0);


error:
	check_error("Error occurred", &sqlca);
	
/*
EXEC SQL WHENEVER SQLERROR CONTINUE;
*/

#line 215 "bibauthor.sqc"


	
/*
EXEC SQL ROLLBACK;
*/

{
#line 217 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 217 "bibauthor.sqc"
  sqlacall((unsigned short)28,0,0,0,0L);
#line 217 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 217 "bibauthor.sqc"
  sqlastop(0L);
}

#line 217 "bibauthor.sqc"

	
/*
EXEC SQL CONNECT reset;
*/

{
#line 218 "bibauthor.sqc"
  sqlastrt(sqla_program_id, &sqla_rtinfo, &sqlca);
#line 218 "bibauthor.sqc"
  sqlacall((unsigned short)29,3,0,0,0L);
#line 218 "bibauthor.sqc"
  if (sqlca.sqlcode == 100)
  {
    sqlastop(0L);
    goto end;
  }
#line 218 "bibauthor.sqc"
  sqlastop(0L);
}

#line 218 "bibauthor.sqc"

	exit(1);
}
