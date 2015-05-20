void key_enter(void)
{
	int i;
	if (CURSOR.X == 0)
	{
		shift_down(CURSOR.Y);
		++CURSOR.Y;
	}
	else
	{
		++CURSOR.Y;
		shift_down(CURSOR.Y);
		for (i = CURSOR.X; i < BUFFER_WIDTH; ++i)
		{
			BUFFER[CURSOR.Y][i-CURSOR.X] = BUFFER[CURSOR.Y-1][i];
			BUFFER[CURSOR.Y-1][i] = 0;
		}
	}
	CURSOR.X = 0;
	++MAX_VPOS;
	UNSAVED = 1;
}

void key_backspace(void)
{
	if (CURSOR.X > 0)
	{
		shift_left(CURSOR.X);
		--CURSOR.X;
		UNSAVED = 1;
	}
	else 
	{
		if (CURSOR.Y > 0 || ACTUAL_VPOS > 0)
		{
			pull_together(CURSOR.Y);
			shift_up(CURSOR.Y);
			--CURSOR.Y;
			UNSAVED = 1;
		}
	}
}

void key_delete(void)
{
	if (CURSOR.X == BUFFER_WIDTH-1 || BUFFER[CURSOR.Y][CURSOR.X+1] == 0)
	{
		if (ACTUAL_VPOS + CURSOR.Y < MAX_VPOS)
		{
			pull_together(CURSOR.Y+1);
			shift_up(CURSOR.Y+1);
		}
	}
	else
	{
		shift_left(CURSOR.X + 1);
	}
	UNSAVED = 1;
}

void key_downarrow(void);

void key_rightarrow(void)
{
	if (CURSOR.X < WIDTH-1 
		&& BUFFER[ACTUAL_VPOS+CURSOR.Y][CURSOR.X] != '\0')
	{
		++CURSOR.X;
	}
	else
	{
		if (CURSOR.Y < MIN(MAX_VPOS-1, HEIGHT))
		{
			CURSOR.X = 0;
			++CURSOR.Y;
		}
	}
}

void key_uparrow(void);

void key_leftarrow(void)
{
	if (CURSOR.X > 0)
	{
		--CURSOR.X;
	}
	else 
	{
		if (CURSOR.Y != 0)
		{
			CURSOR.X = WIDTH-1;
			key_uparrow();
		}
	}
}

void key_downarrow(void)
{
	if (CURSOR.Y < MIN(MAX_VPOS-1, HEIGHT))
	{
		while (CURSOR.X != 0 
				&& BUFFER[ACTUAL_VPOS+CURSOR.Y+1][CURSOR.X-1]=='\0')
		{
			if (CURSOR.X > 0)
			{
				--CURSOR.X;
			}
		}
		if (CURSOR.Y == HEIGHT-1)
		{
			if (ACTUAL_VPOS+HEIGHT < MAX_VPOS + 1)
			{
				++ACTUAL_VPOS;
			}
		}
		else
		{
			++CURSOR.Y;
		}
	}
}

void key_uparrow(void)
{
	if (CURSOR.Y >= 0 && ACTUAL_VPOS + CURSOR.Y > 0)
	{
		while (CURSOR.X!=0 
				&& BUFFER[ACTUAL_VPOS+CURSOR.Y-1][CURSOR.X-1]=='\0')
		{
			if (CURSOR.X > 0)
				--CURSOR.X;
		}

		if (CURSOR.Y == 0)
		{
			--ACTUAL_VPOS;
		}
		else
		{
			--CURSOR.Y;
		}
	}
}

void key_home(void)
{
	CURSOR.X = 0;
}

void key_end(void)
{
	while (CURSOR.X != WIDTH-1 
			&& BUFFER[ACTUAL_VPOS+CURSOR.Y][CURSOR.X] != 0)
	{
		++CURSOR.X;
	}
}

void key_pgdn(void)
{
	if (ACTUAL_VPOS + HEIGHT < MAX_VPOS-HEIGHT)
	{
		ACTUAL_VPOS += HEIGHT;
	}
	else 
	{
		ACTUAL_VPOS = MAX_VPOS-HEIGHT + 1;
		CURSOR.Y = HEIGHT - 1;
	}
	key_home();
}

