from sys import exit
from shutil import which

dependencies = {}

with open("README.md", "r") as readme:
    for line in readme:
        if line == "## Dependencies\n":
            break
    else:
        print("ERROR: Didn't find README.md Dependencies section")
        exit(-1)

    readme.readline()
    for ini_line in readme:
        if ini_line == "```\n":
            break
        ini_line = ini_line.strip()
        if len(ini_line) == 0:
            # Ignore blank lines
            continue
        key, value = ini_line.split('=')
        dependencies[key] = value
    else:
        print("ERROR: README.md Dependencies section never ended?...")
        exit(-1)

anyMissing = False
for dep in dependencies:
    if which(dep) is None:
        anyMissing = True
        print("Missing dependency " + dep + ". Install or set local_config")
if anyMissing:
    exit(-1)
exit(0)
