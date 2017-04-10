// Welcome to the program. The declaration of the functions and the library used is in .h file
#include "main.h"

void authInterface () {
    screenClear ();

    bannerCenBorder ("", "", "", "POS Version : 1.0");

    for ( int i = 3; i > 0; i-- )
        bannerBlankBorder ();

    bannerBlankBorderTextCen ("Please type in your username / Scan the Personnel token code");
    for ( int i = 0; i < 27; i++ )
        bannerBlankBorder ();
    bannerFullBorder ();

    char username[MAX_LNG_TOKEN]; // Copy data to SESSION struct;
    bannerUserInput ();
    scanf (" %[^\n]", username); // Then save to session struct

    // First Check the Token ID
    if(authenticateByToken(username)){
        authInterfaceComplete ();
    }
    // If token is invalid then ask the password (Identify as Normal Login)
    screenClear ();

    bannerCenBorder ("", "", "", "POS Version : 1.0");

    for ( int i = 3; i > 0; i-- )
        bannerBlankBorder ();

    char text[137];
    sprintf (text, "Welcome back %s!", username);
    bannerBlankBorderTextCen (text);
    bannerBlankBorder ();
    bannerBlankBorderTextCen ("And your password is?");

    for ( int i = 0; i < 24; i++ )
        bannerBlankBorder ();

    bannerBlankBorderTextCen ("Please type in your password");
    bannerFullBorder ();
    bannerUserInput ();

    char password[130];
    scanf ("%s", password);

    // If the username and the password is matched from the database -> Call authInterfaceComplete();
    // If the username and the password is not matched from the database -> Call authInterfaceFail();
    // If these were interrupt -> Call authInterfaceError();

    if ( authenticateByUsername (username, password) == 1 ) {
        authInterfaceComplete ();
    } else if ( authenticateByUsername (username, password) == 0 ) {
        authInterfaceFail ();
    } else {
        authInterfaceError ();
    }

    // In case of BETA TEST only     Calling -> authInterfaceComplete ();
}

void authInterfaceComplete () {
    screenClear ();

    bannerCenBorder ("", "", "", "POS Version : 1.0");

    for ( int i = 3; i > 0; i-- )
        bannerBlankBorder ();

    char text[140];
    sprintf (text, "Welcome back %s %s!", Session.user.firstname, Session.user.lastname);
    bannerBlankBorderTextCen (text);
    bannerBlankBorder ();

    char text2[140];
    sprintf (text2, "Signing in as : %s", Session.user.username);
    bannerBlankBorderTextCen (text2);

    for (int i = 2;i>0;i--)
        bannerBlankBorder ();

    printf ("::                                                                 ██████                                                                 ::\n");
    printf ("::                                                                ██    ██                                                                ::\n");
    printf ("::                                                               ██      ██                                                               ::\n");
    printf ("::                                                               ██████████                                                               ::\n");
    printf ("::                                                               ████  ████                                                               ::\n");
    printf ("::                                                               ████  ████                                                               ::\n");
    printf ("::                                                               ██████████                                                               ::\n");

    for (int i = 2;i>0;i--)
        bannerBlankBorder ();

    bannerBlankBorderTextCen ("POS system is now LOCK");

    for ( int i = 0; i < 13; i++ ) {
        bannerBlankBorder ();
    }
    bannerFullBorder ();

    delay (2);

    screenClear ();

    bannerCenBorder ("", "", "", "POS Version : 1.0");

    for ( int i = 3; i > 0; i-- )
        bannerBlankBorder ();

    bannerBlankBorderTextCen (text);
    bannerBlankBorder ();

    bannerBlankBorderTextCen (text2);

    for (int i = 2;i>0;i--)
        bannerBlankBorder ();

    printf ("::                                                                 ██████                                                                 ::\n");
    printf ("::                                                                ██    ██                                                                ::\n");
    printf ("::                                                                       ██                                                               ::\n");
    printf ("::                                                               ██████████                                                               ::\n");
    printf ("::                                                               ████  ████                                                               ::\n");
    printf ("::                                                               ████  ████                                                               ::\n");
    printf ("::                                                               ██████████                                                               ::\n");

    for (int i = 2;i>0;i--)
        bannerBlankBorder ();

    bannerBlankBorderTextCen ("POS system is now UNLOCK");


    for ( int i = 0; i < 12; i++ ) {
        bannerBlankBorder ();
    }

    bannerBlankBorderTextCen ("Redirecting you to POS system...");
    bannerFullBorder ();
    delay (3);

    /* During this betq test only (assuming all user are admin) ->*/ switchHub ();
}

