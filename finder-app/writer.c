
#include <fcntl.h>
#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>

int create_dir_if_not_exists(char *path)
{
    struct stat sb;
    if (stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
    {
        return 0;
    }
    syslog(LOG_DEBUG, "Creating dir: %s", path);
    return mkdir(path, 0755);
}

void log_error(const char *message)
{
    char *err = strerror(errno);
    syslog(LOG_ERR, "%s", err);
    fprintf(stderr, "%s: %s\n", message, err);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: writer <path> <str>\n");
        return 1;
    }

    openlog(argv[0], LOG_PID | LOG_CONS, LOG_USER);

    char *path_input = argv[1];
    char *str = argv[2];
    char file_path[strlen(path_input)+1];

    strcpy(file_path, path_input);
    char *dir_path = dirname(path_input);

    if (create_dir_if_not_exists(dir_path) != 0)
    {
        log_error("Error creating dir");
        return 1;
    }

    int fd = open(file_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
    {
        log_error("Error opening file");
        return 1;
    }
    syslog(LOG_DEBUG, "Writing %s to file %s", str, file_path);
    int write_result = write(fd, str, strlen(str));
    if (write_result < 0)
    {
        log_error("Error writing file");
    }

    int close_err = close(fd);
    if (close_err < 0)
    {
        log_error("Error closing file");
        return 1;
    }

    return 0;
}
