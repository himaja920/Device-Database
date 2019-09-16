# Device-Database
TCP Server Client


#TCP SERVER

#include <fcntl.h>
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h>
#include <stdio.h> 
#define MAX 80 
#define PORT 8080 
#define SIZE 2560
#define size 31
#define byte 256
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int sockfd) 
{ 
	char data[SIZE],ch = '\0',buf[size];//buf is for storing in fread 
	int n,i; 
        //int8_t command;
       //creating  a database file
        
	// infinite loop for chat 
	for (;;)
        {       
                bzero(data,SIZE);
                read(sockfd,data,sizeof(data));                     //reading data from client
                
                printf("Data from client is \n\n");
                int s = strlen(data);
                char ci;    
                for(n=0;n<s;n++)
                {
                 printf("data[%d] is %x\n",n,data[n]);
                }
                printf("\n\n");
                FILE *fp;
                fp = fopen("filename.txt","r+");
                //while((ci == fgetc(fp) != EOF)
                //{
                  
              
                if(data[0] == 1)                                    // if command is 1 it is for adding devices
                {
                    printf("If cond check\n");                   // checking if cond if command is 1
                    
                    FILE *f;
                    f = fopen("filename.txt","a+");
                     /* while ((ci = fgetc(f)) != EOF)
                          {
                            if (ci == data[1])
                            { 
                              printf("Device number exits already\n");
                            }
                    else{*/
                    fputc(data[1],f);                                 // writing data[1] that is device id into file
                    int8_t x = data[3] ;// 1 st attribute length
                    i = 4;
                    while(i > 3 && i < x+4)
                    {
                      fputc(data[i],f);
                      i++;
                    }  
                     
                    /* i = 4;
                     while(data[i] != 2 )
                    {
                      
                      fputc(data[i],f);
                      i++;
                                   
                    }*/
               

                    int k=x;// i is value  (4+lenghth after name)//k=i+2;
                    
                    int j;
                    for(j=k+2;j<=(size+1);j++)  //starts after name in file size =31
                    {
                      fputc(ch,f);
                    }

                      i = 6+x; 
 
                     int l = data[5+x];// 2nd attribute length
                    printf("att leng %d\n ",l);
                     while(i > (x+5) && i <= (x+5+l))
                     {
                       fputc(data[i],f);
                       i++;
                     }
                    
                     for(j = (size+l+2);j<=63;j++)   // size = 31 so j = 33+l
                     {
                        fputc(ch,f);
                     }
                      int ml = data[x+l+7];//3rd attribute length
                     i = x+l+8;
                     while(i > (x+l+7) && i<=(x+l+ml+7))
                     {
                        fputc(data[i],f);
                        i++;
                     }
                     
                     for(j = 64+ml;j<=byte;j++)
                     {
                         fputc(ch,f);
                     }
                     //}}
                     fclose(f);
                   }          //  if close
              
                 else if(data[0] == 2)                                 // if command is 2 it is read condn
                 {
                   char ci;
                    printf("The device number is %d\n",data[1]);

                    printf("Attribute ID is %d\n",data[2]); 
                    FILE *f;
                             int b=1,i=1,j=2,k=32,l=33,m=63,n=64;//s=256 this is byte from #define ;           // positions of attributes
                              f = fopen("filename.txt","r"); 
                    while ((ci = fgetc(f)) != EOF)
                          {
                            if (ci == data[1])
                            {                              
                             if(data[2] > 3 || data[2] <=0)
                           {
                              printf("Not a valid attribute id\n");
                           }
                            else
                          {
                                                    // opening database file in read mode 
                                 if(ci == data[1])
                                 {
                                   printf("Data[1] is %d\n",data[1]);
                                   if(data[2] == 1)
                                     { 
                                       i=i+(byte*((data[1])-1));
                                            printf("i is %d\n",i);
                                         j=j+(byte*((data[1])-1));
                                     k=k+(byte*((data[1])-1));
                                     fseek(f,i,SEEK_SET);//fseek(f,1,SEEK_SET); setting position after  1st byte
                       
                                     fread(buf, j,k, f);//fread(buf,2,32,f); reading from 2nd byte to 32 nd byte 
                       
                          printf(" %s\n", buf);
                          write(sockfd,buf,sizeof(buf));
                        }
                        else if(data[2] == 2)
                        {
                          l=l+(byte*((data[1])-1));
                          n=n+(byte*((data[1])-1));
                          k = k+(byte*((data[1])-1));
                          fseek(f,k,SEEK_SET);//fseek(f,32,SEEK_SET);//setting position after 32
                          fread(buf,l,n,f);//fread(buf,33,64,f);//reading from 33 to 64 bytes
                      
                          printf("%s\n",buf);
                          write(sockfd,buf,sizeof(buf));

                        } 
                       else if (data[2] == 3)
                       { 
                         m = m+(byte*((data[1])-1)); 
                         n = n+(byte*((data[1])-1));
                         s = s+(byte*((data[1])-1));
                         fseek(f,m,SEEK_SET);//fseek(f,63,SEEK_SET); setting position after 63 
                         fread(buf,n,s,f);//fseek(buf,64,256,f); reading from 64 to 256 bytes 
                         
                         printf("%s\n",buf);     
                         write(sockfd,buf,sizeof(buf));

                       } 
                     }//closing if in else
                     //closing file                    
}//closing else in  else
                 }//closing else in else if
               }//while
               fclose(f);
                }   //closing actual else if
                    


                   else if (data[0] == 3)
                     {
                         printf("Device number to be deleted is %d\n",data[1]);
                         char ch = '\0',ci;
                         int i;
                         FILE *f;
                         f = fopen("filename.txt","r+");
                        
                         while ((ci = fgetc(f)) != EOF)
                          {
                            if (ci == data[1])
                            {
                              i=0+(byte*(data[1]-1));
                               fseek(f,i,SEEK_SET);
                               for(i = 0+(byte*(data[1]-1)); i < byte*(data[1]); i++)
                                 {
                                    fputc(ch,f);
                                 }
                            }                                                                       //fseek(ft, -1, SEEK_CUR);
                            
                          }
                        fclose(f);
                       }
                    
 

                   else if (data[0] == 4)
                    {
                         printf("Edit gng\n");
                        printf("The device number to be edited is %d\n",data[1]);
                        printf("The device attribute id is %d\n",data[2]);
                        char buf[31],ci;
                        FILE *f;
                        f = fopen("filename.txt","r+");
                          while ((ci = fgetc(f)) != EOF)
                          {
                            if (ci == data[1])
                            {
                               if(data[2] == 1)
                               {
                                                             
                                 read(sockfd,buf,sizeof(buf));
                                 int8_t s = strlen(buf);
                                 i = 0;
                                 fseek(f,(i+1)+(byte*((data[1])-1)),SEEK_SET);
 
                                 for(i = 0; i < s; i++)
                                 {
                                   
                                    fwrite(buf+i,sizeof(char),1,f);
                                 } 
                                 for(i = s+2;i<=(size+1);i++)
                                 {
                                    fputc(ch,f);
                                 }                                    
                             }//3
                            else if(data[2] == 2)
                             { //4
                                  read(sockfd,buf,sizeof(buf));
                                   i = 0;
                                  int8_t b = strlen(buf);
                                  fseek(f,(i+(size+1))+(byte*((data[1])-1)),SEEK_SET); 
                                    for(i = 0; i < b;i++)                       
                                   {
                                     fwrite(buf+i,sizeof(char),1,f);
                                  
                                   }
                                  for( i = (size+2)+b; i <=63;i++) // size = 31 + 2 i=33+b
                                  {
                                     fputc(ch,f);
                                  }
                             } //4
                            else 
                             { //5
                                 read(sockfd,buf,sizeof(buf));
                                  i = 0;
                                  int8_t m = strlen(buf);
                                  fseek(f,(i+63)+(byte*((data[1])-1)),SEEK_SET);
                                  for(i = 0; i < m; i++)
                                  {
                                    
                                    fwrite(buf+i,sizeof(char),1,f);
                                  }
                                  for( i = 64+m; i<(byte-1);i++)
                                  {
                                    fputc(ch,f);
                                  }
                              } //5
                            //2      
                               
                    }} 
                   fclose(f);
               }  // else if data[0] == 4
                   
/* for printing file contents in client side
                     
                          char buf[SIZE];
                          int outft, inft,fileread;
                          // output file opened or created
                          if((outft = open("filename1.txt", O_CREAT | O_APPEND | O_RDWR))==-1){
                          perror("open");
                          }
                          // lets open the input file
                          inft = open("filename.txt", O_RDONLY);
                          if(inft >0){ // there are things to read from the input
                          fileread = read(inft, buf, sizeof(buf));
                          printf("%s\n", buf);
                          write(outft, buf, sizeof(buf));
                          close(inft);
                          }
                          close(outft);*/


                           bzero(data, SIZE); 
		            n = 0; 
                            printf("Enter server message to client\n");
		            // copy server message in the data 
		            while ((data[n++] = getchar()) != '\n') 
			           ;               
		           // and send that data to client 
		           write(sockfd, data, sizeof(data)); 
		           // if msg contains "Exit" then server exit and chat ended. 
		           
                           if (strncmp("exit", data, 4) == 0)  
			   {
                             printf("Server Exit...\n"); 
			     break; 
                           }
                     }//for loop close
}



