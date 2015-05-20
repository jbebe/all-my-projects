void init_buffer()
{
	int i, j;
	BUFFER_WIDTH = WIDTH;
	BUFFER_HEIGHT = 200; /* 80 * 26214 ~ 2mb */

	BUFFER = (unsigned char **)malloc(BUFFER_HEIGHT * sizeof(char *));
	if (BUFFER == NULL)
	{
		BUFFER_WIDTH = 0;
		BUFFER_HEIGHT = 0;
		DestroyAndExit("Can't allocate memory.");
	}

	for (i = 0; i < BUFFER_HEIGHT; ++i)
	{
		BUFFER[i] = (unsigned char *)malloc(BUFFER_WIDTH * sizeof(char));
		if (BUFFER[i] == NULL)
		{
			BUFFER_WIDTH = 0;
			BUFFER_HEIGHT = i;
			DestroyAndExit("Can't allocate all lines of buffer.");
		}
		for (j = 0; j < WIDTH; ++j)
		{
			BUFFER[i][j] = '\0';
		}
	}
}

void file_to_buffer(void)
{
	int c,
		h = 0, w = 0;

	if (FILENAME == NULL)
	{
		DestroyAndExit("Can't open file!");
	}

	DOCUMENT = fopen((char *)FILENAME, "r+");
	
	if (DOCUMENT == NULL)
	{
		DestroyAndExit("Can't open file!");
	}

	while (((c = fgetc(DOCUMENT)) != EOF) && h < BUFFER_HEIGHT)
    {
		if (c == '\r')
		{
			continue;
		}
		if (c == '\n')
		{
			++h;
			w = 0;
		}
		else
		{
			if (w < WIDTH)
			{
				BUFFER[h][w] = (unsigned char)c;
				++w;
			}
			else
			{
				++h;
				w = 0;
				BUFFER[h][w] = (unsigned char)c;
			}
		}
    }
	MAX_VPOS = h;
}

void init_clipboard(void)
{
	int i;
	CLIPBOARD = (unsigned char *)malloc(WIDTH * sizeof(unsigned char));
	for (
		i = 0; 
		i < WIDTH; 
		CLIPBOARD[i++] = 0
	);
}