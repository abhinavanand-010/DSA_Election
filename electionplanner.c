// THIS PROJECT IS AN ELECTION PLANNER WHICH DEMONSTRATES THE FOLLOWING:
// VOTING PROCESSS
// ELECTION RESULT
// TO FIND THE MINIMUM DISTANCE BETWEEN THE BOOTHS AND THE SHORTEST DISTANCE THROUGH MST TO TRAVERSE THROUGH ALL THE ALLOCATED BOOTHS.
#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#include<stdbool.h>
#include<strings.h>
#define INF INT_MAX
struct candidate
{
    char cid[5];
    char cname[20];
};
struct candidate can[20];

// FUNCTION TO CREATE GRAPH DYNAMICALLY
int **create_graph(int vertices)
{
    int **graph = (int **)malloc(vertices * sizeof(int *));
    int i, j;
    for (i = 0; i < vertices; i++)
        graph[i] = (int *)malloc(vertices * sizeof(int));

    for (i = 0; i < vertices; i++)
    {
        for (j = 0; j < vertices; j++)
        {
            graph[i][j] = 0; // Initialize all elements to 0
        }
    }
    return graph;
}

// ADDING EDGES TO THE GRAPH
void add_edge(int **graph, int src, int dest, int dist)
{
    graph[src][dest] = dist;
    graph[dest][src] = dist;
}

// READING EDGES OF GRAPH
void read_edges(FILE *file,int **graph)
{
    int a, b, c;
    while (!feof(file))
    {
        fscanf(file, "%d  %d  %d\n", &a, &b, &c);
        // printf("hi %d %d %d",a,b,c);
        add_edge(graph, a-1, b-1, c);
        // break;
    }
}
//prism code part
int minKey(int key[], int mstSet[],int V)
{
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;

    return min_index;
}

//DISPLAY THE TOTAL COST
void printMST(int parent[], int **graph,int v)
{
    int sum=0;
    printf("path \tdistance\n");
    for (int i = 1; i < v; i++)
    {
        printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
        sum=sum+graph[i][parent[i]];
    }
    printf("total distance is :- %d\n",sum);
}

// PRIMS ALGORITHM TO FIND MST OF POLLING BOOTHS
void primMST(int **graph, int V)
{
    int parent[V];
    int key[V];
    int mstSet[V];

    for (int i = 0; i < V; i++)
        key[i] = INF, mstSet[i] = 0;

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = minKey(key, mstSet,V);

        mstSet[u] = 1;

        for (int j = 0; j < V; j++)

            if (graph[u][j] && mstSet[j] == 0 && graph[u][j] < key[j])
                parent[j] = u, key[j] = graph[u][j];
    }

    printMST(parent, graph,V);
}

//FUNCTION TO START VOTING PROCESS
void startEleection(char *fl1, char *fl2, int voterID)
{
    FILE *fp;
    FILE *fp2;
    FILE *fp3;


    bool found = false;
    bool found2 = false;
    int data;
    int data2;
    char vote[1];


    fp = fopen(fl1, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", fl1);
        return;
    }

    while (fscanf(fp, "%d", &data) != EOF) {
        if (data == voterID) {
            found = true;
            break;
        }
    }

    fclose(fp);
// duplicacy verificatiion
    if (found) {



            fp2 = fopen(fl2, "r");
            if (fp2 == NULL) {
            printf("Error: could not open file %s\n", fl2);
            return;
        }

        while (!feof(fp2)) {
            fscanf(fp2, "%d %c", &data2,vote);
            if (data2 == voterID) {
            found2 = true;
            break;
        }
    }
        fclose(fp2);
        //white data when not found IN WRITE FILE(VOTE STORE)
        if (!found2) {
            printf("Enter your vote");
            scanf("%s",&vote);
            fp3 = fopen(fl2, "a");        // append mode to avoid overwriting of data in file2
            if (fp3 == NULL) {
            printf("Error: could not open file %s\n", fl2);
            return;
        }

        fprintf(fp3, "%d %s\n", voterID, vote);

        fclose(fp3);
    }


    }
}
// FIND MAXIMUM INDEX EQUIVALENT TO LINE NUMBER IN CANDIDATE LIST

int find_max_index(int arr[], int size) {
    int max_index = 0;
    for (int i = 1; i < size; i++) {
        if (arr[i] > arr[max_index]) {
            max_index = i;
        }
    }
    return max_index;
}

