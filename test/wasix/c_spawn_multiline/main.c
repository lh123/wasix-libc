#include <spawn.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

extern char **environ;

static const char expected_argument[] = "alpha\nbeta";

static int run_child(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "child received %d arguments, expected 3\n", argc);
        return 10;
    }
    if (strcmp(argv[2], expected_argument) != 0) {
        fprintf(stderr, "child argument mismatch: <%s>\n", argv[2]);
        return 11;
    }

    printf("argc=1 arg=<%s>\n", argv[2]);
    return 0;
}

int main(int argc, char **argv)
{
    if (argc > 1 && strcmp(argv[1], "--child") == 0) {
        return run_child(argc, argv);
    }

    char *child_argv[] = {
        "c-spawn-multiline",
        "--child",
        (char *)expected_argument,
        NULL,
    };
    pid_t child_pid;
    int error = posix_spawn(
        &child_pid,
        "/bin/c-spawn-multiline",
        NULL,
        NULL,
        child_argv,
        environ
    );
    if (error != 0) {
        fprintf(stderr, "posix_spawn failed: %d\n", error);
        return 20;
    }

    int status;
    if (waitpid(child_pid, &status, 0) < 0) {
        perror("waitpid");
        return 21;
    }
    if (!WIFEXITED(status)) {
        fprintf(stderr, "child did not exit normally: %d\n", status);
        return 22;
    }
    return WEXITSTATUS(status);
}
