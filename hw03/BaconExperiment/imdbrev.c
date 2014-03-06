/*
This code was written to practice using the MySQL C API, with the eventual goal of solving the Kevin Bacon "degrees of separation" problem.
This was written for the Software Systems class at Olin College, spring 2014.

NOTE: Compile this file as follows: gcc imdbrev.c -std=c99  `mysql_config --cflags --libs`

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

/*
Executes a MySQL query that, given a movie's title, will look up all actors involved in that movie.
*/

int main(int argc, char **argv)
{      

  // Initializing variables, including a connection object.  
  MYSQL *con = mysql_init(NULL);
  char *movie= (char *) malloc(sizeof(char)*101);
  char *query1= (char *) malloc(sizeof(char)*1001);

  // Reads in a movie title provided by the user
  printf("%s\n", "Enter a movie title: ");
  scanf("%100s", movie);

  
  // Tries to make a connection. If connection fails, terminates with error.
  if (con == NULL)
  {
      fprintf(stderr, "mysql_init() failed\n");
      exit(1);
  }  
  
  // Connects to a MySQL database. If fails, terminates with error.
  // Enter your own host, user, password, and database names.
  if (mysql_real_connect(con, "[HOST]", "[USER]", "[PASSWORD]", 
          "[DATABASE]", 0, NULL, 0) == NULL) 
  {
      finish_with_error(con);
  }    

  // Pieces together a valid SQL query, using regex to identify matching movie titles.
  // Enter your own column and table names.
  strcpy(query1, "SELECT [FIRST_NAME_COL], [LAST_NAME_COL] FROM [MOVIE_TABLE] WHERE [MOVIE_TABLE] REGEXP '.*");
  strcat(query1, movie);
  strcat(query1, ".*' LIMIT 10");
  strtok(query1, "\n");

  // If the query is unsuccessful, terminate with an error.
  if (mysql_query(con, query1)) {
      finish_with_error(con);
  }
  
  // Store the results. If they do not exist, terminate with an error.
  MYSQL_RES *result = mysql_store_result(con);
  
  if (result == NULL) {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  // Loop through the results and print each row.
  MYSQL_ROW row;
  while ((row = mysql_fetch_row(result))) { 
      for(int i = 0; i < num_fields; i++) { 
        printf("%s ", row[i] ? row[i] : "NULL"); 
      } 
      printf("\n"); 
  }
  
  // Free the variables and exit.
  mysql_free_result(result);
  mysql_close(con);
  free(movie);
  free(query1);
  exit(0);

}