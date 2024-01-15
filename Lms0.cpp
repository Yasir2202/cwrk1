#include <iostream>
#include<conio.h>
#include<iomanip>
#include<string.h>
#include<fstream>

using namespace std;

// Class representing a book
class book {
    char bno[6];
    char bname[50];
    char aname[20];

public:
    // Function to create a new book entry
    void createbook() {
        cout << "\n=============NEW BOOK ENTRY=============\n";
        cout << "ENTER BOOK NO. : ";
        cin >> bno;
        cout << "ENTER BOOK NAME : ";
        gets(bname);
        cout << "ENTER AUTHOR NAME : ";
        gets(aname);
        cout << "\nBook Created..";
    }

    // Function to display book details
    void showbook() {
        cout << "\nBook Number : " << bno;
        cout << "\nBook Name : ";
        puts(bname);
        cout << "\nBook Author Name: ";
        puts(aname);
    }

    // Function to modify book details
    void modifybook() {
        cout << "\nBook Number: " << bno;
        cout << "\nModify Book Name :";
        gets(bname);
        cout << "\nModify Author's Name :";
        gets(aname);
    }

    // Function to return the book number
    char* retbno() {
        return bno;
    }

    // Function to display book details in a report format
    void report() {
        cout << bno << setw(30) << bname << setw(30) << aname << endl;
    }
};

// Class representing a student
class student {
    char admno[6];
    char name[20];
    char stbno[6];
    int token;

public:
    // Function to create a new student entry
    void createstudent() {
        cout << "\n=============NEW STUDENT ENTRY=============\n";
        cout << "\nEnter Admission No. : ";
        cin >> admno;
        cout << "Enter Student Name : ";
        gets(name);
        token = 0;
        stbno[0] = '\0';
        cout << "\n\nStudent Record Created...";
    }

    // Function to display student details
    void showstudent() {
        cout << "\nAdmission Number : " << admno;
        cout << "\nStudent Name : ";
        puts(name);
        cout << "\nNo of Book Issued : " << token;
        if (token == 1) {
            cout << "\nBook Number " << stbno;
        }
    }

    // Function to modify student details
    void modifystudent() {
        cout << "\nAdmission No. : " << admno;
        cout << "\nModify Student Name : ";
        gets(name);
    }

    // Function to return admission number
    char* retadmno() {
        return admno;
    }

    // Function to return issued book number
    char* retstbno() {
        return stbno;
    }

    // Function to return the token count
    int rettoken() {
        return token;
    }

    // Function to add a token when a book is issued to a student
    void addtoken() {
        token = 1;
    }

    // Function to reset the token count
    void resettoken() {
        token = 0;
    }

    // Function to get the issued book number
    void getstbno(char t[]) {
        strcpy(stbno, t);
    }

    // Function to display student details in a report format
    void report() {
        cout << "\t" << admno << setw(20) << name << setw(10) << token << endl;
    }
};

fstream fp, fp1;
book bk;
student st;

