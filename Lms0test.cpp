#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "book.h"
#include "student.h"

TEST_CASE("Book Class Test Cases", "[book]") {
    SECTION("Create Book") {
        book testBook;
        testBook.createbook();
        REQUIRE(strlen(testBook.retbno()) == 5); 
    }

    SECTION("Show Book") {
        book testBook;
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        testBook.showbook();

        std::cout.rdbuf(old);
        REQUIRE(buffer.str().find("Book Number") != std::string::npos);
    }

    SECTION("Modify Book") {
        book testBook;
        strcpy(testBook.retbno(), "12345");
        testBook.modifybook();
        REQUIRE(strcmp(testBook.retbno(), "12345") != 0);
    }
}

TEST_CASE("Student Class Test Cases", "[student]") {
    SECTION("Create Student") {
        student testStudent;
        testStudent.createstudent();
        REQUIRE(strlen(testStudent.retadmno()) == 5); 
    }

    SECTION("Show Student") {
        student testStudent;
        std::stringstream buffer;
        std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

        testStudent.showstudent();

        std::cout.rdbuf(old);
        REQUIRE(buffer.str().find("Admission Number") != std::string::npos);
    }

    SECTION("Modify Student") {
        student testStudent;
        strcpy(testStudent.retadmno(), "S12345");
        testStudent.modifystudent();
        REQUIRE(strcmp(testStudent.retadmno(), "S12345") != 0);
    }
}

TEST_CASE("Library Functions Test Cases", "[library]") {
    SECTION("Write Student") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv"); 
        REQUIRE(file.is_open());
        file.close();
        fp.open("C:/Users/yhuss/Downloads/test_books.csv", std::ios::out | std::ios::app);
        REQUIRE(fp.is_open());
        st.createstudent();
        writestudent();
        fp.close();
    }

    SECTION("Display Book") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        bk.createbook();
        file.write((char*)&bk, sizeof(book));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());
        displayspb(bk.retbno());
        fp.close();
    }

    SECTION("Display Student") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        st.createstudent();
        file.write((char*)&st, sizeof(student));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());
        displaysps(st.retadmno());
        fp.close();
    }
}

TEST_CASE("Library Modifications Test Cases", "[library][modifications]") {
    SECTION("Modify Book") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        bk.createbook();
        file.write((char*)&bk, sizeof(book));
        file.close()
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in | std::ios::out);
        REQUIRE(fp.is_open());
        modifybook();
        fp.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());

        bool bookModified = false;
        while (fp.read((char*)&bk, sizeof(book))) {
            if (strcmpi(bk.retbno(), "12345") == 0) { 
                bookModified = true;
                break;
            }
        }

        fp.close();
        REQUIRE(bookModified);
    }

    SECTION("Modify Student") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        st.createstudent();
        file.write((char*)&st, sizeof(student));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in | std::ios::out);
        REQUIRE(fp.is_open());
        modifystudent();
        fp.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());

        bool studentModified = false;
        while (fp.read((char*)&st, sizeof(student))) {
            if (strcmpi(st.retadmno(), "S12345") == 0) { 
                studentModified = true;
                break;
            }
        }

        fp.close();
        REQUIRE(studentModified);
    }
}

TEST_CASE("Library Deletion Test Cases", "[library][deletion]") {
    SECTION("Delete Student") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        st.createstudent();
        file.write((char*)&st, sizeof(student));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in | std::ios::out);
        REQUIRE(fp.is_open());
        deletestudent();
        fp.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());

        bool studentDeleted = true;
        while (fp.read((char*)&st, sizeof(student))) {
            if (strcmpi(st.retadmno(), "S12345") == 0) {
                studentDeleted = false;
                break;
            }
        }

        fp.close();
        REQUIRE(studentDeleted);
    }

    SECTION("Delete Book") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        bk.createbook();
        file.write((char*)&bk, sizeof(book));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in | std::ios::out);
        REQUIRE(fp.is_open());
        deletebook();
        fp.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());

        bool bookDeleted = true;
        while (fp.read((char*)&bk, sizeof(book))) {
            if (strcmpi(bk.retbno(), "12345") == 0) { 
                bookDeleted = false;
                break;
            }
        }

        fp.close();
        REQUIRE(bookDeleted);
    }
}


TEST_CASE("Library Operations Test Cases", "[library][operations]") {
    SECTION("Display All Students") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        st.createstudent();
        file.write((char*)&st, sizeof(student));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());
        displayalls();
        fp.close();
    }

    SECTION("Display All Books") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        bk.createbook();
        file.write((char*)&bk, sizeof(book));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in);
        REQUIRE(fp.is_open());
        displayallb();
        fp.close();
    }

    SECTION("Book Issue") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        st.createstudent();
        file.write((char*)&st, sizeof(student));
        bk.createbook();
        file.write((char*)&bk, sizeof(book));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in | std::ios::out);
        REQUIRE(fp.is_open());
        bookissue();
        fp.close();
    }

    SECTION("Book Deposit") {
        std::ofstream file("C:/Users/yhuss/Downloads/books.csv");
        REQUIRE(file.is_open());
        st.createstudent();
        st.addtoken();
        bk.createbook();
        bk.showbook();
        st.getstbno(bk.retbno());
        file.write((char*)&st, sizeof(student));
        file.write((char*)&bk, sizeof(book));
        file.close();
        fp.open("C:/Users/yhuss/Downloads/books.csv", std::ios::in | std::ios::out);
        REQUIRE(fp.is_open());
        bookdeposit();
        fp.close();
    }
}


