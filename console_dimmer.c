/*
 * This is a simple console-based lighting control program. It can be used
 *  for shell scripts (for one shot lighting commands) such as this:
 *
 *    console_dimmer blackout 1
 *
 * ...to just kill all active lights. For example. This can also be used as
 *  as interactive control program. If no commands are given on the command
 *  line, then the program takes input and converts it to dimmer API calls.
 *  Current levels are noted in interactive mode, and assuming you could type
 *  fast enough, you could even use it to run a show.
 *
 *    Copyright (c) Lighting and Sound Technologies, 1999.
 *     Written by Ryan C. Gordon.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <readline.h>
#include <history.h>
#include "dimmer.h"

#define VERSION "v0.1.0"

static struct DimmerDeviceInfo devInfo;
static struct DimmerSystemInfo sysInfo;

static void inline displayHelp(void)
/*
 * Dump some help on available commands to stdout.
 *
 *   params : void.
 *  returns : void.
 */
{
    printf("Lighting and Sound Technologies Console Dimmer.\n"
           "\n"
           " Usage:\n"
           "   start with no command line args for interactive mode.\n"
           "   help\n"
           "   set <channelnum> <0-255>\n"
           "   fade <channelnum> <0-255> <seconds>\n"
           "   blackout <0 or 1>\n"
           "   gm <0-255>\n"
          );
} /* displayHelp */


static int getNumbers(char **tokens, double *numbers, int needNums)
/*
 * Convert a bunch of tokens to numbers.
 *
 *    params : tokens  == array of tokens to convert.
 *             numbers == where to fill in converted numbers.
 *             needNums == number of numbers we want.
 *   returns : 0 on success, -1 on error. Error messages are sent to
 *              stderr here, so there's no need to reprint them in the
 *              calling function.
 */
{
    int i;

    for (i = 0; i < needNums; i++)
    {
        if (tokens[i] == NULL)
        {
            fprintf(stderr, "Too few arguments.\n");
            return(-1);
        } /* if */
        else
        {
            numbers[i] = atof(tokens[i]);
            /* !!! really a number? */
        } /* else */
    } /* for */

    if (tokens[needNums] != NULL)
    {
        fprintf(stderr, "Too many arguments.\n");
        return(-1);
    } /* if */

    return(0);
} /* getNumbers */


static void parseCommand(int tokenCount, char **tokens)
/*
 * Figure out which dimmer API we want to call, get the arguments, and do it.
 *
 *     params : tokenCount == number of tokens. Like argc.
 *              tokens     == tokens. Like argv.
 *    returns : void.
 */
{
    double numbers[5];
    int rc = 0;
    int tmp;

    if ((tokenCount < 1) || (tokens == NULL) || (tokens[0] == NULL))
        return;

    if (strcasecmp(tokens[0], "help") == 0)
        displayHelp();

    else if (strcasecmp(tokens[0], "set") == 0)
    {
        if (getNumbers(&tokens[1], numbers, 2) == 0)
            rc = dimmer_channel_set(numbers[0], numbers[1]);
    } /* else if */

    else if (strcasecmp(tokens[0], "fade") == 0)
    {
        if (getNumbers(&tokens[1], numbers, 3) == 0)
            rc = dimmer_channel_fade(numbers[0], numbers[1], numbers[2]);
    } /* else if */

    else if (strcasecmp(tokens[0], "blackout") == 0)
    {
        if (getNumbers(&tokens[1], numbers, 1) == 0)
            rc = dimmer_toggle_blackout(numbers[0]);
    } /* else if */

    else if (strcasecmp(tokens[0], "gm") == 0)
    {
        if (getNumbers(&tokens[1], numbers, 1) == 0)
            rc = dimmer_set_grand_master((unsigned char) numbers[0]);
    } /* else if */

    else if (strcasecmp(tokens[0], "askdev") == 0)
    {
        if (getNumbers(&tokens[1], numbers, 0) == 0)
        {
            rc = dimmer_query_device(&devInfo);
            if (rc == -1)
                fprintf(stderr, "error. (%d).\n", errno);
            else
            {
                printf("(%d) channels, (%d) outputs, duplex %s.\n",
                        devInfo.numChannels, devInfo.numOutputs,
                        (devInfo.isDuplexed) ? "enabled" : "disabled");
            } /* else */
        } /* if */
    } /* else if */

    else if (strcasecmp(tokens[0], "asksys") == 0)
    {
        if (getNumbers(&tokens[1], numbers, 0) == 0)
        {
            rc = dimmer_query_system(&sysInfo);
            if (rc == -1)
                fprintf(stderr, "error. (%d).\n", errno);
            else
            {
                printf("(%d) device modules available:\n", sysInfo.devCount);
                    // !!! dimmer_device_name()...
                //int devCount;
                //int *devsAvailable;
                //int activeDevID;
            } /* else */
        } /* if */
    } /* else if */

    else  /* unknown command. */
        fprintf(stderr, "Unknown command: [%s].\n", tokens[0]);

    if (rc != 0)
    {
        tmp = errno;
        fprintf(stderr, "Command [%s] failed. rc == (%d)", tokens[0], rc);
        errno = tmp;
        perror("");
    } /* if */
} /* parseCommand */


static void interactiveMode(void)
{
    int getOut = 0;
    char *inCmd = NULL;
    char *tmp;
    char *cmdToks[30];
    int count;

    printf("Console dimmer (%s) -=[INTERACTIVE MODE]=-\n", VERSION);

    while (!getOut)
    {
        inCmd = readline("> ");
        if (inCmd != NULL)
        {
            tmp = inCmd;
            for (count = 0; (count < 30) && (inCmd != NULL); count++)
            {
                while (*inCmd == ' ')
                    inCmd++;

                cmdToks[count] = inCmd;
                inCmd = strchr(inCmd, ' ');
                if (inCmd != NULL)
                {
                    *inCmd = '\0';
                    inCmd++;
                } /* if */
            } /* for */

            cmdToks[count] = NULL;

            if (cmdToks[0][0] != '\0')
            {
                if (strcasecmp(cmdToks[0], "quit") == 0)
                    getOut = 1;
                else
                    parseCommand(count, cmdToks);
            } /* if */
            free(tmp);
        } /* if */
    } /* while */
} /* interactiveMode */


int main(int argc, char **argv)
/*
 * The mainline. Initialize libdimmer, and figure out if we're in 
 *  interactive mode, or a one-shot command line deal...
 */
{
    if (dimmer_init(1) == -1)
        perror("dimmer_init() failed");
    else
    {
        if (argc == 1)
            interactiveMode();
        else
            parseCommand(argc - 1, argv + 1);
    } /* else */

    return(0);
} /* main */


// Matt in Dallas:
// 972-826-1229