void key_pgup(void)
{
	if (ACTUAL_VPOS > HEIGHT)
	{
		ACTUAL_VPOS -= HEIGHT;
	}
	else 
	{
		ACTUAL_VPOS = 0;
		CURSOR.Y = 0;
	}
	key_home();
}

void key_ctrl_s(void)
{
	int h, w;
	if (FILENAME == NULL)
	{
		FILENAME = (unsigned char *)malloc(256*sizeof(char));
		if (FILENAME == NULL)
		{
			DestroyAndExit("Can't open file!");
		}
		set_crd(WIDTH/2, HEIGHT);
		printf("Save to: ");
		scanf("%255[^\n]s", FILENAME);
		DOCUMENT = fopen((char *)FILENAME, "w+");
		if (DOCUMENT == NULL)
		{
			DestroyAndExit("Can't open file!");
		}
	}
	fseek(DOCUMENT, 0, SEEK_SET);
	for (h = 0; h < MAX_VPOS; ++h)
	{
		for(w = 0; w < BUFFER_WIDTH; ++w)
		{
			if (BUFFER[h][w] == 0)
			{
				break;
			}
		}
		if (w != 0)
		{
			fwrite(BUFFER[h], w, 1, DOCUMENT);
		}
		fwrite("\n", 1, 1, DOCUMENT);
	}
	UNSAVED = 0;
}

void select_func(void)
{
	if (SELECTION_STATE == 0)
	{
		SELECTION_STATE = 1;
		SELECTION[0].X = ACTUAL_VPOS + CURSOR.X;
		SELECTION[0].Y = ACTUAL_VPOS + CURSOR.Y;
	}
	else 
	{
		SELECTION[1].X = ACTUAL_VPOS + CURSOR.X;
		SELECTION[1].Y = ACTUAL_VPOS + CURSOR.Y;
	}
}

void key_sel_left(void)
{
	select_func();
	key_leftarrow();
}

void key_sel_up(void)
{
	select_func();
	key_uparrow();
}

void key_sel_right(void)
{
	select_func();
	key_rightarrow();
}

void key_sel_down(void)
{
	select_func();
	key_downarrow();
}

void key_copy(void)
{
	int i,
		min = MIN(SELECTION[0].X, SELECTION[1].X),
		max = MAX(SELECTION[0].X, SELECTION[1].X);
	if (SELECTION_STATE)
	{
		for (
			i = min; 
			i < max; 
			CLIPBOARD[i-min] = BUFFER[SELECTION[0].Y][i], ++i
		);
	}
}

void key_cut(void)
{
	int i,
		min = MIN(SELECTION[0].X, SELECTION[1].X),
		max = MAX(SELECTION[0].X, SELECTION[1].X);
	key_copy();
	for (
		i = MAX(SELECTION[0].X, SELECTION[1].X);
		i < WIDTH;
		BUFFER[SELECTION[0].Y][i-(max-min)] = BUFFER[SELECTION[0].Y][i], ++i
	);
}

void key_paste(void)
{
	int i,
		min = MIN(SELECTION[0].X, SELECTION[1].X),
		max = MAX(SELECTION[0].X, SELECTION[1].X);
	for (
		i = min;
		i < max;
		BUFFER[CURSOR.Y][CURSOR.X + i] = CLIPBOARD[i-min], ++i
	);
}

void key_find(void)
{
	int		i;
	char	*position;
	char	strbuf[80];
	set_crd(WIDTH/2, HEIGHT);
	fwrite("find: ", 6, 1, stdout); 
	fgets(strbuf, 80, stdin);
	for (i = 0; i < MAX_VPOS; ++i)
	{
		position = strstr((char *)BUFFER[i], strbuf);
		if (position != NULL)
		{
			ACTUAL_VPOS = i;
			CURSOR.X = (int)(position - (char *)BUFFER[i]);
			return;
		}
	}
}