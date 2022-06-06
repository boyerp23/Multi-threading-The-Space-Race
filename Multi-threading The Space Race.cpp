// Multi-threading The Space Race.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <mutex>
#include <chrono>


using namespace std;
mutex m;
void searchIter(int* ary, int start, int search_length) {
    int ii = 0;
    for (int i = start; i < start + search_length; i++) {
        if (ary[i] == 400) {
            printf("\nfound on %d iterations", ii);
        }
        ++ii;
    }
}
void launchRokcet(int type_i) {
    if (type_i == 1) { //main launch
        m.lock();
        printf("launching rocket from Main Base on thread id: %d\n", this_thread::get_id());
        for (int i = 5; i >= 0; i--) {
            printf("countdown: %d\n", i);
        }

        this_thread::sleep_for(chrono::seconds(3)); //delay for 3 secs
        m.unlock();
    }
    else { //laaunch from launch pad
        m.lock();
        printf("Space Cadet launching rocket from Rocket Pad  on thread id: %d\n", this_thread::get_id());
        for (int i = 5; i >= 0; i--) {
            printf("countdown: %d\n", i);
        }

        this_thread::sleep_for(chrono::seconds(3)); //delay for 3 secs
        m.unlock();
    }

}
class MainSpace {
public:
    void Launch() {
        thread t1(launchRokcet, 1);
        t1.join();
    }
};

class RocketPad {

public:
    void Launch() {
        thread t1(launchRokcet, 99);
        t1.join();
    }
};
void loopFunc() {
    int n = 100;
    srand(time(0));
    int* ary = new int[n];

    for (int i = 0; i < n; i++)
    {
        ary[i] = rand() % 999;
    }

    thread t1(searchIter, ary, 0, 19);
    thread t2(searchIter, ary, 20, 39);
    thread t3(searchIter, ary, 40, 59);
    thread t4(searchIter, ary, 60, 79);
    thread t5(searchIter, ary, 80, 99);
    t5.detach();

    t1.join();
    if (t2.joinable()) {
        t2.join();
    }
    t3.join();
    t4.join();
    if (t5.joinable()) {
        t5.join();
    }
    else {
        printf("");
    }

}
void Introduction()
{
    cout << "\t\t\tWelcome to Rocket Launcher!\t\t\t\n" << endl;
    cout << "Today we are going to be launching several rockets into space to complete the new cadets\n";
    cout << "final check ride before being able to perform duties without supervison. You are the \n";
    cout << "Senior Instructor and Main Base Commander to determine whether the Cadet is ready or requires retraining.\n";
    cout << "The first rocket will be launched locally from Main Base at your command.\n";
    cout << "Once first rocket has been launched the cadet will have three seconds to launch the next 9.\n";
    cout << "On your mark 'pressing any key' rocket launches will begin!\n\n";
    system("pause");
}