// DISPLAY WINNER
void showWinner(char *filename, char *filename2)
{
    FILE *fp;
    int line_count = 0;
    char line[80];
    char ch;
    char *chars;
    int i;
   // char chars[] = "ABCD";
    char c;
    int count[15] = {0}; // initialize count array to 0    MAKE 15 AS MODULAR INPUT
//    int i, max_index;


//DECLARING CHARACTER ARRAY-----------------------------------------------------

    // Open the file in read mode
    fp = fopen(filename, "r");

    //printf("test1\n");
    // Check if the file was opened successfully
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }
    //printf("test2\n");
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }

    fclose(fp);

    chars = (char*) malloc(line_count * sizeof(char));
    //printf("test3\n");
    for (i = 0; i < line_count; i++) {
        chars[i] = 'A' + i;
    }
    chars[i] = '\0';

  //  printf("String: %s\n", chars);

//COUNTING THE OCCURENCES:------------------------------------------------------

     // open the file
    fp = fopen(filename2, "r");
    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename2);
        return;
    }

    // read each character from the file
    //printf("test4\n");
    while ((ch = fgetc(fp)) != EOF) {
        // check if the character is present in the string
        for (int i = 0; i < line_count; i++) {
            if (chars[i] == ch) {
                count[i]++;
                break;
            }
        }
    }

    //printf("test5\n");
    fclose(fp);
    free(chars);
//--------------------------------------------------------------------
    int arr_size = sizeof(count) / sizeof(count[0]);
    int maax = find_max_index(count, arr_size);




//DISPLAY RESULT-----------------------------------------------------


   // printf("test6\n");
    char str1[100];
    char str2[100];

     // open the file for reading
    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }
    // read each line of the file
    int current_line = 0;
    while (!feof(fp)) {
        fscanf(fp, "%s %s",str1, str2);
        if (current_line == maax) {
            // if we're on the right line, get the second string
            printf("The winner is: %s\n",str2);
            break;
        }
       current_line++;
    }

    fclose(fp);
}


