#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>

#define READ_SIZE 512
#define MAX_DIR_PATH 512

struct Paths{
    char* source, *dest;
};

void *copy(void * threadargs){
    int f1, f2, nr;
    char s[READ_SIZE];
    struct Paths * paths;
    paths = (struct Paths *) threadargs;

    f1 = open(paths->source,O_RDONLY);
    if (f1 == -1){
        perror(paths->source);
        return NULL;
    }

    f2 = open(paths->dest, O_WRONLY | O_CREAT, 0644);
    if (f2 == -1){
        perror(paths->dest);
        return NULL;
    }

    while((nr = read(f1,s,READ_SIZE))){
        if (nr == -1) break;
        write(f2,s,nr);
    }

    close(f1);
    close(f2);

    return NULL;
}

int main(int argc, char* argv[]){
    DIR *dirp;
    struct dirent *direntp;
    struct stat stat_buf;
    if (argc != 2)
    {
        fprintf( stderr, "Usage: %s dest_dir_name\n", argv[0]);
        exit(1);
    }
    if ((dirp = opendir(".")) == NULL)
    {
        perror(argv[1]);
        exit(2);
    }
    while ((direntp = readdir( dirp)) != NULL)
    {
        if (lstat(direntp->d_name, &stat_buf) != 0) {
            perror(argv[1]);
            exit(3);
        }
        if (S_ISREG(stat_buf.st_mode)) {
            char path[MAX_DIR_PATH];
            strcpy(path, argv[1]);
            strcat(path, "/");
            strcat(path, direntp->d_name);
            pthread_t thread;
            struct Paths *paths = malloc(sizeof(struct Paths *));
            paths->source = direntp->d_name;
            paths->dest = path;
            pthread_create(&thread, NULL, copy, (void *) paths);
            pthread_join(thread, NULL);
        }
        else {
            continue;
        }
    }
    closedir(dirp);
    pthread_exit(0);
}                �?                    �?                    �?                    �?         	           �?         
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ��H��H��/  H��t��H���     �5j/  ��%k/   ��h    ���������h   ���������h   ���������h   ��������h   ��������h   ��������h   ����������%M/  D  ����%�.  D  ����%�.  D  ����%�.  D  ����%�.  D  ����%�.  D  ����%�.  D  ����%�.  D  ��1�I��^H��H���PTL��  H�o  H�=
  ��.  ��H�=�.  H��.  H9�tH�n.  H��t	���    ��    H�=�.  H�5�.  H)�H��H��?H��H�H��tH�E.  H��t��fD  ��    ���=E.   u+UH�=".   H��tH�=&.  �����d����.  ]� ��    ���w�����UH��H��0H�}�H�E�H�E�H�E��H�E��@ЉE�   ����H�E�H�E��U�H�E�����UH��H��0H�}�H�E�H�E�H�E��H�E��@)ЉE�   �j���H�E�H�E��U�H�E�����UH��H��0H�}�H�E�H�E�H�E��H�E��@�E�   �"���H�E�H�E��U�H�E�����UH��H��0H�}�H�E�H�E�H�E��@��uf���E��"H�E�� �*�H�E��@�*��^��Z��E�   ����H�E�H�E��E�� H�E�����UH��H��PdH�%(   H�E�1��!   H�5�  �   �=���H�E�H�PH�E�H��H�=�  �    �m���H�U�H�E�H��H�T����    H�������H�E�H�U�H�zH��H�x����    �����H�E�H�U�H�zH��H������    ����H�E�H�U�H�zH��H������    �����E�    �6�E�H�H�D��H�U�H��H������H�E�� ��H�=�  �    �s����E��}�~�H�E�H�U�H��H������H�E�� �Z�H�=�  �   �9����    �?���f.�     D  ��AWL�=�(  AVI��AUI��ATA��UH�-�(  SL)�H������H��t1��    L��L��D��A��H��H9�u�H��[]A\A]A^A_�ff.�     ���   ��H��H���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 Write 2 numbers (0, 0 to leave):  %d %d %d
 %f
 ;d      �����   h����   x����   �����   �����   ���  a���0  ����P  ���p  x����  �����             zR x�        `���/    D    $   4   H����    FJw� ?:*3$"       \   ����              t   ����p              �   ����G    E�C~      �    ���I    E�C@     �   )���H    E�C      �   Q���q    E�Ch       ����O   E�C       D   ,  ����e    F�I�E �E(�D0�H8�G@n8A0A(B BBB    t  ���                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  �                           v                            (             x=                           �=                    ���o    �                           �      
       �                                           �?             �                                         P             �       	                            ���o          ���o           ���o           ���o    �      ���o                                                                                           �=                      0      @      P      `      p      �      �                                                      @      GCC: (Ubuntu 9.2.1-9ubuntu2) 9.2.1 20191008                                                       8                    X                    |                    �                    �                                         �                   	                     
 P                                                                                  �                    �                                         (                                          8                     �                     x=                    �=                    �=                    �?                     @                    @                                        ��                     P                   �              !     �              7     @             F     �=              m                    y     x=              �    ��                    ��                �     $"                   ��                �      �=              �     �=              �      x=              �      8               �     �?              �                                                          .                      �      @              J                     ]    @              d    �      q          (              l                     �                     �     @              �    P      I       �    	      G       �                      �   @              �    �      H       �                   �    �      e                                                 �     @              �           /       2    @              >    R      O      C                     ]                     w   @              �                      �  "                    crtstuff.c deregister_tm_clones __do_global_dtors_aux completed.8055 __do_global_dtors_aux_fini_array_entry frame_dummy __frame_dummy_init_array_entry ex5.c __FRAME_END__ __init_array_end _DYNAMIC __init_array_start __GNU_EH_FRAME_HDR _GLOBAL_OFFSET_TABLE_ __libc_csu_fini pthread_create@@GLIBC_2.2.5 _ITM_deregisterTMCloneTable write@@GLIBC_2.2.5 _edata divisao printf@@GLIBC_2.2.5 __libc_start_main@@GLIBC_2.2.5 __data_start subtracao soma __gmon_start__ __dso_handle multiplicacao _IO_stdin_used __libc_csu_init pthread_exit@@GLIBC_2.2.5 malloc@@GLIBC_2.2.5 __bss_start main pthread_join@@GLIBC_2.2.5 __isoc99_scanf@@GLIBC_2.7 __TMC_END__ _ITM_registerTMCloneTable __cxa_finalize@@GLIBC_2.2.5  .symtab .strtab .shstrtab .interp .note.gnu.property .note.gnu.build-id .note.ABI-tag .gnu.hash .dynsym .dynstr .gnu.version .gnu.version_r .rela.dyn .rela.plt .init .plt.got .plt.sec .text .fini .rodata .eh_frame_hdr .eh_frame .init_array .fini_array .dynamic .data .bss .comment                                                                                                                             #             8      8                                     6             X      X      $                              I             |      |                                     W   ���o       �      �      $                             a             �      �      8                          i                           �                              q   ���o       �      �                                  ~   ���o                     P                            �             P      P      �                            �      B                   �                           �                                                         �                           �                             �             �      �                                   �             �      �      p                             �                                                        �             (      (                                    �                             8                              �             8       8       d                              �             �       �       �                             �             x=      x-                                   �             �=      �-                                   �             �=      �-                                  �             �?      �/      x                                          @       0                                                @      0                                         0               0      ,                                                   @0               .                 	                      H7      �                                                   :                                   