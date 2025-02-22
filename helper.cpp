//
// CDDL HEADER START
//
// The contents of this file are subject to the terms of the Common Development
// and Distribution License Version 1.0 (the "License").
//
// You can obtain a copy of the license at
// http://www.opensource.org/licenses/CDDL-1.0.  See the License for the
// specific language governing permissions and limitations under the License.
//
// When distributing Covered Code, include this CDDL HEADER in each file and
// include the License file in a prominent location with the name LICENSE.CDDL.
// If applicable, add the following below this CDDL HEADER, with the fields
// enclosed by brackets "[]" replaced with your own identifying information:
//
// Portions Copyright (c) [yyyy] [name of copyright owner]. All rights reserved.
//
// CDDL HEADER END
//

//
// Copyright (c) 2019, Regents of the University of Minnesota.
// All rights reserved.
//
// Contributors:
//    Mingjian Wen
//

#include "helper.hpp"
#include <cstring>
#include <iostream>

//******************************************************************************
// process parameter file
//******************************************************************************

void getNextDataLine(FILE * const filePtr,
                     char * nextLinePtr,
                     int const maxSize,
                     int * endOfFileFlag)
{
  do
  {
    if (fgets(nextLinePtr, maxSize, filePtr) == NULL)
    {
      *endOfFileFlag = 1;
      break;
    }

    while ((nextLinePtr[0] == ' ' || nextLinePtr[0] == '\t')
           || (nextLinePtr[0] == '\n' || nextLinePtr[0] == '\r'))
    { nextLinePtr = (nextLinePtr + 1); }
  } while ((strncmp("#", nextLinePtr, 1) == 0) || (strlen(nextLinePtr) == 0));

  // remove comments starting with `#' in a line
  char * pch = strchr(nextLinePtr, '#');
  if (pch != NULL) { *pch = '\0'; }
}

//******************************************************************************
int getXdouble(char * linePtr, const int N, double * list)
{
  int ier;
  char * pch;
  char line[MAXLINE];
  int i = 0;

  strcpy(line, linePtr);
  pch = strtok(line, " \t\n\r");
  while (pch != NULL)
  {
    ier = sscanf(pch, "%lf", &list[i]);
    if (ier != 1) { return true; }
    pch = strtok(NULL, " \t\n\r");
    i += 1;
  }

  if (i != N) { return true; }

  return false;
}

//******************************************************************************
int getXint(char * linePtr, const int N, int * list)
{
  int ier;
  char * pch;
  char line[MAXLINE];
  int i = 0;

  strcpy(line, linePtr);
  pch = strtok(line, " \t\n\r");
  while (pch != NULL)
  {
    ier = sscanf(pch, "%d", &list[i]);
    if (ier != 1) { return true; }
    pch = strtok(NULL, " \t\n\r");
    i += 1;
  }
  if (i != N) { return true; }

  return false;
}

//******************************************************************************
void lowerCase(char * linePtr)
{
  for (int i = 0; linePtr[i]; i++) { linePtr[i] = tolower(linePtr[i]); }
}
