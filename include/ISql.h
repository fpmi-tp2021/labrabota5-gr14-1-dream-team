#pragma once
#include "sqlite3.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

void CreateTable(sqlite3* db, char* tableName, char* fields);
void OpenDb(char* name, sqlite3* db);
static int callback(void* NotUsed, int argc, char** argv, char** azColName);
void Execute(char* sql, sqlite3* db);
void Display(sqlite3* db, char* tableName);