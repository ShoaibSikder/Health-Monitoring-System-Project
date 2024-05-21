#include<stdio.h>
#include<time.h>
#include<conio.h> //use for delay(), getch() etc.
#include<ctype.h> //use for toupper(), tolower() etc.
#include<string.h> //use for strcmp(),strcpy(),strlen() etc.
#include<stdlib.h> //use for malloc() etc.
#include<windows.h>//use for gotoxy() etc.

//gotoxy function for better row colum and pixel control
void gotoxy(short x, short y) 
{
    COORD pos = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

// Function Declaration
void WelcomeScreen();                    //done by arnob
void managepatient();                    //done by arnob
void viewlist();                         //done by arnob
void seeyourrecord(char hospitalName[]); // done by Arnob
void viewDoctors();                      // done by Arnob

void registe(char hospitalName[]);              // done by shoaib
void login();                                   // done by shoaib
void Addrecord();                               // done by shoaib
void generatePrescription(char hospitalName[]); // done by shoaib
void detectDisease(char hospitalName[]);        // done by shoaib
void resourceAllocation();                      // done by shoaib
void addDoctor();                               // done by shoaib
void chooseHospital();                          // done by shoaib

void Title(char hospitalName[]);        // done by forhad
void MainMenu();                        // done by forhad
void searchrecord();                    // done by forhad
void otherResources();                  // done by forhad

//struct declaration for login system
struct login
{
    char username[50];
    char password[50];
};
struct login l;

//structure for patient details
struct patient
{
    int patientID;
    char firstname[50];
    char lastname[50];
    char age[50];
    char gender[50];
    char Contactno[50];
    char disease[50];
    char date[50];
};
struct patient p;

//structure for doctor details
struct Doctor {
    char name[50];
    char specialization[50];
    char contact[20];
};
struct Doctor d;

// Structure to represent available resources
struct Resources {
    int doctors;
    int generalRooms;
    int vipRooms;
};
struct Resources r;

//hospital struct
struct hospital {
    int hospitalID;
    char name[50];
    char address[100];
    char contactNo[20];
};
struct hospital h;

//globaly declared file pointer
FILE *user_file;
FILE *pass_file;
FILE *info_file;
FILE *doctorFile;

char hospitalName[50]; 
int main()
{
    WelcomeScreen(); // calling WelcomeScreen Function
    chooseHospital(hospitalName); // Pass hospitalName to chooseHospital function
    Title(hospitalName); // calling Title Function with hospitalName
    int cho;
    printf("\n\n\n\n\n\t\t\t\t1. Register\n\n\t\t\t\t2. Login\n");

    a:
    printf("Enter your choice : ");
    scanf("%d", &cho);
    switch(cho)
    {
        case 1:
            system("cls");
            registe(hospitalName);
            break;
        case 2:
            system("cls");
            login();
            break;
        default:
            printf("Invalid Choice.......\n\n");
            goto a;
            break;
    }

}


/* ***************************************************** Welcome Screen ***************************************************** */ 
void WelcomeScreen()
{
    printf("\n\n\n\n\n\n\n\t\t\t\t#########################################");
    printf("\n\t\t\t\t#\t\t Welcome to\t\t#");
    printf("\n\t\t\t\t#     Rural Health Monitoring System    #");
    printf("\n\t\t\t\t#########################################");
    printf("\n\n\n\n\n Press any key to  continue......\n");
    getch(); // hold the screen
    system("cls"); // use to clear screen
}

/* ****************************************************** Title Screen ***************************************************** */ 
void Title(char hospitalName[])
{
    printf("\n\n\t\t-------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t        Rural Health Monitoring System");
    printf("\n\t\t\t\t\t  Hospital: %s", hospitalName);
    printf("\n\n\t\t-------------------------------------------------------------------------------------");
}


/* ****************************************************** hospital ***************************************************** */
void chooseHospital(char hospitalName[]) {
    int hospitalChoice;
    printf("\n\n\t\t-------------------------------------------------------------------------------------");
    printf("\n\t\t\t\t        Rural Health Monitoring System");
    printf("\n\n\t\t-------------------------------------------------------------------------------------");

    // Open file for reading hospitals. If it doesn't exist, create and populate it
    FILE *hospital_file = fopen("hospitals.txt", "r");
    if (hospital_file == NULL) {
        // If the file doesn't exist, create it and populate it with initial data
        hospital_file = fopen("hospitals.txt", "w");
        if (hospital_file == NULL) {
            printf("\nError creating hospitals file.\n");
            exit(1);
        }

        fprintf(hospital_file, "1 DIU_Hospital DSA 09884578\n");
        fprintf(hospital_file, "2 Ashulia_Hospital Ashulia 095874534\n");
        fprintf(hospital_file, "3 Savar_Hospital Savar 091258745\n");

        fclose(hospital_file);
        // Reopen the file in read mode
        hospital_file = fopen("hospitals.txt", "r");
        if (hospital_file == NULL) {
            printf("\nError opening hospitals file.\n");
            exit(1);
        }
    }

    printf("\n\n\t\t\tAvailable Hospitals:\n");
    printf("\t\t\t-------------------\n");

    int hospitalID;
    char name[50], address[100], contactNo[20];
    while (fscanf(hospital_file, "%d %s %s %s", &hospitalID, name, address, contactNo) != EOF) {
        printf("\t\t\t%d. %s\n", hospitalID, name);
    }

    fclose(hospital_file);

    printf("\n\n\t\t\tChoose a Hospital : ");
    scanf("%d", &hospitalChoice);

    // Open the hospitals file again to retrieve the chosen hospital name
    hospital_file = fopen("hospitals.txt", "r");
    if (hospital_file == NULL) {
        printf("Error opening hospitals file.\n");
        exit(1);
    }

    while (fscanf(hospital_file, "%d %s %s %s", &hospitalID, name, address, contactNo) != EOF) {
        if (hospitalID == hospitalChoice) {
            strcpy(hospitalName, name); // Copy the chosen hospital name to hospitalName
            break;
        }
    }

    fclose(hospital_file);

    printf("\n\nPress any key to continue.........");
    getch();
    system("cls");
}


/* ***************************************************** Registration Screen ***************************************************** */ 
void registe(char hospitalName[]) {
    system("cls");

    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);

    user_file = fopen("username.txt", "a"); // Open file for usernames
    pass_file = fopen("password.txt", "a"); // Open file for passwords
    info_file = fopen(infoFileName, "a"); // Open file for user info

    // Generate a random 4-digit ID
    srand(time(NULL));
    int patientID = rand() % 9000 + 1000; // Generate a random number between 1000 and 9999

    printf("\n\n\t\t\t!!!!!!!!!!!!!! User Registration !!!!!!!!!!!!!!");

    printf("\n\n\n\n\n\t\t\t\tEnter First Name : ");
    scanf("%s", p.firstname);
    printf("\n\t\t\t\tEnter Last Name : ");
    scanf("%s", p.lastname);
    printf("\n\t\t\t\tEnter Age : ");
    scanf("%s", p.age);
    printf("\n\t\t\t\tEnter Your Gender : ");
    scanf("%s", p.gender);
    printf("\n\t\t\t\tEnter Your Contact No. : ");
    scanf("%s", p.Contactno);

    printf("\n\n\t\t\t\tEnter Username : ");
    scanf("%s", l.username);
    printf("\n\t\t\t\tEnter Password : ");
    scanf("%s", l.password);

    // Assign the generated ID to the patient
    p.patientID = patientID;

    // Write user information to info file
    fprintf(info_file, "%d %s %s %s %s %s ", p.patientID, p.firstname, p.lastname, p.age, p.gender, p.Contactno);

    // Write username to username file
    fputs(l.username, user_file);
    fputs("\n", user_file);

    // Write password to password file
    fputs(l.password, pass_file);
    fputs("\n", pass_file);

    fclose(user_file);
    fclose(pass_file);
    fclose(info_file);

    printf("\n\n\t\t\t-------------- Registration Done --------------");
    printf("\n\n\t\t\t\t  Your Patient ID: %d\n", p.patientID);
    printf("\n\t\t\t.....Please Remember your patient ID......");
    printf("\n\n\t\t\tNow login with Username and Password\n");
    printf("\n\nPress any key to continue.........");
    getch();
    system("cls");

    login(); // Uncomment if login function is defined
}

