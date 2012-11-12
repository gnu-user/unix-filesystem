//(Char [6]) The file name contains the user name given to the file or directory, it will take up 6 bytes and be limited to 6 characters.
//(Boolean) File type identifies whether the index file points to file (1) or a directory (0) which will take up 1 byte.
//(Boolean) File permissions is whether the file has read, write executable, or locked permissions, which will take up 4 bytes.
//(Integer) File created date stores the date the file was created on, and will take up 4 bytes.
//(Integer) File last accessed date stores the date the file was last accessed on, and will take up 4 bytes.
//(Integer) File last modified date stores the date the file was last modified on, and will take up 4 bytes.
//(Integer) File owner stores the user's unique identifier, taking up 4 bytes.
//(Integer) Last modified stores the unique identifier of the user to last modify the file, and it will take up 4 bytes.
//(Short Integer) File size stores size of the file, and will take up 2 bytes.
//(Pointer) Location stores the address of the block on disk, and will take up 4 bytes.
//(Boolean) The encrypted identifier will identities whether the file is encrypted and will take up 1 byte.
//(Integer) The check sum of the data (taken before it is encrypted) will take up 4 bytes.
