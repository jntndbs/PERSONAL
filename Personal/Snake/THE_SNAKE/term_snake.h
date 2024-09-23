#ifndef TERM_SNAKE_H
# define TERM_SNAKE_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <string.h>
# include <stdarg.h>
# include <limits.h>
# include <limits.h>
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <errno.h>
# include <fcntl.h>
# include <stdbool.h>
# include <termios.h>
# include <math.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>
# include <ncurses.h>

# define STARTING_LEN 4
# define STARTING_LIVES 3
# define QUIT_KEY 27
# define INP_BUFFER_SIZE 128
# define FRAMETIME 10000

# define C_RESET "\033[0m"
# define C_BOLD "\033[1m"
# define C_GREEN "\033[32m"
# define C_RED "\033[31m"
# define END_MESSAGE "GAME OVER\n\n"

enum	e_error
{
	SUCC = 0,
	FAIL = 1,
	RUNNING = 2
};

enum	e_directions
{
	UP = 'w',
	DOWN = 's',
	LEFT = 'a',
	RIGHT = 'd',
	SPACE = ' ',
	ESC = '\033'
};

typedef struct s_body
{
	__uint16_t		pos[2];
	bool			head;
	struct s_body	*next;
}	t_body;

typedef struct s_data
{
	__uint32_t		snake_len;
	__uint16_t		candy_pos[2];
	__uint16_t		new_body_pos[2];
	t_body			*snake;
	uint_fast16_t	rows;
	uint_fast16_t	cols;
	char			input;
	short			level;
	short			score;
	short			lives;
	bool			resized;
	bool			dead;
	bool			game_started;
	bool			game_paused;
	bool			game_over;
	short			exit_code;
	bool			tick;
	pthread_mutex_t	input_lock;
	pthread_mutex_t	data_lock;
	pthread_t		input_thread;
}	t_data;

// game_loop.c

void	game_loop(t_data *data);

// input_loop.c

void	*input_loop(void *arg);


// loop_utils.c

void	candy_pos_generate(t_data *data);
void	pause_game(t_data *data);
void	esc_sequence(t_data *data);
void	check_candy(t_data *data);
char	get_pos_char(t_data *data, __uint16_t x, __uint16_t y);
void	image_to_buffer(t_data *data, char *buffer);
char	*malloc_buffer(t_data *data);
char	*resize_image(t_data *data, char *buffer);

// list.c

t_body	*new_body(const t_body *data);
void	node_back(t_body **body, t_body *node);
void	free_list(t_body **body);
bool	body_add_back(t_body **body, const t_body *data);
int		body_len(t_body *body);
t_body	*last_node(t_body *body);

// utils.c

__uint16_t		get_terminal_rows(void);
__uint16_t		get_terminal_cols(void);
__uint64_t		get_time_us(void);
uint_fast32_t	delta_time(__uint64_t prev_time_ms);
void			clean_up(t_data *data);
void			error_exit(t_data *data, bool clean);
void			wait_for_start(t_data *data);
void			game_over_message(t_data *data);

#endif