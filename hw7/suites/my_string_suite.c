/**
 * @file my_string_suite.c
 * @author Farzam TN a.k.a Unc Zam
 * @brief Testing Suites to HW7 - Spring 2020
 * @date 2020-03-06
 */

// Check Docs
// Tutorial : https://libcheck.github.io/check/doc/check_html/check_3.html
// Check API: https://libcheck.github.io/check/doc/doxygen/html/check_8h.html

// System Headers
#include <stdio.h>
#include <string.h>
#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#include "test_utils.h"

// For checking my_string.c array notation
#define NO_ARRAY_NOTATION 2200
#define MY_STRING_C_NOT_FOUND 1
#define MY_STRING_FAILURE 2
#define STRING_H_USED 3
#define STRINGS_H_USED 4

// This is the variable that determines if they used illegal stuff @see whatIsA2110StudentDoingHere()
static int dontReverseEngineerBro = MY_STRING_FAILURE; // TODO: make it const

static void randStringGenerator(char *dest, int length);
static int whatIsA2110StudentDoingHere(void);

/******************************************************************************/
/**************************** my_strlen tests *********************************/
/******************************************************************************/

START_TEST(test_my_strlen_1)
{
    const char *str = "12345";
    const char *backup = str; // pointers should not be changed
    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_2)
{
    const char *str = "1\0";
    const char *backup = str; // pointers should not be changed

    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_3)
{
    const char str[] = {'1', '2', '3', '\0', 'Z', 'f'};
    const char *backup = str; // pointers should not be changed
    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

START_TEST(test_my_strlen_4)
{
    srand(time(0));
    unsigned long randBoi = rand() % 512;
    if (randBoi < 100)
    {
        // Everybody gotta do at least 155 characters
        randBoi += 155;
    } 
    else if (randBoi > 499)
    {
        // Dont let index be anything farther than the last index
        randBoi = 499;
    }

    // The only function that doesn't use the random string generator
    #define max 500
    char str[max];  // no vlas!
    const char *backup = str; // pointers should not be changed

    // place a non-zero value (7) in the first n-1 indexes 
    memset(str, 7, randBoi - 1);

    // place null term at the randomly generated index
    str[randBoi] = '\0';

    size_t retVal = my_strlen(str);
    ck_assert_ptr_eq(str, backup);
    ck_assert_int_eq(retVal, strlen(str));
}
END_TEST

/******************************************************************************/
/**************************** my_strncmp tests ********************************/
/******************************************************************************/

/**
 * All the strncmp test cases just check for negative, positive, or zero value
 * and the actual value doesn't matter. This is done to adhere to strncmp man page
 * and resources online.
 */

START_TEST(test_my_strncmp_equal)
{
    const char *str1 = "1234/#?\\21tenMo";
    const char *str2 = "1234/#?\\21tenMo";

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2; // pointers should not be changed

    size_t n = strlen(str1);

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_null_terminator_in_middle_almost_same)
{
    const char str1_buf[] = {'Z', '\0',       'y', '0', 'h', 'a', '\0',      'Z', 'f'};
    const char *str1 = str1_buf + 2;
    const char str2_buf[] = {'A', 'a',        'y', '0', 'h', 'a', '\0',      'A', 'a'};
    const char *str2 = str2_buf + 2;

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2;

    size_t n = strlen(str1) + 2;

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_null_terminator_in_middle_different)
{
    // Should return negative
    const char str1_buf[] = {'Z', 'f',   'y', 'e', 'e', 'h', 'a', '\0',                   'Z', 'f'};
    const char *str1 = str1_buf + 2;
    const char str2_buf[] = {'A', '\0',  'y', 'e', 'e', 'h', 'a', 'B', 'r', 'o', '\0',    'A', 'a'};
    const char *str2 = str2_buf + 2;

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2;
    size_t n = strlen(str1) + 1;

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST

START_TEST(test_my_strncmp_random)
{
    // Let's see if student's can hack this test case (without zerodays tho..)

    srand(time(0));
    unsigned int randBoi = rand() % 128;
    if (randBoi < 70)
    {
        randBoi += 100; // Everybody gonna do 100 minimum
    }
    else if (randBoi > 123)
    {
        // no one goes out out bounds
        randBoi = 123;
    }

    // no vlas!
    #define cmp_max 125
    char str1[cmp_max];

    randStringGenerator(str1, cmp_max - 1);

    char str2[cmp_max];
    strncpy(str2, str1, strlen(str1)); // Creating a copy
    str2[cmp_max - 1] = '\0';

    str2[randBoi] = 'F';

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2;

    size_t n = (strlen(str1) / 2) + 1;

    // compare your results to std lib results
    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        // less than
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        // greater than
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        // equal to
        ck_assert_int_eq(retVal, correctValSign);
    }

    // make sure we did not modify the pointers
    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);
}
END_TEST