// Driver function 
 int main() 
  { 

                  	int sockfd, connfd, len; 
	                struct sockaddr_in servaddr, cli; 

	                // socket create and verification 
	                sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	                if (sockfd == -1) { 
		           printf("socket creation failed...\n"); 
		           exit(0); 
	                } 
	                else
		           printf("Socket successfully created..\n"); 
	              
                         bzero(&servaddr, sizeof(servaddr)); 

	                 // assign IP, PORT 
	
                         servaddr.sin_family = AF_INET; 
	                 servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	                 servaddr.sin_port = htons(PORT); 

	                 // Binding newly created socket to given IP and verification 
	
                         if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
		         {
                             printf("socket bind failed...\n"); 
		             exit(0); 
	                 } 
	
                         else
		          printf("Socket successfully binded..\n"); 

	                 // Now server is ready to listen and verification 
	                 if ((listen(sockfd, 5)) != 0)  
               		 {
                             printf("Listen failed...\n"); 
		             exit(0); 
	                 } 
	                else
		            printf("Server listening..\n"); 
	
                        len = sizeof(cli); 

	                // Accept the data packet from client and verification 
	                connfd = accept(sockfd, (SA*)&cli, &len); 
	                if (connfd < 0)  
		        {
                            printf("server acccept failed...\n"); 
		            exit(0); 
	                } 
	                else
		             printf("server acccept the client...\n");
                        /*char buffer[SIZE];
                        FILE *fp;
                        fp = fopen("filename.txt","r+");
                        fscanf(fp,"%s",buffer);
                        write(sockfd,buffer,sizeof(buffer));
                        printf("File sent successfully\n");
                        fclose(fp);*/

                        // Function for chatting between client and server 

	                func(connfd); 

	                // After chatting close the socket 
	                close(sockfd); 
   } 
