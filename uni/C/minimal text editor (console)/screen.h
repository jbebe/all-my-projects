void draw_fun()
{
	int i;
	char *tips[] = {
		"What seems to be the problem?",
		"Are you in trouble, human?   ",
		"Shall I go off your screen?  ",
		"What a lovely day for coding!",
		"I stay here just in case.    ",
		"Find any difficulties so far?",
		"Is my presence bothering you?",
		"I like staying here, manlet. ",
		"Does this program even work? ",
		"My name is clip. Paperclip.  "
	};
	char *paperclip[] = {
		" .-------------------------------. ",
		" |           random text         | ",
		"  `````\\/```````````````````````` ",
		" .-. ",
		" O O ",
		" | | ",
		" |_|| ",
		" \\__/ ",
	};
	set_color(yellow, black);
	for (i = 0; i < sizeof(tips)/sizeof(char *); ++i)
	{
		if (i > 2)
		{
			set_crd(WIDTH-29, i + HEIGHT-9);
			set_text((unsigned char *)paperclip[i], 6);
		}
		else 
		{
			set_crd(WIDTH-35, i + HEIGHT-9);
			if (i == 1)
			{
				printf(" | %-29s | ", tips[RAND]);
			}
			else 
			{
				set_text((unsigned char *)paperclip[i], 35);
			}
		}
	}
}

void update_status(void)
{
	int info_length;
	set_color(black, grey);
	set_crd(0, HEIGHT);
	
	info_length = printf(
			" Ln %2d | Col %2d | %10s%c "
			#ifdef DEBUG_MODE
			"| HEIGHT: %2d | ACTUAL_VPOS: %2d | MAX_VPOS: %2d"
			#endif
			, 
			CURSOR.Y + 1, CURSOR.X + 1, FILENAME == NULL ? "unnamed" : FILENAME, UNSAVED ? '*' : ' '
			#ifdef DEBUG_MODE
			, HEIGHT, ACTUAL_VPOS, MAX_VPOS
			#endif
	);

	printf("%*s", WIDTH-info_length, " ");
	set_color(grey, black);
}

void redraw_buffer(void)
{
	int i,
		min = MIN(SELECTION[0].X, SELECTION[1].X),
		max = MAX(SELECTION[0].X, SELECTION[1].X);
	for (i = 0; i < MIN(MAX_VPOS,HEIGHT); ++i)
	{
		set_crd(0,i);
		if (CURSOR.Y == i)
		{
			set_color(white, darkgrey);
		}
		else
		{
			set_color(grey, black);
		}
		set_text(BUFFER[ACTUAL_VPOS + i], WIDTH);
		/* selection */
		if (SELECTION_STATE && ACTUAL_VPOS + i == SELECTION[0].Y)
		{
			set_color(black, white);
			set_crd(min, i);
			set_text(&BUFFER[ACTUAL_VPOS + i][min], max-min);
		}
	}
}

void redraw_screen()
{
	update_status();
	redraw_buffer();
	draw_fun();
	set_crd(CURSOR.X, CURSOR.Y);
}