/*H**********************************************************************
* FILENAME :        jsonParser.c             
*
* DESCRIPTION :
*       Example for using the JSMN JSON Parser library in mikroC for PIC32
*
* NOTES :
*       Credits for the JSMN library go to Serge Zaitsev
*       https://github.com/zserge/jsmn
*
*
* AUTHOR :    Alfredo Valdes (https://github.com/alfredovaldes 
* START DATE :    24 Aug 2018
*
*H*/
/* Include libraries */
#include <jsmn.h>
/* Declare Methods */
void mcuInit(void);
void parseJson(const char *JSON_STRING);
/* Declare the JSON Objects to use, you must escape the " character */
const char *JSON_STRING = 
"{ \n\t \"userId\": 1,\n\t\"id\": 1,\n\t\"title\": \"sunt aut facere repellat\", \n\t\"body\": \"quia et suscipit suscipit recusandae consequuntur expedita et cum reprehenderit\"\n}";

/* Program starts here */
void main()
{
     mcuInit(); //Configure UART2
     parseJson(JSON_STRING); //Parse the Json Object
}

/* Method to initialize UART2 */
void mcuInit(){
    ANSELB = 0; //Make PORTB Digital
    PORTB = 0; //Set PORTB as Output
    U2RXR = 0x1; //Enable UART2 RX Peripheral Pin Select register
    RPB14R = 0x2; //Enable UART2 TX Peripheral Pin Select register
    /* These come with mikroC for PIC32 */
    Unlock_IOLOCK();//Unlocks I/O pins for Peripheral Pin Mapping
    PPS_Mapping_NoLock( _RPG6, _OUTPUT, _U2TX );
    PPS_Mapping_NoLock( _RPB14, _INPUT, _U2RX );
    Lock_IOLOCK();
    UART2_Init(115200); //Init UART at 115200 BPS
    Delay_ms(100);
}
void parseJson(const char *JSON_STRING){
     int i = 0, r = 0, j= 0;
     jsmn_parser parser;
     jsmntok_t tokens[20];
     int JSON_STRING_LENGTH=0;
     char* JsonSize[1];
     JSON_STRING_LENGTH = strlen((char*)JSON_STRING);
     jsmn_init(&parser);
     r = jsmn_parse(&parser, JSON_STRING, JSON_STRING_LENGTH, tokens, 20);
     r--;
     UART2_Write_Text("The original JSON String is: ");
     UART2_Write('\n');
     UART2_Write_Text(JSON_STRING);
     UART2_Write('\n');
     InttoStr(r,JsonSize);
     UART2_Write_Text("The JSON has");
     UART2_Write_Text(JsonSize);
     UART2_Write_Text(" objects.");
     UART2_Write('\n');
     for(j=1;j<=r;j++){
        for(i=tokens[j].start;i<tokens[j].end;i++){
            UART2_Write(JSON_STRING[i]);
        }
        UART2_Write('\n');
     }
}