/*
Test for shuffled letters in a string
Eg. s1 = "ABC", s2 = "CBA"
*/
START_TEST(test_my_strncmp_letters_shuffled)
{
    const char *str1 = "ABCD";
    const char *str2 = "BCDA";

    const char *backup1 = str1; // pointers should not be changed
    const char *backup2 = str2; // pointers should not be changed

    size_t n = strlen(str1) + 1;

    int retVal = my_strncmp(str1, str2, n);
    int correctValSign = strncmp(str1, str2, n);

    if (correctValSign < 0)
    {
        ck_assert_int_lt(retVal, 0);
    }
    else if (correctValSign > 0)
    {
        ck_assert_int_gt(retVal, 0);
    }
    else
    {
        ck_assert_int_eq(retVal, correctValSign);
    }

    ck_assert_ptr_eq(str1, backup1);
    ck_assert_ptr_eq(str2, backup2);

}
END_TEST

/******************************************************************************/
/*************************** my_strncpy tests *********************************/
/******************************************************************************/
START_TEST(test_my_strncpy_basic)
{
    char src[] = {'\0'};
    const char *backup = src; // pointers should not be changed

    char dest[] = {'a', '\0'};
    size_t n = 1;

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not overwrite first byte of dest\n");
}
END_TEST

START_TEST(test_my_strncpy_destination_larger)
{
    char *src = "His palms are sweaty, knees weak, arms are heavy ... mom's spaghetti";
    const char *backup = src; // pointers should not be changed

    char dest[100];
    memset(dest, 0, sizeof(dest)); // just to be safe
    size_t n = strlen(src);

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not overwrite first byte of dest\n");
}
END_TEST

START_TEST(test_my_strncpy_random_basic_256)
{
    srand(time(0) - 5000); // 5000 means something Sean

    // Generate random source
    char src[256 + 1];
    const char *backup = src; // pointers should not be changed

    randStringGenerator(src, sizeof(src));

    // No null-termination on dest on purpose
    char dest[256];
    size_t n = strlen(src);
    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not copy the first 256 characters of src to dest correctly\n");
}
END_TEST

START_TEST(test_my_strncpy_null_terminator_in_middle)
{
    srand(time(0) - 5000); // 5000 means something Sean

    // Generate random source
    char src[256];
    randStringGenerator(src, sizeof(src));
    const char *backup = src; // pointers should not be changed

    // Null terminating in middle to make sure they only copy all the way to null terminator
    150 [src] = 0; // gangsta move

    // No null-termination on dest on purpose
    char dest[256];
    memset(dest, 7, sizeof(256)); // Filling destination with arbitrary val
    size_t n = 256;
    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Size should be the same because of n and null terminator position
    ck_assert_int_eq(strlen(dest), strlen(src));

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, strlen(src) + 1), "did not copy src to dest correctly when null terminator is in middle\n");
}
END_TEST

START_TEST(test_my_strncpy_overwrite)
{
    char src[100];
    randStringGenerator(src, sizeof(src));
    const char *backup = src; // pointers should not be changed

    char dest[100];
    randStringGenerator(dest, sizeof(dest));
    size_t n = strlen(dest);

    char *retVal = my_strncpy(dest, src, n);

    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);

    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, n), "did not overwrite destination completely\n");
}
END_TEST

