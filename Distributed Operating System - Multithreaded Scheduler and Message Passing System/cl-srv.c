/*
Project 4
Girish Dasarathy - 1207555332
Niranjan Krishna Ravichandran - 1207518529
*/

#include<stdio.h>
#include "msg.h"
#include<stdlib.h>
#include<math.h>
int client_port=0;

void client()
{
int num[10];//integer message array
int cl=0,sp=0,i=0,j=0,k=0;
int position=-1;
char input_message_1[4][20]={"distributdproc\0","malware_attack\0","worm_attack\0","timeshare\0"};
char input_message_2[4][20]={"program\0","lindaprogramming\0","multitasking\0","barrier_sync\0"};
char input_message_3[10]={"GetData"};
int rand_index=0;
int int_input_msg1[10];
int int_input_msg2[10];
int int_input_msg3[10];
int len;
if(client_port<99){
cl=++client_port;
while(1){
if(cl==1){
rand_index=random()%4;
int_input_msg1[9]=cl;//10th position is allotted for client port
int_input_msg1[8]=rand()%10;
int_input_msg1[7]=rand()%3;
int_input_msg1[6]=strlen(input_message_1[rand_index]);

memcpy(int_input_msg1,(int *)input_message_1[rand_index],int_input_msg1[6]);

sleep(1);
send(0,int_input_msg1);
}
else if(cl==2){
rand_index=random()%4;
int_input_msg2[9]=cl;//10th position is allotted for client port
int_input_msg2[8]=rand()%10;
int_input_msg2[7]=rand()%3;
int_input_msg2[6]=strlen(input_message_2[rand_index]);
memcpy(int_input_msg2,(int *)input_message_2[rand_index],int_input_msg2[6]);


sleep(1);
send(0,int_input_msg2);
}
char result[10][20] = {0};




if(cl==3){

input_message_3[9]=cl;//10th position is allotted for client port
input_message_3[8]=rand()%10;
input_message_3[7]=rand()%3;
for(j=0;j<7;j++)
{
int_input_msg3[j]=(int)input_message_3[j];
}
for(j=7;j<10;j++)
{
int_input_msg3[j]=input_message_3[j];
}
sleep(1);
send(0,int_input_msg3);
//Receive all entries from server table
receive(cl,(int *)result[0]);
receive(cl,(int *)result[1]);
receive(cl,(int *)result[2]);
receive(cl,(int *)result[3]);
receive(cl,(int *)result[4]);
receive(cl,(int *)result[5]);
receive(cl,(int *)result[6]);
receive(cl,(int *)result[7]);
receive(cl,(int *)result[8]);
receive(cl,(int *)result[9]);
printf("\n****** Client:Message (10 Strings) received from Server %d at Client %d .# denotes the field is empty\n", sp,cl);


for(i=0;i<10;i++)
{
if(strcmp(result[i],"") == 0)
printf("______\n",result[i]);
else
printf("%s\n",result[i]);
}


}
sleep(1);
}
}
else
printf("\nNo more ports \n");
}



void server()
{
int counter=0;
char server_table[10][20] = {0};
int server_table_t[10][20];
char final[30];
int position=0;
int operation=0;
int cp=0;
int final_num[10];
int i=0,j=0;

while(1){
    receive(0,final_num);
	operation=final_num[7];
	
    memcpy(final,(char *)final_num,final_num[6]);
	final[final_num[6]]='\0';
	
	
	cp=final_num[9];
if(cp==3){
for(i=0;i<10;i++)
{
for(j=0;j<10;j++)
{
server_table_t[i][j]=(int)server_table[i][j];
}
}
//Send response to clients
send(cp,(int *)server_table[0]);
send(cp,(int *)server_table[1]);
send(cp,(int *)server_table[2]);
send(cp,(int *)server_table[3]);
send(cp,(int *)server_table[4]);
send(cp,(int *)server_table[5]);
send(cp,(int *)server_table[6]);
send(cp,(int *)server_table[7]);
send(cp,(int *)server_table[8]);
send(cp,(int *)server_table[9]);
}
else{
operation=final_num[7];
position=final_num[8];
//Server Operations
if(operation==0){
{
strcpy(server_table[counter],final);
printf("Client %d adds %s @ %d\n", cp, final, position);
}
counter=(counter+1)%10;
}
else if(operation==1){

strcpy(server_table[position],"");

printf("Client %d deletes @ %d\n", cp, position);
}
else{
for(i=0;i<strlen(final);i++)
{
server_table[position][i]=(char)(final[i]-32);
}
printf("Client %d modifies string %s @ %d\n", cp, final, position);
}
    }
}
}
	
	

int main()
{
printf("The application has 3 clients which talk to 1 serverClients 1 and 2 keep sending messages to the server.Client 3 just displays the table received from the server.There are 4 different messages that are being sent to the server randomnly by the clients.The server performs 3 operations.\n");
printf("\n ADD-->Adds the incoming message to the respective position in the server table. \n DELETE-->Deletes the message at the respective position from the server table.After delete operation, the string gets replaced by '____________'.\n MODIFY--> Converts the incoming messages in lowercase to uppercase at the respective position in the server table \n\n");
sleep(1);
init_message();//initialize structure variables sem_send,sem_recv and mutex . Initialize message array to zeroes
//Starting 3 client and 1 server thread
start_thread(client);
start_thread(client);
start_thread(client);
start_thread(server);
run();//call run

}