/* This function will enable you the "Senior Instructor and Main Base Commander" the option to allow the cadet
to complete their final check ride in order perform flight duties by themselves. If the choice is anything other 
than 'y' program will terminate immediatly.
*/
void controlTransfer()
{    
        //stores player choice to memory
        string playerChoice;
        cout << "\n\nInitiate control Transfer to Rocket Pad Space Cadet - 'Y or N'?\n" << endl;
        //gets players choice stored in memory
        getline(cin, playerChoice);
        // if players choice equals 'yes' program will execute
        if (playerChoice == "y" or playerChoice == "Y")
        {
            cout << "Transfer confirmed.\n";
            cout << "Space Cadet is now laucnhing rockets from the Rocket Pad!\n" << endl;
            // enables the cadet to launch the next 9 rockets with a 3 second delay and countdown from 5 
            //before and after each launch
            RocketPad rp;
            for (int i = 0; i < 9; i++)
            {
                rp.Launch();
            }
        }
        // if player choice equals 'no' program will print ouput and terminate.
        else if (playerChoice == "n" or playerChoice == "N")
        {
            cout << "Sorry cadet you have not made the correct choice. Report to the Senior Instructor immediatly!\n";
        }
        // if player choice does not equal 'yes or no' than program will make user try again one more time.
        else 
        {
            cout << "\t\t\t\t *** Warning *** Warning *** Warning ***\t\t\t\t\n";
            cout << "Commander, you need to input correctly otherwise program will automatically terminate!\n";
            cout << " This will prevent further access until system reset. Please try again.\n";
            string playerChoice;
            cout << "\n\nInitiate control Transfer to Rocket Pad Space Cadet - 'Y or N'?\n" << endl;
            getline(cin, playerChoice);
            if (playerChoice == "y" or playerChoice == "Y")
            {
                cout << "Transfer confirmed.\n";
                cout << "Space Cadet is now laucnhing rockets from the Rocket Pad!\n" << endl;
                RocketPad rp;
                for (int i = 0; i < 9; i++)
                {
                    rp.Launch();
                }//end of for statement in warning
            }//end of if statement for player choice in warning
            else if (playerChoice == "n" or playerChoice == "N")
              {
                    cout << "Sorry cadet you have not made the correct choice. Report to the Senior Instructor immediatly!\n";
              }//end of if statement for player choice 'n' in warning
            
        }//end of else statement warning 
}
// used to return control back to you and the Main Base by confirming your identity. Any input data will suffice.
void returnControl()
{
    cout << "All rockets have been launched. Cadet is now transferring back launch control.\n";
    string playerName;
    string badgeNumber;
    cout << "Please enter credentials to confirm control - Name: \n";
    //asks for playerName to store to memory
    getline(cin, playerName);
    cout << "Please enter 3 digit Badge Number: \n";
    //asks for badgeNumber to store to memory
    getline(cin, badgeNumber);
    //outputs with information stored to memory
    cout << "\n\nThank you " + playerName + " " + badgeNumber + " your identity has been verified.\n";
    cout << "\t\t\t\t*** TRANSFER COMPLETE - MAIN BASE HAS CONTROL ***\t\t\t\t\n\n";
    system("pause");
   }
// you decide whether your cadet passed or failed thier final check ride.
void cdrsDecision()
{
    string playerChoice2;
    cout << "Has the cadet succesfully completed thier final check ride? (Y or N)\n";
    getline(cin, playerChoice2);
    if (playerChoice2 == "y" or playerChoice2 == "y")
    {
        cout << "Congratulations Cadet! You have successfully completed your final check ride.\n";
        cout << "You may now see the Senior Instructor for your debrief and duty assignment.\n\n";
        system("pause");
    }
    else if (playerChoice2 == "n" or playerChoice2 == "N")
    {
        cout << "Cadet you failed to meet the standards set by the Senior Instructor.\n";
        cout << "Report to the Senior Instructor for debrief and further evaluation.\n\n";
        system("pause");
    }
    else
    {
        cout << "\t\t\t\t*** Warning *** Warning *** Warning ***\t\t\t\t\n";
        cout << "Input not accepted. Try again..\n";
        string playerChoice2;
        cout << "Has the cadet succesfully completed thier final check ride? (Y or N)\n";
        if (playerChoice2 == "y" or playerChoice2 == "y")
        {
            cout << "Congratulations Cadet! You have successfully completed your final check ride.\n\n";
            cout << "You may now see the Senior Instructor for your debrief and duty assignment.";
            system("pause");
        }
        else if (playerChoice2 == "n" or playerChoice2 == "N")
        {
            cout << "Cadet you failed to meet the standards set by the Senior Instructor.\n";
            cout << "Report to the Senior Instructor for debrief and further evaluation.\n\n";
            system("pause");
        }
    }
}
//Closing remarks and end of the program
void outro()
{
    cout << "\t\t\t*** CONGRATS YOU HAVE COMPLETED THE SPACE RACE SIMULATION ***\n";
    cout << "Thanks for playing along as the Senior Instructor and choosing if your new cadet is up to\n";
    cout << "the challenge or not after their rigerous check ride. During the simulation we were able to multi-thread\n";
    cout << "and display the location of each instance (rocket) as it was launched. \n";
}
int main()
{
    Introduction();
    // When player enters a key this will print and the 1st rocket from Main Base will launch.
    cout << "Mark. First rocket from the Main Base launch\n\n" << endl;
        MainSpace ms;
        for (int i = 0; i < 1; i++)
        {
            ms.Launch();
        }
    // Will execute after first rocket launch
    controlTransfer();
    // Will ask for user input to confirm identity
    returnControl();
    cdrsDecision();
    outro();
}
// O(n^2) + O(n)
// f(x) = x^2 +x
// x dx = 2x +1
// = O(n^2)


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
