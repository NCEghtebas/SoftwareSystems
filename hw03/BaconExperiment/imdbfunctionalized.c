/*
This code was written to practice using the MySQL C API, with the eventual goal of solving the Kevin Bacon "degrees of separation" problem.
This was written for the Software Systems class at Olin College, spring 2014.

We would like to thank Allen Downey (our professor), Github user dedeler (for writing code to parse IMDB list files), and zetcode.com/db/mysqlc for providing C API tutorials and examples (we have borrowed one of their examples to write the code below). 

Authors: Chloe Eghtenbas, Samantha Kumarasena
Date: 3/3/14
*/

#include <my_global.h>
#include <mysql.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
If connection is invalid, prints an error and closes the program.
Author: zetcode.com
*/

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);        
}


void print_result(MYSQL_RES *result, MYSQL *con){
  int num_fields = mysql_num_fields(result);
  MYSQL_ROW row;

  if (result == NULL) 
  {
      finish_with_error(con);
  }  
  while ((row = mysql_fetch_row(result))) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
          printf("\n"); 
  }
}


/*
Executes a MySQL query that, given a movie's title, will look up all actors involved in that movie.
*/
MYSQL_RES * get_actor(MYSQL_RES *result, MYSQL *con, int i){
  char* movie= (char *) malloc(sizeof(char)*101);
  char * query= (char *) malloc(sizeof(char)*1001);

  printf("%s\n", "Print movie title: ");
  scanf("%100s", movie);


  strcpy(query, "SELECT firstname, lastname FROM imdbrev WHERE movie REGEXP '.*");
  strcat(query, movie);
  strcat(query, ".*' LIMIT ");
  strcat(query, (char *)i);
  strtok(query, "\n");

  printf("%s\n", query);

  if (mysql_query(con, query)) {
      finish_with_error(con);
  }

  result = mysql_store_result(con);
  free(query);
  free(movie);

  return result;
}


MYSQL_RES * get_movie(MYSQL_RES *result, MYSQL *con, int i){
  char* firstname= (char *) malloc(sizeof(char)*101);
  char* lastname= (char *) malloc(sizeof(char)*101);
  char * query2= (char *) malloc(sizeof(char)*1001);

  printf("%s\n", "Print actor's first name: ");
  scanf("%100s", firstname);

  printf("%s\n", "Print actor's last name: ");
  scanf("%100s", lastname);

  strcpy(query2, "SELECT movie FROM imdb WHERE firstname = '");
  strcat(query2, firstname);
  strcat(query2, "' AND lastname= '");
  strcat(query2, lastname);
  strcat(query2, "' LIMIT ");
  strcat(query2, (char *)i);
  strtok(query2, "\n");

  printf("%s\n", query2);

  if (mysql_query(con, query2)) {
      finish_with_error(con);
  }

  result = mysql_store_result(con);
  free(query2);
  free(firstname);
  free(lastname);

  return result;
}


int get_bacon(MYSQL *con){
  MYSQL_RES *actorresult;
  MYSQL_RES * movieresult;
  int num_fields;
  MYSQL_ROW row;


  actorresult= get_actor();
  num_fields= mysql_num_fields(actorresult);
  actor = mysql_fetch_row(actorresult);

  if (actorresult == NULL) 
  {
      finish_with_error(con);
  }  
  while (actor) 
  { 
      for(int i = 0; i < num_fields; i++) 
      { 
          movieresult[i]= 
          //printf("%s ", actor[i] ? actor[i] : "NULL"); 

      } 
          printf("\n"); 
  }

}


int main(int argc, char **argv)
{      

  // Tries to make a connection. If connection fails, terminates with error.
  MYSQL *con = mysql_init(NULL);

  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  

  // Connects to MySQL database "imdb" hosted on localhost. If fails, terminates with error.
  if (mysql_real_connect(con, "localhost", "root", "[obscured]", 
          "imdb", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    


  //MYSQL_RES *result = mysql_store_result(con);
  MYSQL_RES *movieresult;
  MYSQL_RES *actorresult;
  actorresult= get_actor(actorresult,con, 10);
  //movieresult= get_movie(movieresult,con, 10);
  
  print_result(actorresult, con);
  //print_result(movieresult, con);

  mysql_free_result(movieresult);
  mysql_free_result(actorresult);
  mysql_close(con);
  
  exit(0);
  

}