void authInterfaceFail () {
    screenClear ();

    bannerCenBorder ("", "", "", "POS Version : 1.0");

    bannerBlankBorder ();
    bannerBlankBorderTextCen ("Your login credentials is incorrect.");
    bannerBlankBorder ();
    bannerBlankBorderTextCen ("We are redirecting you try again. If you wish to do that, type any key to continue");
    bannerBlankBorder ();
    bannerBlankBorderTextCen ("or type 'N' to exit the program");

    for ( int i = 0; i < 31; i++ )
        bannerBlankBorder ();

    bannerFullBorder ();
    bannerUserInput ();
    char flag;
    scanf (" %c", &flag);

    switch (toupper(flag)) {

        case ('N'):
            terminate ();
            return;

        default:
            screenClear ();
            authInterface ();
            return;
    }
    // If user type anything (except N or n) program will not be terminate + rerouting to login page again
    // If user type 'N' or 'n' program will be rerouting to terminate(); and they can shut the program down...
}

void authInterfaceError () {
    bannerFullBorder ();
    bannerBlankBorderTextCen ("Oops!");
    bannerFullBorder ();

    bannerBlankBorderTextCen ("The username that you have type are not in the system...");
    bannerBlankBorder ();
    bannerBlankBorderTextCen ("Please try again or contact an administrator if this occur too many times");
    for ( int i = 0; i < 32; i++ )
        bannerBlankBorder ();
    bannerBlankBorderTextCen ("Redirect to sign in...");
    bannerFullBorder ();

    delay (4);
    authInterface ();

    // Program will delay for 4 seconds, and will be redirect back to login page...
}

int authenticateByUsername (char *username, char *password) {
    int numberOfRecords;    // Number of the records in a table
    numberOfRecords = RecordCount.personnel;

    for ( int i = 0; i < numberOfRecords; i++ ) {
        if ( strcmp (Personnel[i].username, username) == 0 ) {
            if ( strcmp (Personnel[i].password, password) == 0 ) {
                // Save user's information on the Session
                Session.user = Personnel[i];
                Session.isLogedin = 1;
                return 1;   // Login success
            } else
                return 0;   // Password incorrect
        }
    }
    return -1;  // User Not found
}

int authenticateByToken (char *barcodeToken) {
    int numberOfRecords;    // Number of the records in a table
    numberOfRecords = RecordCount.personnel;

    for ( int i = 0; i < numberOfRecords; i++ ) {
        if ( strcmp (Personnel[i].barcodeToken, barcodeToken) == 0 ) {
            // Save user's information on the Session
            Session.user = Personnel[i];
            Session.isLogedin = 1;
            return 1;
        }
    }
    return 0;
}

void deauthenticate () {
    Session.isLogedin = 0;

    screenClear ();
    bannerFullBorder ();

    char text[137];
    strcpy (text, "User ");
    strcat (text, Session.user.username);
    strcat (text, " account has successfully logout.");
    bannerBlankBorderTextCen (text);

    for ( int i = 3; i > 0; i-- )
        bannerBlankBorder ();
    bannerBlankBorderTextCen ("(,, ･A･)ﾉ゛");

    for ( int i = 30; i > 0; i-- )
        bannerBlankBorder ();

    bannerBlankBorderTextCen ("Returning you back to login...");
    bannerFullBorder ();

    delay (3);
    screenAdjust ();
}

/*
 *                                             All hail the god..
 *  -----------------------------------------------------------------------------------------------------------------------
 *  |      _=_      ||      _=_      ||      _=_      ||      _=_      ||      _=_      ||      _=_      ||      _=_      |
 *  |    q(-_-)p    ||    q(-_-)p    ||    q(-_-)p    ||    q(-_-)p    ||    q(-_-)p    ||    q(-_-)p    ||    q(-_-)p    |
 *  |    '_) (_`    ||    '_) (_`    ||    '_) (_`    ||    '_) (_`    ||    '_) (_`    ||    '_) (_`    ||    '_) (_`    |
 *  |    /__/  \    ||    /__/  \    ||    /__/  \    ||    /__/  \    ||    /__/  \    ||    /__/  \    ||    /__/  \    |
 *  |  _(<_   / )_  ||  _(<_   / )_  ||  _(<_   / )_  ||  _(<_   / )_  ||  _(<_   / )_  ||  _(<_   / )_  ||  _(<_   / )_  |
 *  | (__\_\_|_/__) || (__\_\_|_/__) || (__\_\_|_/__) || (__\_\_|_/__) || (__\_\_|_/__) || (__\_\_|_/__) || (__\_\_|_/__) |
 *  |---------------||---------------||---------------||---------------||---------------||---------------||---------------|
 *  |     Hello     ||     Hello     ||     Hello     ||     Hello     ||     Hello     ||     Hello     ||     Hello     |
 *  |     Monday    ||    Tuesday    ||   Wednesday   ||    Thursday   ||     Friday    ||    Saturday   ||     Sunday    |
 *  -----------------------------------------------------------------------------------------------------------------------
 *                                         Program bug best enemy
 *                                 Please. No bug. No crash. No interrupt.
 *  -----------------------------------------------------------------------------------------------------------------------
 */