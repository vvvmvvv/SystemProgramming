
char    lowercase_to_uppercase(char c) {
    const int     shift = 'A' - 'a';

    if (c >= 'a' && c <= 'z') {
        return (c + shift);
    } else {
        return (c);
    }
}

int    transform_text(char *text) {
    int     i;
    int     chars_rewritten;
    char    new_char;

    i = 0;
    chars_rewritten = 0;
    while (text[i] != '\0') {
        new_char = lowercase_to_uppercase(text[i]);
        if (text[i] != new_char)
            chars_rewritten++;
        text[i] = new_char;
        i++;
    }
    return (chars_rewritten);
}