START_TEST(test_my_strncpy_adv)
{
    #define BASE 5
    char src[BASE];
    randStringGenerator(src, BASE);
    const char *backup = src; // pointers should not be changed
    
    #define BUFFER 8
    char dest[BUFFER];
    randStringGenerator(dest, BUFFER);
    
    // everything upto src should be copied correctly
    // everything after src length should be nulled out
    char *retVal = my_strncpy(dest, src, BUFFER);
    
    // Checking if dest didn't change
    ck_assert_ptr_eq(retVal, dest);
    ck_assert_ptr_eq(src, backup);

    // Checking if strncmp returns 0
    ck_assert_msg(!strncmp(dest, src, strlen(src)), "did not copy src into dest correctly\n");
    
    /*
        We should not use stncmp (even the stdlib version)
        It will stop checking if both chars are 0 (null-term)
        So, it does not check if the user *completely* zeroed out the remaining n chars
        as requried by strncpy implmentation
    */
    #define TAIL 4 // value is BUFFER - (BASE - 1)
    char zeroedOut[TAIL]    = {'\0', '\0', '\0', '\0'};
    char notZeroedOut[TAIL] = {'\0', '\0', 'a', '\0'};
    int shouldBeDifferent = 0;
    int shouldBeSame = 0;

    for (int i = 0; i < TAIL; i++) {
        shouldBeSame += (*(dest + (BASE-1) + i) - *(zeroedOut + i));
        shouldBeDifferent += (*(dest + (BASE-1) + i) - *(notZeroedOut + i));
    }
    
    // ck_assert_msg(test, "Make sure you read the man page carefully\n");
    ck_assert_int_eq(shouldBeSame, 0);
    ck_assert_int_eq(shouldBeDifferent, -97);
}
END_TEST

/**
 * @brief Automatically ran before every test. Just checks whether illegal things are used and fails if so.
 */
static void setup(void)
{
    if (dontReverseEngineerBro != NO_ARRAY_NOTATION)
    {
        if (dontReverseEngineerBro == MY_STRING_C_NOT_FOUND) {
            ck_abort_msg("ERROR: Can't open my_string.c");
        } else if (dontReverseEngineerBro == MY_STRING_FAILURE) {
            ck_abort_msg("ALL TESTS FAILED: Using array notation is not allowed in file my_string.c");
        } else if (dontReverseEngineerBro == STRING_H_USED || dontReverseEngineerBro == STRINGS_H_USED) {
            ck_abort_msg("ALL TESTS FAILED: Using <string.h> is not allowed");
        } else {
            ck_abort_msg("ERROR: Illegal stuff used in my_string.c");
        }
    }
}

/**
 * @brief Helper function for creating random strings. It will null-terminate like a champ.
 */
// Thanks bro --> https://stackoverflow.com/questions/15767691/whats-the-c-library-function-to-generate-random-string/15768317
static void randStringGenerator(char *buffer, int length)
{
    // C weird syntax once again
    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // So we don't have to keep adding space for the null terminator
    length--;

    while (length-- > 0)
    {
        // The magic of double, this guy is a flexer
        size_t index = ((double)rand() / RAND_MAX) * (sizeof(charset) - 1);
        *buffer++ = charset[index];
    }

    *buffer = '\0';
}

/**
 * @brief Unc Z's method for checking illegal stuff such as <string.h> and array notation (modified by Justin).
 *       Current Problems: Strings... if a student has: char*haha="// <- this stops the checker from looking farther";arr[i]=2;
 *                         Backslashes... ex. #include <strin\
 *                         g.c>
 * 
 * @return int a status code (@see #defines at the top)
 */
