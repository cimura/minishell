
#include <stdio.h>

int main ()

{
  /* Read preferences.  */

  FILE *prefs = fopen ("myprefs", "r");

  /* Parse preferences.  Forget to fclose prefs.  */

  return 0;
}
