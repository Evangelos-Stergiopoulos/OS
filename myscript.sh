#!/bin/bash

ls /home | shuf -n 3 > usernames.txt
usernames_file="usernames.txt"

file_to_find="myscript.sh"

# Check if the usernames file exists
if [ ! -f "$usernames_file" ]; then
    echo "Usernames file $usernames_file not found."
    exit 1
fi

# Read usernames from the file
while IFS= read -r username; do
    # Skip empty lines or invalid usernames
    if [ -z "$username" ]; then
        continue
    fi

    # Get the home directory of the user
    home_dir=$(eval echo ~$username)

    echo "$username"
    echo "##########"

    # Check if we can access the home directory
    if [ ! -d "$home_dir" ]; then
        echo "Permission denied for user $username (home directory not found or inaccessible)."
        continue
    fi

    # Check if the file exists in the user's home directory
    file_path="$home_dir/$file_to_find"

    if [ -f "$file_path" ]; then
        # If file exists, get its size
        file_size=$(stat --format=%s "$file_path")
        echo "$file_to_find: File found, size $file_size bytes"
    else
        # If file does not exist
        echo "$file_to_find: File not found"
    fi
done < "$usernames_file"
