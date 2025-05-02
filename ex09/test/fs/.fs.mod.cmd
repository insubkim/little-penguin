savedcmd_fs.mod := printf '%s\n'   fs.o | awk '!x[$$0]++ { print("./"$$0) }' > fs.mod
