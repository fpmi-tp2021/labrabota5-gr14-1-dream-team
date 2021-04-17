#pragma warning(disable : 4996)

#include "sqlite3.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "../include/ISql.h"

const char* LOGIN = "admin";
const char* PASSWORD = "admin";

const char* NAME = "tourism.db";

const char* ORDERS = "orders";
const char* ROUTES = "routes";
const char* BUSES = "buses";
const char* CREW = "crew";
const char* ORDER_STATUS = "order_status";

const char* queryAdd = "INSERT INTO \"main\".\"orders\" (\"ticket_cost\", \"route_id\", \"bus_id\", \"passengers\", \"order_status_id\", \"start_date\", \"finish_date\") VALUES(22, 6, 4, 23, 4, '2021-04-18', '2021-04-19');";
const char* query1 = "select orders.bus_id,buses.name, routes.name, orders.start_date, orders.finish_date from orders, routes, buses WHERE orders.route_id = routes.id AND orders.bus_id = buses.id AND orders.bus_id = 4 and order_status_id = 2 GROUP BY orders.start_date HAVING orders.finish_date < '2021.02.20'";
const char* query2 = "select count(orders.bus_id), (orders.passengers * count(orders.bus_id)), (orders.passengers* orders.ticket_cost) from orders where orders.bus_id = 4";
const char* query3 = "select buses.name, crew.last_name, maxt from buses inner join(select orders.bus_id as bid, max(orders.ticket_cost) as maxt from orders) on bid = buses.id inner join crew on crew.bus_id = buses.id";
const char* query4 = "select bid, rn, SUM(orders.passengers) FROM (SELECT max(buses.run) as rn, buses.id as bid FROM buses ) inner join orders on orders.bus_id = bid";
const char* queryN3 = " ";
const char* queryN4 = " ";
const char* queryN5 = "insert into salary select orders.id, orders.bus_id, crew.last_name, orders.ticket_cost, orders.passengers, printf(\"%.2f\", (orders.ticket_cost* orders.passengers * 0.2 / 3)) as route_salary from orders, crew where orders.start_date >= '2021-04-18' and orders.finish_date <= '2021-04-22' and crew.bus_id = orders.bus_id";
const char* queryN6 = "select orders.bus_id, crew.last_name,orders.ticket_cost, orders.passengers, (orders.ticket_cost* orders.passengers * 0.2 / 3) as salary from orders, crew where orders.finish_date = '2021-02-15' and crew.bus_id = orders.bus_id";

int main()
{
    int rc;
    sqlite3* database;
    char* table1 = "salary";
    char str[220];

    char l[20];
    char p[20];

    printf("Enter login and password.\nLogin: ");
    scanf("%s", &l);
    printf("Password: ");
    scanf("%s", &p);
    
    if (strcmp(l, LOGIN) || strcmp(p, PASSWORD)) {
        printf("Login is not correct!");
        return;
    }
    printf("\nWelcome!\n\n");

    OpenDb(NAME, &database);

    int answer;

    while (1) {
        printf("List of queries: \n\
0) Exit\n\
1) for the specified bus - a list of flights performed for the specified period\n\
2) by the specified bus - the total number of trips, the number of transported passengers and money received\n\
3) on the most expensive route - information about buses, crews and ticket prices\n\
4) by bus with the highest total mileage - information on the number of passengers transported and the mileage\n\
5) for the specified period determines the amount of money accrued to each crew for service excursions\n\
6) on the specified date displays information about the quantity money credited to the specified crew\n\
7) %s\n\
8) %s\n\
9) %s\n\
10) %s\n\
11) %s\n\
12) Modify\n\
Enter your choice: ", ORDERS, ROUTES, BUSES, CREW, ORDER_STATUS);
        
        scanf("%d", &answer);

        if (answer == 0) {
            printf("\nBye!\n");
            break;
        }
        if(answer != 12)
            printf("\nResult:\n");

        switch (answer)
        {
        case 1:
            Execute(query1, database);
            break;
        case 2:
            Execute(query2, database);
            break;
        case 3:
            Execute(query3, database);
            break;
        case 4:
            Execute(query4, database);
            break;
        case 5:
            Execute(queryN5, database);
            break;
        case 6:
            Execute(queryN6, database);
            break;
        case 7:
            Display(database, ORDERS);
            break;
        case 8:
            Display(database, ROUTES);
            break;
        case 9:
            Display(database, BUSES);
            break;
        case 10:
            Display(database, CREW);
            break;
        case 11:
            Display(database, ORDER_STATUS);
            break;
        case 12:
            printf("\nEnter sql query: ");
            char modify[220];
            gets(modify);
            fgets(modify, 220, stdin);
            Execute(modify, database);
            printf("\n");
            break;
        default:
            printf("Incorrect input! try again!\n\n");
            break;
        }
    }

    sqlite3_close(database);

    return 0;
}
