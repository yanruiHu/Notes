// Author: Yanrui Hu
// Date: 2022/10/10
// Description: Using C to implement the basic function of linux command `ls
// -l`.
// Keywords: 面试题, 模拟Linux命令`ls -l`
// Version: 0.1

#include <dirent.h>
#include <error.h>
#include <grp.h>
#include <pwd.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

#define ELOG(exp) (printf("%d: " exp "\n", __LINE__))
#define SLOG(str_p) (printf("%d: " #str_p ": %s\n", __LINE__, str_p))

void custom_ls(const char[]);
void custom_stat(char *filepath, char *filename);
void show_file_info(char *, struct stat *);
void mode_to_letters(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int argc, char *argv[]) {
  if (argc == 1) {
    custom_ls(".");
  } else {
    while (--argc) {
      ++argv;
      printf("%s:\n", *argv);
      custom_ls(*argv);
    }
  }
  return 0;
}

/* 自定义的 ls */
void custom_ls(const char dirname[]) {
  DIR *dir_ptr;
  struct dirent *dirent_ptr;

  if ((dir_ptr = opendir(dirname)) == NULL) {
    fprintf(stderr, "custom_ls :cannot open %s\n", dirname);
  } else {
    while ((dirent_ptr = readdir(dir_ptr)) != NULL) {
      char filepath[256 * 12];
      strcpy(filepath, dirname);
      strcat(filepath, "/");
      strcat(filepath, dirent_ptr->d_name);
      // SLOG(filepath);      // SLOG(dirent_ptr->d_name);

      custom_stat(filepath, dirent_ptr->d_name);
    }
    closedir(dir_ptr);
  }
}

/* 自定义的 stat */
void custom_stat(char *filepath, char *filename) {
  struct stat info;
  if (stat(filepath, &info) == -1) {
    perror(filepath);
  } else {
    show_file_info(filename, &info);
  }
}

/* 展示文件信息 */
void show_file_info(char *filename, struct stat *info_p) {
  char modestr[11];

  mode_to_letters(info_p->st_mode, modestr);

  printf("%s", modestr);  // 显示文件的MODE（文件类型和权限模式）
  printf(" %4d", (int)info_p->st_nlink);        // 显示文件的Link Count
  printf(" %-s", uid_to_name(info_p->st_uid));  // 显示文件的所有者s
  printf(" %-s", gid_to_name(info_p->st_gid));  // 显示文件的群组
  printf(" %8ld", (long)info_p->st_size);       // 显示文件的Size
  printf(" %.12s",
         4 + ctime(&info_p->st_mtime));  // 显示文件的Last-Modified Time
  printf(" %s\n", filename);             // 显示文件名
}

/* 将 mode 的数字表示 转换成字母表示 */
void mode_to_letters(int mode, char str[]) {
  strcpy(str, "----------");
  if (S_ISDIR(mode)) str[0] = 'd';
  if (S_ISCHR(mode)) str[0] = 'c';
  if (S_ISBLK(mode)) str[0] = 'b';

  if (mode & S_IRUSR) str[1] = 'r';
  if (mode & S_IWUSR) str[2] = 'w';
  if (mode & S_IXUSR) str[3] = 'x';

  if (mode & S_IRGRP) str[4] = 'r';
  if (mode & S_IWGRP) str[5] = 'w';
  if (mode & S_IXGRP) str[6] = 'x';

  if (mode & S_IROTH) str[7] = 'r';
  if (mode & S_IWOTH) str[8] = 'w';
  if (mode & S_IXOTH) str[9] = 'x';
}

/* 通过 uid 获取 user name */
char *uid_to_name(uid_t uid) {
  struct passwd *getpwuid(__uid_t __uid), *pw_ptr;

  static char numstr[10];

  if ((pw_ptr = getpwuid(uid)) == NULL) {
    sprintf(numstr, "%d", uid);
    return numstr;
  } else {
    return pw_ptr->pw_name;
  }
}

/* 通过 gid 获取 group name */
char *gid_to_name(gid_t gid) {
  struct group *getgrgid(), *grp_ptr;
  static char numstr[10];

  if ((grp_ptr = getgrgid(gid)) == NULL) {
    sprintf(numstr, "%d", gid);
    return numstr;
  } else {
    return grp_ptr->gr_name;
  }
}
