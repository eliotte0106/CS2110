/**
 * @file my_string.c
 * @author JP
 * @collaborators NAMES OF PEOPLE THAT YOU COLLABORATED WITH HERE
 * @brief Your implementation of these famous 3 string.h library functions!
 *
 * NOTE: NO ARRAY NOTATION IS ALLOWED IN THIS FILE
 *
 * @date 2022-03-xx
 */

// DO NOT MODIFY THE INCLUDE(s) LIST
#include <stddef.h>
#include "hw7.h"

/**
 * @brief Calculate the length of a string
 *
 * @param s a constant C string
 * @return size_t the number of characters in the passed in string
 */
size_t my_strlen(const char *s)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  UNUSED_PARAM(s);

  int cnt = 0;
  while (*s != '\0') {
    cnt++;
    s++;
  }
  return cnt;
}

/**
 * @brief Compare two strings
 *
 * @param s1 First string to be compared
 * @param s2 Second string to be compared
 * @param n First (at most) n bytes to be compared
 * @return int "less than, equal to, or greater than zero if s1 (or the first n
 * bytes thereof) is found, respectively, to be less than, to match, or be
 * greater than s2"
 */
int my_strncmp(const char *s1, const char *s2, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */

  UNUSED_PARAM(s1);
  UNUSED_PARAM(s2);
  UNUSED_PARAM(n);

  // while (n > 0) {
  //   if (*s1 != *s2) {
  //     return *s1 - *s2;
  //   }
  //   if (*s1 == '\0' && *s2 == '\0') {
  //     return *s1 - *s2;
  //   }
  //   n--;
  //   s1++;
  //   s2++;
  // }
  // return 0;
  size_t count = 0;

    while (*s1 && *s2 && *s1 == *s2 && count < n) {
        s1++;
        s2++;
        count++;
    }

    return *s1 - *s2;
}

/**
 * @brief Copy a string
 *
 * @param dest The destination buffer
 * @param src The source to copy from
 * @param n maximum number of bytes to copy
 * @return char* a pointer same as dest
 */
char *my_strncpy(char *dest, const char *src, size_t n)
{
  /* Note about UNUSED_PARAM
   *
   * UNUSED_PARAM is used to avoid compiler warnings and errors regarding unused function
   * parameters prior to implementing the function. Once you begin implementing this
   * function, you can delete the UNUSED_PARAM lines.
   */
  UNUSED_PARAM(dest);
  UNUSED_PARAM(src);
  UNUSED_PARAM(n);
  
  int l = my_strlen(src);
  char *s = dest;
  while(n > 0) {
    if (l <= 0) {
      *dest = '\0';
    } else {
      *dest = *src;
    }
    dest++;
    src++;
    n--;
    l--;
  }
  return s;

  //return NULL;
}
