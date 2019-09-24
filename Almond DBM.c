//#include <fcntl.h>
#include <stdio.h>
#include <string.h>
//#include <unistd.h>
//#include <stdlib.h>
#include "libAlmondDBM.h"

#define num 50

enum index{
   Temperature = 1,
   Firestate = 2
}; 

enum devType{
  UnknownDeviceType = 0,
  BinarySwitch = 1,
  MultilevelSwitch = 2,
  BinarySensor = 3,
  MultilevelSwitchOnOff = 4,
  DoorLock = 5,
  Alarm = 6,
  Thermostat = 7,
  Gateway = 8,
  FireSensor = 9,
  WaterSensor = 10, 
  TemperatureSensor = 11,
  DoorSensor = 12
} ;
struct deviceData {
    int id;
    int deviceType; //devType deviceType; 
    char name[32];
    char location[32];
    char manufacturer[32];
    int lastModifiedTime;
}Data;

struct dvPair {
    int type;
    int id; // to indicate the dvPair number
    char value[32];
}Pair;



int main()
{
   printf("\n---MENU---\n\n");
   printf("1.ADD DEVICE\n");
   printf("2.EDIT DEVICE\n");
   printf("3.DELETE DEVICE\n");
   printf("4.DELETE ALL\n\n");

   int t;
   printf("Enter the user choice\n");
   scanf("%d",&t);
   DEPOT *depot;
   FILE *f;
   f = fopen("FILE.DB","a+");
   
   if(t == 1)
   {
      
      printf("Enter the Device ID \n");
      scanf("%d",&Data.id);
      printf("Enter the DeviceType \n");
      scanf("%d",&Data.deviceType);
      printf("Enter the Device name\n");
      scanf("%s",&Data.name);
      printf("Enter the Device location\n");
      scanf("%s",&Data.location);
      printf("Enter the Device manufacturer\n"); 
      scanf("%s",&Data.manufacturer);
      printf("Enter the Device last modified time\n");
      scanf("%d",&Data.lastModifiedTime);
      printf("Enter the device type\n");
      scanf("%d",&Pair.type);
      printf("Enter the index id\n");
      scanf("%d",&Pair.id);
      printf("Enter the index value\n");
      scanf("%s",&Pair.value);
      depot =  dpopen("FILE.DB",DP_OWRITER,1);
      printf("%d depot \n",depot);
      printf("KEY    VALUE \n");

       int put = dpput(depot,"1",1,"1",1,DP_DCAT);
       printf("%d put\n",put);
   }
   else
      printf("ncx\n");
  //dpclose(depot);
    return 0;
}
