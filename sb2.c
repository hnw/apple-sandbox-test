#include <stdio.h>
#include <sandbox.h>

/*
 * $ sudo cp sb2.sb /Library/Sandbox/Profiles/sb2.sb
 * $ echo "w" > /private/var/tmp/can_w
 * $ echo "r" > /private/var/tmp/can_r
 * $ ./sb2
 * pid: 30011
 * [SANDBOXED]...$ cat /private/var/tmp/can_w
 * cat: /private/var/tmp/can_w: Operation not permitted
 * [SANDBOXED]...$ cat /private/var/tmp/can_r
 * r
 * [SANDBOXED]...$ echo "foo" > /private/var/tmp/can_w
 * [SANDBOXED]...$ echo "foo" > /private/var/tmp/can_r
 * sh: /private/var/tmp/can_r: Operation not permitted
 * [SANDBOXED]...$ exit
 * $
 * 
 */

int main(int argc, char *argv[]) {
    int rv;
    char *errbuff;

	rv = sandbox_init("sb2", SANDBOX_NAMED, &errbuff);
    if (rv != 0) {
        fprintf(stderr, "sandbox_init failed: %s\n", errbuff);
        sandbox_free_error(errbuff);
    } else {
        printf("pid: %d\n", getpid());
        putenv("PS1=[SANDBOXED] \\h:\\w \\u\\$ ");
        execl("/bin/sh", "sh", NULL);
    }

    return 0;
}
