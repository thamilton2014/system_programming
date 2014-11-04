#include <string.h>
#include <signal.h>
#include <time.h>
#include "signal_functions.h"           

static volatile int sigintCnt = 0;
static volatile sig_atomic_t gotSigquit = 0;
static void
handler(int sig)
{
    printf("Caught signal %d (%s)\n", sig, strsignal(sig));
                                        /* UNSAFE (see Section 21.1.2) */
    if (sig == SIGQUIT)
        gotSigquit = 1;
    sigintCnt++;
}
int
main(int argc, char *argv[])
{
    int loopNum;
    int sleepTime;
    time_t startTime;
    sigset_t origMask, blockMask;
    struct sigaction sa;

    printSigMask(stdout, "Initial signal mask is:\n");

    sigemptyset(&blockMask);
    sigaddset(&blockMask, SIGINT);
    sigaddset(&blockMask, SIGQUIT);

    sleepTime = (argc > 1) ? getInt(argv[1], GN_NONNEG, NULL) : 0;

    /* Block SIGINT and SIGQUIT - at this point we assume that these signals
      are not already blocked (obviously true in this simple program) so that
      'origMask' will not contain either of these signals after the call. */

    if (sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
        errExit("sigprocmask - SIG_BLOCK");

    /* Set up handlers for SIGINT and SIGQUIT */

    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sa.sa_handler = handler;
    if (sigaction(SIGINT, &sa, NULL) == -1)
        errExit("sigaction");
    if (sigaction(SIGQUIT, &sa, NULL) == -1)
        errExit("sigaction");

    /* Loop until SIGQUIT received */

    for (loopNum = 1; !gotSigquit; loopNum++) {
        printf("=== LOOP %d\n", loopNum);

        /* Simulate a critical section by delaying a few seconds */

        printSigMask(stdout, "Starting critical section, signal mask is:\n");
        for (startTime = time(NULL); time(NULL) < startTime + 4; )
            continue;                   /* Run for a few seconds elapsed time */

#ifndef USE_PAUSE
        /* The right way: use sigsuspend() to atomically unblock
           signals and pause waiting for signal */

        printPendingSigs(stdout,
                "Before sigsuspend() - pending signals:\n");
        if (sigsuspend(&origMask) == -1 && errno != EINTR)
            errExit("sigsuspend");
#else

        /* The wrong way: unblock signal using sigprocmask(),
           then pause() */

        if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
            errExit("sigprocmask - SIG_SETMASK");

        /* At this point, if SIGINT arrives, it will be caught and
           handled before the pause() call and, in consequence,
           pause() will block. (And thus only another SIGINT signal
           AFTER the pause call() will actually cause the pause()
           call to be interrupted.)  Here we make the window between
           the two calls a bit larger so that we have a better
           chance of sending the signal. */

        if (sleepTime > 0) {
            printf("Unblocked SIGINT, now waiting for %d seconds\n", sleepTime);
            for (startTime = time(NULL);
                    time(NULL) < startTime + sleepTime; )
                continue;
            printf("Finished waiting - now going to pause()\n");
        }

        /* And now wait for the signal */

        pause();

        printf("Signal count = %d\n", sigintCnt);
        sigintCnt = 0;
#endif
    }

    /* Restore signal mask so that signals are unblocked */

    if (sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
        errExit("sigprocmask - SIG_SETMASK");

    printSigMask(stdout, "=== Exited loop\nRestored signal mask to:\n");

    /* Do other processing... */

    exit(EXIT_SUCCESS);
}