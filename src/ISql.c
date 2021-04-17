#pragma warning(disable : 4996)
#include "../include/ISql.h"
#include "sqlite3.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

char* error = "";

void CreateTable(sqlite3* db, char* tableName, char* fields)
{
    int rc;

    char str[220];
    strcpy(str, "CREATE TABLE IF NOT EXISTS ");
    strcat(str, tableName);
    strcat(str, " (\"id\" INTEGER PRIMARY KEY AUTOINCREMENT, ");
    strcat(str, fields);
    strcat(str, ");");

    rc = sqlite3_exec(db, str, NULL, NULL, &error);
    if (rc)
    {
        printf("Error executing SQLite3 statement: %s \n\n", sqlite3_errmsg(db));
        sqlite3_free(error);
    }
}

void OpenDb(char* name, sqlite3* db)
{
    int rc;
    rc = sqlite3_open(name, db);
    if (rc)
    {
        printf("Error opening SQLite3 database: %s \n\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
}

static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    int i;
    for (i = 0; i < argc; i++) {
        printf("%s\n", argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

void Execute(char* sql, sqlite3* db)
{
    int rc;
    rc = sqlite3_exec(db, sql, callback, NULL, &error);
    if (rc)
    {
        printf("Error executing SQLite3 statement: %s \n\n", sqlite3_errmsg(db));
        sqlite3_free(error);
    }
}

void Display(sqlite3* db, char* tableName)
{
    int rc;

    char str[200];
    strcpy(str, "SELECT * FROM ");
    strcat(str, tableName);
    strcat(str, ";");

    char** results = NULL;
    int rows, columns;
    rc = sqlite3_get_table(db, str, &results, &rows, &columns, &error);

    if (rc)
    {
        printf("Error executing SQLite3 query: %s \n\n", sqlite3_errmsg(db));
        sqlite3_free(error);
    }
    else
    {
        for (int rowCtr = 0; rowCtr <= rows; ++rowCtr)
        {
            for (int colCtr = 0; colCtr < columns; ++colCtr)
            {
                int cellPosition = (rowCtr * columns) + colCtr;

                printf("%-16s ", results[cellPosition]);
            }

            printf("\n");

            if (0 == rowCtr)
            {
                for (int colCtr = 0; colCtr < columns; ++colCtr)
                {
                    printf("----------------");
                }
                printf("\n");
            }
        }
    }
    printf("\n");
    sqlite3_free_table(results);
}
