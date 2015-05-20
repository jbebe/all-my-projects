void shift_left(int offset)
{
	int i;
	BUFFER[CURSOR.Y][WIDTH-1] = 0;
	for (i = offset; i < WIDTH; ++i)
	{
		BUFFER[ACTUAL_VPOS+CURSOR.Y][i-1] = BUFFER[ACTUAL_VPOS+CURSOR.Y][i];
	}
}

void shift_right(int offset)
{
	int i;
	for (i = WIDTH - 2; i > offset; --i)
	{
		BUFFER[ACTUAL_VPOS+CURSOR.Y][i] = BUFFER[ACTUAL_VPOS+CURSOR.Y][i-1];
	}
	BUFFER[CURSOR.Y][WIDTH-1] = 0;
}

void shift_up(int offset)
{
	int h, w;
	for (h = offset; h < MAX_VPOS; ++h)
	{
		for (w = 0; w < BUFFER_WIDTH; ++w)
		{
			BUFFER[h][w] = BUFFER[h+1][w];
		}
	}
	for (w = 0; w < BUFFER_WIDTH; ++w)
	{
		BUFFER[MAX_VPOS][w] = 0;
	}
}

void shift_down(int offset)
{
	int h, w;

	for (h = MAX_VPOS + 1; h > offset; --h)
	{
		for (w = 0; w < BUFFER_WIDTH; ++w)
		{
			BUFFER[h][w] = BUFFER[h-1][w];
		}
	}
	for (w = 0; w < BUFFER_WIDTH; ++w)
	{
		BUFFER[CURSOR.Y][w] = 0;
	}
}

void pull_together(int offset)
{
	int i, 
		freespace = BUFFER_WIDTH;
	for (i = BUFFER_WIDTH-1; i >= 0; --i)
	{
		if (BUFFER[offset-1][i] != 0)
		{
			break;
		}
		freespace = i;
	}
	for (i = freespace; i < BUFFER_WIDTH; ++i)
	{
		BUFFER[offset-1][i] = BUFFER[offset][i-freespace];
	}
	CURSOR.X = freespace;
}
