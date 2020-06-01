from sys import exit
from shutil import which
from os.path import isfile

# dependency : (associate make variable, comment)
dependencies = {}

make_vars = {}
if isfile("local_config"):
    with open("local_config", 'r') as makefile:
        for line in makefile:
            line = line.strip()
            if '=' in line:
                if line.startswith("export"):
                    line = line[len("export"):]
                key, val = line.split('=')
                make_vars[key.strip()] = val.strip()

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
        if "#" in ini_line:
            ini_line_only = ini_line.split('#')[0]
            comment = '#'.join(ini_line.split('#')[1:])
            comment = comment.strip()
            ini_line = ini_line_only
        else:
            comment = ''
        ini_line = ini_line.strip()
        if len(ini_line) == 0:
            # Ignore blank lines
            continue
        dependency, make_var = ini_line.split('=')
        dependency = dependency.strip()
        make_var = make_var.strip()
        dependencies[dependency] = (make_var, comment)
    else:
        print("ERROR: README.md Dependencies section never ended?...")
        exit(-1)

anyMissing = False
for dep in dependencies:
    if which(dep) is not None:
        print("Dependency "+dep+" satisfied in PATH")
        continue
    if dependencies[dep][0] in make_vars:
        print("Dependency "+dep+" satisfied manually")
        continue
    else:
        anyMissing = True
        print("Missing dependency "+dep, end='. ')
        if dependencies[dep][0] == '':
            print("Record installation in local_config.")
        else:
            print("Install it from your package manager.")
        print(" Reason: "+dependencies[dep][1])
if anyMissing:
    exit(-1)
exit(0)
