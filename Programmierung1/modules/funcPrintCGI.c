/*funcPrintCGI.c*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include"../func.h"

char errHandlerPP[7+1] = "success";
char actionHandlerPP[7+1] = "naction";
char filter[200+1] = {'\0'};
char filterType = 'U'; // U-undefined I-ID N-Name
int filterStatus = 0; // 0-no filter 1-to be filtered

void proccessPosted() {
    char posted[256];
    fgets(posted,256,stdin); // get input
    int i;
    // check if input is longer than buffer
    for(i=0; posted[i]!='\0'; i++) {
        replaceAvailibleCharacters(&posted[i]);
        if(i>=254) { // longer than buffer
            strcpy(errHandlerPP,"pstLgEr");
            return;
        }
    }
    //printf("str: %s :: %d <br>",posted, i);
    char *pstr = strtok(posted, "="); // get function name
    //form addElem=0&1=<unit name>&2=<unit number>&3=<unit count>
    if(!strcmp(pstr, "addElem")) { // take parameter for func insLast
        addElemCore(pstr);
    }
    //form deleteElement=<element number>
    else if(!strcmp(pstr, "deleteElement")) { // take parameter for func deleteElement
        pstr = strtok(NULL, "&");
        deleteElement(atoi(pstr));
        strcpy(actionHandlerPP, "deleted");
    }
    //form listChangeParameter=3&unitNumber=<unit number>&val=<value for Parameter> 0...n-1
    else if(!strcmp(pstr, "listChangeParameter")&& !strcmp((pstr=strtok(NULL, "&")), "3")) {// take parameter for func listChangeParameter
        listChangeParameterCore(pstr);
    }
    //form sortName=0
    else if(!strcmp(pstr, "sortName")) {
        sortCore('N');
    }
    //form sortID=0
    else if(!strcmp(pstr, "sortID")) {
        sortCore('I');
    }
    //form sortCount=0
    else if(!strcmp(pstr, "sortCount")) {
        sortCore('C');
    }
    //form search=<N/I>&key=<key word>
    else if(!strcmp(pstr, "search")) {
        searchCore(pstr);
    }
    //form refresh=0
    else if(!strcmp(pstr, "refresh")) {
        strcpy(actionHandlerPP, "refresh");
    }
    else
        strcpy(actionHandlerPP, "naction");
}

void printHead() {
    puts("Content-type:text/html\n\n");
    puts("<head> <title>Material Managment</title> <style> table { font-family: arial, sans-serif; border-collapse: collapse; width: 100%; } td, th { border: 1px solid #dddddd; text-align: left; padding: 8px; } tr:nth-child(even) { background-color: #dddddd; } ul {list-style-type: none;margin: 0; padding: 0;overflow: hidden;background-color: #595959;} li p {display: block;color: white;text-align: center; padding: 8px;text-decoration: none;} input[type=submit] {    background-color: #555555;border: none;color: white;padding: 7px 17px;text-align: center;text-decoration: none;display: inline-block;font-size: 16px;margin: 4px 2px;cursor: pointer;} img { max-width: auto; max-height:50;} well well-sm { display: inline-block; } </style> ");
    
    puts("<link rel='stylesheet' href='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css'>");
    puts("<script src='https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js'></script>");
    puts("<script src='https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js'></script>");
    puts("</head>");
}

void printBody() {
    puts("<body style='background-color:#F9F9F9;'>");
    //top menu =================================
    puts("<h1>Material Management<img src='../images/HTW-Logo.svg' align='right'></h1>");
    //<img src='../images/burenko-logo.png' align='right'>
    puts("<hr>");
    //output action handler ====================    
    puts("<div class='well well-sm'>");
    if(strcmp(actionHandlerPP, "stdActn") == 0)
        puts("<p></p>");
    else if(strcmp(actionHandlerPP,"elAdded") == 0)
        puts("<p>Added.</p>");
    else if(strcmp(actionHandlerPP,"deleted") == 0)
        puts("<p>Deleted.</p>");
    else if(strcmp(actionHandlerPP,"changed") == 0)
        puts("<p>Changed.</p>");
    else if(strcmp(actionHandlerPP,"sortSuc") == 0)
        puts("<p>Sorted.</p>");
    else if(strcmp(actionHandlerPP,"filterd") == 0)
        puts("<p>Filtered.</p>");
    else if(strcmp(actionHandlerPP,"refresh") == 0)
        puts("<p>Refreshed.</p>");
    else
        puts("<p>Welcome.</p>");
    //output error handler =====================
    if(strcmp(errHandlerPP,"addElEr") == 0)
        puts("<p style='color:red;'> Pass all parameters please</p>");
    else if(strcmp(errHandlerPP,"pstLgEr") == 0)
        puts("<p style='color:red;'> Input string is too long</p>");
    else if(strcmp(errHandlerPP,"stdinEr") == 0)
        puts("<p style='color:red;'> Input Error: Sorry we'll fix it</p>");
    puts("</div>");
    //search block ============================
    puts("<div class='well well-sm'>");

    puts("<b>Search for</b>");
    puts("<form name='search' action='' METHOD='POST'>");
    puts("<input name='search' type='radio' value='N' checked>Name</input><br>");
    puts("<input name='search' type='radio' value='I'>ID</input><br>");
    puts("<input name='key' type='text' maxlength='200' placeholder='key word'></input><br>");
    puts("<input type='submit' value='start'></input>");
    puts("</form>");

    puts("</div>");
    //separate line
    puts("<hr>");
    //main data table
    puts("<table>");
    //output headers ===========================
    puts("<tr>");
    //Refresh----------------------------------
    puts("<th>");
    puts("<form action='' method='POST'>");
    puts("<input type='hidden' name='refresh' value='0'>");
    puts("<input type='submit' value='refresh' style='background-color:#4CAF50;'>");
    puts("</form>");
    puts("</th>");
    //sorts ------------------------------------
    //name -----------=----------=--------=-----
    puts("<th>");
    puts("<form action='' method='POST'>");
    puts("<input type='hidden' name='sortName' value='0'>");
    puts("<input type='submit' value='Name | sort'>");
    puts("</form>");
    puts("</th>");
    //id -----------=----------=--------=------
    puts("<th>");
    puts("<form action='' method='POST'>");
    puts("<input type='hidden' name='sortID' value='0'>");
    puts("<input type='submit' value='ID | sort'>");
    puts("</form>");
    puts("</th>");
    //count -----------=----------=--------=------
    puts("<th>");
    puts("<form action='' method='POST'>");
    puts("<input type='hidden' name='sortCount' value='0'>");
    puts("<input type='submit' value='Count | sort'>");
    puts("</form>");
    puts("</th>");
    //sorts end ------------------------------- 
    puts("<th>Action</th>");
    puts("</tr>");
    //header end ===============================
    //add new element block ====================
    puts("<tr><form action='' method='POST'>");
    puts("<th></th>");
    puts("<input type='hidden' name='addElem' value='0'>");
    puts("<th><input type='text' name='1' value='' placeholder='name' maxlength='30'></th>");
    puts("<th><input type='number' name='2' value='' placeholder='id' maxlength='10'></th>");
    puts("<th><input type='number' name='3' value='' placeholder='count' maxlength='10'></th>");
    puts("<th><input type='submit' value='add' style='background-color: #008CBA;'></th>");
    puts("</tr></form>");
    //element blocks =============================
    tcnt * pointerWhile = list->pfirst;
    int i;
    // loop parameters
    for(i=0; pointerWhile!=NULL; i++,pointerWhile = pointerWhile->pnxt) { 
        // filtering the output ==================
        if(filterStatus){
            if(filterType=='N' && 
                strstr(pointerWhile->pdata->unitName, filter)==NULL) 
            {
                continue;
            }
            else if (filterType=='I' && 
                (pointerWhile->pdata->unitID != atoi(filter))) {
                continue;
            }
        }
        // unit block ============================
        puts("<tr>");
        // delete element block ------------------
        puts("<form action='' method='POST'>");
        printf("<th><input type='hidden' name='deleteElement' value='%d'>", i);
        puts("<input type='submit' value='delete'  style='background-color: #f44336;'></th>");
        puts("</form>");
        // listChangeParameter block -------------
        puts("<form action='' method='POST'>");
        puts("<input type='hidden' name='listChangeParameter' value='3'>");
        printf("<input type='hidden' name='unitNumber' value='%d'>", i);
        printf("<th> %s </th>",pointerWhile->pdata->unitName);
        printf("<th> %d </th>",pointerWhile->pdata->unitID);
        printf("<th><input type='text' name='val' value='%d' maxlength='20'></th>",pointerWhile->pdata->unitCount);
        puts("<th><input type='submit' value='set'></th>");
        puts("</form>");
        // close unit block -- 
        puts("</tr>");
        // unit block end =======================
    }
    //conclusion ===============================
    puts("</table>");
    puts("<ul>");
    puts("<li><p>2018 Burenko Anton || Programmierung I || Teacher: <a href='https://www2.htw-dresden.de/~beck' target='_blank'>Prof. Beck</a></p></li>");
    puts("");
    puts("</ul>");
//     printf("errHandlerPP:%s <br>", errHandlerPP);
//     printf("actionHandlerPP:%s", actionHandlerPP);
    puts("</body>");
}

char charToLow(char ch) {
        if(ch>='A' && ch<='Z')
            return tolower(ch);
        else 
            return ch;
} 

void searchCore(char *pstr) {
    pstr = strtok(NULL, "&"); // get type
    // set filterType
    if(strcmp(pstr, "I") == 0)
        filterType = 'I';
    else 
        filterType = 'N';
    //get string
    pstr = strtok(NULL, "=");
    pstr = strtok(NULL, "&");
    //check if string consists symbols
    if(pstr!=NULL) {
        strcpy(filter,pstr);
        filterStatus = 1;
    }
    strcpy(actionHandlerPP, "filterd");
}

void sortCore(char type) {
    listSortBy(type);
    strcpy(actionHandlerPP, "sortSuc");
}

void listChangeParameterCore(char *pstr) {
        pstr = strtok(NULL, "=");
        pstr = strtok(NULL, "&"); // get parameter unitNumber
        char * pp = strtok(NULL, "=");
        pp = strtok(NULL, "&"); // get parameter number
      
        tcnt * pointerWhile = list->pfirst; 
        int i = 0;
        int limit = atoi(pstr);
        while(pstr != NULL && i<limit) { // loop parameters
            pointerWhile = pointerWhile->pnxt;
            i++;
        }
        if(pointerWhile == NULL)
            fprintf(stderr, "ERROR in proccessPosted: overlooping the list or list is empty");
        else
            unitWriteParameter(3, pointerWhile->pdata, pp); // change parameter value
        strcpy(actionHandlerPP, "changed");
}

void addElemCore(char *pstr) {
    unit *m = malloc(sizeof(unit));
    pstr = strtok(NULL, "&");
    int i = 0;
    for(i=1;i<=3;i++) { // loop parameters
        pstr = strtok(NULL, "=");
        pstr = strtok(NULL, "&");
        // check for empty input
        if( pstr==NULL || (pstr[0]=='2' && pstr[1]=='=') || 
            (pstr[0]=='3' && pstr[1]=='=') ) {
            strcpy(actionHandlerPP, "stdActn");
            strcpy(errHandlerPP, "addElEr");
            return;
        }
        unitWriteParameter(i, m, pstr); // fill unit
    }
    insLast(m);
    strcpy(actionHandlerPP, "elAdded");
}

void replaceAvailibleCharacters(char *ch) {
    switch(*ch) {
        case '+': 
            *ch = ' ';
            break;
    }
}