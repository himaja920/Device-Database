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
   
   
   
   
   #///TCP CLIENT
   
   
   
   
   
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

