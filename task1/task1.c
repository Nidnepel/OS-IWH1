//
// Created by lependin on 20.03.23.
//

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


char *key_words[] = {"for", "int", "char", "const", "void"};
int index_shifts[] = {3, 3, 4, 5, 4};
const int keywords_count = 5;
const int buf_size = 6000;
const int output_buff_size = 300;

void solve_task(const char *input_text, size_t size, int *answer) {
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < keywords_count; ++j) {
            if (i + index_shifts[j] >= size)
                continue;

            int flag = 1;
            for (size_t d = 0; d < index_shifts[j]; ++d) {
                if (input_text[i + d] != key_words[j][d])
                    flag = 0;
            }

            answer[j] += flag;
        }
    }
}

int main(int argc, char *argv[]) {
    int fd1[2], fd2[2], result;
    size_t size;

    if (pipe(fd1) < 0 || pipe(fd2) < 0) {
        printf("Can\'t open pipe\n");
        exit(-1);
    }

    result = fork();
    if (result < 0) {
        printf("Can\'t fork child\n");
        exit(-1);
    } else if (result > 0) { /* Parent process */
        if (close(fd1[0]) < 0) {
            printf("parent: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        int input_file = open(argv[1], O_RDONLY, 0666);

        char read_buf[buf_size];
        size_t input_size = read(input_file, read_buf, sizeof(read_buf) - 1);
        close(input_file);
        read_buf[input_size] = 0;

        size = write(fd1[1], read_buf, input_size + 1);
        if (size != input_size + 1) {
            printf("Can\'t write all string to pipe\n");
            exit(-1);
        }
        if (close(fd1[1]) < 0) {
            printf("parent: Can\'t close writing side of pipe\n");
            exit(-1);
        }
    } else { /* Child process */
        char logic_buf[buf_size];
        if (close(fd1[1]) < 0) {
            printf("child: Can\'t close writing side of pipe\n");
            exit(-1);
        }
        size = read(fd1[0], logic_buf, buf_size);
        if (close(fd1[0]) < 0) {
            printf("child: Can\'t close reading side of pipe\n");
            exit(-1);
        }
        int *answer = (int*) malloc(100 * sizeof(int));
        solve_task(logic_buf, size, answer);
        char output_buff[output_buff_size];
        for (int j = 0, curr = 0; j < keywords_count; ++j) {
            for (int t = 0; t < index_shifts[j]; ++t) {
                output_buff[curr++] = key_words[j][t];
            }
            output_buff[curr++] = ' ';
            output_buff[curr++] = ':';
            output_buff[curr++] = ' ';
            char num[10];
            size_t num_size = sprintf(num, "%d", answer[j]);
            for (int t = 0; t < num_size; ++t) {
                output_buff[curr++] = num[t];
            }
            output_buff[curr++] = '\n';
        }
        int result2 = fork();

        if (result2 > 0) {

            if (close(fd2[0]) < 0) {
                printf("parent: Can\'t close reading side of pipe\n");
                exit(-1);
            }
            size = write(fd2[1], output_buff, strlen(output_buff) + 1);
            if (size != strlen(output_buff) + 1) {
                printf("Can\'t write all string to pipe\n");
                exit(-1);
            }
            if (close(fd2[1]) < 0) {
                printf("child: Can\'t close writing side of pipe\n");
                exit(-1);
            }

        } else if (result2 == 0) {
            char output[buf_size];

            if (close(fd2[1]) < 0) {
                printf("child: Can\'t close writing side of pipe\n");
                exit(-1);
            }
            read(fd2[0], output, buf_size);

            int output_file = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);

            write(output_file, output, strlen(output + 1));
        } else {
            printf("something wrong, i can feel it\n");
        }
    }
    return 0;
}