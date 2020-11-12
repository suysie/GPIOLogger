#include "PJ_RPI.h"
#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
	MYSQL *conn;
	int value;
	int lastvalue = 0;
	int value2;
	int lastvalue2 = 0;

	if ((conn = mysql_init(NULL)) == NULL)                                                             
  	{                                                                                                  
		fprintf(stderr, "Could not init DB\n");                                                 
		return EXIT_FAILURE;                                                                             
  	}

	if (mysql_real_connect(conn, "localhost", "pi", "????", "gpio", 0, NULL, 0) == NULL)             
	{                                                                                                  
		fprintf(stderr, "DB Connection Error\n");                                                        
		return EXIT_FAILURE;                                                                             
	}         

	if(map_peripheral(&gpio) == -1) 
	{
       	 	printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
        	return -1;
    	}

	while(1)
	{
		// Toggle 17 (blink a led!)
		if(GPIO_READ(26)){
			value = 1;
			//printf("hoog\n");
		}
		else{
			value = 0;
			//printf("laag\n");
		}

		if(GPIO_READ(19)){
			value2 = 1;
			//printf("hoog\n");
		}
		else{
			value2 = 0;
			//printf("laag\n");
		}
		if(value == lastvalue){}
		else{
			lastvalue = value;
			if(value == 1){
				if (mysql_query(conn, "INSERT INTO  gpio (pin, value) VALUES ('pin 26',1)") != 0)                   
					{                                                                                                  
						fprintf(stderr, "Query Failure\n");                                                              
						return EXIT_FAILURE;                                                                             
					}
				}
			if(value == 0){
				if (mysql_query(conn, "INSERT INTO  gpio (pin, value) VALUES ('pin 26',0)") != 0)                   
					{                                                                                                  
						fprintf(stderr, "Query Failure\n");                                                              
						return EXIT_FAILURE;                                                                             
					}
				}
			
			}
		if(value2 == lastvalue2){}
		else{
			lastvalue2 = value2;
			if(value2 == 1){
				if (mysql_query(conn, "INSERT INTO  gpio (pin, value) VALUES ('pin 19',1)") != 0)                   
					{                                                                                                  
						fprintf(stderr, "Query Failure\n");                                                              
						return EXIT_FAILURE;                                                                             
					}
				}
			if(value2 == 0){
				if (mysql_query(conn, "INSERT INTO  gpio (pin, value) VALUES ('pin 19',0)") != 0)                   
					{                                                                                                  
						fprintf(stderr, "Query Failure\n");                                                              
						return EXIT_FAILURE;                                                                             
					}
				}
			       
		}
		sleep(1);
	}

	return 0;	








	
}