/* ***************************************************** Login Screen ***************************************************** */ 
void login()
{
    system("cls");
    char username[50], password[50];

    // Open username and password files for reading
    FILE *user_file = fopen("username.txt", "r");
    FILE *pass_file = fopen("password.txt", "r");

    Title(hospitalName); // calling title function

    printf("\n\n\t\t\t!!!!!!!!!!!!!! Login Screen !!!!!!!!!!!!!!");

    printf("\n\n\n\n\n\t\t\tUsername : ");
    scanf("%s", username);
    printf("\n\t\t\tPassword : ");
    scanf("%s", password);

    int loggedIn = 0; // Flag to track login status

    // Read each line from the username and password files and compare with input
    while (fscanf(user_file, "%s", l.username) == 1 && fscanf(pass_file, "%s", l.password)!=EOF)
    {
        printf("Comparing: %s - %s\n", l.username, l.password); // traceing output
        
        if (strcmp(username, l.username) == 0 && strcmp(password, l.password) == 0)
        {
            loggedIn = 1; // Set login status to true
            break;
        }
    }

    fclose(user_file);
    fclose(pass_file);

    if (loggedIn==1)
    {
        printf("Login Successful...\n");
        printf("\nPress any key to continue......");
        getch();
        system("cls");
        MainMenu(); //calling MainMenu function
    }
    else
    {
        printf("Please Enter correct username and password\n");
        printf("\nPress any key to continue.....");
        getch();
        system("cls");
        login(); // Retry login if credentials don't match
    }
}