// Function to write book records to the file
void writebook() {
    char ch;
    // Open file in append mode
    fp.open("ghdas hjdfv hsd", ios::out | ios::app);
    do {
        // Create a new book and add to the file
        bk.createbook();
        fp.write((char*)&bk, sizeof(book));
        cout << "\n\nDo you want to add more record...(y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

// Function to write student records to the file
void writestudent() {
    char ch;
    // Open file in append mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::out | ios::app);
    do {
        // Create a new student and add to the file
        st.createstudent();
        fp.write((char*)&st, sizeof(student));
        cout << "\n\nDo you want to add more record...(y/n?) ";
        cin >> ch;
    } while (ch == 'y' || ch == 'Y');
    fp.close();
}

// Function to display book details based on book number
void displayspb(char n[]) {
    cout << "\nBOOK DETAILS\n";
    int flag = 0;
    // Open file in input mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in);
    while (fp.read((char*)&bk, sizeof(book))) {
        if (strcmpi(bk.retbno(), n) == 0) {
            // Display book details
            bk.showbook();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\nBook does not exist";
    }
    getch(); // Pauses the console
}

// Function to display student details based on admission number
void displaysps(char n[]) {
    cout << "\nSTUDENT DETAILS\n";
    int flag = 0;
    // Open file in input mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in);
    while (fp.read((char*)&st, sizeof(student))) {
        if (strcmpi(st.retadmno(), n) == 0) {
            // Display student details
            st.showstudent();
            flag = 1;
        }
    }
    fp.close();
    if (flag == 0) {
        cout << "\nStudent does not exist";
    }
    getch(); // Pauses the console
}

// Function to modify book records based on book number
void modifybook() {
    char n[6];
    int found = 0;

    cout << "\n=============MODIFY BOOK RECORD=============";
    cout << "\nEnter the book no. ";
    cin >> n;

    // Open file in input/output mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);

    while (fp.read((char*)&bk, sizeof(book)) && found == 0) {
        if (strcmpi(bk.retbno(), n) == 0) {
            // Display existing book details
            bk.showbook();

            // Modify book details
            cout << "\nEnter the new details of the book";
            bk.modifybook();

            // Move the file pointer to the position to update the record
            int pos = -1 * static_cast<int>(sizeof(bk));
            fp.seekp(pos, ios::cur);

            // Write the modified record back to the file
            fp.write((char*)&bk, sizeof(book));

            cout << "\nRecord Updated";
            found = 1;
        }
    }

    fp.close();

    if (found == 0) {
        cout << "\nRecord Not Found";
    }

    getch();
}

// Function to modify student records based on admission number
void modifystudent() {
    char n[6];
    int found = 0;

    cout << "\n=============MODIFY STUDENT RECORD=============";
    cout << "\nEnter the Admission no. : ";
    cin >> n;

    // Open file in input/output mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);

    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        if (strcmpi(st.retadmno(), n) == 0) {
            // Display existing student details
            st.showstudent();

            // Modify student details
            cout << "\nEnter the new details of the student";
            st.modifystudent();

            // Move the file pointer to the position to update the record
            int pos = -1 * static_cast<int>(sizeof(st));
            fp.seekp(pos, ios::cur);

            // Write the modified record back to the file
            fp.write((char*)&st, sizeof(student));

            cout << "\n\nRecord Updated";
            found = 1;
        }
    }

    fp.close();

    if (found == 0) {
        cout << "\nRecord Not Found";
    }

    getch();
}

// Function to delete a student record based on admission number
void deletestudent() {
    char n[6];
    int flag = 0;

    cout << "\n=============REMOVE STUDENT=============";
    cout << "\nEnter the Admission no. : ";
    cin >> n;

    // Open file in input/output mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);

    fstream fp2;
    fp2.open("temp.dat", ios::out);

    // Move the file pointer to the beginning
    fp.seekg(0, ios::beg);

    while (fp.read((char*)&st, sizeof(student))) {
        if (strcmpi(st.retadmno(), n) != 0) {
            // Write the student record to a temporary file
            fp2.write((char*)&st, sizeof(student));
        } else {
            flag = 1; // Student record found
        }
    }

    fp2.close();
    fp.close();

    // Remove the original file
    remove("C:/Users/yhuss/Downloads/books.csv");

    // Rename the temporary file to the original file
    rename("temp.dat", "student.dat");

    if (flag == 1) {
        cout << "\nRecord Deleted..";
    } else {
        cout << "\nRecord not Found";
    }

    getch();
}

 // Function to delete a book record based on book number
void deletebook() {
    char n[6];
    int flag = 0;

    cout << "\n=============DELETE BOOK=============";
    cout << "\nEnter the Book no : ";
    cin >> n;

    // Open file in input/output mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);

    fstream fp2;
    fp2.open("Temp.dat", ios::out);

    // Move the file pointer to the beginning
    fp.seekg(0, ios::beg);

    while (fp.read((char*)&bk, sizeof(book))) {
        if (strcmpi(bk.retbno(), n) != 0) {
            // Write the book record to a temporary file
            fp2.write((char*)&bk, sizeof(book));
        } else {
            flag = 1;
        }
    } 

    fp2.close();
    fp.close();

    // Remove the original file
    remove("C:/Users/yhuss/Downloads/books.csv");

    // Rename the temporary file to the original file
    rename("Temp.dat", "book.dat");

    if (flag == 1) {
        cout << "\nRecord Deleted... ";
    } else {
        cout << "\nRecord not Found"; 
    }

    getch();
}

// Function to display all student records
void displayalls() {
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in);

    if (!fp) {
        cout << "File Could Not Be Open";
        getch();
        return;
    }

    cout << "\n\n\t\tStudent List\n\n";
    cout << "==================================================================\n";
    cout << "\tAdmission No." << setw(10) << "Name" << setw(20) << "Book Issued\n";
    cout << "==================================================================\n";

    while (fp.read((char*)&st, sizeof(student))) {
        st.report();
    }

    fp.close();
    getch();
}

// Function to display all book records
void displayallb() {
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in);

    if (!fp) {
        cout << "File Could Not Be Open";
        getch();
        return;
    }

    cout << "\n\n\t\tBook List\n\n";
    cout << "==================================================================\n";
    cout << "\tBook No." << setw(20) << "Book Name" << setw(25) << "Book Author\n";
    cout << "==================================================================\n";

    while (fp.read((char*)&bk, sizeof(book))) {
        bk.report();
    }

    fp.close();
    getch();
}

