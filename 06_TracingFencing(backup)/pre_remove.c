#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int remove(const char *pathname)
{
	char* substr = "PROTECT";
	char* ch = strstr(pathname, substr);
	if (ch != NULL) return 0;
	struct stat tmp;
	stat(pathname, &tmp);
	if(tmp.st_mode & S_IFDIR) return rmdir(pathname);
	else return unlink(pathname);
	return -1;
}
