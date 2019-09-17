#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <fcntl.h>
#define MAX 80 
#define SIZE 2560
#define PORT 8080 
#define SA struct sockaddr 

enum AttributeID{
Name = 1,
Loc = 2,
Man =3
};
enum command{
Read = 2,
Write = 1,
Response =3
};
void func(int sockfd) 
{ 
	char data[SIZE]; 
	int n; 
	
         for (;;) 
          { 
		bzero(data,SIZE); 
	        
                int8_t h =0,id,choice,n=0;
                int8_t dn,did;
                char name[31],n1[31],location[31],l1[31],manuf[31],m1[31];                // n1,l1,m1 are for displaying to user on request
                
                printf("+-------MENU------+\n");
                printf("-------1.ADD-------\n");
                printf("-------2.READ------\n");
                printf("-------3.DELETE----\n");
                printf("-------4.EDIT------\n");
                
                printf("Enter your choice \n\n");
                scanf("%d",&choice);
               
                data[h] = choice;                                                        // assigning command value to data[0]
                printf("data[0] is %i\n",choice);
                
                if(data[0] == 1)
                {
                   printf("Enter the device ID\n");
                   scanf("%d",&id);
                
                   h = h+1;
                   data[h] = id;                                                          // Device ID assigned to data[1] by incrementing h
                   printf("Data[h++] = id is %d\n",data[h]);
                   h = h+1;
                   data[h] = Name;                                                         //Attribute ID assigned to data[2] by incrementing h
                   printf("DAta[h++] attribute id = 1 is %d\n",data[h]);
                  
                   printf("Enter the device name\n");
                   scanf("%s",name);
                   strcpy(n1,name);
                   
                   //printf("name is %s\n",name);
                   //printf("Name is %s\n",n1);
                
                   h = h+1;
                   data[h] = strlen(name);//Attribute length
                    
                   printf("data[%d] is %d\n",h,data[h]);             
                   printf("After strlen(name) insertion h is %d\n",data[h]);
                   
                   h = strlen(data);
                   printf("Length of data is  %d\n",h);
                
                   strcpy(data+h,name);//Value of attribute
                   h = strlen(data);
     
//SECOND ATTRIBUTE  
                   //h = h+1;                           
                   data[h++] = Loc;//Second attribute ID
                  
                   printf("data[%d] is %d\n",h,data[h]);
                   
                   printf("Enter the device location \n");
                   scanf("%s",location);
                   strcpy(l1,location);                                                     //to store location in l1 and send to user on request
                   //h = h+1;
                  
                   h = strlen(data);
                   //h = h+1;
                   data[h++] = strlen(location);//Attribute length
                  
                   printf("data[%d] is %d\n",h,data[h]);
                
                   h =  strlen(data);
                 
                   //printf("Length of whole data after second attribute length taken and value of that is  %d %d \n",h,data[h]);
                
                   strcpy(data+h,location);//Second Attribute value
                   h = strlen(data);
                
                   //printf("After all added second things h is %d\n",h);
               
//THIRD ATTRIBUTE 
                   // printf("H+1 is %d\n",h);
                   data[h++] = Man;//Third attribute ID
             
                   printf("Length of third  attribute ID is %d\n",h);
                   printf("Enter the device manufacturer\n");
                   
                   scanf("%s",manuf);
                   strcpy(m1,manuf);
                   //h = h+1;
                   data[h++] = strlen(manuf);//Third attribute length

                   h = strlen(data);
                   strcpy(data+h,manuf);//Third attribute value
                   
                   int8_t g= strlen(data);
                   
                   //printf("Whole length of the data is %d\n",g);
                   //printf("Request the attribute to display by user\n");
                
                   int8_t a;
                   printf("Enter the choice to retrieve required attribute\n");
                   scanf("%d",&a);
                   if(a == 1)
                    { printf("The attribute chosen is device name and it is : %s\n",n1);}
                   else if(a == 2)
                    { printf("The attribute chosen is device location and it is : %s\n",l1);}
                   else if (a == 3)
                    { printf("The attribute chosen is device manufacturer and it is : %s\n",m1);}
                   else
                    { printf("Not a valid Attribute ID\n");}
             
                   printf("Sending data..\n");
                   write(sockfd,data,sizeof(data));
                  // int s =write(sockfd,data,sizeof(data));
                  // printf("write return %d\n",s);
                   
                  

             }

                   else if(data[0] == 2)
                    {
                      // printf("This is Read command so no adding of devices\n");
                      //int8_t dn,did;
                      int8_t i=0;
                      char buf[31];
                      printf("Enter the device number that is to be read\n");
                      scanf("%d",&dn);
                     
                      i = i+1;
                      printf("i  after data[0] is %d\n",i);
                      data[i] = dn;
                     //while((dn[n++] = getchar()) != '\n');
                     
                      printf("Enter the attribute ID that is to be read\n");
                      scanf("%d",&did);
                      i=i+1;
                      data[i] = did;
                      printf("i after data[1] is %d\n",i);
                     //while((dn[n++] = getchar()) != '\n');
                     
                      printf("device attribute id is %d\n",did);
                     
                      write(sockfd,data,sizeof(data));
                      write(sockfd,dn,sizeof(dn));
                      write(sockfd,did,sizeof(did));
                      
                      
                       read(sockfd,buf,sizeof(buf));
                       printf("The client request for attribute is : %s\n",buf);
                      

                     }  //else if bracket close
                  
                ////  3.DELETE DEVICE  ////

                  
                     else if (data[0] == 3)
                     {
                        printf("Enter the device number that is to be deleted\n");
                        int8_t d;
                        int c =0 ;
                        scanf("%d",&d);
                        c = c+1;
                        data[c] = d;
                         printf("Sending device number to deleted\n");
                             

                           write(sockfd,data,sizeof(data));                
                     } // else if data[0] == 3


                ////  4.EDIT DEVICE  ////


                     else if(data[0] == 4)
                     {
                        int8_t dn,did,k=0;
                        
                        char buf[31];
                       
                        printf("Enter the device number to be edited\n");
                        scanf("%d",&dn);
                        k = k+1;                        
                        data[k] = dn;
                          printf("Enter the device attribute that is to be edited\n");
                          scanf("%d",&did);

                        k = k+1;
                          data[k] = did;
                         printf("Sending data\n");
                       write(sockfd,data,sizeof(data));
                          
                             if(did == 1)
                             {//3
                                 printf("Enter new device name\n");
                                 scanf("%s",buf);
                                 write(sockfd,buf,sizeof(buf));
                                                                   
                             }//3
                            else if(did == 2)
                             { //4
                                  printf("Enter new device location\n");
                                  scanf("%s",buf);
                                    write(sockfd,buf,sizeof(buf));
                                  
                             } //4
                            else 
                             { //5
                                  printf("Enter new device manufacturer\n");
                                  scanf("%s",buf);
                          write(sockfd,buf,sizeof(buf));
                                 
                              } //5
                                                         
                    }//else if data[0] == 4
               	     


                  /* char buf[SIZE];
                   int inft,outft,fileread;
                   outft = open("filename1.txt", O_CREAT | O_APPEND | O_RDWR);
                   printf("File contents are : \n");                   
                   read(outft,buf,sizeof(buf));
                   printf("\n\n");
                   close(outft);*/
                 

                     bzero(data, sizeof(data)); 
		     read(sockfd, data, sizeof(data)); 
		     printf("From Server : %s", data); 
	       	     if ((strncmp(data, "exit", 4)) == 0)  
                      {			
                        printf("Client Exit...\n"); 
	                break; 
                      }	         
        						
	         }//for loop 
               }// function close
 

