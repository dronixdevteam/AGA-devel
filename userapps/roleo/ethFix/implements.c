/*
 *
 * AUTHOR:   Stefano Viola (aka) Esteban Sannin
 * CONTACT:  stefanoviola[at]sannioglug[dot]org
 * HOME:     http://esteban.homelinux.org   
 *
 *      Licenze GLPv3
 *      This program is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU General Public License
 *      as published by the Free Software Foundation; either version
 *      3 of the License, or (at your option) any later version.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "include/implements.h"
#include "../shared/gpio_api.h"

#define NETWORK "/proc/net/dev"
#define ETH_LED_GPIO 6
#define INTERVAL 100	//100 ms

long long int get_byte_received(char *interface){
        FILE *fp;
        char line[1024];
        char *tok;
        int i,j; 
        int control_token = 0;
        int count_string_token = 0;
        char *token_true;
        int token2; 
        long long int number_byte;
        char *final_down;
        
        int one_token = 0;
        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        tok = strtok(line," ");
                        count_string_token = 0; 
                   if (one_token == 0){     
                        while(tok != NULL){
                                if(token2){
                                        token2 = 0;
                                        number_byte = atoll(tok);
                                }
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);           //search the interface in the string
                                        final_down = strchr(tok,':');                 //cut the byte download oh the interface
                                        int equal_string = strcmp(final_down,":");
                                        if (equal_string == 0){
                                        token2 = 1;
                                        }else{
                                        char byte_down_temp[strlen(final_down)];      //array for temporary byte download
                                        strcpy(byte_down_temp, final_down);           //copy the string in to array byte_down
                                        i=1;                                          //for control
                                        j = 0;                                        //for control
                                        int dim = strlen(final_down);                 //computing the dimension for the array
                                        char byte_download[dim];
                                        for(j = 0; j<(dim-1); j++){                   //get byte clean
                                                one_token = 1;
                                                byte_download[j] = byte_down_temp[i];
                                                i++;
                                        }
                                        number_byte = atoll(byte_download);
                                        }
                                        }else{
                                                if(control_token !=1 ){
                                                number_byte = -1;
                                                }
                                        }
                tok = strtok(NULL, " ");
                }
                   }
                        }
                
                fclose(fp);
        } else {
                printf("Error!!\n\n");
        }
        return number_byte;
}     


long long int get_byte_trasmitted(char *interface){
        int loop = 9;
        FILE *fp;
        char line[1024];
        int iRet = 0;
        char *tok;
        int i,j; 
        int control_token = 0;
        int count_string_token = 0;
        char *token_true; 
        long long int number_byte;
        char *final_down;
        int token2 = 0;
        
        fp = fopen(NETWORK, "r");
        if (fp != NULL) {
                while (fgets(line, sizeof(line), fp)) {
                        tok = strtok(line," ");
                        count_string_token = 0;      
                        while(tok != NULL){
                                count_string_token++;
                                if(strstr(tok,interface)){
                                        control_token=1;
                                        token_true = strstr(tok,interface);             //search the interface in the string
                                        final_down = strchr(tok,':');                 //cut the byte download oh the interface
                                        int equal_string = strcmp(final_down,":");
                                        if(equal_string == 0){
                                                token2 = 1;
                                        }
                                }
                                if (token2 == 1){
                                        loop++;
                                        token2 = 0;
                                }
                                if (count_string_token == loop && control_token == 1){
                                        control_token = 0;
                                        number_byte = atoll(tok);
                                }
                tok = strtok(NULL, " ");
                }
                        }
                
                fclose(fp);
        } else {
                printf("Error!!\n\n");
        }
      return number_byte; 
}

int command(char *command){
	FILE *fp;
	char line[1024];
	int status = 0;
	fp = popen(command, "r");
	if (fp != NULL) {
		while (fgets(line, sizeof(line), fp)) {
			printf("%s", line);
		}
		pclose(fp);
		status = 0;
	} else {
		status = -1;
	}
	return status;
}
void blink_led(){
	//int i;
	//for (i = 0; i<10; i++){
	sysSetGpioBit(ETH_LED_GPIO, 0);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 1);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 0);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 1);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 0);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 1);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 0);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 1);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 0);
	usleep(INTERVAL * 1000);
	sysSetGpioBit(ETH_LED_GPIO, 1);
	usleep(INTERVAL * 1000);
	//}
	sysSetGpioBit(ETH_LED_GPIO, 0);
	
}


/* Function plug_state:
 * Control the plug state of the ethernet cable
 *
 * Function plug_state() return status:
 * return  1 ---> if the cable eth is plugged
 * return -1 ---> if the cable eth is3 not plugged
 * return -2 ---> if don't read /var/lan/ethX/linkstate file
 */
int plug_state(){

#define ETH0 "/var/lan/eth0/linkstate"
#define ETH1 "/var/lan/eth1/linkstate"	

	FILE *feth1, *feth0;
	char line[1024], line2[1024];
	int status_eth0 = 0;
	int status_eth1 = 0;
	int status_plug = 0;
	feth0 = fopen(ETH0, "r");
	feth1 = fopen(ETH1, "r");

	if(feth0 != NULL) {
		while (fgets(line, sizeof(line), feth0)){
			int compare = strcmp(line,"1");
			//printf("%s",line);
			if(compare != -1){
				status_eth0 = 1;
			}else{
				status_eth0 = -1;
			}
		}
		fclose(feth0);
	} else {
		status_plug = -2;
	}
	
	if(feth1 != NULL) {
		while (fgets(line2, sizeof(line2), feth1)){
			int compare = strcmp(line2,"1");
			//printf("%s",line2);
			if(compare != -1){
				status_eth1 = 1;
			}else{
				status_eth1 = -1;
			}
		}
		fclose(feth1);
	} else {
		status_plug = -2;
	}

	if(status_eth0 == 1 || status_eth1 == 1)
		status_plug = 1;
	else
		status_plug = -1;

	return status_plug;
	
}


int data_byte_rate(int rate){

	rate = rate*2;

                        for(;;){
                                long long int first = get_byte_received("eth1");
                                long long int first_up = get_byte_trasmitted("eth1");
				
				long long int first2 = get_byte_received("eth0");
				long long int first_up2 = get_byte_trasmitted("eth0");

				sleep(2);
                                
				long long int second2 = get_byte_received("eth0");
				long long int second_up2 = get_byte_trasmitted("eth0");
				
				long long int second = get_byte_received("eth1");
				long long int second_up = get_byte_trasmitted("eth1");
			
				// Calculate the data rate

				long long int difference = second - first;
				long long int difference2 = second2 - first2;
				
				long long int difference_up = second_up - first_up;
				long long int difference_up2 = second_up2 - first_up2;
			
					
				//printf("difference: %lld  difference2: %lld \n",difference,difference2);
				//printf("difference up: %lld difference up2: %lld \n",difference_up, difference_up2);
				//printf("state: %d\n",plug_state());

				if(plug_state() == 1){
					sysSetGpioBit(ETH_LED_GPIO, 0);
					if (difference != 0 || difference2 != 0){
						if (difference > rate || difference2 > rate){
							blink_led();
						}else{
							sysSetGpioBit(ETH_LED_GPIO, 0);
						}
						
					}
					if (difference_up != 0 || difference_up2 !=0){
						if (difference_up > rate || difference_up2 > rate){
							blink_led();
						}else{
							sysSetGpioBit(ETH_LED_GPIO, 0);
						}
					}
				}else{
					sysSetGpioBit(ETH_LED_GPIO, 1);
				}
				

	}
}
