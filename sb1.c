#include <stdio.h>
#include <sandbox.h>

/*
 * $ ./sb1
 * pid: 30310
 * [SANDBOXED]...$ ping -c4 8.8.8.8
 * PING 8.8.8.8 (8.8.8.8): 56 data bytes
 * ping: sendto: Operation not permitted
 * ping: sendto: Operation not permitted
 * Request timeout for icmp_seq 0
 * ping: sendto: Operation not permitted
 * Request timeout for icmp_seq 1
 * ping: sendto: Operation not permitted
 * Request timeout for icmp_seq 2
 *
 * --- 8.8.8.8 ping statistics ---
 * 4 packets transmitted, 0 packets received, 100.0% packet loss
 * [SANDBOXED]...$ exit
 * $
 *
 * (注：no-internetはmacOS用、iOSならnointernet。)
 */

int main(int argc, char *argv[]) {
    int rv;
    char *errbuff;

	rv = sandbox_init("no-internet", SANDBOX_NAMED, &errbuff);
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