int main() 
{ 

            printf("The commands are  Write = %d , Read = %d , Response = %d \n",Write,Read,Response);
            printf("Attribute IDs are Name = %d , Location = %d , Manufacturer = %d \n\n",Name,Loc,Man);

            
             /*char c;
             FILE *f;
             f = fopen("filename.txt","r+");
             printf("The file contents are \n");
             while((c = fgetc(f))!=EOF)
             {
                printf("%c ",c);
             }
             printf("\n");*/
             /*if(s == 1)
             {
               func(sockfd);
             }
             else if(s == 2)
             {
               edit();
             }
             else if(s ==3)
             { printf("Delete\n");}
             else
                printf("Not a valid option\n");*/
          
                  int sockfd,connfd;
	         struct sockaddr_in servaddr, cli; 

	         // socket creation and verification 
	         sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	         if (sockfd == -1) 
		 {
                  printf("socket creation failed...\n"); 
		  exit(0); 
	         } 
	         else
		   printf("Socket successfully created..\n"); 

	         bzero(&servaddr, sizeof(servaddr)); 

	       // assign IP, PORT 
	       servaddr.sin_family = AF_INET; 
	       servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	       servaddr.sin_port = htons(PORT); 

	       // connect the client socket to server socket 
	      if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0)  
		{
                  printf("connection with the server failed...\n"); 
		  exit(0); 
	        } 
	      else
		printf("connected to the server..\n"); 
                //send_data(sockfd);

              FILE *f;
              f = fopen("filename.txt","r");
              char c;
              printf("File content :\n");
              while((c = fgetc(f)) != EOF)
              {
                 printf("%c ",c);
              }
              printf("\n\n");
              /*FILE *f;
              char buffer[SIZE];
              read(sockfd,buffer,sizeof(buffer));
              f = fopen("filename.txt","r");
              printf("file contents are \n");
              printf("%s",buffer);
              printf("\n\n");
              fclose(f);*/
	        // function for chat 
	
        func(sockfd);
        // close the socket 
	close(sockfd); 
} 