// Function to issue a book to a student
void bookissue() {
    char sn[6], bn[6]; // Variables to store student admission number and book number
    int found = 0, flag = 0; // Flags to track student and book existence

    cout << "\n\nBOOK ISSUE...";
    cout << "\n\n\tEnter Admission no.";
    cin >> sn;

    // Open student file in input/output mode
    fp.open("C:/Users/yhuss/Downloads/books.csvt", ios::in | ios::out);
    // Open book file in input/output mode
    fp1.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);

    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        // Check if student admission number exists
        if (strcmpi(st.retadmno(), sn) == 0) {
            found = 1;

            // Check if the student has not issued a book already
            if (st.rettoken() == 0) {
                cout << "\n\n\tEnter The Book No.";
                cin >> bn;

                while (fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    // Check if the book number exists
                    if (strcmpi(bk.retbno(), bn) == 0) {
                        flag = 1;

                        // Update student token and book details
                        st.addtoken();
                        st.getstbno(bk.retbno());

                        // Move the file pointer to the position to update the record
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekg(pos, ios::cur);
                        // Write the modified student record back to the file
                        fp.write((char*)&st, sizeof(student));

                        cout << "\n\n\tBook Issued Successfully\n Please Note Return Book Within 3 Days, Otherwise Fine Of 1 Euro Per Day";
                    }
                }

                // Check if the book number does not exist
                if (flag == 0) {
                    cout << "Book No. Does Not Exist";
                }
            } else {
                cout << "You Have Not Returned The Last Book";
            }
        }
    }

    // If student record is not found
    if (found == 0) {
        cout << "Student Record Not Exists...";
    }

    getch(); // Pauses the console
    fp.close();
    fp1.close();
}

// Function to handle book deposit
void bookdeposit() {
    char sn[6], bn[6]; // Variables to store student admission number and book number
    int found = 0, flag = 0, day, fine; // Flags to track student and book existence, and variables for days and fine

    cout << "\n\nBOOK DEPOSIT...";
    cout << "\n\n\tEnter Admission no. Of Student";
    cin >> sn;

    // Open student file in input/output mode
    fp.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);
    // Open book file in input/output mode
    fp1.open("C:/Users/yhuss/Downloads/books.csv", ios::in | ios::out);

    while (fp.read((char*)&st, sizeof(student)) && found == 0) {
        // Check if student admission number exists
        if (strcmpi(st.retadmno(), sn) == 0) {
            found = 1;

            // Check if the student has issued a book
            if (st.rettoken() == 1) {
                while (fp1.read((char*)&bk, sizeof(book)) && flag == 0) {
                    // Check if the book number matches the student's issued book
                    if (strcmpi(bk.retbno(), st.retstbno()) == 0) {
                        flag = 1;

                        // Display book details
                        bk.showbook();
                        cout << "\n\n Book Deposited In No. Of Days";
                        cin >> day;

                        // Calculate fine if the book is returned after 15 days
                        if (day > 15) {
                            fine = (day - 15) * 1;
                            cout << "\n\n Fine = " << fine;
                        }

                        // Reset student token
                        st.resettoken();

                        // Move the file pointer to the position to update the record
                        int pos = -1 * static_cast<int>(sizeof(st));
                        fp.seekg(pos, ios::cur);

                        // Write the modified student record back to the file
                        fp.write((char*)&st, sizeof(student));

                        cout << "\n\n\tBook Deposited Successfully";
                    }
                }

                // Check if the book number does not exist
                if (flag == 0) {
                    cout << "Book No. Does Not Exist";
                }
            } else {
                cout << "No Book Issued";
            }
        }
    }

    // If student record is not found
    if (found == 0) {
        cout << "Student Record Not Exists...";
    }

    getch(); // Pauses the console
    fp.close();
    fp1.close();
}