/* ******************************************************* Main Menu ******************************************************* */ 
void MainMenu()
{
    system("cls");
    int choose;
    Title(hospitalName); // Again calling Title function
    printf("\n\n\t\t\t!!!!!!!!!!!!!! Main Menue !!!!!!!!!!!!!!");

    printf("\n\n\n\n\n\t\t\t\t1. Detect Diseas\n");
    printf("\n\t\t\t\t2. Generate Prescription\n");
    printf("\n\t\t\t\t3. See Your Records\n");
    printf("\n\t\t\t\t4. Manage Patient (Admin Only)\n");
    printf("\n\t\t\t\t5. Available Resources\n");
    printf("\n\t\t\t\t6. Exit\n");

    M:
    printf("\nEnter your choice : ");
    getch();
    scanf("%d",&choose);
    switch(choose)
    {
        case 1:
            detectDisease(hospitalName);
            break;
        case 2:
            generatePrescription(hospitalName);
            break;
        case 3:
            seeyourrecord(hospitalName);
            break;
        case 4:
            managepatient();
            break;
        case 5:
            resourceAllocation();
            break;
        case 6:
            printf("\n\n\t\t\tExiting the program......\n");
            return;
            break;
        default:
            printf("\n\n\n\n\n\t\t\tInvalid Choice !!!");
            goto M;
    }
}

/* ***************************************************** Detect Disease ***************************************************** */ 
void detectDisease(char hospitalName[]) {
    system("cls");
    Title(hospitalName);
    printf("\n\n\t\t\t!!!!!!!!!!! Detect Disease !!!!!!!!!!!\n");
    float temperature, bloodSugarLevel, systolicBP, diastolicBP;
    char detectedDisease[200] = ""; // Initialize as empty string

    // Open file in append mode
    FILE *info_file;
    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);
    info_file = fopen(infoFileName, "a"); // Open file for user information

    printf("\n\n\t\t\t\tEnter your body temperature : ");
    scanf("%f", &temperature);

    printf("\n\t\t\t\tEnter your blood sugar level in mg/dL: ");
    scanf("%f", &bloodSugarLevel);

    printf("\n\t\t\t\tEnter your systolic blood pressure: ");
    scanf("%f", &systolicBP);

    printf("\n\t\t\t\tEnter your diastolic blood pressure: ");
    scanf("%f", &diastolicBP);

    // Check for each specific combination and assign to detectedDisease
    if (temperature > 98 && bloodSugarLevel >= 126 && systolicBP >= 140 && diastolicBP >= 90) 
    {
        strcpy(detectedDisease, "Fever,Diabetes,H.BP");
    } 
    else if (temperature > 98 && bloodSugarLevel >= 126 && systolicBP < 90 && diastolicBP < 60) 
    {
        strcpy(detectedDisease, "Fever,Diabetes,L.BP");
    } 
    else if (temperature > 98 && bloodSugarLevel >= 126 && systolicBP >= 140) 
    {
        strcpy(detectedDisease, "Fever,Diabetes");
    } 
    else if (temperature > 98 && bloodSugarLevel >= 126) 
    {
        strcpy(detectedDisease, "Fever,Diabetes");
    } 
    else if (temperature > 98 && systolicBP >= 140) 
    {
        strcpy(detectedDisease, "Fever,H.BP");
    } 
    else if (temperature > 98 && diastolicBP >= 90) 
    {
        strcpy(detectedDisease, "Fever,H.BP");
    } 
    else if (bloodSugarLevel >= 126 && systolicBP >= 140) 
    {
        strcpy(detectedDisease, "Diabetes,H.BP");
    } 
    else if (bloodSugarLevel >= 126 && diastolicBP >= 90) 
    {
        strcpy(detectedDisease, "Diabetes,H.BP");
    } 
    else if (systolicBP < 90 && diastolicBP < 60) 
    {
        strcpy(detectedDisease, "L.BP");
    } 
    else if (temperature > 98 && bloodSugarLevel >= 126) 
    {
        strcpy(detectedDisease, "Fever,Diabetes");
    } 
    else if (temperature > 98) 
    {
        strcpy(detectedDisease, "Fever");
    } 
    else if (bloodSugarLevel >= 126) 
    {
        strcpy(detectedDisease, "Diabetes");
    } 
    else if (systolicBP >= 140 && diastolicBP >= 90) 
    {
        strcpy(detectedDisease, "H.BP");
    } 
    else if (systolicBP < 90 && diastolicBP < 60) 
    {
        strcpy(detectedDisease, "L.BP");
    } 
    else 
    {
        strcpy(detectedDisease, "Nothing");
    }

    // Print detected diseases
    printf("\n\n\t\t\tDisease(s) detected: %s\n", detectedDisease);

    // Write to the file
    fprintf(info_file, "%s", detectedDisease);
    fclose(info_file);

    printf("\n\n\t\t\t\tReturning to Main Menu...");
    getch();
    MainMenu();
}

