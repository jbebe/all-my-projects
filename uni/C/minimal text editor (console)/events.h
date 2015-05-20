void process_key(void)
{
	if (INPUT_KEY < 32 || INPUT_MOD == 1)
	{
		/* spec. chars */
		switch (INPUT_KEY)
		{
		case 19:
			key_ctrl_s();
			break;
		case 27:
			/* escape */
			RUN = 0;
			break;
		case '\r':
			SELECTION_STATE = 0;
			key_enter();
			break;
		case '\b':
			SELECTION_STATE = 0;
			key_backspace();
			break;
		case 75:
			SELECTION_STATE = 0;
			key_leftarrow();
			break;
		case 72:
			SELECTION_STATE = 0;
			key_uparrow();
			break;
		case 77: 
			SELECTION_STATE = 0;
			key_rightarrow();
			break;
		case 80:
			SELECTION_STATE = 0;
			key_downarrow();
			break;
		case 83:
			SELECTION_STATE = 0;
			key_delete();
			break;
		case 71:
			SELECTION_STATE = 0;
			key_home();
			break;
		case 79:
			SELECTION_STATE = 0;
			key_end();
			break;
		case 73:
			SELECTION_STATE = 0;
			key_pgup();
			break;
		case 81:
			SELECTION_STATE = 0;
			key_pgdn();
			break;
		case 115:
			key_sel_left();
			break;
		case 141:
			key_sel_up();
			break;
		case 116:
			key_sel_right();
			break;
		case 145:
			key_sel_down();
			break;
		case 3:
			key_copy();
			break;
		case 24:
			SELECTION_STATE = 0;
			key_cut();
			break;
		case 22:
			SELECTION_STATE = 0;
			key_paste();
			break;
		case 6:
			key_find();
			break;
		default:
			break;
		}
		INPUT_MOD = 0;
	}
	else
	{
		if (INPUT_KEY == 224)
		{
			INPUT_MOD = 1;
		}
		else 
		{
			if (INPUT_KEY > 31 && INPUT_KEY < 256)
			{
				/* letters */
				shift_right(CURSOR.X);
				BUFFER[ACTUAL_VPOS+CURSOR.Y][CURSOR.X]=(unsigned char)INPUT_KEY;
				if (CURSOR.X + 1 < WIDTH)
				{
					++CURSOR.X;
				}
				else 
				{
					++CURSOR.Y;
					CURSOR.X = 0;
				}
				UNSAVED = 1;

				SELECTION_STATE = 0;
			}
		}
	}
}