void start()
{ 
cout<<"=============LMS=============";
getch();
}
// Function to display the administrator menu and handle administrative actions
void adminmenu() {
    int ch2; // Variable to store the user's menu choice

    // Displaying the administrator menu
    cout << "\n\n\n=============ADMINISTRATOR MENU=============";
    cout << "\n\t1.CREATE STUDENT RECORD";
    cout << "\n\t2.DISPLAY ALL STUDENT RECORD";
    cout << "\n\t3.DISPLAY SPECIFIC STUDENT RECORD";
    cout << "\n\t4.MODIFY STUDENT RECORD";
    cout << "\n\t5.DELETE STUDENT RECORD";
    cout << "\n\t6.CREATE BOOK";
    cout << "\n\t7.DISPLAY ALL BOOKS";
    cout << "\n\t8.DISPLAY SPECIFIC BOOK";
    cout << "\n\t9.MODIFY BOOK RECORD";
    cout << "\n\t10.DELETE BOOK RECORD";
    cout << "\n\t11.BACK TO MAIN MENU";
    cout << "\n\tPLEASE ENTER YOUR CHOICE(1-11)";
    cin >> ch2;

    // Using a switch statement to perform actions based on user's choice
    switch (ch2) {
        case 1:
            writestudent(); // Call function to create a new student record
            break;
        case 2:
            displayalls(); // Call function to display all student records
            break;
        case 3: {
            char num[6];
            cout << "\n\n\t Please enter admission no.";
            cin >> num;
            displaysps(num); // Call function to display specific student record
            break;
        }
        case 4:
            modifystudent(); // Call function to modify a student record
            break;
        case 5:
            deletestudent(); // Call function to delete a student record
            break;
        case 6:
            writebook(); // Call function to create a new book
            break;
        case 7:
            displayallb(); // Call function to display all books
            break;
        case 8: {
            char num[6];
            cout << "\n\n\tPlease enter book no.";
            cin >> num;
            displayspb(num); // Call function to display specific book
            break;
        }
        case 9:
            modifybook(); // Call function to modify a book record
            break;
        case 10:
            deletebook(); // Call function to delete a book record
            break;
        case 11:
            return; // Return to the main menu
        default:
            cout << "Invalid choice";
    }

    adminmenu(); // Recursively call the adminmenu function to continue administrator actions
}

// Main function where the program execution begins
int main() {
    char ch; // Variable to store user's menu choice

    // Call the start function to initialize and display welcome messages
    start();

    // Main loop to display the main menu and handle user's choices
    do {
        cout << "\n\n\n=============MAIN MENU============";
        cout << "\n\t1 BOOK ISSUE";
        cout << "\n\t2 BOOK DEPOSIT";
        cout << "\n\t3 ADMINISTRATOR MENU";
        cout << "\n\t4 EXIT";
        cout << "\n\t PLEASE SELECT YOUR OPTION(1-4)";
        ch = getche(); // Read a character from the user

        // Using a switch statement to perform actions based on user's choice
        switch (ch) {
            case '1':
                bookissue(); // Call function to handle book issuing
                break;
            case '2':
                bookdeposit(); // Call function to handle book deposit
                break;
            case '3':
                adminmenu(); // Call function to display and handle the administrator menu
                break;
            case '4':
                exit(0); // Exit the program
                break;
            default:
                cout << "INVALID CHOICE";
        }

    } while (ch != '4'); // Continue the loop until the user chooses to exit

    return 0; // Return 0 to indicate successful program execution
}