int main()
{
    int pop, eachpop,noofcandidate;
    int nopolls;
    int choice,pass,select,tal;
    int t_vote;                  // vote store
    int vid;
    FILE *taluka;//for making the graph
    FILE *candidates;//for taking the candidates input
    FILE *state;//for making the graph
    FILE *candidates1;//for taking the candidates input
    FILE *country;//for making the graph
    FILE *candidates2;//for taking the candidates input
    //taluka
    char filenameT[] = "talukacand.txt";  // name of candidates for getting result
    char tfileread[] = "Taluka_f_vid.txt";
    char tfilewrite[] = "Taluka_f_w.txt";
    //state
    char filenameS[]="statecand.txt";
     char sfileread[] = "State_f_vid.txt";
    char sfilewrite[] = "State_f_w.txt";
    //country
    char filenameC[]="countrycand.txt";
    char cfileread[] = "Country_f_vid.txt";
    char cfilewrite[] = "Country_f_w.txt";

    // VARIABES FOR MASKING PASSWORD
    int MAX_PASSWORD_LENGTH=6;
    char password_string[MAX_PASSWORD_LENGTH + 1]; // Array to store password as string
    int i = 0; // Counter variable for password string
    char ch; // Variable to store each character entered by user

    while (1)
    {


        printf("ENTER ADMIN PASSWORD\n");
//  // Loop to read each character and mask it with *
//     while ((ch = getch()) != '\r' && i < MAX_PASSWORD_LENGTH) {
//         if (ch == '\b') { // If backspace is pressed, remove the last character
//             if (i > 0) {
//                 printf("\b \b");
//                 i--;
//             }
//         } else if (ch >= '0' && ch <= '9') { // If digit is entered, add it to password string and mask it
//             password_string[i++] = ch;
//             printf("*");
//         }
//     }
//     password_string[i] = '\0'; // Add null terminator to password string
//     pass = atoi(password_string); // Convert password string to integer

        scanf("%d",&pass);
        if (pass==123456)
        {
            printf("ENTER YOUR CHOICE\n1->TALUKA ELECTION\n2->STATE ELECTION\n3->COUNTRY ELECTION\n4-> LOGOUT\n");
            scanf("%d",&select);
            switch (select)
            {
            case 1: system("cls");
                     printf("WELCOME to TALUKA Election Portal.\n");
                    printf("ENTER CHOICE:\n1-START VOTING\n2-RESULT\n3-GET COST");
                    scanf("%d",&tal);
                    switch(tal)
                    {
                        case 1: while(1)
                                {
                                    candidates=fopen("talukacandidates.txt","r");
                                        fscanf(candidates,"%d",&noofcandidate);
                                        for (int i = 1; i <= noofcandidate; i++)
                                        {
                                            fscanf(candidates,"%s",can[i].cid);
                                            fscanf(candidates,"%s",can[i].cname);
                                        }
                                        for (int  i = 1; i <= noofcandidate; i++)
                                        {
                                            printf("%s \t %s\n",can[i].cid,can[i].cname);
                                        }
                                        fclose(candidates);
                                    printf("ENTER YOUR VOTER ID");
                                    scanf("%d",&vid);
                                    if(vid==1001) break;
                                    startEleection(tfileread, tfilewrite, vid);
                                    system("cls");
                                }
                                break;
                        case 2: //display result
                                showWinner(filenameT,tfilewrite);
                                break;
                        case 3:    taluka = fopen("taluka.txt", "r");
                                    if (taluka == NULL)
                                     {
                                         printf("File not found\n");
                                         exit(0);
                                     }
                                     fscanf(taluka, "%d", &pop);
                                     fscanf(taluka, "%d", &eachpop);
                                     nopolls = (int)(pop / eachpop);
                                     int vertices = nopolls;
                                     int **graph = create_graph(vertices);
                                     read_edges(taluka,graph);
                                     fclose(taluka);
                                     primMST(graph,vertices);
                                break;
                    }
                    break;

            case 2: printf("WELCOME TO STATE ELECTION PORTAL.\n");
                    printf("ENTER CHOICE:\n1-START VOTING\n2-RESULT\n3-GET COST");
                    scanf("%d",&tal);
                    switch(tal)
                    {
                        case 1: while(1)
                                {
                                    candidates1=fopen("statecandidates.txt","r");
                                        fscanf(candidates1,"%d",&noofcandidate);
                                        for (int i = 1; i <= noofcandidate; i++)
                                        {
                                            fscanf(candidates1,"%s",can[i].cid);
                                            fscanf(candidates1,"%s",can[i].cname);
                                        }
                                        for (int  i = 1; i <= noofcandidate; i++)
                                        {
                                            printf("%s \t %s\n",can[i].cid,can[i].cname);
                                        }
                                        fclose(candidates1);
                                    printf("ENTER YOUR VOTER ID");
                                    scanf("%d",&vid);
                                    if(vid==1001) break;
                                     startEleection(sfileread, sfilewrite, vid);
                                    system("cls");


                                }
                                break;
                        case 2: //display result
                                showWinner(filenameS,sfilewrite);
                                break;
                        case 3:  state = fopen("state.txt", "r");
                                    if (state == NULL)
                                     {
                                         printf("File not found\n");
                                         exit(0);
                                     }
                                     fscanf(state, "%d", &pop);
                                     fscanf(state, "%d", &eachpop);
                                     nopolls = (int)(pop / eachpop);
                                     int vertices = nopolls;
                                     int **graph = create_graph(vertices);
                                     read_edges(state,graph);
                                     fclose(state);
                                     primMST(graph,vertices);
                                break;
                    }
                    break;
            case 3: printf("WELCOME TO country ELECTION PORTAL.\n");
                    printf("ENTER CHOICE:\n1-START VOTING\n2-RESULT\n3-GET COST");
                    scanf("%d",&tal);
                    switch(tal)
                    {
                        case 1: while(1)
                                {
                                    candidates2=fopen("countrycandidates.txt","r");
                                        fscanf(candidates2,"%d",&noofcandidate);
                                        for (int i = 1; i <= noofcandidate; i++)
                                        {
                                            fscanf(candidates2,"%s",can[i].cid);
                                            fscanf(candidates2,"%s",can[i].cname);
                                        }
                                        for (int  i = 1; i <= noofcandidate; i++)
                                        {
                                            printf("%s \t %s\n",can[i].cid,can[i].cname);
                                        }
                                        fclose(candidates1);
                                    printf("ENTER YOUR VOTER ID");
                                    scanf("%d",&vid);
                                    if(vid==1001) return 0;
                                     startEleection(cfileread, cfilewrite, vid);
                                    system("cls");

                                 }
                                break;
                        case 2: //display result
                                    showWinner(filenameC,cfilewrite);
                                break;
                        case 3: country = fopen("country.txt", "r");
                                    if (country == NULL)
                                     {
                                         printf("File not found\n");
                                         exit(0);
                                     }
                                     fscanf(country, "%d", &pop);
                                     fscanf(country, "%d", &eachpop);
                                     nopolls = (int)(pop / eachpop);
                                     int vertices = nopolls;
                                     int **graph = create_graph(vertices);
                                     read_edges(country,graph);
                                     fclose(country);
                                     primMST(graph,vertices);
                                break;
                    }
                    break;
            case 4: printf("SESSION TERMINATED\nPLEASE RESTART THE APPLICATION./n");
                    return 0;
                    break;
            }
        }
        else
        {
            printf("access denied\n\n");
        }

    }
  }
