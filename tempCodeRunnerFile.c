  while ((ch = getch()) != '\r' && i < MAX_PASSWORD_LENGTH) {
        if (ch == '\b') { // If backspace is pressed, remove the last character
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (ch >= '0' && ch <= '9') { // If digit is entered, add it to password string and mask it
            password_string[i++] = ch;
            printf("*");
        }
    }
    password_string[i] = '\0'; // Add null terminator to password string
    pass = atoi(password_string); // Convert password string to integer