#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define INITIAL_DELAY 100000  // Initial delay in microseconds
#define WIDTH 60
#define HEIGHT 50

typedef struct Snake {
    int x, y;
    struct Snake *next;
} Snake;

Snake *head = NULL;
int foodX, foodY;
int score = 0;
int delay = INITIAL_DELAY;  // Variable delay to adjust speed
char direction = 'R';

void init_snake() {
    Snake *new_node = (Snake *)malloc(sizeof(Snake));
    new_node->x = WIDTH / 2;
    new_node->y = HEIGHT / 2;
    new_node->next = NULL;
    head = new_node;
}

void place_food() {
    foodX = rand() % (WIDTH - 2) + 1;  // Ensures food appears within borders
    foodY = rand() % (HEIGHT - 2) + 1;
}

void add_segment() {
    Snake *new_segment = (Snake *)malloc(sizeof(Snake));
    new_segment->x = head->x;
    new_segment->y = head->y;
    new_segment->next = head;
    head = new_segment;
}

void move_snake() {
    int prevX = head->x, prevY = head->y, tempX, tempY;
    Snake *current = head->next;

    switch (direction) {
        case 'U': head->y--; break;
        case 'D': head->y++; break;
        case 'L': head->x--; break;
        case 'R': head->x++; break;
    }

    while (current) {
        tempX = current->x;
        tempY = current->y;
        current->x = prevX;
        current->y = prevY;
        prevX = tempX;
        prevY = tempY;
        current = current->next;
    }
}

int check_collision() {
    if (head->x <= 0 || head->x >= WIDTH - 1 || head->y <= 0 || head->y >= HEIGHT - 1)
        return 1;

    Snake *current = head->next;
    while (current) {
        if (current->x == head->x && current->y == head->y)
            return 1;
        current = current->next;
    }
    return 0;
}

void update_food() {
    if (head->x == foodX && head->y == foodY) {
        score++;
        add_segment();
        place_food();
        delay = delay > 30000 ? delay - 5000 : 30000;  // Increase speed
    }
}

void draw_game() {
    clear();

    // Draw borders
    for (int i = 0; i < WIDTH; i++) {
        mvprintw(0, i, "#");
        mvprintw(HEIGHT - 1, i, "#");
    }
    for (int i = 1; i < HEIGHT - 1; i++) {
        mvprintw(i, 0, "#");
        mvprintw(i, WIDTH - 1, "#");
    }

    // Draw food
    mvprintw(foodY, foodX, "*");

    // Draw snake
    Snake *current = head;
    while (current) {
        mvprintw(current->y, current->x, "O");
        current = current->next;
    }

    // Display score
    mvprintw(HEIGHT, 0, "Score: %d", score);
    mvprintw(HEIGHT + 1, 0, "Use arrow keys to move. Press 'q' to quit.");
    refresh();
}

void free_snake() {
    Snake *current = head;
    while (current) {
        Snake *next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    initscr();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    init_snake();
    place_food();

    while (1) {
        int ch = getch();
        if (ch == 'q') break;  // Quit the game
        if (ch == KEY_UP && direction != 'D') direction = 'U';
        if (ch == KEY_DOWN && direction != 'U') direction = 'D';
        if (ch == KEY_LEFT && direction != 'R') direction = 'L';
        if (ch == KEY_RIGHT && direction != 'L') direction = 'R';

        move_snake();
        if (check_collision()) break;

        update_food();
        draw_game();

        usleep(delay);
    }

    free_snake();
    endwin();
    printf("Game Over! Final Score: %d\n", score);
    return 0;
}
