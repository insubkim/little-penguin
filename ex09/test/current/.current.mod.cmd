savedcmd_current.mod := printf '%s\n'   current.o | awk '!x[$$0]++ { print("./"$$0) }' > current.mod