/* ***************************************************** Generate Prescription ***************************************************** */
void generatePrescription(char hospitalName[]) {
    int patientid;
    time_t rawtime;
    struct tm *info;
    system("cls");
    Title(hospitalName);

    printf("\n\n\t\t\t!!!!!!!!!!! Generate Prescription !!!!!!!!!!!\n");
    char ans;
    printf("\n\n\t\t\t\tHave you Detected your disease? [y/n]: ");
    scanf(" %c", &ans);

    if (ans == 'n' || ans == 'N') {
        printf("\nPlease detect disease before generating prescription.");
        printf("\nReturning to Main Menu...");
        getch();
        MainMenu();
        return;
    }

    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);

    FILE *info_file;
    info_file = fopen(infoFileName, "r");

    if (info_file == NULL) {
        printf("\nError opening file!");
        printf("\nReturning to Main Menu...");
        getch();
        MainMenu();
        return;
    }

    // Get current time
    time(&rawtime);
    info = localtime(&rawtime);

    // Add 7 days to the current time
    rawtime += 7 * 24 * 60 * 60;
    info = localtime(&rawtime);

    char date[50];
    strftime(date, 11, "%d-%m-%y", info); // Updated format specifier to "d-m-y"

    fprintf(info_file, " %s\n", date);

    // Get patient id
    printf("\n\n\t\t\t\tEnter Your Patient ID : ");
    scanf("%d", &patientid);
    fflush(stdin);

    while(fscanf(info_file,"%d %s %s %s %s %s %s %s\n", &p.patientID, p.firstname, p.lastname, p.age, p.gender, p.Contactno, p.disease,p.date) != EOF) {
        // Compare the entered patient ID with the patient ID in the file
        if (p.patientID == patientid) {
            // Print the prescription
            printf("\n");
            printf("______________________________________________________________________________________________\n");
            printf("                             Rural Health Monitoring System          \n");
            printf("\n");
            printf("       Phone : +91 987655432                            Email : health@monitoring.com\n");
            printf("______________________________________________________________________________________________\n");
            printf("               Patient Details  for id : %d\n", p.patientID);
            printf("       Name : %s %s                     Age : %s\n", p.firstname, p.lastname, p.age);
            printf("       Gender : %s                      Contact No. : %s\n", p.gender, p.Contactno);
            printf("______________________________________________________________________________________________\n");
            printf("           About illness : ");

            // Convert disease string to uppercase
            char uppercase_disease[50];
            strcpy(uppercase_disease, p.disease); // Copy p.disease to uppercase_disease
            for (int i = 0; uppercase_disease[i]; i++) {
                uppercase_disease[i] = toupper(uppercase_disease[i]); // Convert each character to uppercase
            }
            // Compare uppercase disease with uppercase "FEVER" and "DIABETES"
            
            if (strcmp(uppercase_disease, "FEVER,DIABETES") == 0) {
                printf("Fever & Diabetes\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Cough syrup\n\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Soup\n");
                printf("                - Fruits\n\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n\n");
                printf("         Note : Monitor body temperature & blood sugar regularly\n");
            } else if (strcmp(uppercase_disease, "FEVER,H.BP") == 0) {
                printf("Fever & High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Low sodium foods\n");
                printf("                - Fruits\n\n");
                printf("         Note : Monitor blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "FEVER,L.BP") == 0) {
                printf("Fever & Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Salty foods\n");
                printf("                - Fluids\n\n");
                printf("         Note : Increase fluid intake\n");
            } else if (strcmp(uppercase_disease, "DIABETES,H.BP") == 0) {
                printf("Diabetes & High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Low sodium foods\n\n");
                printf("         Note : Monitor blood sugar & blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "DIABETES,L.BP") == 0) {
                printf("Diabetes & Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Salty foods\n\n");
                printf("         Note : Monitor blood sugar & increase fluid intake\n");
            } else if (strcmp(uppercase_disease, "FEVER,DIABETES,,H.BP") == 0) {
                printf("Fever, Diabetes & High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Cough syrup\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Soup\n");
                printf("                - Fruits\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n\n");
                printf("         Note : Monitor body temperature, blood sugar & blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "FEVER,DIABETES,L.BP") == 0) {
                printf("Fever, Diabetes & Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Cough syrup\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Soup\n");
                printf("                - Fruits\n");
                printf("                - High fiber foods\n");
                printf("                - Salty foods\n\n");
                printf("         Note : Monitor body temperature, blood sugar & increase fluid intake\n");
            } else if (strcmp(uppercase_disease, "DIABETES,,H.BP") == 0) {
                printf("Diabetes & High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n");
                printf("                - Low sodium foods\n\n");
                printf("         Note : Monitor blood sugar & blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "DIABETES,L.BP") == 0) {
                printf("Diabetes & Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n");
                printf("                - Salty foods\n\n");
                printf("         Note : Monitor blood sugar & increase fluid intake\n");
            } else if (strcmp(uppercase_disease, "FEVER,,H.BP") == 0) {
                printf("Fever & High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Soup\n");
                printf("                - Fruits\n");
                printf("                - Low sodium foods\n\n");
                printf("         Note : Monitor body temperature & blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "FEVER,L.BP") == 0) {
                printf("Fever & Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Soup\n");
                printf("                - Fruits\n");
                printf("                - Salty foods\n\n");
                printf("         Note : Monitor body temperature & increase fluid intake\n");
            } else if (strcmp(uppercase_disease, "DIABETES,,H.BP") == 0) {
                printf("Diabetes & High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n");
                printf("                - Low sodium foods\n\n");
                printf("         Note : Monitor blood sugar & blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "DIABETES,L.BP") == 0) {
                printf("Diabetes & Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n");
                printf("                - Salty foods\n\n");
                printf("         Note : Monitor blood sugar & increase fluid intake\n");
            } else if (strcmp(uppercase_disease, "FEVER") == 0) {
                printf("Fever\n\n");
                printf("         Medicines Given :\n");
                printf("                - Paracetamol\n");
                printf("                - Cough syrup\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Soup\n");
                printf("                - Fruits\n\n");
                printf("         Note : Take plenty of rest\n");
            } else if (strcmp(uppercase_disease, "DIABETES") == 0) {
                printf("Diabetes\n\n");
                printf("         Medicines Given :\n");
                printf("                - Insulin\n");
                printf("                - Metformin\n\n");
                printf("         Foods to Eat :\n");
                printf("                - High fiber foods\n");
                printf("                - Non-starchy vegetables\n\n");
                printf("         Note : Monitor blood sugar regularly\n");
            } else if (strcmp(uppercase_disease, "H.BP") == 0) {
                printf("High Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Antihypertensive medication\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Low sodium foods\n");
                printf("                - Fruits\n\n");
                printf("         Note : Monitor blood pressure regularly\n");
            } else if (strcmp(uppercase_disease, "L.BP") == 0) {
                printf("Low Blood Pressure\n\n");
                printf("         Medicines Given :\n");
                printf("                - Rehydration solution\n\n");
                printf("         Foods to Eat :\n");
                printf("                - Salty foods\n");
                printf("                - Fluids\n\n");
                printf("         Note : Increase fluid intake\n");
            } else {
                printf("            No specific prescription available for detected disease.\n\n");
            }
            printf(" Next visit : %s\n",date);
            printf("                               ~~~~ Get Well Soon ~~~~\n");
            printf("______________________________________________________________________________________________\n");

            //notification system
            char filename[100];
            sprintf(filename, "%s_%s_notification.txt", p.firstname, p.lastname);
            FILE *notification_file = fopen(filename, "w");
            if (notification_file != NULL) {
                // Print notification message to file
                fprintf(notification_file, "Dear %s %s, your next visit is on %s.\n", p.firstname, p.lastname, date);
                fclose(notification_file);
                printf("\nNotification file created for %s %s.\n", p.firstname, p.lastname);
            } else {
                printf("\nFailed to create notification file for %s %s.\n", p.firstname, p.lastname);
            }
            break;
        }
    }

    if (p.patientID != patientid) {
        printf("\n\n\t\t\tRecord not found !!");
        fclose(info_file);
        getch();
    }

    // Close the file
    fclose(info_file);

    info_file = fopen(infoFileName, "a");
    fprintf(info_file, " %s\n", date);

    fclose(info_file);

    printf("Returning to Main Menu...");
    getch();
    MainMenu();
}

/* ***************************************************** See Your Record ***************************************************** */ 
void seeyourrecord(char hospitalName[])
{
    int patientid;
    system("cls");
    Title(hospitalName);

    FILE *info_file;
    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);
    info_file = fopen(infoFileName, "r");

    printf("\n\n\t\t\t!!!!!!!!!!! Search Record !!!!!!!!!!!\n");
    gotoxy(12, 8);
    printf("\n\n\t\t\t\tEnter Patient ID : ");
    scanf("%d",&patientid);
    fflush(stdin);
    
    while(fscanf(info_file,"%d %s %s %s %s %s %s %s\n",&p.patientID,p.firstname,p.lastname,p.age,p.gender,p.Contactno,p.disease,p.date)!=EOF)
    {
        if(p.patientID == patientid)
        {
            gotoxy(1, 15);
            printf("ID ");
            gotoxy(10, 15);
            printf("Full Name");
            gotoxy(35, 15);
            printf("Age");
            gotoxy(45, 15);
            printf("Gender");
            gotoxy(55, 15);
            printf("Contact No.");
            gotoxy(70, 15);
            printf("Disease");
            gotoxy(90, 15);
            printf("Next Visit\n");
            printf("========================================================================================================\n");
            gotoxy(1, 17);
            printf("%d",p.patientID);
            gotoxy(10, 17);
            printf("%s %s",p.firstname,p.lastname);
            gotoxy(35, 17);
            printf("%s",p.age);
            gotoxy(45, 17);
            printf("%s",p.gender);
            gotoxy(55, 17);
            printf("%s",p.Contactno);
            gotoxy(70, 17);
            printf("%s",p.disease);
            gotoxy(90, 17);
            printf("%s", p.date);
            break;
        }
    }
    if(p.patientID != patientid)
    {
        gotoxy(5, 10);
        printf("\n\n\t\t\t\t   Record not found !!");
        getch();
    }
    fclose(info_file);
    S:
    printf("\n\n\n\t\t\t\tDo you want to view more[Y / N] : ");
    getch();
    char ans;
    scanf("%c", &ans);
    if(toupper(ans)=='Y' || ans == 'Y')
    {
        searchrecord(hospitalName);
    }
    else if(toupper(ans)=='N' || ans == 'N')
    {
        printf("\n\n\t\t\t\t!!!!!!!!!!! Thank You !!!!!!!!!!!\n");
        printf("\n\nReturning to Main Menu...");
        getch();
        MainMenu();
    }
    else
    {
        printf("\n\t\t\t\t\tInvalid input\n");
        goto S;
    }

}

/* ***************************************************** Manage Patient ***************************************************** */ 
void managepatient()
{
    system("cls");
    Title(hospitalName); // calling Title Function
    printf("\n\n\t\t\t!!!!!!!!!!!!!! Patient Management !!!!!!!!!!!!!!");
    int cho;
    printf("\n\n\n\n\n\t\t\t\t1. Add Patient Record");
    printf("\n\n\t\t\t\t2. View Patient Lis");
    printf("\n\n\t\t\t\t3. Search Patient Record");
    printf("\n\n\t\t\t\t4. Return to Main Menue\n");

    M:
    printf("Enter your choice : ");
    scanf("%d", &cho);
    switch(cho)
    {
    
        case 1:
            Addrecord(hospitalName);
            break;
        case 2:
            viewlist(hospitalName);
            break;
        case 3:
            searchrecord(hospitalName);
            break;
        case 4:
            MainMenu();
            break;
        default:
            printf("Invalid Choice.......\n\n");
            goto M;
            break;
    }
}

/* ***************************************************** Add record ***************************************************** */ 
void Addrecord(char hospitalName[]) {
    system("cls");
    Title(hospitalName);

    // Open file in append mode
    FILE *info_file;
    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);
    info_file = fopen(infoFileName, "a"); // Open file for user information

    printf("\n\n\t\t\t!!!!!!!!!!!!!! Add Patient Record !!!!!!!!!!!!!!");

    // Generate a random 4-digit ID
    srand(time(NULL));
    int patientID = rand() % 9000 + 1000; // Generate a random number between 1000 and 9999

    printf("\n\n\n\n\n\t\t\t\tEnter First Name : ");
    scanf("%s", p.firstname);
    printf("\n\t\t\t\tEnter last Name : ");
    scanf("%s", p.lastname);
    printf("\n\t\t\t\tEnter Age : ");
    scanf("%s", p.age);
    printf("\n\t\t\t\tEnter Your Gender : ");
    scanf("%s", p.gender);
    printf("\n\t\t\t\tEnter Your Contact No. : ");
    scanf("%s", p.Contactno);
    printf("\n\t\t\t\tDisease : ");
    printf("\n\t\t\t\t1.Fever\n\t\t\t\t2.Diabetes\n\t\t\t\t3.Fever,Diabetes");
    printf("\n\t\t\t\tEnter Your Disease Name : ");
    scanf("%s", p.disease);
    printf("\n\t\t\t\tEnter Next visit date (d-m-y) : ");
    scanf("%s", p.date);

    // Assign the generated ID to the patient
    p.patientID = patientID;

    // Write user information to info file
    fprintf(info_file, "%d %s %s %s %s %s %s %s\n", p.patientID, p.firstname, p.lastname, p.age, p.gender, p.Contactno,p.disease,p.date);
    // Print the patient ID
    printf("\n\n\t\t\t\t\t\t  Your Patient ID: %d\n", p.patientID);
    printf("n\n\t\t\t\t\t.....Please Remember your patient ID......");
    printf("\n\n\t\t\t\t.... Information Record Successful ....");

    fclose(info_file);

    S:
    printf("\n\n\n\t\t\t\tDo you want to add more[Y / N] : ");
    getch();
    char ans;
    scanf("%c", &ans);
    if(toupper(ans)=='Y' || ans == 'Y')
    {
        Addrecord(hospitalName);
    }
    else if(toupper(ans)=='N' || ans == 'N')
    {
        printf("\n\n\t\t\t!!!!!!!!!!! Thank You !!!!!!!!!!!\n");
        printf("\n\nReturning to Manage Patient...");
        getch();
        managepatient();
    }
    else
    {
        printf("\n\t\t\t\t\tInvalid input\n");
        goto S;
    }
}

/* ***************************************************** View list ***************************************************** */ 
void viewlist(char hospitalName[]) {
    int row;
    system("cls");
    Title(hospitalName);

    FILE *info_file;
    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);
    info_file = fopen(infoFileName, "r");

    printf("\n\n\t\t\t!!!!!!!!!!!!!! List Patient Record !!!!!!!!!!!!!!");
    gotoxy(1, 15);
    printf("ID ");
    gotoxy(10, 15);
    printf("Full Name");
    gotoxy(35, 15);
    printf("Age");
    gotoxy(45, 15);
    printf("Gender");
    gotoxy(55, 15);
    printf("Contact No.");
    gotoxy(70, 15);
    printf("Disease\n");
    gotoxy(90, 15);
    printf("Next visit\n");

    printf("========================================================================================================\n");
    row = 17;

    while(fscanf(info_file,"%d %s %s %s %s %s %s %s\n",&p.patientID,p.firstname,p.lastname,p.age,p.gender,p.Contactno,p.disease,p.date)!=EOF)
    {
        gotoxy(1, row);
        printf("%d",p.patientID);
        gotoxy(10, row);
        printf("%s %s",p.firstname,p.lastname);
        gotoxy(35, row);
        printf("%s",p.age);
        gotoxy(45, row);
        printf("%s",p.gender);
        gotoxy(55, row);
        printf("%s",p.Contactno);
        gotoxy(70, row);
        printf("%s",p.disease);
        gotoxy(90, row);
        printf("%s", p.date);

        row++;
    }
    fclose(info_file);
    printf("\n\n\nPress any key to continue.......");
    getch();
    managepatient();
}

/* ***************************************************** Search record ***************************************************** */ 
void searchrecord(char hospitalName[]) {
    int patientid;
    system("cls");
    Title(hospitalName);

    FILE *info_file;
    char infoFileName[100];
    sprintf(infoFileName, "%s_information.txt", hospitalName);
    info_file = fopen(infoFileName, "r");

    printf("\n\n\t\t\t!!!!!!!!!!! Search Record !!!!!!!!!!!\n");
    gotoxy(12, 8);
    printf("\n\n\t\t\t\tEnter Patient ID : ");
    scanf("%d",&patientid);
    fflush(stdin);
    
    while(fscanf(info_file,"%d %s %s %s %s %s %s %s\n",&p.patientID,p.firstname,p.lastname,p.age,p.gender,p.Contactno,p.disease,p.date)!=EOF)
    {
        if(p.patientID == patientid)
        {
            gotoxy(1, 15);
            printf("ID ");
            gotoxy(10, 15);
            printf("Full Name");
            gotoxy(35, 15);
            printf("Age");
            gotoxy(45, 15);
            printf("Gender");
            gotoxy(55, 15);
            printf("Contact No.");
            gotoxy(70, 15);
            printf("Disease");
            gotoxy(90, 15);
            printf("Next Visit\n");
            printf("========================================================================================================\n");
            gotoxy(1, 17);
            printf("%d",p.patientID);
            gotoxy(10, 17);
            printf("%s %s",p.firstname,p.lastname);
            gotoxy(35, 17);
            printf("%s",p.age);
            gotoxy(45, 17);
            printf("%s",p.gender);
            gotoxy(55, 17);
            printf("%s",p.Contactno);
            gotoxy(70, 17);
            printf("%s",p.disease);
            gotoxy(90, 17);
            printf("%s", p.date);
            break;
        }
    }
    if(p.patientID != patientid)
    {
        gotoxy(5, 10);
        printf("\n\n\t\t\t\t   Record not found !!");
    }
    fclose(info_file);
    S:
    printf("\n\n\n\t\t\t\tDo you want to view more[Y / N] : ");
    getch();
    char ans;
    scanf("%c", &ans);
    if(toupper(ans)=='Y' || ans == 'Y')
    {
        searchrecord(hospitalName);
    }
    else if(toupper(ans)=='N' || ans == 'N')
    {
        printf("\n\n\t\t\t\t!!!!!!!!!!! Thank You !!!!!!!!!!!\n");
        printf("\n\nReturning to Manage Patient...");
        getch();
        managepatient();
    }
    else
    {
        printf("\n\t\t\t\t\tInvalid input\n");
        goto S;
    }
}

/* ***************************************************** Available Resources ***************************************************** */ 
void resourceAllocation()
{
    system("cls");
    Title(hospitalName); // calling Title Function
    printf("\n\n\t\t\t!!!!!!!!!!!!!! Available Resources !!!!!!!!!!!!!!");
    int cho;
    printf("\n\n\n\n\n\t\t\t\t1. Add Doctor");
    printf("\n\n\t\t\t\t2. View List of Doctors");
    printf("\n\n\t\t\t\t3. Other Resources");
    printf("\n\n\t\t\t\t4. Return to Main Menue\n");

    M:
    printf("Enter your choice : ");
    scanf("%d", &cho);
    switch(cho)
    {
    
        case 1:
            addDoctor();
            break;
        case 2:
            viewDoctors();
            break;
        case 3:
            otherResources();
            break;
        case 4:
            MainMenu();
            break;
        default:
            printf("Invalid Choice.......\n\n");
            goto M;
            break;
    }
}

/* ***************************************************** add doctor ***************************************************** */ 
void addDoctor() {

    system("cls");
    Title(hospitalName);// Print the title
    doctorFile = fopen("doctors.txt", "a");
    if (doctorFile == NULL) {
        printf("Error opening file!");
        exit(1);
    }

    printf("\n\n\n\t\t\t\tEnter Doctor Name: ");
    scanf("%s", d.name);
    printf("\n\n\t\t\t\tEnter Doctor Specialty: ");
    scanf("%s", d.specialization);
    printf("\n\n\t\t\t\tEnter Doctor Phone: ");
    scanf("%s", d.contact);

    fprintf(doctorFile, "%s %s %s\n", d.name, d.specialization, d.contact);
    fclose(doctorFile);

    printf("\n\t\t\tDoctor details added successfully!\n");

    S:
    printf("\n\n\n\t\t\t\tDo you want to add more[Y / N] : ");
    getch();
    char ans;
    scanf("%c", &ans);
    if(toupper(ans)=='Y' || ans == 'Y')
    {
        addDoctor();
    }
    else if(toupper(ans)=='N' || ans == 'N')
    {
        printf("\n\n\t\t\t!!!!!!!!!!! Thank You !!!!!!!!!!!\n");
        printf("\n\nPress Any Key to continue.....");
        getch();
        resourceAllocation();
    }
    else
    {
        printf("\n\t\t\t\t\tInvalid input\n");
        goto S;
    }
}


/* ***************************************************** doctor list ***************************************************** */ 
void viewDoctors() {
    system("cls");
    Title(hospitalName); // Print the title

    // Open the file containing doctors' information in read mode
    FILE *doctorFile = fopen("doctors.txt", "r");
    if (doctorFile == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\n\n\t\t\t!!!!!!!!!!!!!! List of Doctors !!!!!!!!!!!!!!");

    gotoxy(1, 15);
    printf("Name ");
    gotoxy(20, 15);
    printf("Specialization ");
    gotoxy(40, 15);
    printf("Contact\n");

    printf("========================================================================================================\n");
    int row = 17;

    // Read and print each doctor's information from the file
    while (fscanf(doctorFile, "%s %s %s\n", d.name, d.specialization, d.contact) == 3) {
        gotoxy(1, row);
        printf("Dr. %s", d.name);
        gotoxy(20, row);
        printf("%s", d.specialization);
        gotoxy(40, row);
        printf("%s\n", d.contact);
        row++;
    }

    // Close the file
    fclose(doctorFile);

    printf("\n\nPress any key to continue.......");
    getch();
    resourceAllocation(); // Return to main menu
}


/* ***************************************************** Other Resources ***************************************************** */
void otherResources() {
    system("cls");
    Title(hospitalName);// Print the title
    // Simulated total counts of doctors and rooms in the hospital
    int totalDoctors = 15;
    int totalGeneralRooms = 50;
    int totalVipRooms = 10;
    int totalOT = 5;

    printf("\n\n\t\t\tTotal available resources :\n");
    printf("\n\t\t\t- Total available doctors: %d\n", totalDoctors);
    printf("\n\t\t\t- Total available general rooms: %d\n", totalGeneralRooms);
    printf("\n\t\t\t- Total available VIP rooms: %d\n\n", totalVipRooms);
    printf("\n\t\t\t- Total Operation Theater : %d", totalOT);

    char disease[50];
    printf("\n\n\t\t\t\tEnter patient's disease: ");
    scanf("%s", disease);

    char uppercase_disease[50];
        strcpy(uppercase_disease, disease); // Copy disease to uppercase_disease
        for (int i = 0; uppercase_disease[i]; i++) {
            uppercase_disease[i] = toupper(uppercase_disease[i]); // Convert each character to uppercase
        }
    if (strcmp(uppercase_disease, "FEVER") == 0) {
        r.doctors = 3;
        r.generalRooms = 5;
        r.vipRooms = 1;
    } else if (strcmp(uppercase_disease, "DIABETES") == 0) {
        r.doctors = 2;
        r.generalRooms = 6;
        r.vipRooms = 2;
    } else if (strcmp(uppercase_disease, "H.BP") == 0) {
        r.doctors = 4;
        r.generalRooms = 7;
        r.vipRooms = 3;
    }else if (strcmp(uppercase_disease, "H.BP") == 0) {
        r.doctors = 4;
        r.generalRooms = 5;
        r.vipRooms = 3;
    }else {
        printf("No resources available for the specified disease.\n");
        return;
    }

    printf("\n\n\t\t\tResources for patient's disease (%s):\n", disease);
    printf("\n\t\t\t- Available doctors: %d\n", r.doctors);
    printf("\n\t\t\t- Available general rooms: %d\n", r.generalRooms);
    printf("\n\t\t\t- Available VIP rooms: %d\n", r.vipRooms);
}
