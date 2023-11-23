# hashes a file, ignoring whitespaces and comments
# use for verifying that code is copied correctly
cpp -dD -P -fpreprocessed | tr -d '[:space:]' | md5sum | cut -c-6