static int whatIsA2110StudentDoingHere(void)
{
    FILE *myStringDotC = fopen("my_string.c", "r");
    if (!myStringDotC) {
        printf("ERROR: Can't open my_string.c\n\n");
        return MY_STRING_C_NOT_FOUND;
    }

    char buffer[512]; // Should not have code lines more than this size --> This could result in a bug if anybody bypasses this length
    int insideMultiFlag = 0; // Boolean flag for whether we're currently inside a /* */ multi-line comment

    // Checking for disallowed stuff
    while (!feof(myStringDotC))
    {
        if (fgets(buffer, sizeof(buffer), myStringDotC))
        {
            char *i = buffer;
            // traverse buffer (current line) in case of multiple multi-line comments on same line
            while (i && *i)
            {
                char *nextI = NULL; // nextI is what i is set to on the next iteration (used as a delayed break in some cases)

                if (insideMultiFlag) {
                    // if in a multi-line commment, ignore everything until we reach a */
                    char *nextMultiEnd = strstr(i, "*/");
                    if (!nextMultiEnd) {
                        nextI = NULL; // we don't need to check rest of line because the multi-line comment doesn't end on this line
                    } else {
                        insideMultiFlag = 0;
                        nextI = nextMultiEnd + strlen("*/");
                    }
                } else {
                    // if we find a // comment first, the rest of the line will be commented, if a /* is first, the line will be commented until the next */
                    char *nextSingleStart = strstr(i, "//");
                    char *nextMultiStart = strstr(i, "/*");
                    char nonCommentChars[sizeof(buffer) / sizeof(char) + 1];

                    if ((!nextSingleStart && nextMultiStart) || ((nextSingleStart && nextMultiStart) && nextMultiStart < nextSingleStart)) {
                        // a /* */ comment starts at some point in this line
                        insideMultiFlag = 1;
                        nextI = nextMultiStart + strlen("/*");

                        // Grabbing everything from line to comment
                        int beforeCommentSize = (nextMultiStart - i);
                        strncpy(nonCommentChars, i, beforeCommentSize);
                        nonCommentChars[beforeCommentSize] = '\0';
                    } else if ((nextSingleStart && !nextMultiStart) || ((nextSingleStart && nextMultiStart) && nextSingleStart < nextMultiStart)) {
                        // rest of line is // comment
                        nextI = NULL;

                        // Grabbing everything from line to comment
                        int beforeCommentSize = (nextSingleStart - i);
                        strncpy(nonCommentChars, i, beforeCommentSize);
                        nonCommentChars[beforeCommentSize] = '\0';
                    } else {
                        // rest of line isn't a comment
                        nextI = NULL;

                        // Grab rest of line (buffer/i always ends with \0 because of fgets so we can strcpy)
                        strcpy(nonCommentChars, i);
                    }

                    if (strstr(nonCommentChars, "<string.h>")) {
                        printf("ALL TESTS FAILED: Using <string.h> is not allowed\n\n");
                        return STRING_H_USED;
                    }

                    if (strstr(nonCommentChars, "<strings.h>")) {
                        printf("ALL TESTS FAILED: (Trying to be sneaky huh?). Using <strings.h> is not allowed\n\n");
                        return STRINGS_H_USED;
                    }

                    if (strstr(nonCommentChars, "]") || strstr(nonCommentChars, "[")) {
                        printf("ALL TESTS FAILED: Using array notation is not allowed in file my_string.c\n\n");
                        return MY_STRING_FAILURE;
                    }
                }

                i = nextI;
            }
        }
    }

    // Nice one ese
    return NO_ARRAY_NOTATION;
}

Suite *my_string_suite(void)
{
    Suite *s = suite_create("my_string_suite");

    // Even if they bypass this, they still need a valid implementation
    dontReverseEngineerBro = whatIsA2110StudentDoingHere();

    tcase_hack(s, setup, NULL, test_my_strlen_1);
    tcase_hack(s, setup, NULL, test_my_strlen_2);
    tcase_hack(s, setup, NULL, test_my_strlen_3);
    tcase_hack(s, setup, NULL, test_my_strlen_4);

    tcase_hack(s, setup, NULL, test_my_strncmp_equal);
    tcase_hack(s, setup, NULL, test_my_strncmp_null_terminator_in_middle_almost_same);
    tcase_hack(s, setup, NULL, test_my_strncmp_null_terminator_in_middle_different);
    tcase_hack(s, setup, NULL, test_my_strncmp_random);
    tcase_hack(s, setup, NULL, test_my_strncmp_letters_shuffled);

    tcase_hack(s, setup, NULL, test_my_strncpy_basic);
    tcase_hack(s, setup, NULL, test_my_strncpy_destination_larger);
    tcase_hack(s, setup, NULL, test_my_strncpy_random_basic_256);
    tcase_hack(s, setup, NULL, test_my_strncpy_null_terminator_in_middle);
    tcase_hack(s, setup, NULL, test_my_strncpy_overwrite);
    tcase_hack(s, setup, NULL, test_my_strncpy_adv);

    return s;
}
